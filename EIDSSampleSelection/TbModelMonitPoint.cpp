/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: TbModelMonitPoint.cpp
* 文件描述: 查询模型监测测点
*  作  者 : %林晓雨%
* 创建日期: 2016-8-31 15:20:32
*******************************************************************************/
#include "TbModelMonitPoint.h"

#include "Util.h"
#include "RDbSQLAdapter.h"


TbModelMonitPoint::TbModelMonitPoint(RsdbAdapter * mQtOpt)
:
RDbOperationComplex(mQtOpt),
mBufferSize(0)
{
    mBufferSize = MONIT_POINT_BUFFER_SIZE;
}

TbModelMonitPoint::~TbModelMonitPoint(void)
{
 
}


bool 
TbModelMonitPoint::loadDB(const std::string &strModelId, MapStringToDataValueInfo &pMapDataValueInfo)
{
    Aos_Assert_R(Util::IsQtConnect(), false);

    std::string strSql = SINGLETON(RDbSQLAdapter)->getMonitPointSQL();
    Aos_Assert_R(stmtPrepare(MONIT_POINT_VALUECONFIG, strSql), false);
    Aos_Assert_R(loadValue(pMapDataValueInfo), false);
    stmtCloseStream();
	return true;   
}

bool 
TbModelMonitPoint::loadValue(MapStringToDataValueInfo &pMapDataValueInfo)
{
    while (mQtOpt->SQLStmtFetch())
    {
        std::string strCode = mQtOpt->m_query->value(0).toString().toStdString();
        std::string strPointSource = mQtOpt->m_query->value(1).toString().toStdString();

        MapStringToDataValueInfo_It dItr = pMapDataValueInfo.find(strCode);
        if (dItr == pMapDataValueInfo.end())
            continue;
        dItr->second->mPointSource = strPointSource;
    }
    Aos_WriteLog(PubOpt::StringOpt::StringFormat("Load %s Info Total: %d", MONIT_POINT_VALUECONFIG, pMapDataValueInfo.size()).c_str());
    return true;
}





bool 
TbModelMonitPoint::loadCorrDB(const std::string &strModelId, MapStringToDataValueInfo &pMapDataValueInfo)
{
//	Aos_Assert_R(Util::otlIsConnect(), false);

//	std::string strSql = SINGLETON(RDbSQLAdapter)->getCorrMointPointSQL(strModelId);
//	Aos_Assert_R(stmtPrepare(MONIT_POINT_VALUECONFIG, strSql, mBufferSize), false);
//	Aos_Assert_R(loadCorrValue(pMapDataValueInfo), false);
//	Aos_Assert_R(stmtCloseStream(MONIT_POINT_VALUECONFIG), false);
	return true;   
}

bool 
TbModelMonitPoint::loadCorrValue(MapStringToDataValueInfo &pMapDataValueInfo)
{
	bool nErr = false;
	MapStringToDataValueInfo_It dItr;
	DataValueInfo *dataValueInfo = NULL;
	std::string strCode, strPointSource;
//int i = 0;
//	while (!SINGLETON(OtlAdapter)->SQLStmtFetch())
//	{
//		int nNumber = 0;
//		nErr = SINGLETON(OtlAdapter)->BindOutputByName(strCode);
//		Aos_Assert_R(nErr, false);
//		nErr = SINGLETON(OtlAdapter)->BindOutputByName(strPointSource);
//		Aos_Assert_R(nErr, false);

//		dItr = pMapDataValueInfo.find(strCode);
//		if (dItr != pMapDataValueInfo.end()) continue;

//if (i > 8) continue;
//if (i == 0)
//{
//strCode = "D3_FLTE23";
//}
//if (i == 1)
//{
//strCode = "D3_FLTE24";
//}
//if (i == 2)
//{
//strCode = "D3_FLN01AM";
//}
//if (i == 3)
//{
//strCode = "D3_PATE07";
//}
//if (i == 4)
//{
//strCode = "D3_PATE08";
//}
//if (i == 5)
//{
//strCode = "D3_PATE09";
//}
//if (i == 6)
//{
//strCode = "D3_PATE10";
//}
//if (i == 7)
//{
//strCode = "D3_PATE11";
//}
//if (i == 8)
//{
//strCode = "D3_PATE12";
//}
//i++;
//		dataValueInfo = new DataValueInfo();
//		dataValueInfo->mStrCode = strCode;
//		dataValueInfo->mPointSource = strPointSource;
//		pMapDataValueInfo.insert(make_pair(strCode, dataValueInfo));
//	}
//	Aos_WriteLog(PubOpt::StringOpt::StringFormat("Load %s Info Total: %d",
//		MONIT_POINT_VALUECONFIG, pMapDataValueInfo.size()).c_str());
	return true;
}
