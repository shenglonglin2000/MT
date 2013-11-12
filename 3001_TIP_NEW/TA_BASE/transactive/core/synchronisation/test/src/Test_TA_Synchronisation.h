/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/synchronisation/test/src/Test_TA_Synchronisation.h $
  * @author:  Kent Yip
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Header file for the cppunit test units that will test the
  * TA_Synchronisation package.  The test units have only been developed on
  * the WIN32 platform.  This will not compile for any other environment.
  *
  * This testing package is reliant on the TA_Thread package being properly
  * tested and functional.
  */

#ifndef TEST_TA_SYNCHRONISATION_H
#define TEST_TA_SYNCHRONISATION_H

// Check for supported platforms.
#ifndef WIN32
#error Unsupported platform!!!
#endif

#include "core/utilities/src/TAAssert.h"

#include "core/utilities/src/DebugUtil.h"

// Includes for CppUnit
#include "cots/CppUnit/src/TestCase.h"
#include "cots/CppUnit/src/TestFramework.h"


#include "core/threads/src/Thread.h"

#endif // TEST_TA_SYNCHRONISATION_H