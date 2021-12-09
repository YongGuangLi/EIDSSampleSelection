/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: TbModelSampleTimeCon.cpp
* 文件描述: 样本时间段过滤条件
*  作  者 : %林晓雨%
* 创建日期: 2016-8-31 11:55:33
*******************************************************************************/

#include "TbModelSampleTimeCon.h"

#include "Util.h"
#include "RDbSQLAdapter.h"

TbModelSampleTimeCon::TbModelSampleTimeCon(RsdbAdapter * mQtOpt)
:
RDbOperationComplex(mQtOpt),
mBufferSize(0)
{
    mBufferSize = TIME_CON_BUFFER_SIZE;
}

TbModelSampleTimeCon::~TbModelSampleTimeCon(void)
{

}


bool 
TbModelSampleTimeCon::loadDB(std::string &strSampleTimeId, VectorSampleTimeConInfo &pVectorTimeConInfo)
{
    Aos_Assert_R(Util::IsQtConnect(), false);

    std::string strSql = SINGLETON(RDbSQLAdapter)->getSampleTimeConSQL(strSampleTimeId);
    Aos_Assert_R(stmtPrepare(TIME_CON_VALUECONFIG, strSql), false);
    Aos_Assert_R(loadValue(pVectorTimeConInfo), false);
    stmtCloseStream();
    return true;
}


bool 
TbModelSampleTimeCon::loadValue(VectorSampleTimeConInfo  &pVectorTimeConInfo)
{
    while (mQtOpt->SQLStmtFetch())
    {
        SampleTimeConInfo * pConInfo = new SampleTimeConInfo();
        pConInfo->mMonitPointId = mQtOpt->m_query->value(0).toString().toStdString();

        std::string strUpperLimitCond= mQtOpt->m_query->value(1).toString().toStdString();
        pConInfo->mUpperLimitCond = pConInfo->toEnum(strUpperLimitCond);

        pConInfo->mUpperLimitValue = mQtOpt->m_query->value(2).toDouble();

        std::string strLowerLimitCond = mQtOpt->m_query->value(3).toString().toStdString();
        pConInfo->mLowerLimitCond = pConInfo->toEnum(strLowerLimitCond);

        pConInfo->mLowerLimitValue = mQtOpt->m_query->value(4).toDouble();

        pVectorTimeConInfo.push_back(pConInfo);
    }
    Aos_WriteLog(PubOpt::StringOpt::StringFormat("Load %s Info Total: %d",
        TIME_CON_VALUECONFIG, pVectorTimeConInfo.size()).c_str());
    return true;
}
