/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/utilities/test/src/ThreadThatCallsLog.h $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * <description>
  *
  */
#ifndef THREADTHATCALLSLOG_H_INCLUDED
#define THREADTHATCALLSLOG_H_INCLUDED


#if defined( WIN32 )
#pragma warning( disable : 4786 )
#endif // defined( WIN32 )

#include <string>
#include <stdarg.h>
#include "core/utilities/src/DebugUtil.h"
#include "core/threads/src/Thread.h"

class ThreadThatCallsLog : public TA_Base_Core::Thread
{
public:

	enum ELogType
	{
		Log,
		LogMore,
		Mix
	};

	ThreadThatCallsLog();

	ThreadThatCallsLog(ELogType logtype);
	
	virtual ~ThreadThatCallsLog() {}

	virtual void run();

	virtual void terminate();

private:

	bool m_done;

	ELogType m_logtype;

	void callLogOnce(int count);

	void callLogMultiple();

	void callLogMoreOnce(int count);

	void callLogMoreMultiple();

	void callLogAndLogMore();

};

#endif // THREADTHATCALLSLOG_H_INCLUDED
