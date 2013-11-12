# Microsoft Developer Studio Project File - Name="core.timers.TA_Timers" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=core.timers.TA_Timers - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "core.timers.TA_Timers.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "core.timers.TA_Timers.mak" CFG="core.timers.TA_Timers - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "core.timers.TA_Timers - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "core.timers.TA_Timers - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/4 - Engineering/4.20 Common Code/core.timers.TA_Timers", YGFAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "core.timers.TA_Timers - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../../build/win32_nr"
# PROP Intermediate_Dir "../../../../build/win32_nr/transactive/core/timers"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe -link
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "..\..\cots\omniORB\omniORB_3.0.3\include" /I "..\exceptions\src" /I "..\..\core\versioning\src" /I "..\..\core\synchronisation\src" /I "..\..\..\cots\omniORB\omniORB_4.0.5\include" /I "..\..\\" /I ".\src" /I "..\..\..\cots\boost\boost_1_31_0" /I "..\..\..\cots\ACE\5_3\ACE_wrappers" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "__WIN32__" /D "__x86__" /D "__NT__" /D __OSVERSION__=4 /D "_AFXDLL" /D _WIN32_WINNT=0X400 /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../../build/win32_nr/TA_Timers.lib" /ignore:4006

!ELSEIF  "$(CFG)" == "core.timers.TA_Timers - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../build/win32_nd"
# PROP Intermediate_Dir "../../../../build/win32_nd/transactive/core/timers"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe -link
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /I "..\..\..\cots\omniORB\omniORB_4.0.5\include" /I "..\..\\" /I ".\src" /I "..\..\..\cots\boost\boost_1_31_0" /I "..\..\..\cots\ACE\5_3\ACE_wrappers" /I "..\..\..\\" /D "_AFXDLL" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "__WIN32__" /D "__x86__" /D "__NT__" /D __OSVERSION__=4 /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../../build/win32_nd/TA_Timers_d.lib" /ignore:4006

!ENDIF 

# Begin Target

# Name "core.timers.TA_Timers - Win32 Release"
# Name "core.timers.TA_Timers - Win32 Debug"
# Begin Group "Timers"

# PROP Default_Filter "*.cpp. *.h"
# Begin Source File

SOURCE=.\src\AbstractThreadedTimeoutUser.cpp
# End Source File
# Begin Source File

SOURCE=.\src\AbstractThreadedTimeoutUser.h
# End Source File
# Begin Source File

SOURCE=.\src\ITimeoutCallback.h
# End Source File
# Begin Source File

SOURCE=.\src\SingletonTimerUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\src\SingletonTimerUtil.h
# End Source File
# Begin Source File

SOURCE=.\src\StopwatchUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StopwatchUtil.h
# End Source File
# Begin Source File

SOURCE=.\src\TimerUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\src\TimerUtil.h
# End Source File
# Begin Source File

SOURCE=.\src\WindowsTimerQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\src\WindowsTimerQueue.h
# End Source File
# End Group
# Begin Group "TimedWaitSemaphore"

# PROP Default_Filter "*.cpp, *.h"
# Begin Source File

SOURCE=.\src\TimedWaitSemaphore.cpp
# End Source File
# Begin Source File

SOURCE=.\src\TimedWaitSemaphore.h
# End Source File
# End Group
# Begin Group "TimedSingleThreadBarrier"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\TimedSingleThreadBarrier.cpp
# End Source File
# Begin Source File

SOURCE=.\src\TimedSingleThreadBarrier.h
# End Source File
# End Group
# End Target
# End Project
