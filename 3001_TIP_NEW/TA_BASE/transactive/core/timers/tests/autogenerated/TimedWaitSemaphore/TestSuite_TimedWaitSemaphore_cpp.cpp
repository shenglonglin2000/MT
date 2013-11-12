#include "cpptest.h"
#include "core/synchronisation/src/Condition.h"
#include "core/threads/src/Thread.h"

CPPTEST_CONTEXT("Core.UnitTest/core.timers/TimedWaitSemaphore/TimedWaitSemaphore.cpp");
CPPTEST_TEST_SUITE_INCLUDED_TO("Core.UnitTest/core.timers/TimedWaitSemaphore/TimedWaitSemaphore.cpp");

extern int timedWaitDebugFlag;

class ThreadUtil0 : public TA_Base_Core::Thread
{
public:
	TA_Base_Core::TimedWaitSemaphore& m_value;
	ThreadUtil0(TA_Base_Core::TimedWaitSemaphore& count):m_value(count)
	{
	}

	virtual void run() 
	{
		Sleep(1000);
		m_value.post();
	}

	virtual void terminate() 
	{
	}
};

class ThreadUtil : public TA_Base_Core::Thread
{
public:
	int volatile& m_value;
	ThreadUtil(int volatile & count):m_value(count)
	{
	}

	virtual void run() 
	{
		Sleep(1000);
		m_value--;
	}

	virtual void terminate() 
	{
	}
};

class ThreadUtil2 : public TA_Base_Core::Thread
{
public:
	bool volatile & m_value;
	ThreadUtil2(bool volatile & b_value):m_value(b_value)
	{
	}

	virtual void run() 
	{
		Sleep(2000);
		m_value = true;
	}

	virtual void terminate() 
	{
	}
};

class TestSuite_TimedWaitSemaphore_cpp_beb1a4fc : public CppTest_TestSuite
{
    public:
        CPPTEST_TEST_SUITE(TestSuite_TimedWaitSemaphore_cpp_beb1a4fc);
        CPPTEST_TEST(test_TimedWaitSemaphore_1);
        CPPTEST_TEST(test_post_1);
        CPPTEST_TEST(test_post_2);
        CPPTEST_TEST(test_timedWait_1);
        CPPTEST_TEST(test_timedWait_2);
        CPPTEST_TEST(test_timedWait_3);
		CPPTEST_TEST(test_timedWait_4);
        CPPTEST_TEST(test_tryWait_1);
        CPPTEST_TEST(test_tryWait_2);
        CPPTEST_TEST(test_wait_1);
        CPPTEST_TEST(test_wait_2);
        CPPTEST_TEST(test_x7eTimedWaitSemaphore_1);
		CPPTEST_TEST(test_x7eTimedWaitSemaphore_2);
        CPPTEST_TEST_SUITE_END();
        
        void setUp();
        void tearDown();

        void test_TimedWaitSemaphore_1();
        void test_post_1();
        void test_post_2();
        void test_timedWait_1();
        void test_timedWait_2();
        void test_timedWait_3();
		void test_timedWait_4();
        void test_tryWait_1();
        void test_tryWait_2();
        void test_wait_1();
        void test_wait_2();
        void test_x7eTimedWaitSemaphore_1();
		void test_x7eTimedWaitSemaphore_2();
};

CPPTEST_TEST_SUITE_REGISTRATION(TestSuite_TimedWaitSemaphore_cpp_beb1a4fc);

void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::setUp()
{
}

void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::tearDown()
{
	timedWaitDebugFlag = 0;
}

/* CPPTEST_TEST_CASE_BEGIN test_TimedWaitSemaphore_1 */
/* CPPTEST_TEST_CASE_CONTEXT TA_Base_Core::TimedWaitSemaphore::TimedWaitSemaphore(unsigned int) */
void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::test_TimedWaitSemaphore_1()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (initial) */ 
    unsigned _initial  = 1;
    /* Testing constructor. */
    ::TA_Base_Core::TimedWaitSemaphore _return(_initial);
    /* Post-condition check */
}
/* CPPTEST_TEST_CASE_END test_TimedWaitSemaphore_1 */

/* CPPTEST_TEST_CASE_BEGIN test_post_1 */
/* CPPTEST_TEST_CASE_CONTEXT virtual void TA_Base_Core::TimedWaitSemaphore::post(void) */
void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::test_post_1()
{
    /* Pre-condition initialization */
    /* Initializing argument 0 (this) */ 
        /* Initializing constructor argument 1 (initial) */ 
        unsigned _initial_0  = 127;
    ::TA_Base_Core::TimedWaitSemaphore _cpptest_TestObject (_initial_0);
	TA_Base_Core::Condition *pCond = new TA_Base_Core::Condition();
	_cpptest_TestObject.m_condList.push_back(pCond);
    /* Tested function call */
    _cpptest_TestObject.post();
    /* Post-condition check */
}
/* CPPTEST_TEST_CASE_END test_post_1 */

