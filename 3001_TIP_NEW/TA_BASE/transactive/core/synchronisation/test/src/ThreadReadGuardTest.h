/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/ThreadReadGuardTest.h $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Header file for the ThreadReadGuardTest class.
  *
  * This TestCase is heavily reliant on the ThreadLockableTest class.  This
  * should be executed first, because if that is broken, then will be too.
  *
  */

#ifndef THREADREADGUARDTEST_H
#define THREADREADGUARDTEST_H

#include "Test_TA_Synchronisation.h"
#include <time.h>
#include "core/synchronisation/src/ReadWriteThreadLockable.h"

class ThreadReadGuardTest : public TestCase
{
public:
    const static int SLEEP_DELAY_MS;
    const static int TOLERANCE;

    /**
     * Constructor
     */
	ThreadReadGuardTest ( const std::string & name );

    /**
     * Destructor
     */
	virtual ~ThreadReadGuardTest();

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
    void testAcquire(void);
    void testRelease(void);

private:

    // Objects needed for testing
    
};

/**
 * A dummy thread class.
 */
class ThreadReadGuardTestThread
: public TA_Base_Core::Thread
, public TA_Base_Core::ReadWriteThreadLockable
{
public:
    /**
     * Constructor
     */
    ThreadReadGuardTestThread(void);
    /**
     * Destructor
     */
    virtual ~ThreadReadGuardTestThread();

protected:
};

#endif // THREADREADGUARDTEST_H
