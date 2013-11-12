#include "cpptest.h"
#include "core/exceptions/src/TransactiveException.h"

/**
 * This file contains user stub definitions.
 *
 * To create a user stub:
 * 1. Open stub template list:
 *    - Eclipse IDE: type 'stub' and press <Ctrl> <Space>
 *    - Microsoft Visual Studio IDE: use context menu C++test->Insert Snippet...
 * 2. Choose the stub template from the list.
 * 3. #include the header file where the function you want to stub is originally 
 *    declared as well as any supporting header files as necessary.
 * 4. Fill out the stub signature to match that of the original function, 
 *    while keeping the CppTest_Stub prefix when it applies.
 *    Note: for C++ operators, use appropriate stub names - e.g.:
 *        CppTest_Stub_operator_new    for operator new
 *        CppTest_Stub_operator_delete for operator delete
 *        CppTest_Stub_operator_plus   for operator +
 *    Refer to C++test User's Guide for a complete list of stub names for operators. 
 * 5. Fill out the body of the stub according to intent.
 *
 * Available C++test API functions (see C++test Users Guide for details):
 *     void CppTest_Assert(bool test, const char * message)
 *     void CppTest_Break()
 *     const char* CppTest_GetCurrentTestCaseName()
 *     const char* CppTest_GetCurrentTestSuiteName()
 *     bool CppTest_IsCurrentTestCase(const char* testCaseName)
 */

/** 
 * Header files where the stubbed functions are originally declared.
 * Verify #include directives and add any additional header files as necessary.
 */
#include "omniORB4\CORBA.h"
#include "core\utilities\src\DebugSETranslator.h"

int downcastDebugFlag = 0;
int NP_minorStringDebugFlag = 0;

/** User stub definition for function: const CORBA::SystemException * CORBA::SystemException::_downcast(const CORBA::Exception *) */
const ::CORBA::SystemException * (::CORBA::SystemException::CppTest_Stub__downcast) (const ::CORBA::Exception * _MT_var2) 
{
	if(0 == downcastDebugFlag)
		return (const ::CORBA::SystemException *)0;
	return ::CORBA::SystemException::_downcast(_MT_var2);
}

/** User stub definition for function: virtual const char * CORBA::SystemException::NP_minorString(void) const */
const char * (::CORBA::SystemException::CppTest_Stub_NP_minorString) (void)  const
{
	if(0 == NP_minorStringDebugFlag)
		return (const char *)NULL;
	return (const char *)"";
}


/** User stub definition for function: const char * CORBA::TypeCode::name(void) const */
const char * (::CORBA::TypeCode::CppTest_Stub_name) (void)  const
{
    throw TA_Base_Core::TransactiveException("test");
}

/** User stub definition for function: void TA_Base_Core::gDoAssertionAction(int, const char *, int, const char *, const char *) */
namespace TA_Base_Core{
void gDoAssertionAction (int action, const char * file, int line, const char * test, const char * info) ;
void CppTest_Stub_gDoAssertionAction (int action, const char * file, int line, const char * test, const char * info) 
{
	return;
}
}

/** User stub definition for function: int TA_Base_Core::gGetRuntimeBreakAction(void) */
namespace TA_Base_Core{
int gGetRuntimeBreakAction () ;
int CppTest_Stub_gGetRuntimeBreakAction (void) 
{
    return 0;
}
}

/** User stub definition for function: CONTEXT * TA_Base_Core::gContextFromExceptionInfo(EXCEPTION_POINTERS *) */
namespace TA_Base_Core{
::CONTEXT * gContextFromExceptionInfo (::EXCEPTION_POINTERS * exceptionInfo) ;
::CONTEXT * CppTest_Stub_gContextFromExceptionInfo (::EXCEPTION_POINTERS * exceptionInfo) 
{
    return (::CONTEXT *)0;
}
}