/* CPPTEST_TEST_CASE_BEGIN test_post_2 */
/* CPPTEST_TEST_CASE_CONTEXT virtual void TA_Base_Core::TimedWaitSemaphore::post(void) */
void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::test_post_2()
{
    /* Pre-condition initialization */
    /* Initializing argument 0 (this) */ 
        /* Initializing constructor argument 1 (initial) */ 
        unsigned _initial_0  = 122;
    ::TA_Base_Core::TimedWaitSemaphore _cpptest_TestObject (_initial_0);
	_cpptest_TestObject.m_bDestroyed = true;
    /* Tested function call */
    _cpptest_TestObject.post();
    /* Post-condition check */
}
/* CPPTEST_TEST_CASE_END test_post_2 */

/* CPPTEST_TEST_CASE_BEGIN test_timedWait_1 */
/* CPPTEST_TEST_CASE_CONTEXT bool TA_Base_Core::TimedWaitSemaphore::timedWait(unsigned long) */
void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::test_timedWait_1()
{
    /* Pre-condition initialization */
    /* Initializing argument 0 (this) */ 
        /* Initializing constructor argument 1 (initial) */ 
        unsigned _initial_0  = 180;
    ::TA_Base_Core::TimedWaitSemaphore _cpptest_TestObject (_initial_0);
    /* Initializing argument 1 (timeoutMsec) */ 
    unsigned long _timeoutMsec  = 3000;
	//timedWaitDebugFlag = 1;
    /* Tested function call */

	new ThreadUtil0(_cpptest_TestObject)->start();
    bool _return  = _cpptest_TestObject.timedWait(_timeoutMsec);
    /* Post-condition check */
}
/* CPPTEST_TEST_CASE_END test_timedWait_1 */

/* CPPTEST_TEST_CASE_BEGIN test_timedWait_2 */
/* CPPTEST_TEST_CASE_CONTEXT bool TA_Base_Core::TimedWaitSemaphore::timedWait(unsigned long) */
void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::test_timedWait_2()
{
    /* Pre-condition initialization */
    /* Initializing argument 0 (this) */ 
        /* Initializing constructor argument 1 (initial) */ 
        unsigned _initial_0  = 132;
    ::TA_Base_Core::TimedWaitSemaphore _cpptest_TestObject (_initial_0);
    /* Initializing argument 1 (timeoutMsec) */ 
    unsigned long _timeoutMsec  = 180;
    /* Tested function call */
	_cpptest_TestObject.m_bDestroyed = true;
    bool _return  = _cpptest_TestObject.timedWait(_timeoutMsec);
    /* Post-condition check */
}
/* CPPTEST_TEST_CASE_END test_timedWait_2 */

/* CPPTEST_TEST_CASE_BEGIN test_timedWait_3 */
/* CPPTEST_TEST_CASE_CONTEXT bool TA_Base_Core::TimedWaitSemaphore::timedWait(unsigned long) */
void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::test_timedWait_3()
{
    /* Pre-condition initialization */
    /* Initializing argument 0 (this) */ 
        /* Initializing constructor argument 1 (initial) */ 
        unsigned _initial_0  = 0u;
    ::TA_Base_Core::TimedWaitSemaphore _cpptest_TestObject (_initial_0);
    /* Initializing argument 1 (timeoutMsec) */ 
    unsigned long _timeoutMsec  = 180;
	new ThreadUtil2(_cpptest_TestObject.m_bDestroyed)->start();
    /* Tested function call */
    bool _return  = _cpptest_TestObject.timedWait(_timeoutMsec);
    /* Post-condition check */
}
/* CPPTEST_TEST_CASE_END test_timedWait_3 */


/* CPPTEST_TEST_CASE_BEGIN test_timedWait_3 */
/* CPPTEST_TEST_CASE_CONTEXT bool TA_Base_Core::TimedWaitSemaphore::timedWait(unsigned long) */
void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::test_timedWait_4()
{
	/* Pre-condition initialization */
	/* Initializing argument 0 (this) */ 
	/* Initializing constructor argument 1 (initial) */ 
	unsigned _initial_0  = 0u;
	::TA_Base_Core::TimedWaitSemaphore _cpptest_TestObject (_initial_0);
	/* Initializing argument 1 (timeoutMsec) */ 
	unsigned long _timeoutMsec  = 180;
	timedWaitDebugFlag = 1;
	/* Tested function call */
	bool _return  = _cpptest_TestObject.timedWait(_timeoutMsec);
	_cpptest_TestObject.m_condList.clear();
	/* Post-condition check */
}

/* CPPTEST_TEST_CASE_BEGIN test_tryWait_1 */
/* CPPTEST_TEST_CASE_CONTEXT bool TA_Base_Core::TimedWaitSemaphore::tryWait(void) */
void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::test_tryWait_1()
{
    /* Pre-condition initialization */
    /* Initializing argument 0 (this) */ 
        /* Initializing constructor argument 1 (initial) */ 
        unsigned _initial_0  = 91;
    ::TA_Base_Core::TimedWaitSemaphore _cpptest_TestObject (_initial_0);
    /* Tested function call */
    bool _return  = _cpptest_TestObject.tryWait();
    /* Post-condition check */
    CPPTEST_POST_CONDITION_BOOL("bool _return", ( _return ));
}
/* CPPTEST_TEST_CASE_END test_tryWait_1 */

