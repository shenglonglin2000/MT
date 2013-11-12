# Microsoft Developer Studio Project File - Name="core.thread.TA_Thread" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=core.thread.TA_Thread - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "core.threads.TA_Thread.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "core.threads.TA_Thread.mak" CFG="core.thread.TA_Thread - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "core.thread.TA_Thread - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "core.thread.TA_Thread - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "core.thread.TA_Thread"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "core.thread.TA_Thread - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../../build/win32_nr"
# PROP Intermediate_Dir "../../../../build/win32_nr/transactive/core/threads"
# PROP Target_Dir ""
LINK32=link.exe -link
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "..\..\core\exceptions\src" /I "..\..\core\utilities\src" /I "..\..\core\synchronisation\src" /I "..\..\..\cots\omniORB\omniORB_4.0.5\include" /I "..\..\\" /I "..\..\..\cots\boost\boost_1_31_0" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "__WIN32__" /D "__x86__" /D "__NT__" /D __OSVERSION__=4 /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../../build/win32_nr/TA_Thread.lib" /ignore:4006

!ELSEIF  "$(CFG)" == "core.thread.TA_Thread - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../build/win32_nd"
# PROP Intermediate_Dir "../../../../build/win32_nd/transactive/core/threads"
# PROP Target_Dir ""
LINK32=link.exe -link
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\cots\omniORB\omniORB_4.0.5\include" /I "..\..\\" /I "..\..\..\cots\boost\boost_1_31_0" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "__WIN32__" /D "__x86__" /D "__NT__" /D __OSVERSION__=4 /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../../build/win32_nd/TA_Thread_d.lib" /ignore:4006

!ENDIF 

# Begin Target

# Name "core.thread.TA_Thread - Win32 Release"
# Name "core.thread.TA_Thread - Win32 Debug"
# Begin Group "src"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\Thread.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Thread.h
# End Source File
# Begin Source File

SOURCE=.\src\ThreadMemberFunction.h
# End Source File
# End Group
# Begin Group "ThreadPool"

# PROP Default_Filter "*.cpp, *.h"
# Begin Source File

SOURCE=.\src\IThreadPoolWorkerCallback.h
# End Source File
# Begin Source File

SOURCE=.\src\IWorkItem.h
# End Source File
# Begin Source File

SOURCE=.\src\ThreadedWorker.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ThreadedWorker.h
# End Source File
# Begin Source File

SOURCE=.\src\ThreadPoolManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ThreadPoolManager.h
# End Source File
# Begin Source File

SOURCE=.\src\ThreadPoolSingletonManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ThreadPoolSingletonManager.h
# End Source File
# End Group
# Begin Group "QueueProcessorPool"

# PROP Default_Filter "*.cpp, *.h"
# Begin Source File

SOURCE=.\src\PriorityQueueProcessor.h
# End Source File
# Begin Source File

SOURCE=.\src\QueueItem.h
# End Source File
# Begin Source File

SOURCE=.\src\QueueProcessor.h
# End Source File
# Begin Source File

SOURCE=.\src\QueueProcessorPool.h
# End Source File
# End Group
# Begin Group "WorkItemQueue"

# PROP Default_Filter "*.cpp, *.h"
# Begin Source File

SOURCE=.\src\WorkItemQueueProcessor.cpp
# End Source File
# Begin Source File

SOURCE=.\src\WorkItemQueueProcessor.h
# End Source File
# End Group
# End Target
# End Project
