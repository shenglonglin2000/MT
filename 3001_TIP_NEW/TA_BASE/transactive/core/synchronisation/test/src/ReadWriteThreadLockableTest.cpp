/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/ReadWriteThreadLockableTest.cpp $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Implementation of the ReadWriteThreadLockableTest test cases.
  *
  */

#include "ReadWriteThreadLockableTest.h"
const int ReadWriteThreadLockableTest::SLEEP_DELAY_MS = 1000;
const int ReadWriteThreadLockableTest::TOLERANCE = 5;
/**
 * Constructor
 */
ReadWriteThreadLockableTest::ReadWriteThreadLockableTest ( const std::string & name )
: TestCase( name )
{
}

/**
 * Destructor
 */
ReadWriteThreadLockableTest:: ~ReadWriteThreadLockableTest()
{
}

/**
 * suite
 * 
 * This adds all the test methods to the suite of tests and returns it.
 *
 * @return TestSuite* A collection of all tests that can be run.
 */
TestSuite *ReadWriteThreadLockableTest::suite()
{
    TestSuite * testSuite = new TestSuite( "ReadWriteThreadLockableTest" );

    testSuite->addTest( new TestCaller< ReadWriteThreadLockableTest >( "testAcquireWrite1", &ReadWriteThreadLockableTest::testAcquireWrite1, this ) );
    testSuite->addTest( new TestCaller< ReadWriteThreadLockableTest >( "testAcquireRead1",  &ReadWriteThreadLockableTest::testAcquireRead1, this ) );
    testSuite->addTest( new TestCaller< ReadWriteThreadLockableTest >( "testAcquireRead2",  &ReadWriteThreadLockableTest::testAcquireRead2, this ) );
    testSuite->addTest( new TestCaller< ReadWriteThreadLockableTest >( "testReleaseWrite1", &ReadWriteThreadLockableTest::testReleaseWrite1, this ) );
    testSuite->addTest( new TestCaller< ReadWriteThreadLockableTest >( "testReleaseWrite2", &ReadWriteThreadLockableTest::testReleaseWrite2, this ) );
    testSuite->addTest( new TestCaller< ReadWriteThreadLockableTest >( "testReleaseRead1",  &ReadWriteThreadLockableTest::testReleaseRead1, this ) );
    testSuite->addTest( new TestCaller< ReadWriteThreadLockableTest >( "testReleaseRead2",  &ReadWriteThreadLockableTest::testReleaseRead2, this ) );
    testSuite->addTest( new TestCaller< ReadWriteThreadLockableTest >( "testReadPriority",  &ReadWriteThreadLockableTest::testReadPriority, this ) );
    
    return testSuite;
}


/**
 * setUp
 * 
 * Initialises variables before each method is run.
 */
void ReadWriteThreadLockableTest::setUp( const std::string & INFile , const std::string & OUTFile )
{
}

/**
 * tearDown
 * 
 * Destroys variables after each method is run.
 *
 */
void ReadWriteThreadLockableTest::tearDown( const std::string & OUTFile )
{
}


void ReadWriteThreadLockableTest::testAcquireWrite1(void)
{
    //
    // Test: This tests the acquire(void) method in ReadWriteThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, lock and then
    // unlock a ReadWriteThreadLockable instance.  Success is if NO
    // exception is thrown.
    
    TA_Base_Core::ReadWriteThreadLockable lock;

    try
    {
        lock.acquire();
        Assert( true );
    }
    catch( TA_Base_Core::AssertException e )
    {
        Assert( false );
    }
}


void ReadWriteThreadLockableTest::testAcquireRead1(void)
{
    //
    // Test: This tests the acquireRead(void) method in ReadWriteThreadLockable
    // Expected: TA_Base_Core::AssertException
    // Preconditions: NONE
    //

    // The strategy to test this is to instantiate a ReadWriteThreadLockable
    // object and attempt to acquire the read lock on it.
    // Success is where there is no exception
    
    TA_Base_Core::ReadWriteThreadLockable lock;

    try
    {
        lock.acquireRead();
        Assert( true );
    }
    catch( TA_Base_Core::AssertException e )
    {
        Assert( false );
    }
}
void ReadWriteThreadLockableTest::testAcquireRead2(void)
{
    //
    // Test: This tests the acquireRead(void) method in ReadWriteThreadLockable
    // Expected: TA_Base_Core::AssertException
    // Preconditions: NONE
    //

    // The strategy to test this is to instantiate a ReadWriteThreadLockable
    // object and attempt to acquire the lock on it twice in succession.
    // Success is where there is no exception
    
    TA_Base_Core::ReadWriteThreadLockable lock;

    try
    {
        lock.acquireRead();
        lock.acquireRead();
        Assert( true );
    }
    catch( TA_Base_Core::AssertException e )
    {
        Assert( false );
    }
}

void ReadWriteThreadLockableTest::testReleaseWrite1(void)
{
    //
    // Test: This tests the release(void) method in ReadWriteThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, lock and then
    // unlock a ReadWriteThreadLockable instance.  Success is if NO
    // exception is thrown.
    
    TA_Base_Core::ReadWriteThreadLockable lock;

    try
    {
        lock.acquire();
        lock.release();
        Assert( true );
    }
    catch( TA_Base_Core::AssertException e )
    {
        Assert( false );
    }
}


void ReadWriteThreadLockableTest::testReleaseWrite2(void)
{
    //
    // Test: This tests the release(void) method in ReadWriteThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, lock and then
    // unlock twice a ReadWriteThreadLockable instance.  Success is if a
    // exception is thrown.
    
    TA_Base_Core::ReadWriteThreadLockable lock;

    try
    {
        lock.acquire();
        lock.release();
        lock.release();
        Assert( false );
    }
    catch( ... )
    {
        Assert( true );
    }
}

