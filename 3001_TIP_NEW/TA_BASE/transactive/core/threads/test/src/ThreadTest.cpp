/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/threads/test/src/ThreadTest.cpp $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Test method implementation for cppunit unit testing of the Thread
  * implementation.
  *
  */

#include "ace/ACE.h"

#include "ThreadTest.h"
#include "WorkItem.h"
#include "core/threads/src/ThreadPoolSingletonManager.h"

const int ThreadTest::SLEEP_DELAY_MS = 5000;

/**
 * Constructor
 */
ThreadTest::ThreadTest ( const std::string & name )
    : TestCase ( name )
{
}

/**
 * Destructor
 */
ThreadTest::~ThreadTest()
{
}

/**
 * suite
 * 
 * This adds all the test methods to the suite of tests and returns it.
 *
 * @return TestSuite* A collection of all tests that can be run.
 */
TestSuite *ThreadTest::suite()
{
    TestSuite * testSuite = new TestSuite( "ThreadTest" );

    testSuite->addTest( new TestCaller< ThreadTest >( "testId", &ThreadTest::testId, this ) );
    testSuite->addTest( new TestCaller< ThreadTest >( "testSleep", &ThreadTest::testSleep, this ) );
    testSuite->addTest( new TestCaller< ThreadTest >( "testStart", &ThreadTest::testStart, this ) );
    testSuite->addTest( new TestCaller< ThreadTest >( "testTerminateAndWait", &ThreadTest::testTerminateAndWait, this ) );
    testSuite->addTest( new TestCaller< ThreadTest >( "testGetCurrentState", &ThreadTest::testGetCurrentState, this ) );
    testSuite->addTest( new TestCaller< ThreadTest >( "testThreadPool", &ThreadTest::testThreadPool, this ) );
   
    return testSuite;
}


/**
 * setUp
 * 
 * Initialises variables before each method is run.
 */
void ThreadTest::setUp( const std::string & INFile , const std::string & OUTFile )
{
}

/**
 * tearDown
 * 
 * Destroys variables after each method is run.
 *
 */
void ThreadTest::tearDown( const std::string & OUTFile )
{
}


///////////
// Tests
///////////

void ThreadTest::testId()
{
    //
    // Test: This tests the getId(void) and getCurrentThreadId(void) method
    //       in Thread.
    // Expected: Normal return
    // Preconditions: this method must be the first test case to run, cos getId() will return unique 
    // omni_threadids in current process increment by 1 and starting from 0.
    
    // The strategy to test this is to create a thread and to see that the
    // thread id's match. Note that getId() is different with getCurrentThreadId().

    class ThreadTestThread : public TA_Base_Core::Thread
    {
    public:
        /**
         * Constructor.
         */
        ThreadTestThread()
            : Thread()
            , keepRunning( false )
        {
        }
        /**
         * Deconstructor.
         */
        virtual ~ThreadTestThread() {}

        virtual void run()
        {
            this->keepRunning = true;
            do 
            {
                TA_Base_Core::Thread::sleep(100);
            } while( keepRunning );
        }

        virtual void terminate()
        {
            this->keepRunning = false;
        }
    private:
        /**
         * Flag indicating if the thread should continure running.
         */
        volatile bool keepRunning;
    };

    const int MAX_THREAD = 10;
    ThreadTestThread multiThread[MAX_THREAD];
    for (unsigned int i=0;i<MAX_THREAD;i++)
    {
        multiThread[i].start();
        // give a little sleep to start the thread
        Thread::sleep(10);
        Assert( multiThread[i].getId() == (i+1) );
    }

    for (unsigned int j=0;j<MAX_THREAD;j++)
    {
        multiThread[j].terminateAndWait();
        unsigned int currId = multiThread[j].getId();
    }
}

void ThreadTest::testSleep()
{
    //
    // Test: This tests the sleep(void) method in Thread
    // Expected: Normal return
    // Preconditions: NONE
    //
    
    // The strategy to test this is to create a thread.  This will sleep for
    // SLLEP_DELAY_MS, setting a flag indicating activeness to false.  This
    // thread will be inspectable so that the value of this flag can be
    // determined from THIS thread.
    //
    // NOTE: The time granularity of this test really sucks.  This is due to
    //       the time granularity of the time() method in the standard
    //       library, which is in seconds, not milliseconds.

    class ThreadTestThread : public TA_Base_Core::Thread
    {
    public:
        /**
         * Constructor.
         */
        ThreadTestThread()
            : Thread()
            , active( false )
        {
        }
        /**
         * Deconstructor.
         */
        virtual ~ThreadTestThread() {}

        virtual void run()
        {
            this->active = false;
            TA_Base_Core::Thread::sleep( ThreadTest::SLEEP_DELAY_MS );
            this->active = true;
        }

        virtual void terminate()
        {
            this->active = false;
        }

        bool inspect()
        {
            return this->active;
        }
    private:
        bool active;
    };

    // Create the thread
    ThreadTestThread thread;

    // Should not be active
    Assert( !thread.inspect() );

    // Start the thread
    thread.start();
    ACE_Time_Value timeStarted = ACE_OS::gettimeofday();

    // Do something, but DONT USE SLEEP since we are testing this.
    do
    {
        // TA_Base_Core::Thread::sleep(100);
        // Should not be active
        Assert( !thread.inspect() );
    }
    while( ACE_OS::gettimeofday() <= ( timeStarted + ACE_Time_Value (0, SLEEP_DELAY_MS * 1000) ));

    // give some sleep for the thread to wake up.
    Thread::sleep(1000);

    // Should now be active
    Assert( thread.inspect() );

    thread.terminateAndWait();
}


