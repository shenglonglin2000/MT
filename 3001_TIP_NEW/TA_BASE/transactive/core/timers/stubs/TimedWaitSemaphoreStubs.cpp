#include "cpptest.h"
#include "core\threads\src\Thread.h"

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
#include "core\synchronisation\src\Condition.h"
#include "TimedWaitSemaphore.h"

/** User stub definition for function: void TA_Base_Core::Condition::wait(void) */
void (::TA_Base_Core::Condition::CppTest_Stub_wait) (void) 
{
}

/** User stub definition for function: bool TA_Base_Core::TimedWaitSemaphore::tryWait(void) */
bool (::TA_Base_Core::TimedWaitSemaphore::CppTest_Stub_tryWait) (void) 
{
	TA_Base_Core::Thread::sleep(3000);
	return false;
}

int timedWaitDebugFlag = 0;
/** User stub definition for function: int TA_Base_Core::Condition::timedWait(unsigned long) */
int (::TA_Base_Core::Condition::CppTest_Stub_timedWait) (unsigned long milliSeconds) 
{
	if(0 == timedWaitDebugFlag)
		return 0;
    return 1;
}
