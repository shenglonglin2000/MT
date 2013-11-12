/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/ConditionTest.cpp $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Test method implementation for cppunit unit testing of the Condition
  * implementation.
  *
  */

#include "ConditionTest.h"

const int ConditionTest::SLEEP_PERIOD_MS = 1000;

/**
 * Constructor
 */
ConditionTest::ConditionTest ( const std::string & name )
    : TestCase ( name )
    , condition( NULL )
{
}

/**
 * Destructor
 */
ConditionTest::~ConditionTest()
{
    if( NULL != this->condition )
    {
        delete condition;
        this->condition = NULL;
    }
}

/**
 * suite
 * 
 * This adds all the test methods to the suite of tests and returns it.
 *
 * @return TestSuite* A collection of all tests that can be run.
 */
TestSuite *ConditionTest::suite()
{
    TestSuite * testSuite = new TestSuite( "ConditionTest" );

    testSuite->addTest( new TestCaller< ConditionTest >( "testWait", &ConditionTest::testWait, this ) );
    testSuite->addTest( new TestCaller< ConditionTest >( "testTimedWait", &ConditionTest::testTimedWait, this ) );
    testSuite->addTest( new TestCaller< ConditionTest >( "testSignal", &ConditionTest::testSignal, this ) );
    testSuite->addTest( new TestCaller< ConditionTest >( "testBroadcast", &ConditionTest::testBroadcast, this ) );
     
    return testSuite;
}


/**
 * setUp
 * 
 * Initialises variables before each method is run.
 */
void ConditionTest::setUp( const std::string & INFile , const std::string & OUTFile )
{
    if( NULL == this->condition )
    {
        this->condition = new TA_Base_Core::Condition();
    }
}

/**
 * tearDown
 * 
 * Destroys variables after each method is run.
 *
 */
void ConditionTest::tearDown( const std::string & OUTFile )
{
    if( NULL != this->condition )
    {
        delete this->condition;
        this->condition = NULL;
    }
}

void ConditionTest::testWait(void)
{
    //
    // Test: This tests the wait(void) method in Condition
    // Expected: Normal return
    // Preconditions: Created condition
    //
    
    // The strategy to test this is to create a threads.  This will wait on
    // the condition instance member.  We will then signal the condition
    // member, which will release the thread to continue processing.
    // The thread will then be terminated.

    // Implementation of the ConditionTestThread
    class ConditionTestThreadImpl : public ConditionTestThread
    {
    public:
        ConditionTestThreadImpl( TA_Base_Core::Condition& conditionRef )
            : ConditionTestThread( conditionRef )
            , signalled( false )
        {
        }

        virtual ~ConditionTestThreadImpl() {}

        /**
         * The method that actually runs the thread.  Will attempt to acquire
         * condition or be blocked in the attempt.
         */
        virtual void run()
        {
            this->signalled = false;
            // Assume the lock on the condition.
            this->condition.wait();
            this->signalled = true;
        }

        /**
         * inspect
         * Inspects the instance and returns whether the instance has the lock
         * on the condition.
         * @return Bool indicating whether the instance has acquired the lock.
         */
        virtual bool inspect()
        {
            return this->signalled;
        }

        /**
         * terminate
         * Terminates the thread.  Ensures the the condition is released and
         * thus unblocks any blocked threads.
         */
        virtual void terminate()
        {
            this->condition.signal(); // Wake up any blocked thread.
        }

    private:
        /**
         * Instance member to indicate whether the thread instance has
         * been signalled.
         */
        bool signalled;
    };

    // Create the threads.
    ConditionTestThreadImpl blockedThread( *this->condition );

    // Start the thread.
    blockedThread.start();

    // Give thread a chance to run
    TA_Base_Core::Thread::sleep( SLEEP_PERIOD_MS );
    
    // The blockedThread should not have been signalled
    Assert( !blockedThread.inspect() );

    // Terminate the thread.
    blockedThread.terminateAndWait();
}

