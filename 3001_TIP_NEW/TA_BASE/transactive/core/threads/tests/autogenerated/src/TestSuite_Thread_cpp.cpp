#include "cpptest.h"
#include "..\..\..\src\Thread.h"
#include "core\utilities\src\DebugSETranslator.h"
#include "omniORB4\CORBA.h"
#include <exception>

#define TA_Assert(test) {return null}

CPPTEST_CONTEXT("Core.UnitTest/core.thread/src/Thread.cpp");
CPPTEST_TEST_SUITE_INCLUDED_TO("Core.UnitTest/core.thread/src/Thread.cpp");

class TestSuite_Thread_cpp_cf1a0958 : public CppTest_TestSuite
{
    public:
        CPPTEST_TEST_SUITE(TestSuite_Thread_cpp_cf1a0958);
        CPPTEST_TEST(test_sExceptionToString);
        CPPTEST_TEST(test_sExceptionToString_1);
        CPPTEST_TEST(test_sExceptionToString_2);
        CPPTEST_TEST(test_sExceptionToString_3);
        CPPTEST_TEST(test_runThread);
        CPPTEST_TEST(test_runThread_1);
        CPPTEST_TEST(test_runThread_2);
        CPPTEST_TEST(test_runThread_3);
        CPPTEST_TEST_SUITE_END();
        
        void setUp();
        void tearDown();

        void test_sExceptionToString();
        void test_sExceptionToString_1();
        void test_sExceptionToString_2();
        void test_sExceptionToString_3();
        void test_runThread();
        void test_runThread_1();
        void test_runThread_2();
        void test_runThread_3();
};

CPPTEST_TEST_SUITE_REGISTRATION(TestSuite_Thread_cpp_cf1a0958);


class TestThread : public TA_Base_Core::Thread
{
private:
	int m_testFlag;
public:
	TestThread(int testFlag): m_testFlag(testFlag)
	{
	}

	virtual void run() 
	{
		switch (m_testFlag)
		{
		case 1:
			throw TA_Base_Core::TransactiveException("The method or operation is not implemented.");
			break;
		case 2:
			throw TA_Base_Core::WinStructuredException(1, NULL);
			break;
		case 3:
			throw CORBA::PolicyError();
			break;
		default:
			throw 1;
			break;
		}

	}

	virtual void terminate() 
	{
		throw TA_Base_Core::TransactiveException("The method or operation is not implemented.");
	}
};

void TestSuite_Thread_cpp_cf1a0958::setUp()
{
}

void TestSuite_Thread_cpp_cf1a0958::tearDown()
{
}

extern int downcastDebugFlag;
extern int NP_minorStringDebugFlag;

/* CPPTEST_TEST_CASE_BEGIN test_sExceptionToString */
/* CPPTEST_TEST_CASE_CONTEXT std::string TA_Base_Core::sExceptionToString(const CORBA::Exception &) */
void TestSuite_Thread_cpp_cf1a0958::test_sExceptionToString()
{
	downcastDebugFlag = 0;
    /* Pre-condition initialization */
    /* Initializing argument 1 (ex) */ 
    ::CORBA::INV_OBJREF _ex_0 ;
    const ::CORBA::Exception & _ex  = (const ::CORBA::Exception &)_ex_0;
    /* Tested function call */
    ::std::string _return  = ::TA_Base_Core::sExceptionToString(_ex);
    /* Post-condition check */
    CPPTEST_POST_CONDITION_CSTR_N("::std::string _return", ( _return.c_str() ), 256);
}
/* CPPTEST_TEST_CASE_END test_sExceptionToString */

/* CPPTEST_TEST_CASE_BEGIN test_sExceptionToString_1 */
/* CPPTEST_TEST_CASE_CONTEXT std::string TA_Base_Core::sExceptionToString(const CORBA::Exception &) */
void TestSuite_Thread_cpp_cf1a0958::test_sExceptionToString_1()
{
	downcastDebugFlag = 1;
    /* Pre-condition initialization */
    /* Initializing argument 1 (ex) */ 
    ::CORBA::INV_OBJREF _ex_1 ;
    const ::CORBA::Exception & _ex  = (const ::CORBA::Exception &)_ex_1;
    /* Tested function call */
    ::std::string _return  = ::TA_Base_Core::sExceptionToString(_ex);
    /* Post-condition check */
    CPPTEST_POST_CONDITION_CSTR_N("::std::string _return", ( _return.c_str() ), 256);
}
/* CPPTEST_TEST_CASE_END test_sExceptionToString_1 */

