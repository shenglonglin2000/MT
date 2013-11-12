# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:  $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/Makefile $ 
# Author:  Ripple
# Version: $Revision: #2 $
#
# Last modification: $DateTime: 2012/02/06 16:15:14 $
# Last modified by:  $Author: haijun.li $

PROJ_ROOT_DIR 		= ../../../../..
PROJ_CODE_DIR		= transactive/core/utilities/test
PROJ_NAME              	= TestDebugUtil

PROJ_SOURCE            	= main.cpp \
			  	TestGenericLogType.cpp \
              		TestPreformattedLogType.cpp \
              		TestLogger.cpp \
			  	TestDebugUtil.cpp \
			  	TestDebugUtilLogMacros.cpp \
			  	ThreadThatCallsLog.cpp \
				VersionGen.cpp

PROJ_TYPE       		= exe

PROJ_INC_DIR		= ./src $(PROJ_ROOT_DIR)/code/transactive $(PROJ_ROOT_DIR)/code/cots/CppUnit/src

PROJ_OUT_DIR		= $(PROJ_ROOT_DIR)/test/unittest/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

PROJ_LIBS	 		= TA_Utilities \
				TA_Thread \
				TA_Synchronisation \
				TA_Version \
				TA_Exceptions\
				CppUnit

PROJ_LIBDIRS 		= $(PROJ_ROOT_DIR)/sdk/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG) \
				$(PROJ_ROOT_DIR)/build/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

#
# Libraries that this library is dependent upon.
#
# DEPENDENT_LIBRARIES
DEPENDENT_LIBRARIES = \
    			$(PROJ_ROOT_DIR)/code/transactive/core/threads  \
    			$(PROJ_ROOT_DIR)/code/transactive/core/synchronisation  \
    			$(PROJ_ROOT_DIR)/code/transactive/core/versioning  \
    			$(PROJ_ROOT_DIR)/code/transactive/core/exceptions

PROJ_CFLAGS = -Wno-deprecated

##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
	#Do Nothing