void ConditionTest::testTimedWait(void)
{
    //
    // Test: This tests the timedWait(void) method in Condition
    // Expected: Time expired
    // Preconditions: Created condition
    //

    // The strategy to test this is to have THIS thread acquire the lock on
    // the condition.  Then create and start a thread that will immediately
    // attempt to acquire the condition.  This will then time out after 
    // SLEEP_PERIOD_MS milliseconds.  

    // Implementation of the ConditionTestThread
    class ConditionTestThreadImpl : public ConditionTestThread
    {
    public:
        ConditionTestThreadImpl( TA_Base_Core::Condition& conditionRef )
            : ConditionTestThread( conditionRef )
            , signalled( false ),expired(false)
        {
        }

        virtual ~ConditionTestThreadImpl() {}

        /**
         * The method that actually runs the thread.  Will attempt to acquire
         * condition or be blocked in the attempt.
         */
        virtual void run()
        {
            this->signalled = false;
            this->expired = false;
            // Assume the lock on the condition.
            if( 0 == this->condition.timedWait( ConditionTest::SLEEP_PERIOD_MS ) )
            {
                this->signalled = false;
                this->expired = true;
            }
            else
            {
                this->signalled = true;
                this->expired = false;
            }
        }

        /**
         * inspect
         * Inspects the instance and returns whether the instance has the lock
         * on the condition.
         * @return Bool indicating whether the instance has acquired the lock.
         */
        virtual bool inspect()
        {
            return this->signalled;
        }

        virtual bool hasExpired()
        {
            return this->expired;
        }

        /**
         * terminate
         * Terminates the thread.  Ensures the the condition is released and
         * thus unblocks any blocked threads.
         */
        virtual void terminate()
        {
            if( signalled )
            {
                this->condition.signal(); // Wake up any blocked thread.
            }
        }

    private:
        /**
         * Instance member to indicate whether the thread instance has
         * been signalled.
         */
        bool signalled;
        bool expired;
    };

    // Create the threads.
    ConditionTestThreadImpl thread( *this->condition );
    
    // Start the thread.
    thread.start();

    // Give thread a chance to run
    TA_Base_Core::Thread::sleep( SLEEP_PERIOD_MS / 2 );
    
    // The thread should have NOT the lock.
    Assert( !thread.inspect() );

    // haven't timeout yet
    Assert( !thread.hasExpired() );

    TA_Base_Core::Thread::sleep( SLEEP_PERIOD_MS / 2 );

    // The thread should have NOT the lock.
    Assert( !thread.inspect() );

    // haven't timeout yet
    Assert( thread.hasExpired() );

    // Terminate the threads.
    thread.terminateAndWait();
}

void ConditionTest::testSignal(void)
{
    //
    // Test: This tests the signal(void) method in Condition
    // Expected: Normal return
    // Preconditions: Created condition
    //
    
    // The strategy to test this is to create 2 threads.  This will wait on
    // the condition instance member.  We will then signal the condition
    // member, which will release a thread to continue processing.
    // The threads will then be terminated.

    // Implementation of the ConditionTestThread
    class ConditionTestThreadImpl : public ConditionTestThread
    {
    public:
        ConditionTestThreadImpl( TA_Base_Core::Condition& conditionRef )
            : ConditionTestThread( conditionRef )
            , signalled( false )
        {
        }

        virtual ~ConditionTestThreadImpl() {}

        /**
         * The method that actually runs the thread.  Will attempt to acquire
         * condition or be blocked in the attempt.
         */
        virtual void run()
        {
            this->signalled = false;
            // Assume the lock on the condition.
            this->condition.wait();
            this->signalled = true;
        }

        /**
         * inspect
         * Inspects the instance and returns whether the instance has the lock
         * on the condition.
         * @return Bool indicating whether the instance has acquired the lock.
         */
        virtual bool inspect()
        {
            return this->signalled;
        }

        /**
         * terminate
         * Terminates the thread.  Ensures the the condition is released and
         * thus unblocks any blocked threads.
         */
        virtual void terminate()
        {
            if( signalled )
            {
                this->condition.signal(); // Wake up any blocked thread.
            }
        }

    private:
        /**
         * Instance member to indicate whether the thread instance has
         * been signalled.
         */
        bool signalled;
    };

    // Create the threads.
    ConditionTestThreadImpl blockedThread1( *this->condition );
    ConditionTestThreadImpl blockedThread2( *this->condition );

    // Start both the threads.
    blockedThread1.start();
    blockedThread2.start();

    // Give threads a chance to run
    TA_Base_Core::Thread::sleep( SLEEP_PERIOD_MS );
    
    // The blockedThread instances should not have been signalled
    Assert( !blockedThread1.inspect() );
    Assert( !blockedThread2.inspect() );

    // Signal the condition.
    this->condition->signal();

    // Small sleep to ensure the signal propagated before we Assert.
    TA_Base_Core::Thread::sleep( 1000 ); 

    // One of the blockedThread instances should now have been signalled
    Assert( blockedThread1.inspect() || blockedThread2.inspect() );

    // Terminate the thread.
    blockedThread1.terminateAndWait();
    blockedThread2.terminateAndWait();
}


