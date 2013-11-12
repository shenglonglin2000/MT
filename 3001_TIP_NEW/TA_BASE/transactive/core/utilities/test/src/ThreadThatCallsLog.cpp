/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/src/ThreadThatCallsLog.cpp $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * <description>
  *
  */
#include "ThreadThatCallsLog.h"
#include "core/utilities/src/DebugUtil.h"
	
using namespace TA_Base_Core;

ThreadThatCallsLog::ThreadThatCallsLog() 
: m_done(false),
  m_logtype(ThreadThatCallsLog::Mix)
{
	LOG ( SourceInfo, DebugUtil::ThreadCreate, "ThreadThatCallsLog" );
}

ThreadThatCallsLog::ThreadThatCallsLog(ELogType logtype) 
: m_done(false), 
  m_logtype(logtype)
{
	LOG ( SourceInfo, DebugUtil::ThreadCreate, "ThreadThatCallsLog" );
}

void ThreadThatCallsLog::run()
{
	LOG ( SourceInfo, DebugUtil::ThreadBegin, "ThreadThatCallsLog" );

	switch ( m_logtype )
	{
	case Log:		callLogMultiple();
					break;
	case LogMore:	callLogMoreMultiple();
					break;
	case Mix:		callLogAndLogMore();
					break;
	default:		callLogAndLogMore();
					break;
	}

	LOG ( SourceInfo, DebugUtil::ThreadEnd, "ThreadThatCallsLog" );
}


void ThreadThatCallsLog::terminate()
{
	LOG ( SourceInfo, DebugUtil::FunctionEntry, "terminate()" );

	m_done = true;
	
	LOG ( SourceInfo, DebugUtil::FunctionExit, "terminate()" );
}


void ThreadThatCallsLog::callLogOnce(int count)
{
	DebugUtil::EDebugLevel debugLevels[] = 
	{
		DebugUtil::DebugTrace,
		DebugUtil::DebugExternal,
		DebugUtil::DebugDatabase,
		DebugUtil::DebugDebug,
		DebugUtil::DebugInfo,
		DebugUtil::DebugWarn,
		DebugUtil::DebugError,
		DebugUtil::DebugFatal
	};

	DebugUtil::EDebugLevel level = debugLevels[count%8];

	LOG ( SourceInfo, DebugUtil::GenericLog, level, "callLogOnce: %d", count );
}


void ThreadThatCallsLog::callLogMultiple()
{
	LOG ( SourceInfo, DebugUtil::FunctionEntry, "callLogMulitple()" );

	int count = 0;
	int timeInMilliSecs = 5;
	while ( !m_done )
	{
		callLogOnce ( ++count );
		sleep ( timeInMilliSecs );
	}

	LOG ( SourceInfo, DebugUtil::FunctionExit, "callLogMulitple()" );
}


void ThreadThatCallsLog::callLogMoreOnce(int count)
{
	LOGMORE ( SourceInfo, "callLogMoreOnce: %d", count );
}


void ThreadThatCallsLog::callLogMoreMultiple()
{
	LOG ( SourceInfo, DebugUtil::FunctionEntry, "callLogMoreMultiple()" );

	int count = 0;
	int timeInMilliSecs = 5;
	while ( !m_done )
	{
		callLogMoreOnce ( ++count );
		sleep ( timeInMilliSecs );
	}

	LOG ( SourceInfo, DebugUtil::FunctionExit, "callLogMoreMultiple()" );
}


void ThreadThatCallsLog::callLogAndLogMore()
{
	LOG ( SourceInfo, DebugUtil::FunctionEntry, "callLogAndLogMore()" );

	int count = 0;
	int timeInMilliSecs = 5;
	while ( !m_done )
	{
		callLogOnce ( ++count );
		sleep ( timeInMilliSecs );
		callLogMoreOnce ( ++count );
		sleep ( timeInMilliSecs );
	}

	LOG ( SourceInfo, DebugUtil::FunctionExit, "callLogAndLogMore()" );
}
