/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/ThreadLockableHolderVerifierTest.h $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Header file for the ThreadLockableHolderVerifier.
  *
  * This relies on ThreadLockable being fully tested and operational.
  *
  */

#ifndef THREADLOCKABLEHOLDERVERIFIERTEST_H
#define THREADLOCKABLEHOLDERVERIFIERTEST_H

#include "Test_TA_Synchronisation.h"
#include <time.h>
#include "core/synchronisation/src/ReEntrantThreadLockable.h"

// #include "core/synchronisation/src/ThreadLockableHolderVerifier.h"
// We will not include this header, but instead declare our own version of the
// class definition.

/*namespace TA_Base_Core
{
    class ThreadIdWrapper
    {
    public:
  		void setCurrentThreadId();

		bool isCurrentThreadId();

    // private: This is the only difference between this and the real declaration
        unsigned int m_lockHolder;
	};
}*/

class ThreadLockableHolderVerifierTest : public TestCase
{
public:
    const static int SLEEP_DELAY_MS;
    const static int TOLERANCE;

    /**
     * Constructor
     */
	ThreadLockableHolderVerifierTest ( const std::string & name );

    /**
     * Destructor
     */
	virtual ~ThreadLockableHolderVerifierTest();

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
    void testSetCurrentThreadAsLockHolder(void);
    void testIsCurrentThreadTheLockHolder1(void);
    void testIsCurrentThreadTheLockHolder2(void);

private:

    // Objects needed for testing
    
};

/**
 * A dummy thread class.
 */
class ThreadLockableHolderVerifierTestThread
: public TA_Base_Core::Thread
, public TA_Base_Core::ReEntrantThreadLockable
{
public:
    /**
     * Constructor
     */
    ThreadLockableHolderVerifierTestThread(void)
        : TA_Base_Core::Thread()
        , TA_Base_Core::ReEntrantThreadLockable()
    {}
    /**
     * Destructor
     */
    virtual ~ThreadLockableHolderVerifierTestThread() {}

protected:
};

#endif // THREADLOCKABLEHOLDERVERIFIERTEST_H
