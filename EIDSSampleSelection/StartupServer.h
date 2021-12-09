/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: StartupServer.h
* 文件描述: 主控类
*  作  者 : %林晓雨%，
* 创建日期: 2015-6-2 10:23:42
*******************************************************************************/
#ifndef __STARTUPSERVER_H__
#define __STARTUPSERVER_H__

#include <list>

class StartupServer
{
protected:
	bool							mFirstCal;				 //服务开始标志
public:					
	static bool						smDestory;				 //停止信号标识
	static bool						smSanityCheck;
public:
	StartupServer(void);
	~StartupServer(void);

	/* 
	 * 功能描述:  初始化变量
	 * 输入参数: 无
	 * 输出参数: 无
	 * 返回值: true(成功)、false(失败)
	*/
	bool	initial();

	/* 
	 * 功能描述:  传递服务停止信号
	 * 输入参数: 无
	 * 输出参数: 无
	 * 返回值: true(成功)、false(失败)
	*/

	void	destory();

	/* 
	 * 功能描述:  服务停止释放资源
	 * 输入参数: 无
	 * 输出参数: 无
	 * 返回值: true(成功)、false(失败)
	*/
	void	stop();

	/* 
	 * 功能描述:  导入所有配置信息并开始计算
	 * 输入参数: 无
	 * 输出参数: 无
	 * 返回值: true(成功)、false(失败)
	*/
	virtual bool	calculate()  = 0;

private:
	
	// 功能描述: 初始化实时数据库
	bool	initialRtdb();
	// 功能描述: 初始化服务告警
	bool	initServiceAlarm();
	// 功能描述: 停止服务告警
	void	stopServiceAlarm();
	// 功能描述: 休眼
	void	sleepWait(const long now_time, const long last_time, int li_second);
};

#endif
