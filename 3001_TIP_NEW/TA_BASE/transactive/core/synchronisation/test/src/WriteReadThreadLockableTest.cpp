/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/WriteReadThreadLockableTest.cpp $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Implementation of the WriteReadThreadLockableTest test cases.
  *
  */
#include "core/synchronisation/src/ThreadReadGuard.h"
#include "WriteReadThreadLockableTest.h"
const int WriteReadThreadLockableTest::SLEEP_DELAY_MS = 1000;
const int WriteReadThreadLockableTest::TOLERANCE = 5;
/**
 * Constructor
 */
WriteReadThreadLockableTest::WriteReadThreadLockableTest ( const std::string & name )
: TestCase( name )
{
}

/**
 * Destructor
 */
WriteReadThreadLockableTest:: ~WriteReadThreadLockableTest()
{
    std::cout << "Test complete\n" << std::endl;
}

/**
 * suite
 * 
 * This adds all the test methods to the suite of tests and returns it.
 *
 * @return TestSuite* A collection of all tests that can be run.
 */
TestSuite *WriteReadThreadLockableTest::suite()
{
    TestSuite * testSuite = new TestSuite( "WriteReadThreadLockableTest" );

    testSuite->addTest( new TestCaller< WriteReadThreadLockableTest >( "testAcquireWrite1", &WriteReadThreadLockableTest::testAcquireWrite1, this ) );
    testSuite->addTest( new TestCaller< WriteReadThreadLockableTest >( "testAcquireRead1",  &WriteReadThreadLockableTest::testAcquireRead1, this ) );
    testSuite->addTest( new TestCaller< WriteReadThreadLockableTest >( "testAcquireRead2",  &WriteReadThreadLockableTest::testAcquireRead2, this ) );
    testSuite->addTest( new TestCaller< WriteReadThreadLockableTest >( "testReleaseWrite1", &WriteReadThreadLockableTest::testReleaseWrite1, this ) );
    testSuite->addTest( new TestCaller< WriteReadThreadLockableTest >( "testReleaseWrite2", &WriteReadThreadLockableTest::testReleaseWrite2, this ) );
    testSuite->addTest( new TestCaller< WriteReadThreadLockableTest >( "testReleaseRead1",  &WriteReadThreadLockableTest::testReleaseRead1, this ) );
    testSuite->addTest( new TestCaller< WriteReadThreadLockableTest >( "testReleaseRead2",  &WriteReadThreadLockableTest::testReleaseRead2, this ) );
    testSuite->addTest( new TestCaller< WriteReadThreadLockableTest >( "testWritePriority", &WriteReadThreadLockableTest::testWritePriority, this ) );
    
    testSuite->addTest( new TestCaller< WriteReadThreadLockableTest >( "testThreadSafteyOfRelease", &WriteReadThreadLockableTest::testThreadSafteyOfRelease, this ) );
    return testSuite;
}


/**
 * setUp
 * 
 * Initialises variables before each method is run.
 */
void WriteReadThreadLockableTest::setUp( const std::string & INFile , const std::string & OUTFile )
{
}

/**
 * tearDown
 * 
 * Destroys variables after each method is run.
 *
 */
void WriteReadThreadLockableTest::tearDown( const std::string & OUTFile )
{
}