/* CPPTEST_TEST_CASE_BEGIN test_tryWait_2 */
/* CPPTEST_TEST_CASE_CONTEXT bool TA_Base_Core::TimedWaitSemaphore::tryWait(void) */
void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::test_tryWait_2()
{
    /* Pre-condition initialization */
    /* Initializing argument 0 (this) */ 
        /* Initializing constructor argument 1 (initial) */ 
        unsigned _initial_0  = 105;
    ::TA_Base_Core::TimedWaitSemaphore _cpptest_TestObject (_initial_0);
    /* Tested function call */
	_cpptest_TestObject.m_bDestroyed = true;
    bool _return  = _cpptest_TestObject.tryWait();
    /* Post-condition check */
    CPPTEST_POST_CONDITION_BOOL("bool _return", ( _return ));
}
/* CPPTEST_TEST_CASE_END test_tryWait_2 */

/* CPPTEST_TEST_CASE_BEGIN test_wait_1 */
/* CPPTEST_TEST_CASE_CONTEXT void TA_Base_Core::TimedWaitSemaphore::wait(void) */
void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::test_wait_1()
{
    /* Pre-condition initialization */
    /* Initializing argument 0 (this) */ 
        /* Initializing constructor argument 1 (initial) */ 
        unsigned _initial_0  = 86;
    ::TA_Base_Core::TimedWaitSemaphore _cpptest_TestObject (_initial_0);
	_cpptest_TestObject.m_bDestroyed = true;
    /* Tested function call */
    _cpptest_TestObject.wait();
    /* Post-condition check */
}
/* CPPTEST_TEST_CASE_END test_wait_1 */

/* CPPTEST_TEST_CASE_BEGIN test_wait_2 */
/* CPPTEST_TEST_CASE_CONTEXT void TA_Base_Core::TimedWaitSemaphore::wait(void) */
void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::test_wait_2()
{
    /* Pre-condition initialization */
    /* Initializing argument 0 (this) */ 
        /* Initializing constructor argument 1 (initial) */ 
        unsigned _initial_0  = 72;
    ::TA_Base_Core::TimedWaitSemaphore _cpptest_TestObject (_initial_0);
    /* Tested function call */
    _cpptest_TestObject.wait();
    /* Post-condition check */
}
/* CPPTEST_TEST_CASE_END test_wait_2 */

/* CPPTEST_TEST_CASE_BEGIN test_x7eTimedWaitSemaphore_1 */
/* CPPTEST_TEST_CASE_CONTEXT virtual TA_Base_Core::TimedWaitSemaphore::~TimedWaitSemaphore(void) */
void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::test_x7eTimedWaitSemaphore_1()
{
    /* Testing destructor - begin new scope. */
    {
    /* Pre-condition initialization */
    /* Initializing argument 0 (this) */ 
        /* Initializing constructor argument 1 (initial) */ 
        unsigned _initial_0  = 54;
    ::TA_Base_Core::TimedWaitSemaphore _cpptest_TestObject (_initial_0);

	//new ThreadUtil0(_cpptest_TestObject)->start();

	//_cpptest_TestObject.timedWait(3000);

	/*TA_Base_Core::Condition *pCond = new TA_Base_Core::Condition();
	_cpptest_TestObject.m_condList.push_back(pCond);*/
	
    /* Object destruction at the end of scope */
    }

    /* Post-condition check */
}
/* CPPTEST_TEST_CASE_END test_x7eTimedWaitSemaphore_1 */

/* CPPTEST_TEST_CASE_BEGIN test_x7eTimedWaitSemaphore_1 */
/* CPPTEST_TEST_CASE_CONTEXT virtual TA_Base_Core::TimedWaitSemaphore::~TimedWaitSemaphore(void) */
void TestSuite_TimedWaitSemaphore_cpp_beb1a4fc::test_x7eTimedWaitSemaphore_2()
{
    /* Testing destructor - begin new scope. */
    {
    /* Pre-condition initialization */
    /* Initializing argument 0 (this) */ 
        /* Initializing constructor argument 1 (initial) */ 
        unsigned _initial_0  = 54;
    ::TA_Base_Core::TimedWaitSemaphore _cpptest_TestObject (_initial_0);

	_cpptest_TestObject.m_waitCount = 1;
	new ThreadUtil(_cpptest_TestObject.m_waitCount)->start();

	TA_Base_Core::Condition *pCond = new TA_Base_Core::Condition();
	_cpptest_TestObject.m_condList.push_back(pCond);
	
	
    /* Object destruction at the end of scope */
    }

    /* Post-condition check */
}
/* CPPTEST_TEST_CASE_END test_x7eTimedWaitSemaphore_1 */

