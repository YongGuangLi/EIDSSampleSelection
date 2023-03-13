/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: TbModelSampleTime.cpp
* 文件描述: 样本筛选模型状态
*  作  者 : %林晓雨%
* 创建日期: 2016-8-31 11:32:41
*******************************************************************************/

#include "TbModelSampleTime.h"

#include "Util.h"
#include "RDbSQLAdapter.h"

TbModelSampleTime::TbModelSampleTime(RsdbAdapter * QtOpt)
    :
      RDbOperationComplex(QtOpt),
      mBufferSize(0)
{
    mBufferSize = TB_SAMPEL_TIME_BUFFER_SIZE;
}

TbModelSampleTime::~TbModelSampleTime(void)
{
}


bool 
TbModelSampleTime::loadDB(VectorModelSelection &pVectorModelSelection)
{
    Aos_Assert_R(Util::IsQtConnect(), false);

    std::string strSql = SINGLETON(RDbSQLAdapter)->getModelSampleTimeSQL();
    qDebug()<<QString::fromStdString(strSql);
    Aos_Assert_S(strSql.c_str());
    Aos_Assert_R(stmtPrepare(TB_SAMPEL_TIME_VALUECONFIG, strSql), false);

    Aos_Assert_R(loadValue(pVectorModelSelection), false);
    stmtCloseStream();
    return true;
}


bool 
TbModelSampleTime::loadValue(VectorModelSelection &pVectorModelSelection)
{
    while (mQtOpt->SQLStmtFetch())
    {

        ModelSelectionMgr *pSelection = new ModelSelectionMgr();

        pSelection->mModelId = mQtOpt->m_query->value(0).toString().toStdString();

        pSelection->mOriginalSTimeInfo->mSampleTimeId = mQtOpt->m_query->value(1).toString().toStdString();

        pSelection->mOriginalSTimeInfo->mStartTime = mQtOpt->m_query->value(2).toDateTime().toTime_t();

        pSelection->mOriginalSTimeInfo->mEndTime  = mQtOpt->m_query->value(3).toDateTime().toTime_t();

        pSelection->mOriginalSTimeInfo->mStep = mQtOpt->m_query->value(4).toInt();

        pSelection->mOriginalSTimeInfo->train_id = mQtOpt->m_query->value(5).toString().toStdString();

        pVectorModelSelection.push_back(pSelection);
    }
    Aos_WriteLog(PubOpt::StringOpt::StringFormat("Load %s Info Total: %d", TB_SAMPEL_TIME_VALUECONFIG, pVectorModelSelection.size()).c_str());
    return true;
}



bool 
TbModelSampleTime::loadCorrDB(const std::string &strModelId, VectorSampleTimeInfo &pVectorSampleTime)
{
    //	Aos_Assert_R(Util::otlIsConnect(), false);

    //	std::string strSql = SINGLETON(RDbSQLAdapter)->getCorrSampleTimeSQL(strModelId);
    //	Aos_Assert_R(stmtPrepare(TB_SAMPEL_TIME_VALUECONFIG, strSql, mBufferSize), false);
    //	Aos_Assert_R(loadCorrValue(pVectorSampleTime), false);
    //	Aos_Assert_R(stmtCloseStream(TB_SAMPEL_TIME_VALUECONFIG), false);
    return true;
}


bool 
TbModelSampleTime::loadCorrValue(VectorSampleTimeInfo &pVectorSampleTime)
{
    //	bool nErr = false;
    //	std::string strModelId;
    //	MapStringToVectorSampleTimeInfo_It vItr;
    //	while (!SINGLETON(OtlAdapter)->SQLStmtFetch())
    //	{
    //		int nNumber = 0;
    //		SampleTimeInfo * timeInfo = new SampleTimeInfo();
    //		nErr = SINGLETON(OtlAdapter)->BindOutputByName(timeInfo->mSampleTimeId);
    //		Aos_Assert_R(nErr, false);

    //		std::string strStartDate;
    //		nErr = SINGLETON(OtlAdapter)->BindOutputByName(strStartDate);
    //		Aos_Assert_R(nErr, false);
    //		if (!strStartDate.empty())
    //		{
    //			timeInfo->mStartTime = PubOpt::SystemOpt::StrToDateTm(strStartDate);
    //		}

    //		std::string strEndDate;
    //		nErr = SINGLETON(OtlAdapter)->BindOutputByName(strEndDate);
    //		Aos_Assert_R(nErr, false);
    //		if (!strEndDate.empty())
    //		{
    //			timeInfo->mEndTime = PubOpt::SystemOpt::StrToDateTm(strEndDate);
    //		}

    //		nErr = SINGLETON(OtlAdapter)->BindOutputByName(timeInfo->mStep);
    //		Aos_Assert_R(nErr, false);

    //		if (timeInfo->mStartTime == timeInfo->mEndTime)
    //		{
    //			delete timeInfo;
    //			continue;
    //		}
    //		pVectorSampleTime.push_back(timeInfo);
    //	}
    //	Aos_WriteLog(PubOpt::StringOpt::StringFormat("Load %s Info Total: %d",
    //		TB_SAMPEL_TIME_VALUECONFIG, pVectorSampleTime.size()).c_str());
    return true;
}
