/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: RtdbOpt.h
* 文件描述: 从实时数据库取值实现类
*  作  者 : %林晓雨%，
* 创建日期: 2015-5-28 10:47:25
*******************************************************************************/
#ifndef __RTDBOPT_H__
#define __RTDBOPT_H__

#include "XdbThrift.h"
#include "TypeDef.h"
#include "DataValueInfo.h"	
#include "singleton.h"
#include <thrift/transport/TTransportUtils.h>
#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <memory>
#include <iostream>
#include <vector>

using namespace apache::thrift;
using namespace apache::thrift::async;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

class RtdbOpt
{
public:
	 DECLARE_SINGLETON_INIT(RtdbOpt)

	 static bool	smSanityCheck;
public:
    bool connect();
	// 功能描述: 从实时数据库中读取采集原始值D点值
	bool rtdbGetHisValue(
			MapStringToDataValueInfo &pMapDataValueInfo, 
			const long &lStartTime, 
			const long &lEndTime,
			const int iStep);

	bool rtdbIsExistPoint(const std::string &strPoint);

    std::vector<Point> getHistoryValue(const std::string strSourceId, const long &lStartTime, const long &lEndTime, const int iStep);
private:
    XdbThriftClient *client_;

};

#endif
