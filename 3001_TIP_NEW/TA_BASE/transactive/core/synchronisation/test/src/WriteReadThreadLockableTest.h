/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/WriteReadThreadLockableTest.h $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Header file for the WriteReadThreadLockableTest class.
  *
  */

#ifndef WRITEREADTHREADLOCKABETEST_H
#define WRITEREADTHREADLOCKABETEST_H

#include "Test_TA_Synchronisation.h"
#include "core/synchronisation/src/WriteReadThreadLockable.h"

#include <time.h>

class WriteReadThreadLockableTest : public TestCase
{
public:
    const static int SLEEP_DELAY_MS;
    const static int TOLERANCE;

    /**
     * Constructor
     */
	WriteReadThreadLockableTest ( const std::string & name );

    /**
     * Destructor
     */
	virtual ~WriteReadThreadLockableTest();

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
    
    // Successful
    void testAcquireWrite1(void);
    // Successful
    void testAcquireRead1(void);
    // Successful, double locking
    void testAcquireRead2(void);
    // Successful
    void testReleaseWrite1(void);
    // Failure, double release
    void testReleaseWrite2(void);
    // Successful
    void testReleaseRead1(void);
    // Failure, double release
    void testReleaseRead2(void);
    // Successful
    void testWritePriority(void);

	void testThreadSafteyOfRelease(void);

private:

    // Objects needed for testing
    
};

/**
 * A dummy thread class.
 */
class WriteReadThreadLockableTestThread
: public TA_Base_Core::Thread
, public TA_Base_Core::WriteReadThreadLockable
{
public:
    /**
     * Constructor
     */
    WriteReadThreadLockableTestThread(void) {}
    /**
     * Destructor
     */
    virtual ~WriteReadThreadLockableTestThread() {}

protected:
};


#endif // WRITEREADTHREADLOCKABETEST_H