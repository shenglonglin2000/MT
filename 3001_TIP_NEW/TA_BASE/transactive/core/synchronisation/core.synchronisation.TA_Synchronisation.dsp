# Microsoft Developer Studio Project File - Name="core.synchronisation.TA_Synchronisation" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=core.synchronisation.TA_Synchronisation - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "core.synchronisation.TA_Synchronisation.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "core.synchronisation.TA_Synchronisation.mak" CFG="core.synchronisation.TA_Synchronisation - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "core.synchronisation.TA_Synchronisation - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "core.synchronisation.TA_Synchronisation - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Base/code/tools/build", ATMIAAAA"
# PROP Scc_LocalPath "..\..\..\tools\build"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "core.synchronisation.TA_Synchronisation - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../../build/win32_nr"
# PROP Intermediate_Dir "../../../../build/win32_nr/transactive/core/synchronisation"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe -link
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "..\..\\" /I "../../" /I "..\..\..\cots\omniORB\omniORB_4.0.5\include" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "__WIN32__" /D "__x86__" /D "__NT__" /D __OSVERSION__=4 /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../../build/win32_nr/TA_Synchronisation.lib" /ignore:4006

!ELSEIF  "$(CFG)" == "core.synchronisation.TA_Synchronisation - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../build/win32_nd"
# PROP Intermediate_Dir "../../../../build/win32_nd/transactive/core/synchronisation"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe -link
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../../" /I "..\..\..\cots\omniORB\omniORB_4.0.5\include" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "__WIN32__" /D "__x86__" /D "__NT__" /D __OSVERSION__=4 /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../../build/win32_nd/TA_Synchronisation_d.lib" /ignore:4006

!ENDIF 

# Begin Target

# Name "core.synchronisation.TA_Synchronisation - Win32 Release"
# Name "core.synchronisation.TA_Synchronisation - Win32 Debug"
# Begin Group "src"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\AbstractSingleThreadBarrier.h
# End Source File
# Begin Source File

SOURCE=.\src\Condition.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Condition.h
# End Source File
# Begin Source File

SOURCE=.\src\IThreadLockable.cpp
# End Source File
# Begin Source File

SOURCE=.\src\IThreadLockable.h
# End Source File
# Begin Source File

SOURCE=.\src\NonReEntrantThreadLockable.cpp
# End Source File
# Begin Source File

SOURCE=.\src\NonReEntrantThreadLockable.h
# End Source File
# Begin Source File

SOURCE=.\src\ReadWriteThreadLockable.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ReadWriteThreadLockable.h
# End Source File
# Begin Source File

SOURCE=.\src\ReEntrantThreadLockable.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ReEntrantThreadLockable.h
# End Source File
# Begin Source File

SOURCE=.\src\ReEntrantThreadLockableWithMutex.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ReEntrantThreadLockableWithMutex.h
# End Source File
# Begin Source File

SOURCE=.\src\Semaphore.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Semaphore.h
# End Source File
# Begin Source File

SOURCE=.\src\SingleThreadBarrier.cpp
# End Source File
# Begin Source File

SOURCE=.\src\SingleThreadBarrier.h
# End Source File
# Begin Source File

SOURCE=.\src\ThreadGuard.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ThreadGuard.h
# End Source File
# Begin Source File

SOURCE=.\src\ThreadLockableHolderVerifier.h
# End Source File
# Begin Source File

SOURCE=.\src\ThreadReadGuard.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ThreadReadGuard.h
# End Source File
# Begin Source File

SOURCE=.\src\WriteReadThreadLockable.cpp
# End Source File
# Begin Source File

SOURCE=.\src\WriteReadThreadLockable.h
# End Source File
# End Group
# End Target
# End Project
