/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: PTbModelSampleTime.cpp
* 文件描述: 诊断模型样本时间段
*  作  者 : %林晓雨%
* 创建日期: 2016-9-2 14:40:42
*******************************************************************************/

#include "PModelSampleTime.h"

#include "Util.h"
#include "AlarmLog.h"
#include "DataValueInfo.h"
#include "RDbSQLAdapter.h"

PModelSampleTime::PModelSampleTime(RsdbAdapter *QtOpt)
:RDbOperationComplex(QtOpt),
mBufferSize(0)
{
	mBufferSize = MODEL_SAMPLE_BUFFER_SIZE;
}

PModelSampleTime::~PModelSampleTime(void)
{

}

bool 
PModelSampleTime::saveModelSampleTime(
        const std::string &modelId,
        const std::string &train_id,
		const std::string &condId, 
		SampleTimeInfo *timeInfo)
{
    Aos_Assert_R(Util::IsQtConnect(), false);
	
    std::string strTimeState = "1";
    std::string strEndDate = PubOpt::SystemOpt::DateTmToStr(timeInfo->mEndTime);
    std::string strStartDate = PubOpt::SystemOpt::DateTmToStr(timeInfo->mStartTime);
    std::string strSql = SINGLETON(RDbSQLAdapter)->getInsertModelSampleTimeSQL();
    
    if(!Util::SQLDirectExecute(QString::fromStdString(strSql).arg(timeInfo->mSampleTimeId.c_str()).arg(strStartDate.c_str()).
                                                             arg(strEndDate.c_str()).arg(timeInfo->mStep).arg(modelId.c_str()).
                                                             arg(condId.c_str()).arg(timeInfo->mSampleSum).arg(strTimeState.c_str())
                                                             .arg(train_id.c_str()).toStdString()))
    {
    }
	return true;
}

