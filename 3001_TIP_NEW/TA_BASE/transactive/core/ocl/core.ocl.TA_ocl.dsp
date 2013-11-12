# Microsoft Developer Studio Project File - Name="core.ocl.TA_ocl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=core.ocl.TA_ocl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "core.ocl.TA_ocl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "core.ocl.TA_ocl.mak" CFG="core.ocl.TA_ocl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "core.ocl.TA_ocl - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "core.ocl.TA_ocl - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "core.ocl.TA_ocl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../../build/win32_nr/"
# PROP Intermediate_Dir "../../../../build/win32_nr/transactive/core/ocl"
# PROP Target_Dir ""
LINK32=link.exe -link
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\cots\oracle\920\winnt\inc" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../../build/win32_nr/TA_ocl.lib"

!ELSEIF  "$(CFG)" == "core.ocl.TA_ocl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../build/win32_nd/"
# PROP Intermediate_Dir "../../../../build/win32_nd/transactive/core/ocl"
# PROP Target_Dir ""
LINK32=link.exe -link
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\cots\oracle\920\winnt\inc" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../../build/win32_nd/TA_ocl.lib"

!ENDIF 

# Begin Target

# Name "core.ocl.TA_ocl - Win32 Release"
# Name "core.ocl.TA_ocl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\crdb.cpp
# End Source File
# Begin Source File

SOURCE=.\src\crdef.cpp
# End Source File
# Begin Source File

SOURCE=.\src\crparser.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ora.cpp
# End Source File
# Begin Source File

SOURCE=.\src\oracall.cpp
# End Source File
# Begin Source File

SOURCE=.\src\oraextproc.cpp
# End Source File
# Begin Source File

SOURCE=.\src\oraloader.cpp
# End Source File
# Begin Source File

SOURCE=.\src\oramonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\src\orapars.cpp
# End Source File
# Begin Source File

SOURCE=.\src\orascript.cpp
# End Source File
# Begin Source File

SOURCE=.\src\orawinmonitor.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\crdb.h
# End Source File
# Begin Source File

SOURCE=.\src\crdef.h
# End Source File
# Begin Source File

SOURCE=.\src\crparser.h
# End Source File
# Begin Source File

SOURCE=.\src\ocl.h
# End Source File
# Begin Source File

SOURCE=.\src\ora.h
# End Source File
# Begin Source File

SOURCE=.\src\oracall.h
# End Source File
# Begin Source File

SOURCE=.\src\oraextproc.h
# End Source File
# Begin Source File

SOURCE=.\src\oraloader.h
# End Source File
# Begin Source File

SOURCE=.\src\oramonitor.h
# End Source File
# Begin Source File

SOURCE=.\src\orapars.h
# End Source File
# Begin Source File

SOURCE=.\src\orascript.h
# End Source File
# Begin Source File

SOURCE=.\src\orawinmonitor.h
# End Source File
# End Group
# End Target
# End Project
