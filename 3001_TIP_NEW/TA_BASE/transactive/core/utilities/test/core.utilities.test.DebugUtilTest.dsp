# Microsoft Developer Studio Project File - Name="core.utilities.test.DebugUtilTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=core.utilities.test.DebugUtilTest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "core.utilities.test.DebugUtilTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "core.utilities.test.DebugUtilTest.mak" CFG="core.utilities.test.DebugUtilTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "core.utilities.test.DebugUtilTest - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "core.utilities.test.DebugUtilTest - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "core.utilities.test.DebugUtilTest - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "../src" /I "../../.." /I "../../../../build/win32_n/transactive/core/message/IDL/src" /I "../../../../cots/CppUnit/src" /I "../../../../cots/omniORB/omniORB_4.0.5/include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__WIN32__" /D "__x86__" /D "__NT__" /D __OSVERSION__=4 /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /machine:I386
# ADD LINK32 Rpcrt4.lib omniORB405_rt.lib omniDynamic405_rt.lib COS405_rt.lib omnithread30_rt.lib ace.lib tstfwk.lib TA_Base_Core.lib TA_Base_Bus.lib /nologo /subsystem:console /incremental:yes /machine:I386 /nodefaultlib:"MSVCRTD" /out:"../../../../../test/unittest/win32_nr/DebugUtilTest.exe" /pdbtype:sept /libpath:"../../../../../sdk/win32_nr" /libpath:"../../../../cots/ACE/5_3/ACE_wrappers/ace" /libpath:"../../../../cots/CppUnit/lib/nt_x86" /libpath:"../../../../cots/omniORB/omniORB_4.0.5/lib/x86_win32"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "core.utilities.test.DebugUtilTest - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../../build/win32_nd"
# PROP Intermediate_Dir "../../../../../build/win32_nd/transactive/core/utilities/test"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /I "../src" /I "../../.." /I "../../../../build/win32_n/transactive/core/message/IDL/src" /I "../../../../cots/CppUnit/src" /I "../../../../cots/omniORB/omniORB_4.0.5/include" /D TA_ASSERT_LOG=0 /D TA_ASSERT_FAIL=EXCEPTION /D "_DEBUG" /D "__WIN32__" /D "__x86__" /D "__NT__" /D __OSVERSION__=4 /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Rpcrt4.lib omniORB405_rtd.lib omniDynamic405_rtd.lib COS405_rtd.lib omnithread30_rtd.lib aced.lib TA_Base_Core_d.lib TA_Base_Bus_d.lib /nologo /subsystem:console /debug /machine:I386 /out:"debug/DebugUtilUnitTest.exe" /pdbtype:sept /libpath:"../../../../../sdk/win32_nd" /libpath:"../../../../cots/ACE/5_3/ACE_wrappers/ace" /libpath:"../../../../cots/CppUnit/lib/nt_x86" /libpath:"../../../../cots/omniORB/omniORB_4.0.5/lib/x86_win32"
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "core.utilities.test.DebugUtilTest - Win32 Release"
# Name "core.utilities.test.DebugUtilTest - Win32 Debug"
# Begin Group "src"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\exceptions\src\AlarmAgentException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\exceptions\src\AlarmAgentException.h
# End Source File
# Begin Source File

SOURCE=.\src\main.cpp
# End Source File
# Begin Source File

SOURCE=.\src\TestDebugUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\src\TestDebugUtil.h
# End Source File
# Begin Source File

SOURCE=.\src\TestDebugUtilLogMacros.cpp
# End Source File
# Begin Source File

SOURCE=.\src\TestDebugUtilLogMacros.h
# End Source File
# Begin Source File

SOURCE=.\src\TestGenericLogType.cpp
# End Source File
# Begin Source File

SOURCE=.\src\TestGenericLogType.h
# End Source File
# Begin Source File

SOURCE=.\src\TestLogger.cpp
# End Source File
# Begin Source File

SOURCE=.\src\TestLogger.h
# End Source File
# Begin Source File

SOURCE=.\src\TestPreformattedLogType.cpp
# End Source File
# Begin Source File

SOURCE=.\src\TestPreformattedLogType.h
# End Source File
# Begin Source File

SOURCE=.\src\ThreadThatCallsLog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ThreadThatCallsLog.h
# End Source File
# Begin Source File

SOURCE=..\..\versioning\src\VersionGen.cpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\config.ini
# End Source File
# Begin Source File

SOURCE=.\src\config.ini.orig
# End Source File
# End Target
# End Project
