#include "cpptest.h"

CPPTEST_CONTEXT("Core.UnitTest/core.timers/Timers/WindowsTimerQueue.cpp");
CPPTEST_TEST_SUITE_INCLUDED_TO("Core.UnitTest/core.timers/Timers/WindowsTimerQueue.cpp");

extern int debugFlag;

class TestSuite_WindowsTimerQueue_cpp_49b680ee : public CppTest_TestSuite
{
    public:
        CPPTEST_TEST_SUITE(TestSuite_WindowsTimerQueue_cpp_49b680ee);
        CPPTEST_TEST(test_activate_1);
        CPPTEST_TEST(test_restartInternalTimer);
		CPPTEST_TEST(test_restartInternalTimer2);
		CPPTEST_TEST(test_restartInternalTimer3);
        CPPTEST_TEST_SUITE_END();
        
        void setUp();
        void tearDown();

        void test_activate_1();
        
        void test_restartInternalTimer();
		void test_restartInternalTimer2();
		void test_restartInternalTimer3();
};

CPPTEST_TEST_SUITE_REGISTRATION(TestSuite_WindowsTimerQueue_cpp_49b680ee);



void TestSuite_WindowsTimerQueue_cpp_49b680ee::setUp()
{
	debugFlag = 0;
}

void TestSuite_WindowsTimerQueue_cpp_49b680ee::tearDown()
{
	debugFlag = 0;
}


/* CPPTEST_TEST_CASE_BEGIN test_activate_1 */
/* CPPTEST_TEST_CASE_CONTEXT void TA_Base_Core::WindowsTimerQueue::activate(void) */
void TestSuite_WindowsTimerQueue_cpp_49b680ee::test_activate_1()
{
    /* Pre-condition initialization */
    /* Initializing argument 0 (this) */ 
    ::TA_Base_Core::WindowsTimerQueue _cpptest_TestObject ;
    /* Tested function call */
    CPPTEST_ASSERT_NO_THROW(_cpptest_TestObject.activate());
	_cpptest_TestObject.deactivate();
  
}
/* CPPTEST_TEST_CASE_END test_activate_1 */

/* CPPTEST_TEST_CASE_BEGIN test_restartInternalTimer */
/* CPPTEST_TEST_CASE_CONTEXT void TA_Base_Core::WindowsTimerQueue::restartInternalTimer(void) */
void TestSuite_WindowsTimerQueue_cpp_49b680ee::test_restartInternalTimer()
{
	debugFlag = 1;
    /* Pre-condition initialization */
    /* Initializing argument 0 (this) */ 
    ::TA_Base_Core::WindowsTimerQueue _cpptest_TestObject ;
    /* Tested function call */
	TA_Base_Core::WindowsTimerQueue::TimerEntry newTimer( 1,
															ACE_OS::gettimeofday(),
															ACE_Time_Value::zero,
															NULL,
															NULL);
	_cpptest_TestObject.m_timerList.insert(newTimer);

    CPPTEST_ASSERT_NO_THROW(_cpptest_TestObject.restartInternalTimer());

}
/* CPPTEST_TEST_CASE_END test_restartInternalTimer */

/* CPPTEST_TEST_CASE_BEGIN test_restartInternalTimer */
/* CPPTEST_TEST_CASE_CONTEXT void TA_Base_Core::WindowsTimerQueue::restartInternalTimer(void) */
void TestSuite_WindowsTimerQueue_cpp_49b680ee::test_restartInternalTimer2()
{
	debugFlag = 0;
	/* Pre-condition initialization */
	/* Initializing argument 0 (this) */ 
	::TA_Base_Core::WindowsTimerQueue _cpptest_TestObject ;
	/* Tested function call */
	/*TA_Base_Core::WindowsTimerQueue::TimerEntry newTimer( 1,
		ACE_OS::gettimeofday(),
		ACE_Time_Value::zero,
		NULL,
		NULL);
	_cpptest_TestObject.m_timerList.insert(newTimer);*/

	CPPTEST_ASSERT_NO_THROW(_cpptest_TestObject.restartInternalTimer());

}
/* CPPTEST_TEST_CASE_END test_restartInternalTimer */


/* CPPTEST_TEST_CASE_BEGIN test_restartInternalTimer */
/* CPPTEST_TEST_CASE_CONTEXT void TA_Base_Core::WindowsTimerQueue::restartInternalTimer(void) */
void TestSuite_WindowsTimerQueue_cpp_49b680ee::test_restartInternalTimer3()
{
	debugFlag = 0;
	/* Pre-condition initialization */
	/* Initializing argument 0 (this) */ 
	::TA_Base_Core::WindowsTimerQueue _cpptest_TestObject ;
	/* Tested function call */
	TA_Base_Core::WindowsTimerQueue::TimerEntry newTimer( 1,
		ACE_OS::gettimeofday(),
		ACE_Time_Value::zero,
		NULL,
		NULL);
	_cpptest_TestObject.m_timerList.insert(newTimer);

	CPPTEST_ASSERT_NO_THROW(_cpptest_TestObject.restartInternalTimer());

}
/* CPPTEST_TEST_CASE_END test_restartInternalTimer */