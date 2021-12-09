/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: RtdbOpt.cpp
* 文件描述: 从实时数据库取值实现类
*  作  者 : %林晓雨%，
* 创建日期: 2015-5-28 10:47:56
*******************************************************************************/

#include "RtdbOpt.h"

#include "Util.h"
#include "AlarmLog.h"
#include "DataValueInfo.h"

//#include "TesterGetFile.h"

#include <iostream>

IMPLEMENT_SINGLETON(RtdbOpt)

bool RtdbOpt::smSanityCheck = false;

RtdbOpt::RtdbOpt(void)
{
}

RtdbOpt::~RtdbOpt(void)
{
}

bool 
RtdbOpt::rtdbIsExistPoint(const std::string &strPoint)
{
    Point point;

    return	client->checkPoint(point);
}

std::vector<Point> RtdbOpt::getHistoryValue(const std::string strSourceId, const long &lStartTime, const long &lEndTime, const int iStep)
{
    std::vector<Point> vecPoints;
    HisQuery hisQuery;
    int index = strSourceId.find_last_of(".");
    hisQuery.dir = strSourceId.substr(0, index);
    hisQuery.name =  strSourceId.substr(index + 1);
    hisQuery.startTime = lStartTime * 1000;//s->ms
    hisQuery.endTime = lEndTime * 1000;//s->ms
    hisQuery.isFilter = false;
    hisQuery.minValue = 0;
    hisQuery.maxValue = 0;
    hisQuery.interval = iStep * 1000;//无法确定数据库中step的单位是秒还是毫秒

    client->getHistoryPoints(vecPoints, hisQuery);

    return vecPoints;
}


bool RtdbOpt::connect()
{
    std::shared_ptr<TTransport> socket(new TSocket("10.66.195.160", 7912));
    std::shared_ptr<TTransport> transport(new TFramedTransport(socket, 2048));
    std::shared_ptr<TProtocol> protocol(new TCompactProtocol(transport));
    client = new XdbThriftClient(protocol);

    try {
        transport->open();
    } catch(TException& tx)
    {
        std::cout << "InvalidOperation:"<<tx.what()<<std::endl;
    }
}

bool RtdbOpt::rtdbGetHisValue(
        MapStringToDataValueInfo &pMapDataValueInfo,
        const long &lStartTime,
        const long &lEndTime,
        const int iStep)
{
    //return testGetFile.nextValue(pMapDataValueInfo, lStartTime, lEndTime, iStep);
    if (!Util::connectRtdbDB()) return false;
    Aos_Assert_R(iStep > 0, false);
    Aos_Assert_R(!pMapDataValueInfo.empty(), false);
    Aos_Assert_R(lStartTime > 0 && lEndTime > 0 && lEndTime -lStartTime >= 0, false);
    Aos_Assert_R(lEndTime -lStartTime > iStep, false);

    int pTagsNum = ((lEndTime - lStartTime) /iStep) + 1;
    Aos_Assert_R(pTagsNum > 0, false);
    pTagsNum += 10;


    for (MapStringToDataValueInfo_It itr = pMapDataValueInfo.begin(); itr != pMapDataValueInfo.end(); ++itr)
    {
        bool isGetRealTimeValue = true;
        DataValueInfo * data_value_info = itr->second;
        string strSourceId = data_value_info->mPointSource;

        if (strSourceId.empty() || data_value_info->mSourceIdRtdbIsExist)
            isGetRealTimeValue = false;

        int i = 0;
        std::vector<Point> vecPoints =  getHistoryValue(strSourceId, lStartTime, lEndTime, iStep);
        for (long lCalTime = lStartTime; lCalTime <= lEndTime; lCalTime += iStep)
        {
            if (!isGetRealTimeValue)
            {
                data_value_info->moveToOriginalValues(0.00);
                continue;
            }
            Point point = vecPoints.at(i);

            data_value_info->moveToOriginalValues(point.value);
            ++i;
        }
    }

    return true;
}



































