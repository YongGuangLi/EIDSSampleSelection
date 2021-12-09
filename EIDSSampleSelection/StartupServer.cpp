/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: StartupServer.cpp
* 文件描述: 主控类
*  作  者 : %林晓雨%，
* 创建日期: 2015-6-2 10:23:06
*******************************************************************************/
#include "StartupServer.h"

#include "Util.h"
#include "AlarmLog.h"
#include "SelectionDef.h"
#include "RDbOperationSimple.h"
#include "public_function_library.h"

bool StartupServer::smDestory = false;
bool StartupServer::smSanityCheck = true;

StartupServer::StartupServer(void)
:
mFirstCal(true)
{
}

StartupServer::~StartupServer(void)
{

}

bool
StartupServer::initialRtdb()
{
    std::string strFname = PubOpt::SystemOpt::GetCurExePath() + RTDB_CONFIG_FILE;

	if (!PubOpt::FileOpt::IsFindFile(strFname))
	{
		Aos_Assert_S(PubOpt::StringOpt::StringFormat(SAMPLESELE_ERROR_RTDB_CONF, strFname.c_str()).c_str());
		return false;
    }
	return true;
}


bool
StartupServer::initServiceAlarm()
{
    if (!SINGLETON(ServiceSelectionConfig)->openServiceAlarm())
        return true;

	return true;
}


bool
StartupServer::initial()
{
    if (!initialRtdb())
        return false;

	SINGLETON(RDbOperationSimple)->UpdateVersionNumber();
	return true;
}


void
StartupServer::destory()
{
	smDestory = true;
}

void
StartupServer::stop()
{
	Aos_WriteLog("DisConnect Rtdb Data Base Success.");

//	SINGLETON(OtlAdapter)->OtlDisConnect();
//	Aos_WriteLog("DisConnect Oracle Data Base Success.");

	stopServiceAlarm();
}   

void
StartupServer::stopServiceAlarm()
{
    if (!SINGLETON(ServiceSelectionConfig)->openServiceAlarm())
        return;
}


void 
StartupServer::sleepWait(const long now_time, const long last_time, int li_second)
{
	long ll_time_add = now_time - last_time;
	if(ll_time_add < li_second)
	{
		int nTime = li_second -ll_time_add;
		Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("sleepWait %lds, %ldm;",nTime,
			nTime/60).c_str());

		for (long i = 0; i < nTime; i++)
		{
			if (i % 60 == 0)
			{
//				Util::sendRunAlarm();
				//更新服务状态监测时间(监控服务专用)
				SINGLETON(RDbOperationSimple)->SubmitToControlProcessService();
			}

			if (smDestory) return ;
			PubOpt::SystemOpt::SleepWait(1000);
		}
	}
}