void ReadWriteThreadLockableTest::testReleaseRead1(void)
{
    //
    // Test: This tests the release(void) method in ReadWriteThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, read lock and then
    // unlock a ReadWriteThreadLockable instance.  Success is if NO
    // exception is thrown.
    
    TA_Base_Core::ReadWriteThreadLockable lock;

    try
    {
        lock.acquireRead();
        lock.releaseRead();
        Assert( true );
    }
    catch( TA_Base_Core::AssertException e )
    {
        Assert( false );
    }
}


void ReadWriteThreadLockableTest::testReleaseRead2(void)
{
    //
    // Test: This tests the release(void) method in ReadWriteThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, read lock and then
    // unlock twice a ReadWriteThreadLockable instance.  Success is if a
    // exception is thrown.
    
    TA_Base_Core::ReadWriteThreadLockable lock;

    try
    {
        lock.acquireRead();
        lock.releaseRead();
        lock.releaseRead();
        Assert( false );
    }
    catch( ... )
    {
        Assert( true );
    }
}

void ReadWriteThreadLockableTest::testReadPriority(void)
{
    //
    // Test: This tests that a read lock request will succecd
    // while a write lock is pending.
    //

    // The strategy to test this method is to create a thread that
    // will grab a read lock. Create a second thread will try
    // to get a write lock. Create a third thread will try and get 
    // a read lock. The third thread should succeed while the second
    // thread blocks
    enum Mode { READ_ACQUIRE=1, WRITE_ACQUIRE };
    class ReadWriteTestThreadImpl : public ReadWriteThreadLockableTestThread
    {
    public:

        ReadWriteTestThreadImpl(int& signal, Mode mode, TA_Base_Core::IThreadLockable& lock)
            : ReadWriteThreadLockableTestThread(),
              m_mode( mode ),
              m_lock( lock ),
              m_signal( signal )
        {
        }

        virtual ~ReadWriteTestThreadImpl() {}

        /**
         * The method that actually runs the thread.  Will attempt to acquire
         * semaphore or be blocked in the attempt.
         */
        virtual void run()
        {
            switch (m_mode)
            {
            case 1: //READ_ACQUIRE:
                this->readCriticalSection();
                break;
            case 2: //WRITE_ACQUIRE:
                this->enterCriticalSection();
                break;
            }
        }

        /**
         * terminate
         * Terminates the thread.  Ensures the the semaphore is released and
         * thus unblocks any blocked threads.
         */
        virtual void terminate()
        {
        }

    private:
        /**
         * readCriticalSection
         * The critical section method.  This will acquire the read lock on itself
         * and then sleep for SLEEP_DELAY_MS.
         */
        void readCriticalSection()
        {
            m_lock.acquireRead();
            m_signal += 1;
            std::cout << "Read lock acquired" << std::endl;
            TA_Base_Core::Thread::sleep( ReadWriteThreadLockableTest::SLEEP_DELAY_MS );
            TA_Base_Core::Thread::sleep( ReadWriteThreadLockableTest::SLEEP_DELAY_MS );
            TA_Base_Core::Thread::sleep( ReadWriteThreadLockableTest::SLEEP_DELAY_MS );
            m_lock.releaseRead();
        }
        void enterCriticalSection()
        /**
         * enterCriticalSection
         * The critical section method.  This will acquire the lock on itself
         * and then sleep for SLEEP_DELAY_MS.
         */
        {
            m_lock.acquire();
            m_signal += 10;
            std::cout << "Write lock acquired" << std::endl;
            TA_Base_Core::Thread::sleep( ReadWriteThreadLockableTest::SLEEP_DELAY_MS );
            m_lock.release();
        }
        Mode m_mode;
        int& m_signal;
        TA_Base_Core::IThreadLockable& m_lock;
    };

    int signal = 0;
    TA_Base_Core::ReadWriteThreadLockable lock;

    // Create the threads.
    ReadWriteTestThreadImpl ReadLockedThread( signal, READ_ACQUIRE, lock );
    ReadWriteTestThreadImpl ReadBlockedThread( signal, READ_ACQUIRE, lock );
    ReadWriteTestThreadImpl WriteBlockedThread( signal, WRITE_ACQUIRE, lock );
    std::cout << "Threads created" << std::endl;

    // Start the threads.
    ReadLockedThread.start();
    std::cout << "Read thread started" << std::endl;
    TA_Base_Core::Thread::sleep( ReadWriteThreadLockableTest::SLEEP_DELAY_MS );
    Assert( 1 == signal ); // read lock acquired

    WriteBlockedThread.start();
    std::cout << "Write thread started" << std::endl;
    TA_Base_Core::Thread::sleep( ReadWriteThreadLockableTest::SLEEP_DELAY_MS );
    Assert( 1 == signal ); // no lock acquired
    
    ReadBlockedThread.start();
    std::cout << "Read thread started" << std::endl;
    TA_Base_Core::Thread::sleep( ReadWriteThreadLockableTest::SLEEP_DELAY_MS );
    Assert( 2 == signal ); // read lock acquired

    TA_Base_Core::Thread::sleep( ReadWriteThreadLockableTest::SLEEP_DELAY_MS );
    TA_Base_Core::Thread::sleep( ReadWriteThreadLockableTest::SLEEP_DELAY_MS );
    TA_Base_Core::Thread::sleep( ReadWriteThreadLockableTest::SLEEP_DELAY_MS );
    Assert( 12 == signal ); // write lock finally acquired


    // Terminate the threads.
    ReadLockedThread.terminateAndWait();
    WriteBlockedThread.terminateAndWait();
    ReadBlockedThread.terminateAndWait();
}