void ThreadTest::testStart()
{
    //
    // Test: This tests the testStart(void) method in Thread
    // Expected: Normal return
    // Preconditions: NONE
    //
    
    // The strategy to test this is to create a thread, start it and then
    // terminate it.  Success will be if the run method in the thread
    // instance is invoked.

    class ThreadTestThread : public TA_Base_Core::Thread
    {
    public:
        /**
         * Constructor.
         */
        ThreadTestThread()
            : Thread()
            , running( false )
        {
        }
        /**
         * Deconstructor.
         */
        virtual ~ThreadTestThread() {}

        virtual void run()
        {
            this->running = true;
        }

        virtual void terminate()
        {
            this->running = false;
        }

        bool inspect()
        {
            return this->running;
        }
    private:
        /**
         * Flag indicating if the thread is running.
         */
        volatile bool running;
    };

    // Create the thread
    ThreadTestThread thread;

    // Should not be running
    Assert( !thread.inspect() );

    // Start the thread
    thread.start();

    // give a little sleep to start the thread
    Thread::sleep(10);

    // Should be running
    Assert( thread.inspect() );

    // Terminate the thread
    thread.terminateAndWait();
}


void ThreadTest::testTerminateAndWait()
{
    //
    // Test: This tests the testTerminateAndWait(void) method in Thread
    // Expected: Normal return
    // Preconditions: NONE
    //
    
    // The strategy to test this is to create a thread, start it and then
    // terminate it.  Success will be if the terminate method in the thread
    // instance is invoked.

    class ThreadTestThread : public TA_Base_Core::Thread
    {
    public:
        /**
         * Constructor.
         */
        ThreadTestThread()
            : Thread()
            , running( false )
        {
        }
        /**
         * Deconstructor.
         */
        virtual ~ThreadTestThread() {}

        virtual void run()
        {
            this->running = true;
        }

        virtual void terminate()
        {
            this->running = false;
        }

        bool inspect()
        {
            return this->running;
        }
    private:
        /**
         * Flag indicating if the thread is running.
         */
        volatile bool running;
    };

    // Create the thread
    ThreadTestThread thread;

    // Should not be running
    Assert( !thread.inspect() );

    // Start the thread
    thread.start();

    // give a little sleep to start the thread
    Thread::sleep(10);

    // Should be running
    Assert( thread.inspect() );

    // Terminate the thread
    thread.terminateAndWait();

    // Should be not be running
    Assert( !thread.inspect() );
}


void ThreadTest::testGetCurrentState()
{
    //
    // Test: This tests the testGetCurrentState(void) method in Thread
    // Expected: Normal return
    // Preconditions: NONE
    //
    
    // The strategy to test this is to create a thread and to track the state
    // changes and ensure that they are inline with expectations.

    class ThreadTestThread : public TA_Base_Core::Thread
    {
    public:
        /**
         * Constructor.
         */
        ThreadTestThread()
            : Thread()
            , keepRunning( false )
        {
        }
        /**
         * Deconstructor.
         */
        virtual ~ThreadTestThread() {}

        virtual void run()
        {
            this->keepRunning = true;
            do 
            {
                TA_Base_Core::Thread::sleep(100);
            } while( keepRunning );
        }

        virtual void terminate()
        {
            this->keepRunning = false;
        }
    private:
        /**
         * Flag indicating if the thread should continure running.
         */
        volatile bool keepRunning;
    };

    // Create the thread
    ThreadTestThread thread;

    // Should not be active
    Assert( thread.getCurrentState() == TA_Base_Core::Thread::THREAD_STATE_UNKNOWN );

    // Start the thread
    thread.start();
    
    // give a little sleep to start the thread
    Thread::sleep(10);

    // Should be active
    Assert( thread.getCurrentState() == TA_Base_Core::Thread::THREAD_STATE_NEW ||
            thread.getCurrentState() == TA_Base_Core::Thread::THREAD_STATE_RUNNING );

    // Terminate the thread
    thread.terminateAndWait();

    // Should be terminated
    // THREADS CANNOT HAVE TERMINATED STATE IN THIS SYSTEM
    Assert( thread.getCurrentState() == TA_Base_Core::Thread::THREAD_STATE_TERMINATED ||
        thread.getCurrentState() == TA_Base_Core::Thread::THREAD_STATE_UNKNOWN);
}


void ThreadTest::testThreadPool()
{
    TA_Base_Core::ThreadPoolSingletonManager* pool = TA_Base_Core::ThreadPoolSingletonManager::getInstance();

	IWorkItemPtr itemToRemove;

	for (int i = 0; i < 500; ++i)
	{
		IWorkItemPtr item( new WorkItem(i%2==0?1000:5000, i) );
		pool->queueWorkItem(item);

		if (i == 495)
		{
			itemToRemove = item;
		}
		item.reset();
	}

	// test the removal function
	// pretty dependent on timing but seems to be ok
	pool->removeWorkItem(itemToRemove);
	itemToRemove.reset();

	Thread::sleep(60000);

    TA_Base_Core::ThreadPoolSingletonManager::removeInstance(pool);
}