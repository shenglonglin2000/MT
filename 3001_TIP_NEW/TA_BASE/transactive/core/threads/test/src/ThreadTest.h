/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/threads/test/src/ThreadTest.h $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Tests the TA_Base_Core::Thread implementation.
  */

#ifndef THREADTEST_H
#define THREADTEST_H

#include "Test_TA_Thread.h"

#include "core/threads/src/Thread.h"
#include <time.h>

/**
 * Class that tests the public interface of the Thread class.
 */
class ThreadTest : public TestCase
{
public:
    /**
     * Sleep period.
     */
    const static int SLEEP_DELAY_MS;


    /**
     * Constructor
     */
	ThreadTest ( const std::string & name );

    /**
     * Destructor
     */
	virtual ~ThreadTest();

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
     * Thread with one resource.
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
    void testId(void);
    void testSleep(void);
    void testStart(void);
    void testTerminateAndWait(void);
    void testGetCurrentState(void);
    void testThreadPool(void);

private:
};


#endif // THREADTEST_H