void WriteReadThreadLockableTest::testAcquireWrite1(void)
{
    //
    // Test: This tests the acquire(void) method in WriteReadThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, lock and then
    // unlock a WriteReadThreadLockable instance.  Success is if NO
    // exception is thrown.
    
    TA_Base_Core::WriteReadThreadLockable lock;

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


void WriteReadThreadLockableTest::testAcquireRead1(void)
{
    //
    // Test: This tests the acquireRead(void) method in WriteReadThreadLockable
    // Expected: TA_Base_Core::AssertException
    // Preconditions: NONE
    //

    // The strategy to test this is to instantiate a WriteReadThreadLockable
    // object and attempt to acquire the read lock on it.
    // Success is where there is no exception
    
    TA_Base_Core::WriteReadThreadLockable lock;

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

void WriteReadThreadLockableTest::testAcquireRead2(void)
{
    //
    // Test: This tests the acquireRead(void) method in WriteReadThreadLockable
    // Expected: TA_Base_Core::AssertException
    // Preconditions: NONE
    //

    // The strategy to test this is to instantiate a WriteReadThreadLockable
    // object and attempt to acquire the read lock on it twice in succession.
    // Success is where there is no exception
    
    TA_Base_Core::WriteReadThreadLockable lock;

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

void WriteReadThreadLockableTest::testReleaseWrite1(void)
{
    //
    // Test: This tests the release(void) method in WriteReadThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, lock and then
    // unlock a WriteReadThreadLockable instance.  Success is if NO
    // exception is thrown.
    
    TA_Base_Core::WriteReadThreadLockable lock;

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


void WriteReadThreadLockableTest::testReleaseWrite2(void)
{
    //
    // Test: This tests the release(void) method in WriteReadThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, lock and then
    // unlock twice a WriteReadThreadLockable instance.  Success is if a
    // exception is thrown.
    
    TA_Base_Core::WriteReadThreadLockable lock;

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

void WriteReadThreadLockableTest::testReleaseRead1(void)
{
    //
    // Test: This tests the release(void) method in WriteReadThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, read lock and then
    // unlock a WriteReadThreadLockable instance.  Success is if NO
    // exception is thrown.
    
    TA_Base_Core::WriteReadThreadLockable lock;

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


void WriteReadThreadLockableTest::testReleaseRead2(void)
{
    //
    // Test: This tests the release(void) method in WriteReadThreadLockable
    // Expected: Normal Return
    // Preconditions: NONE
    //

    // The strategy to test this method is to simply create, read lock and then
    // unlock twice a WriteReadThreadLockable instance.  Success is if a
    // exception is thrown.
    
    TA_Base_Core::WriteReadThreadLockable lock;

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

void WriteReadThreadLockableTest::testWritePriority(void)
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
    class WriteReadTestThreadImpl : public WriteReadThreadLockableTestThread
    {
    public:

        WriteReadTestThreadImpl(int& signal, Mode mode, TA_Base_Core::IThreadLockable& lock)
            : WriteReadThreadLockableTestThread(),
              m_mode( mode ),
              m_lock( lock ),
              m_signal( signal )
        {
        }

        virtual ~WriteReadTestThreadImpl() {}

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
            TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
            TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
            TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
            TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
            TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
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
            TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
            TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
            m_lock.release();
        }
        Mode m_mode;
        int& m_signal;
        TA_Base_Core::IThreadLockable& m_lock;
    };

    int signal = 0;
    TA_Base_Core::WriteReadThreadLockable lock;

    // Create the threads.
    WriteReadTestThreadImpl ReadLockedThread( signal, READ_ACQUIRE, lock );
    WriteReadTestThreadImpl ReadBlockedThread( signal, READ_ACQUIRE, lock );
    WriteReadTestThreadImpl WriteBlockedThread( signal, WRITE_ACQUIRE, lock );
    std::cout << "Threads created" << std::endl;

    // Start the threads.
    ReadLockedThread.start();
    std::cout << "Read thread started" << std::endl;
    TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
    Assert( 1 == signal ); // read lock acquired

    WriteBlockedThread.start();
    std::cout << "Write thread started" << std::endl;
    TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
    Assert( 1 == signal ); // no lock acquired
    
    ReadBlockedThread.start();
    std::cout << "Read thread started" << std::endl;
    TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
    TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
    TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
    TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
    Assert( 11 == signal ); // write lock acquired

    TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
    TA_Base_Core::Thread::sleep( WriteReadThreadLockableTest::SLEEP_DELAY_MS );
    Assert( 12 == signal ); // read lock finally acquired


    // Terminate the threads.
    ReadLockedThread.terminateAndWait();
    WriteBlockedThread.terminateAndWait();
    ReadBlockedThread.terminateAndWait();
}

void WriteReadThreadLockableTest::testThreadSafteyOfRelease(void)
{
    //
    // Test: This tests that number of aquired read locks doesnt get corrupted
    //

    enum Mode { READ_ACQUIRE=1, WRITE_ACQUIRE };
    class WriteReadTestThreadImpl2 : public TA_Base_Core::Thread
    {
    public:

        WriteReadTestThreadImpl2( TA_Base_Core::WriteReadThreadLockable& lock, bool& flag)
            : the_lock( lock ),
              m_running( false ),
			  m_first( false )
        {
			if(!flag)
			{
				flag=true;
				m_first=true;
			}
        }

        virtual ~WriteReadTestThreadImpl2() {}

        /**
         * The method that actually runs the thread.  Will attempt to acquire
         * semaphore or be blocked in the attempt.
         */
        virtual void run()
        {
			m_running=true;
            while(m_running)
			{
				TA_Base_Core::Thread::sleep( 1 );
				
				{
					TA_Base_Core::ThreadReadGuard guard(the_lock);
					TA_Base_Core::Thread::sleep( 1 );
				
				}
			}
        }

        /**
         * terminate
         * Terminates the thread.  Ensures the the semaphore is released and
         * thus unblocks any blocked threads.
         */
        virtual void terminate()
        {
			m_running=false;
        }

    private:
        
		bool m_running;
		TA_Base_Core::WriteReadThreadLockable& the_lock;
		bool m_first;
    };

    TA_Base_Core::WriteReadThreadLockable lock;

    // Create the threads.
	std::vector<TA_Base_Core::Thread *> readingThreads;
	bool flags = false;
	
	std::vector<TA_Base_Core::Thread *>::iterator itr;

	{
		TA_Base_Core::ThreadGuard guard2(lock);
	
		for(int i=0; i<5; i++)
		{
			readingThreads.push_back(new WriteReadTestThreadImpl2( lock, flags ));
		}
    
		std::cout << "Threads created" << std::endl;

		// Start the threads.
		for(itr = readingThreads.begin(); itr != readingThreads.end(); itr++)
		{
			(*itr)->start();
		}
    
 		std::cout << "Threads Started" << std::endl;
	}   


	TA_Base_Core::Thread::sleep(200000);
	for(itr = readingThreads.begin(); itr != readingThreads.end(); itr++)
	{
		(*itr)->terminateAndWait();
	}
    
 	std::cout << "Threads Stopped" << std::endl;
}

