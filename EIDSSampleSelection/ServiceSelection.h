/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: ServiceSelection.h
* 文件描述: 服务管理类
*  作  者 : 林晓雨，
* 创建日期: 2015-05-14 15:38:21
*******************************************************************************/

#ifndef __SERVICESAMPLESELECTION_H__
#define __SERVICESAMPLESELECTION_H__

#include <map>
#include <string>
#include "thread.h"

class StartupServer;
class ServiceSelection : public Thread
{
	bool	mStopWait;
public:
    ServiceSelection(void);
    virtual ~ServiceSelection(void);
public:
    // 功能描述: 初始化数据统计服务
    bool InitService(void);
    // 功能描述: 启动数据统计服务
    void ServiceStart(void);
    // 功能描述: 停止数据统计服务
    void StopService(void);
private:
	virtual void Run(void);

	StartupServer * mStartSvr;
};

#endif