void ConditionTest::testBroadcast(void)
{
    //
    // Test: This tests the broadcast(void) method in Condition
    // Expected: Normal return
    // Preconditions: Created condition
    //
    
    // The strategy to test this is to create 3 threads.  These will wait on
    // the condition instance member.  We will then braodcast the condition
    // member, which will release the threads to continue processing.
    // The threads will then be terminated.

    // Implementation of the ConditionTestThread
    class ConditionTestThreadImpl : public ConditionTestThread
    {
    public:
        ConditionTestThreadImpl( TA_Base_Core::Condition& conditionRef )
            : ConditionTestThread( conditionRef )
            , signalled( false )
        {
        }

        virtual ~ConditionTestThreadImpl() {}

        /**
         * The method that actually runs the thread.  Will attempt to acquire
         * condition or be blocked in the attempt.
         */
        virtual void run()
        {
            this->signalled = false;
            // Assume the lock on the condition.
            this->condition.wait();
            this->signalled = true;
        }

        /**
         * inspect
         * Inspects the instance and returns whether the instance has the lock
         * on the condition.
         * @return Bool indicating whether the instance has acquired the lock.
         */
        virtual bool inspect()
        {
            return this->signalled;
        }

        /**
         * terminate
         * Terminates the thread.  Ensures the the condition is released and
         * thus unblocks any blocked threads.
         */
        virtual void terminate()
        {
            if( signalled )
            {
                this->condition.signal(); // Wake up any blocked thread.
            }
        }

    private:
        /**
         * Instance member to indicate whether the thread instance has
         * been signalled.
         */
        bool signalled;
    };

    // Create the threads.
    ConditionTestThreadImpl blockedThread1( *this->condition );
    ConditionTestThreadImpl blockedThread2( *this->condition );
    ConditionTestThreadImpl blockedThread3( *this->condition );

    // Start the threads.
    blockedThread1.start();
    blockedThread2.start();
    blockedThread3.start();

    // Give threads a chance to run
    TA_Base_Core::Thread::sleep( SLEEP_PERIOD_MS );
    
    // The blockedThread instances should not have been signalled
    Assert( !blockedThread1.inspect() );
    Assert( !blockedThread2.inspect() );
    Assert( !blockedThread3.inspect() );

    // Broadcast the condition.
    this->condition->broadcast();

    // Sleep to ensure broadcast propagates.
    TA_Base_Core::Thread::sleep( SLEEP_PERIOD_MS );

    // All the blockedThread instances should now have been signalled
    Assert( blockedThread1.inspect() );
    Assert( blockedThread2.inspect() );
    Assert( blockedThread3.inspect() );

    // Terminate the thread.
    blockedThread1.terminateAndWait();
    blockedThread2.terminateAndWait();
    blockedThread3.terminateAndWait();
}

// ConditionTestThread definitions

ConditionTestThread::ConditionTestThread( TA_Base_Core::Condition &conditionRef )
: condition( conditionRef )
{
}

ConditionTestThread::~ConditionTestThread() {}
