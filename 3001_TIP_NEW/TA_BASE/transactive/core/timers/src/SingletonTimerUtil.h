/**
  * The source code in this file is the property of Ripple Systems and is not for redistribution in
  * any form.
  *
  * Source:		$File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/timers/src/SingletonTimerUtil.h $
  * @author:	HoaVu
  * @version:	$Revision: #2 $
  *
  * Last modification:	$DateTime: 2012/02/06 16:15:14 $
  * Last modified by:	$Author: haijun.li $
  *
  * Description:
  *
  *
  */

#ifndef SINGLETON_TIMER_UTIL_H
#define SINGLETON_TIMER_UTIL_H

#include <map>

#include "core/timers/src/TimerUtil.h"
#include "core/threads/src/ThreadPoolManager.h"

#include "core/synchronisation/src/ReEntrantThreadLockable.h"


namespace TA_Base_Core
{
	class ITimeoutCallback;

	class SingletonTimerUtil
	{

	public:

		virtual ~SingletonTimerUtil();

		/**
		*
		* getInstance
		*
		* Get an instance of this SingletonTimerUtil
		*/
		static SingletonTimerUtil & getInstance();

		/**
		*
		* removeInstance
		*
		* Removes an instance of this SingletonTimerUtil
		*/
		static void removeInstance();

		/**
		*
		* startPeriodicTimeOutClock
		*
		* Start the timeout clock, allocated for the register user, for notification
		* when the specified timeout period is expired.
		*
		* @param    user					The registered user of TimerUtil
		* @param    timeoutPeriodMSeconds	The required timeout period in mseconds
        * @param    singleShot	            Whether the timer occurs once only (true) or recurs (false)
        * @param    userData	            Optional pointer to user defined data, owned by user, never deleted here.
        *
        * @return   the timer ID
		*
		*/
		long startPeriodicTimeOutClock ( ITimeoutCallback * user,
										 unsigned long timeoutPeriodMSeconds,
										 bool singleShot = true,
                                         void* userData = NULL );

		/**
		*
		* stopPeriodicTimeOutClock
		*
		* Stop the timeout clock, allocated for the register user.
        * All timers for the user are stopped.
		*
		* @param    user					The registered user of TimerUtil
		*
		*/
		std::vector<void*> stopPeriodicTimeOutClock ( ITimeoutCallback * user );


        /**
		*
		* stopPeriodicTimeOutClock
		*
		* Stop the timeout clock with the specified timer ID.
		*
        * @param    user					The registered user of TimerUtil
		* @param    timerId					the timer id returned by startPeriodicTimeOutClock
		*
		*/
		void* stopPeriodicTimeOutClock ( ITimeoutCallback * user, long timerId );

		//
		// Methods to support a timer specific thread pool
		//
		void queueWorkItem ( IWorkItemPtr workItem );
		void removeWorkItem ( IWorkItemPtr workItem );

	private:

		static SingletonTimerUtil *								m_singletonTimerUtil;
		static unsigned int										m_singletonRefCounter;
		static ReEntrantThreadLockable							m_singletonLock;

		TimerUtil												m_timerUtil;

		ThreadPoolManager*										m_threadPoolManager;

		SingletonTimerUtil();
		SingletonTimerUtil ( const SingletonTimerUtil & theInstance );
		SingletonTimerUtil & operator= ( const SingletonTimerUtil & rhs );
	};

}

#endif
