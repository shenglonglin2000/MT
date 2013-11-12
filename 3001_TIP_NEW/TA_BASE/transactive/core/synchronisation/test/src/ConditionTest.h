/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/ConditionTest.h $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Tests the TA_Base_Core::Condition implementation.
  */

#ifndef CONDITIONTEST_H
#define CONDITIONTEST_H

#include "Test_TA_Synchronisation.h"

#include "core/synchronisation/src/Condition.h"


class ConditionTestThread;

/**
 * Class that tests the public interface of the Semaphore class.
 */
class ConditionTest : public TestCase
{
public:
    // The sleep period.
    const static int SLEEP_PERIOD_MS;

    /**
     * Constructor
     */
	ConditionTest ( const std::string & name );

    /**
     * Destructor
     */
	virtual ~ConditionTest();

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
    void testTimedWait(void);
    void testSignal(void);
    void testBroadcast(void);

private:

    // Objects needed for testing
    TA_Base_Core::Condition *condition;
};


/**
 * A dummy thread class.
 */
class ConditionTestThread : public TA_Base_Core::Thread
{
public:
    /**
     * Constructor
     *
     * @param condition Reference to condition that the thread will use.
     */
    ConditionTestThread( TA_Base_Core::Condition& condition );
    /**
     * Destructor
     */
    virtual ~ConditionTestThread();

protected:
    /**
     * The condition that we will perform the tests on.
     */
    TA_Base_Core::Condition& condition;
};


#endif // CONDITIONTEST_H