/* CPPTEST_TEST_CASE_BEGIN test_sExceptionToString_2 */
/* CPPTEST_TEST_CASE_CONTEXT std::string TA_Base_Core::sExceptionToString(const CORBA::Exception &) */
void TestSuite_Thread_cpp_cf1a0958::test_sExceptionToString_2()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (ex) */ 
    ::CORBA::INV_OBJREF _ex_2 ;
    const ::CORBA::Exception & _ex  = (const ::CORBA::Exception &)_ex_2;
    /* Tested function call */
    ::std::string _return  = ::TA_Base_Core::sExceptionToString(_ex);
    /* Post-condition check */
    CPPTEST_POST_CONDITION_CSTR_N("::std::string _return", ( _return.c_str() ), 256);
}
/* CPPTEST_TEST_CASE_END test_sExceptionToString_2 */

/* CPPTEST_TEST_CASE_BEGIN test_sExceptionToString_3 */
/* CPPTEST_TEST_CASE_CONTEXT std::string TA_Base_Core::sExceptionToString(const CORBA::Exception &) */
void TestSuite_Thread_cpp_cf1a0958::test_sExceptionToString_3()
{
	NP_minorStringDebugFlag = 1;
    /* Pre-condition initialization */
    /* Initializing argument 1 (ex) */ 
    ::CORBA::INV_OBJREF _ex_3 ;
    const ::CORBA::Exception & _ex  = (const ::CORBA::Exception &)_ex_3;
    /* Tested function call */
    ::std::string _return  = ::TA_Base_Core::sExceptionToString(_ex);
    /* Post-condition check */
    CPPTEST_POST_CONDITION_CSTR_N("::std::string _return", ( _return.c_str() ), 256);
}
/* CPPTEST_TEST_CASE_END test_sExceptionToString_3 */

/* CPPTEST_TEST_CASE_BEGIN test_runThread */
/* CPPTEST_TEST_CASE_CONTEXT void * TA_Base_Core::runThread(void *) */
void TestSuite_Thread_cpp_cf1a0958::test_runThread()
{

    /* Pre-condition initialization */
    /* Initializing argument 1 (ptr) */ 
    void * _ptr  = new TestThread(1) ;
    /* Tested function call */
    void * _return  = ::TA_Base_Core::runThread(_ptr);
    /* Post-condition check */
    CPPTEST_POST_CONDITION_PTR("void * _return ", ( _return ));
    CPPTEST_POST_CONDITION_PTR("void * _ptr ", ( _ptr ));
}
/* CPPTEST_TEST_CASE_END test_runThread */

/* CPPTEST_TEST_CASE_BEGIN test_runThread_1 */
/* CPPTEST_TEST_CASE_CONTEXT void * TA_Base_Core::runThread(void *) */
void TestSuite_Thread_cpp_cf1a0958::test_runThread_1()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (ptr) */ 
    void * _ptr  = new TestThread(2) ;
    /* Tested function call */
    void * _return  = ::TA_Base_Core::runThread(_ptr);
    /* Post-condition check */
    CPPTEST_POST_CONDITION_PTR("void * _return ", ( _return ));
    CPPTEST_POST_CONDITION_PTR("void * _ptr ", ( _ptr ));
}
/* CPPTEST_TEST_CASE_END test_runThread_1 */

/* CPPTEST_TEST_CASE_BEGIN test_runThread_2 */
/* CPPTEST_TEST_CASE_CONTEXT void * TA_Base_Core::runThread(void *) */
void TestSuite_Thread_cpp_cf1a0958::test_runThread_2()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (ptr) */ 
    void * _ptr  = new TestThread(3) ;
    /* Tested function call */
    void * _return  = ::TA_Base_Core::runThread(_ptr);
    /* Post-condition check */
    CPPTEST_POST_CONDITION_PTR("void * _return ", ( _return ));
    CPPTEST_POST_CONDITION_PTR("void * _ptr ", ( _ptr ));
}
/* CPPTEST_TEST_CASE_END test_runThread_2 */

/* CPPTEST_TEST_CASE_BEGIN test_runThread_3 */
/* CPPTEST_TEST_CASE_CONTEXT void * TA_Base_Core::runThread(void *) */
void TestSuite_Thread_cpp_cf1a0958::test_runThread_3()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (ptr) */ 
    void * _ptr  = new TestThread(0) ;
    /* Tested function call */
    void * _return  = ::TA_Base_Core::runThread(_ptr);
    /* Post-condition check */
    CPPTEST_POST_CONDITION_PTR("void * _return ", ( _return ));
    CPPTEST_POST_CONDITION_PTR("void * _ptr ", ( _ptr ));
}
/* CPPTEST_TEST_CASE_END test_runThread_3 */
