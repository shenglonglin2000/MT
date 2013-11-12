/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/SemaphoreTest.h $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Tests the TA_Base_Core::Semaphore implementation.
  */

#ifndef SEMAPHORETEST_H
#define SEMAPHORETEST_H

#include "Test_TA_Synchronisation.h"

#include "core/synchronisation/src/Semaphore.h"

class SemaphoreTestThread;

/**
 * Class that tests the public interface of the Semaphore class.
 */
class SemaphoreTest : public TestCase
{
public:

    /**
     * Constructor
     */
	SemaphoreTest ( const std::string & name );

    /**
     * Destructor
     */
	virtual ~SemaphoreTest();

    /**
     * suite
     * 
     * This adds all the test methods to the suite of tests and returns it.
     *
     * @return TestSuite* A collection of all tests that can be run.
     */
    TestSuite *suite();


    /**
     * setUp
     * 
     * Initialises variables before each method is run.  In reality this means
     * delete the semaphore instance member if it still exists and recreate a
     * Semaphore with one resource.
     */
    virtual void setUp( const std::string & INFile , const std::string & OUTFile );

    /**
     * tearDown
     * 
     * Destroys variables after each method is run.  In reality this means
     * delete the semaphore instance member.
     *
     */
    virtual void tearDown( const std::string & OUTFile );

    /**
     * setUpSuite
     *
     * Initialises variables before test suite is run.
     */
    virtual void setUpSuite( const std::string & inFile ) {}

    /**
     * tearDownSuite
     *
     * Destroys variables after test suite is run.
     */
    virtual void tearDownSuite() {}

protected:

    // The test methods
    void testWait(void);
    void testTryWait(void);
    void testPost(void);

private:

    // Objects needed for testing
    TA_Base_Core::Semaphore *semaphore;
    // The sleep period.
    const static int SLEEP_PERIOD_MS;
};


/**
 * A dummy thread class.
 */
class SemaphoreTestThread : public TA_Base_Core::Thread
{
public:
    /**
     * Constructor
     *
     * @param semaphore Reference to semaphore that the thread will use.
     */
    SemaphoreTestThread( TA_Base_Core::Semaphore& semaphore );
    /**
     * Destructor
     */
    virtual ~SemaphoreTestThread();
    /**
     * run
     *
     * The method that is invoked when the thread is to begin executing.
     * This is analogous to the run method in the java.lang.Runnable interface
     * in the Java programming language.
     */
    virtual void run() = 0;
    /**
     * terminate
     * 
     * Will cause the run() method to return.  In other words, end the
     * execution of the thread.
     */
    virtual void terminate() = 0;

    // Allow instances of SemaphoreTest to "inspect" the inner state of
    // SemaphoreTestThreads.
    friend SemaphoreTest;

protected:
    /**
     * The semaphore that we will perform the tests on.
     */
    TA_Base_Core::Semaphore& semaphore;
};


#endif // SEMAPHORETEST_H
