/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: ServiceSelection.cpp
* 文件描述: 服务管理类
*  作  者 : %林晓雨%，
* 创建日期: 2015-6-25 9:26:37
*******************************************************************************/
#include "ServiceSelection.h"

#include "log.h"
#include "AlarmLog.h"
#include "StartupServerSelection.h"
#include "public_function_library.h"

ServiceSelection::ServiceSelection(void)
:
mStopWait(false)
{
    mStartSvr = new StartupServerSelection();
}

ServiceSelection::~ServiceSelection(void)
{
	if (mStartSvr != NULL) delete mStartSvr;
}

bool ServiceSelection::InitService(void)
{
	bool rslt = mStartSvr->initial();
	Aos_Assert_R(rslt, false);
	return true;
}


void ServiceSelection::ServiceStart(void)
{
    Thread::Start();
    Aos_WriteLog("Start Service Success.");
}


void ServiceSelection::Run()
{
	mStartSvr->calculate();	
	if (mStopWait)
	{
		mStartSvr->stop();
		mStopWait = false;
		PubOpt::SystemOpt::SleepWait(2000);
    }
}


void ServiceSelection::StopService(void)
{
    Aos_WriteLog("Start Stop Service");
    if(mStartSvr != NULL)
	{
		mStopWait = true;
		mStartSvr->destory();
	}
	while(mStopWait)
	{
		PubOpt::SystemOpt::SleepWait(1000);
		Aos_WriteLog("Stop Wait");
	}
	Thread::Stop();
    Aos_WriteLog("Stop Service Success..");
}

