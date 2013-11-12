#include "cpptest.h"

CPPTEST_CONTEXT("Core.UnitTest/core.timers/Timers/TimerUtil.cpp");
CPPTEST_TEST_SUITE_INCLUDED_TO("Core.UnitTest/core.timers/Timers/TimerUtil.cpp");

class TestSuite_TimerUtil_cpp_aed353e : public CppTest_TestSuite
{
    public:
        CPPTEST_TEST_SUITE(TestSuite_TimerUtil_cpp_aed353e);
        CPPTEST_TEST(test_cancelTimer_1);
		CPPTEST_TEST(test_cancelTimer_2);
        CPPTEST_TEST(test_cancelTimer_10);
        CPPTEST_TEST(test_cancelTimer_11);
        CPPTEST_TEST_SUITE_END();
        
        void setUp();
        void tearDown();

        void test_cancelTimer_1();
		void test_cancelTimer_2();
        void test_cancelTimer_10();
        void test_cancelTimer_11();
};

CPPTEST_TEST_SUITE_REGISTRATION(TestSuite_TimerUtil_cpp_aed353e);

class TimeoutCallback : public TA_Base_Core::ITimeoutCallback
{
	virtual void timerExpired( long timerId, void* userData ) 
	{
		return;
	}
};


void TestSuite_TimerUtil_cpp_aed353e::setUp()
{
}

void TestSuite_TimerUtil_cpp_aed353e::tearDown()
{
}

/* CPPTEST_TEST_CASE_BEGIN test_cancelTimer_1 */
/* CPPTEST_TEST_CASE_CONTEXT std::vector<void *, std::allocator<void *>> TA_Base_Core::TimerUtil::cancelTimer(TA_Base_Core::ITimeoutCallback *) */
void TestSuite_TimerUtil_cpp_aed353e::test_cancelTimer_1()
{
    /* Pre-condition initialization */
    /* Initializing argument 0 (this) */ 
    ::TA_Base_Core::TimerUtil _cpptest_TestObject ;
    /* Initializing argument 1 (user) */ 
    ::TA_Base_Core::ITimeoutCallback * _user  = 0 ;
    /* Tested function call */
    ::std::vector< void *, ::std::allocator< void *> >  _return  = _cpptest_TestObject.cancelTimer(_user);

}
/* CPPTEST_TEST_CASE_END test_cancelTimer_1 */

/* CPPTEST_TEST_CASE_BEGIN test_cancelTimer_1 */
/* CPPTEST_TEST_CASE_CONTEXT std::vector<void *, std::allocator<void *>> TA_Base_Core::TimerUtil::cancelTimer(TA_Base_Core::ITimeoutCallback *) */
void TestSuite_TimerUtil_cpp_aed353e::test_cancelTimer_2()
{
	/* Pre-condition initialization */
	/* Initializing argument 0 (this) */ 
	::TA_Base_Core::TimerUtil _cpptest_TestObject ;

	TimeoutCallback *callback = new TimeoutCallback();
	::TA_Base_Core::ITimeoutCallback * _user  = callback;

	_cpptest_TestObject.scheduleTimer(_user, 5000, true, new int);


	/* Initializing argument 1 (user) */ 

	_cpptest_TestObject.cancelTimer(_user);

	delete callback;
	
}
/* CPPTEST_TEST_CASE_END test_cancelTimer_1 */


/* CPPTEST_TEST_CASE_BEGIN test_cancelTimer_10 */
/* CPPTEST_TEST_CASE_CONTEXT void * TA_Base_Core::TimerUtil::cancelTimer(TA_Base_Core::ITimeoutCallback *, long) */
void TestSuite_TimerUtil_cpp_aed353e::test_cancelTimer_10()
{
	/* Pre-condition initialization */
	/* Initializing argument 0 (this) */ 
	::TA_Base_Core::TimerUtil _cpptest_TestObject ;

	TimeoutCallback *callback = new TimeoutCallback();

	::TA_Base_Core::ITimeoutCallback * _user  = new TimeoutCallback() ;

	long id = _cpptest_TestObject.scheduleTimer(_user, 2000, true, new int);

	long id2 = _cpptest_TestObject.scheduleTimer(_user, 3000, true, new int);


	/* Initializing argument 1 (user) */ 

	_cpptest_TestObject.cancelTimer(_user, id2);

	delete callback;
}
/* CPPTEST_TEST_CASE_END test_cancelTimer_10 */

/* CPPTEST_TEST_CASE_BEGIN test_cancelTimer_11 */
/* CPPTEST_TEST_CASE_CONTEXT void * TA_Base_Core::TimerUtil::cancelTimer(TA_Base_Core::ITimeoutCallback *, long) */
void TestSuite_TimerUtil_cpp_aed353e::test_cancelTimer_11()
{
	/* Pre-condition initialization */
	/* Initializing argument 0 (this) */ 
	::TA_Base_Core::TimerUtil _cpptest_TestObject ;

	::TA_Base_Core::ITimeoutCallback * _user  = new TimeoutCallback() ;

	long id = _cpptest_TestObject.scheduleTimer(_user, 5000, true, new int);

	
	/* Initializing argument 1 (user) */ 

	_cpptest_TestObject.cancelTimer(_user, -1);
}
/* CPPTEST_TEST_CASE_END test_cancelTimer_11 */

