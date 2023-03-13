/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: Util.cpp
* 文件描述: 基础函数类
*  作  者 : %林晓雨%，
* 创建日期: 2015-6-3 14:33:09
*******************************************************************************/
#include "Util.h"


#include <time.h>

namespace Util
{
    RsdbAdapter *rsdbAdapter = NULL;

    RsdbAdapter *getRsdbAdapter()
    {
        if(rsdbAdapter == NULL)
            rsdbAdapter = new RsdbAdapter();

        return rsdbAdapter;
    }

	bool connectRtdbDB()
    {
        bool result =  SINGLETON(RtdbOpt)->connect();
        if(result)
            PubOpt::StringOpt::StringFormat("Rsdb (QT) Connect Success");
        else
            PubOpt::StringOpt::StringFormat("Rsdb (QT) Connect Failure");
        return result;
	}


	
	bool StringSplit(const std::string &strSrc, 
		std::vector<std::string> &lstRet, 
		const std::string &strSplit)
	{
		if (strSplit.empty())
		{
			return false;
		}
		std::string strSrcBak = strSrc;
		size_t siFind = 0;
		while(!strSrcBak.empty())
		{
			siFind = strSrcBak.find(strSplit);
			if (std::string::npos == siFind)
			{
				lstRet.push_back(strSrcBak);
				strSrcBak.clear();
				continue;
			}
			lstRet.push_back(strSrcBak.substr(0, siFind));
			strSrcBak = strSrcBak.substr(siFind + strSplit.size());
		}
		return true;
	}
	
	
	unsigned long getNowTime()
	{
		time_t nowtime = time(NULL);
		return nowtime;
	}





	long convertIntMinute(const long &ltime)
	{
		long oneMin = 60;
		return ltime - (ltime % oneMin);
	}

	int getMinute(const time_t & c_time)
	{
		int tm_min;
		struct tm *timeinfo; 
		timeinfo = localtime(&c_time);
		tm_min= timeinfo->tm_min;
        return tm_min;
    }

    bool IsQtConnect()
    {
        if(rsdbAdapter->QtIsConnect())
            return true;

        std::string strError;
        DBServerInfo stServerInfo;
        stServerInfo.strSessionName = SINGLETON(ServiceSelectionConfig)->getSessionName();
        stServerInfo.strUserName = SINGLETON(ServiceSelectionConfig)->getUserName();
        stServerInfo.strPasswd = SINGLETON(ServiceSelectionConfig)->getPassWD();         //Tzrd#2021@db
        stServerInfo.strRsdbType = SINGLETON(ServiceSelectionConfig)->getRsdbType();
        stServerInfo.strIp = SINGLETON(ServiceSelectionConfig)->getRsdbIp();
        stServerInfo.iPort = CharPointerConvert2Number<int>(SINGLETON(ServiceSelectionConfig)->getRsdbPort().c_str());

        if(!rsdbAdapter->QtConnect(stServerInfo))
        {
            strError = PubOpt::StringOpt::StringFormat("Rsdb (QT) Connect Failure:%s",rsdbAdapter->GetErrorMessage().c_str());
            Aos_Assert_S(strError.c_str());
            return false;
        }
        else
        {
            strError = PubOpt::StringOpt::StringFormat("Rsdb (QT) Connect Success");
            Aos_WriteLog(strError.c_str());
        }
        return true;
    }

    bool SQLDirectExecute(string sql)
    {
        Aos_Assert_S(sql.c_str());
        return rsdbAdapter->SQLDirectExecute(sql);
    }

}
