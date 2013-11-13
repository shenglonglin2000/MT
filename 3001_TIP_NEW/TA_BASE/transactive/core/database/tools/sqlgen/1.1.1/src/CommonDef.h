/**
  *
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //COTS/sqlgen/1.1.0/src/CommonDef.h $
  * @author Shenglong.Lin
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2013/06/21 12:00:00 $
  * Last modified by: Shenglong.Lin $
  * 
  * to define some common use macro or constant static variables used in the sqlgen
  *
  */
  
  
#ifndef __DEF_COMMONDEF_HH__
#define __DEF_COMMONDEF_HH__



  



//==================================================================================
//file name
#define  defSQLFileName_IN_SQLCODETXT               "sqlcode.txt"	 /*IN*/
#define  defSQLFileName_Out_SQLH					"sql.h"			 /*OUT*/
#define  defSQLFileName_Out_SQLMACRODEFH			"sqlmacrodef.h"	 /*OUT*/

#define  defSQLFilename_OUT_ERRORREPORT				"SqlGenErrorReport.log"  /*OUT*/
//==================================================================================
//param
#define  def_Str_Argv_ProgName        "ProgName"  /*IN*/
#define  def_Str_Argv_inputfile       "Inputfile" /*IN*/
#define  def_Str_Argv_outpath         "Outpath"   /*IN*/



//==================================================================================
#define  LINE_ADD					  '+'
#define  LINE_COMMONT				  ';'
#define  LINE_END				      '\r'

#define  DB_NUM						  3
#define	 DB_COMMON					  "[[common]]"
#define	 DB_ORACLE			          "[[oracle]]"
#define	 DB_MYSQL			          "[[mysql]]"


//==================================================================================


 
//==================================================================================
//==================================================================================
//sql.h header 
#define    SQLH_SQLMACRODEFH_FILE_COMMENT_HEADER   "// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\
// This file is generated by the sql header file tool sqlgen.exe. Please do \n\
// not modify this file directly. Change the sqlcode.txt file instead.\n\
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n\r\n"


//sql.h data 
#define    SQLH_FILE_BEGIN    "#ifndef SQL_H          \n\
#define SQL_H           \n\n\n\n\
#if defined(_UNICODE) || defined(UNICODE)       \n\
typedef wchar_t  CharT;	    \n\
#else					 \n\
typedef char     CharT;		\n\
#endif						\n\r\n\n\n\n\
struct st_sql_data	\n\
{\n\
	const CharT*    pSQLID;\n\
	const CharT*    pCommonSQL;\n\
	const CharT*    pOracleSQL;\n\
	const CharT*    pMySQLSQL;\n\
};\n\n\n\n\
static const st_sql_data  s_SQLArray[]=	\n\
{   \n"


//sql.h end
#define    SQLH_FILE_END       "\n\n}; //static const st_sql_data  s_SQLArray[]  \n\
\n\n #endif//SQL_H           \n"	
//==================================================================================								 
//==================================================================================								 




//==================================================================================
//==================================================================================
//sqlmacrodef.h header 
#define    SQLMACRODEFH_FILE_BEGIN    "#ifndef SQLMACRODEF_H          \n\
#define SQLMACRODEF_H           \n"

//sqlmacrodef.h end
#define    SQLMACRODEFH_FILE_END       "\n\n#endif//SQLMACRODEF_H           \n"								 
//==================================================================================
//==================================================================================



#define	 DEF_INT_BUFFSIZE				  512
#define	 DEF_INT_MAXLINELEN				  8192







//=========================================================
#define SourceFLInfo			__FILE__,__LINE__

#define _SysLog				    CLogger::getInstance().log


//=========================================================

#define DEF_DELETE_ARRAY(pArray)    if (pArray) { delete [](pArray); (pArray) = NULL; }
#define DEF_DELETE(p)   if (p) { delete (p); (p) = NULL; }
//=========================================================


#endif  // __DEF_COMMONDEF_HH__














