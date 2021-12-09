/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: PTbModelSampleTime.cpp
* 文件描述: 模型样本时间段过滤条件
*  作  者 : %林晓雨%
* 创建日期: 2016-9-2 14:40:42
*******************************************************************************/

#include "PModelSampleTimeCon.h"

#include "Util.h"
#include "AlarmLog.h"
#include "DataValueInfo.h"
#include "RDbSQLAdapter.h"

PModelSampleTimeCon::PModelSampleTimeCon()
:
mBufferSize(0)
{
	mBufferSize = MODEL_SAMPLE_TIME_CON_BUFFER_SIZE;
}

PModelSampleTimeCon::~PModelSampleTimeCon(void)
{

}

bool 
PModelSampleTimeCon::saveModelSampleTimeCon(
		const std::string &strId, 
		const std::string &strSampleTimeId,
		SampleTimeConInfo *timeConInfo)
{
	std::string strUpperCond = timeConInfo->toString(timeConInfo->mUpperLimitCond);
	std::string strLowerCond = timeConInfo->toString(timeConInfo->mLowerLimitCond);

	 
    std::string strSql = SINGLETON(RDbSQLAdapter)->getInsertModelSampleTimeConSQL();

    Util::SQLDirectExecute(QString::fromStdString(strSql).arg(strId.c_str()).arg(strSampleTimeId.c_str()).arg(timeConInfo->mMonitPointId.c_str()).arg(strUpperCond.c_str())
                                                         .arg(timeConInfo->mUpperLimitValue).arg(strLowerCond.c_str()).arg(timeConInfo->mLowerLimitValue).toStdString());

	return true;
}

