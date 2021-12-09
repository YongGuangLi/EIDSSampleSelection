/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: TbModelCondition.cpp
* 文件描述: 模型监测条件
*  作  者 : %林晓雨%
* 创建日期: 2016-8-31 14:07:07
*******************************************************************************/

#include "TbModelCondition.h"

#include "Util.h"
#include "RDbSQLAdapter.h"

TbModelCondition::TbModelCondition(RsdbAdapter * QtOpt)
    :
      RDbOperationComplex(QtOpt),
      mBuffTotalSize(0)
{
    mBuffTotalSize = COND_VALUEOUTPUT_BUFFER_SIZE;
}

TbModelCondition::~TbModelCondition(void)
{
}


bool 
TbModelCondition::loadDB(std::string &strModelId, MapStringToSampleConditionInfo &pMapSampleCondInfo)
{
    Aos_Assert_R(Util::IsQtConnect(), false);

    std::string strSql = SINGLETON(RDbSQLAdapter)->getModelConditionSQL(strModelId);
    Aos_Assert_R(stmtPrepare(COND_VALUECONFIG, strSql), false);
    Aos_Assert_R(loadValue(pMapSampleCondInfo), false);
    stmtCloseStream();
    return true;
}

bool 
TbModelCondition::loadValue(MapStringToSampleConditionInfo &pMapSampleCondInfo)
{
    while (mQtOpt->SQLStmtFetch())
    {
        SampleConditionInfo * pCondInfo = new SampleConditionInfo();

        pCondInfo->mCondId = mQtOpt->m_query->value(0).toString().toStdString();

        pCondInfo->mName = mQtOpt->m_query->value(1).toString().toStdString();

        pCondInfo->mLocalVar = mQtOpt->m_query->value(2).toString().toStdString();

        std::string strOutVarAndFunc = mQtOpt->m_query->value(3).toString().toStdString();
        pCondInfo->setOutVarAndFunc(strOutVarAndFunc);

        pCondInfo->mExpression = mQtOpt->m_query->value(4).toString().toStdString();

        pMapSampleCondInfo.insert(make_pair(pCondInfo->mCondId, pCondInfo));
    }

    Aos_WriteLog(PubOpt::StringOpt::StringFormat("Load %s Info Total: %d", COND_VALUECONFIG, pMapSampleCondInfo.size()).c_str());

    return true;
}
