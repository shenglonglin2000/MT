# Microsoft Developer Studio Project File - Name="core.ftp.TA_FTP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=core.ftp.TA_FTP - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "core.ftp.TA_FTP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "core.ftp.TA_FTP.mak" CFG="core.ftp.TA_FTP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "core.ftp.TA_FTP - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "core.ftp.TA_FTP - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "core.ftp.TA_FTP - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../../build/win32_nr/"
# PROP Intermediate_Dir "../../../../build/win32_nr/transactive/core/ftp"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe -link
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../" /I "../../../cots\omniORB\omniORB_4.0.5\include" /D "NDEBUG" /D "__WIN32__" /D "__x86__" /D "__NT__" /D __OSVERSION__=4 /D "WIN32" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../../build/win32_nr/TA_FTP.lib"

!ELSEIF  "$(CFG)" == "core.ftp.TA_FTP - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../build/win32_nd/"
# PROP Intermediate_Dir "../../../../build/win32_nd/transactive/core/ftp"
# PROP Target_Dir ""
MTL=midl.exe
LINK32=link.exe -link
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../../" /I "../../../cots\omniORB\omniORB_4.0.5\include" /D "_DEBUG" /D "__WIN32__" /D "__x86__" /D "__NT__" /D __OSVERSION__=4 /D "WIN32" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../../build/win32_nd/TA_FTP_d.lib"

!ENDIF 

# Begin Target

# Name "core.ftp.TA_FTP - Win32 Release"
# Name "core.ftp.TA_FTP - Win32 Debug"
# Begin Group "src"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\FTPClient.cpp
# End Source File
# Begin Source File

SOURCE=.\src\FTPClient.h
# End Source File
# Begin Source File

SOURCE=.\src\FTPConstants.h
# End Source File
# Begin Source File

SOURCE=.\src\FTPControlConnection.h
# End Source File
# Begin Source File

SOURCE=.\src\FTPDataConnection.cpp
# End Source File
# Begin Source File

SOURCE=.\src\FTPException.cpp
# End Source File
# Begin Source File

SOURCE=.\src\FTPException.h
# End Source File
# Begin Source File

SOURCE=.\src\FTPManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\FTPManager.h
# End Source File
# Begin Source File

SOURCE=.\src\FTPReply.cpp
# End Source File
# Begin Source File

SOURCE=.\src\FTPReply.h
# End Source File
# End Group
# End Target
# End Project
