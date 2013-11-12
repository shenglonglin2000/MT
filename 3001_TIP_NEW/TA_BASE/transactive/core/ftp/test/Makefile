# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:  $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/ftp/test/Makefile $ 
# Author:  Ripple
# Version: $Revision: #2 $
#
# Last modification: $DateTime: 2012/02/06 16:15:14 $
# Last modified by:  $Author: haijun.li $
#

PROJ_ROOT_DIR = ../../..
PROJ_NAME = FTPTest
PROJ_SOURCE = FTPTest.cpp VersionGen.cpp

PROJ_TYPE	= exe
PROJ_OBJDIR = ./obj
PROJ_INCDIR = ./src

PROJ_INCDIRS = \
	$(PROJ_ROOT_DIR) \
	$(PROJ_ROOT_DIR)/app/traffic_analysers/watts_agent/IDL/src \
	$(PROJ_ROOT_DIR)/cots/Traficon/WATTS_SDK \
	$(PROJ_ROOT_DIR)/bus/generic_agent/src \
	$(PROJ_ROOT_DIR)/core/utilities/src \
	$(PROJ_ROOT_DIR)/core/configuration_updates/src \
	$(PROJ_ROOT_DIR)/core/exceptions/src \
	$(PROJ_ROOT_DIR)/core/threads/src \
	$(PROJ_ROOT_DIR)/core/corba/src \
	$(PROJ_ROOT_DIR)/core/database/src \
	$(PROJ_ROOT_DIR)/core/message/IDL/src \
	$(PROJ_ROOT_DIR)/core/message/types \
	$(PROJ_ROOT_DIR)/core/process_management/src \
	$(PROJ_ROOT_DIR)/core/process_management/IDL/src \
	$(PROJ_ROOT_DIR)/core/entity_config/src \
	$(PROJ_ROOT_DIR)/core/synchronisation/src 
	

PROJ_LIBS = \
	TA_FTP \
	TA_Synchronisation \
	TA_Thread \
	TA_Utilities \
	TA_ProcessManagement \
	TA_ProcessManagementCorbaDef \
    TA_CorbaUtil \
    TA_CorbaDef \
	TA_Exceptions \
	TA_Sockets \
	TA_Version

PROJ_LIBDIRS = \
	$(PROJ_ROOT_DIR)/core/ftp/obj \
	$(PROJ_ROOT_DIR)/core/utilities/obj \
	$(PROJ_ROOT_DIR)/core/alarm/obj \
	$(PROJ_ROOT_DIR)/core/alarm/IDL/obj \
	$(PROJ_ROOT_DIR)/core/database/obj \
	$(PROJ_ROOT_DIR)/core/data_access_interface/obj \
	$(PROJ_ROOT_DIR)/core/data_access_interface/entity_access/obj \
	$(PROJ_ROOT_DIR)/core/process_management/obj \
	$(PROJ_ROOT_DIR)/core/process_management/IDL/obj \
	$(PROJ_ROOT_DIR)/core/synchronisation/obj \
	$(PROJ_ROOT_DIR)/core/exceptions/obj \
	$(PROJ_ROOT_DIR)/core/message/obj \
	$(PROJ_ROOT_DIR)/core/message/IDL/obj \
	$(PROJ_ROOT_DIR)/core/naming/obj \
	$(PROJ_ROOT_DIR)/core/naming/IDL/obj \
	$(PROJ_ROOT_DIR)/core/versioning/obj \
	$(PROJ_ROOT_DIR)/core/corba_named_obj/obj \
	$(PROJ_ROOT_DIR)/core/corba/obj \
	$(PROJ_ROOT_DIR)/core/corba/IDL/obj \
	$(PROJ_ROOT_DIR)/core/sockets/obj \
	$(PROJ_ROOT_DIR)/core/uuid/obj \
	$(PROJ_ROOT_DIR)/bus/generic_agent/obj \
	$(PROJ_ROOT_DIR)/cots/oracle/920/solaris/lib \
	$(PROJ_ROOT_DIR)/cots/Traficon/WATTS_SDK/obj \
	$(PROJ_ROOT_DIR)/core/threads/obj

DEPENDENT_LIBRARIES = \
 	$(PROJ_ROOT_DIR)/bus/generic_agent \
 	$(PROJ_ROOT_DIR)/core/naming \
 	$(PROJ_ROOT_DIR)/core/alarm \
 	$(PROJ_ROOT_DIR)/core/alarm/IDL \
 	$(PROJ_ROOT_DIR)/core/corba_named_obj \
 	$(PROJ_ROOT_DIR)/core/sockets \
 	$(PROJ_ROOT_DIR)/core/versioning



##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/tools/build/CommonMakefile.mak


install:
	#Do Nothing
