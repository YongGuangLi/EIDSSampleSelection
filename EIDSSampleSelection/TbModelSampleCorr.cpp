/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: TbModelSampleCorr.cpp
* 文件描述: 查询模型监测测点
*  作  者 : %林晓雨%
* 创建日期: 2016-8-31 15:20:32
*******************************************************************************/
#include "TbModelSampleCorr.h"

#include "Util.h"
#include "RDbSQLAdapter.h"


TbModelSampleCorr::TbModelSampleCorr()
:
RDbOperationComplex(),
mBufferSize(0)
{
    mBufferSize = MODEL_SAMPLE_BUFFER_SIZE;
}

TbModelSampleCorr::~TbModelSampleCorr(void)
{
 
}


bool 
TbModelSampleCorr::loadDB(VectorString &pVectorModelIdInfo)
{
//	Aos_Assert_R(Util::otlIsConnect(), false);

//	std::string strSql = SINGLETON(RDbSQLAdapter)->getModelSampleCorrSQL();
//	Aos_Assert_R(stmtPrepare(MODEL_SAMPLE_VALUECONFIG, strSql, mBufferSize), false);
//	Aos_Assert_R(loadValue(pVectorModelIdInfo), false);
//	Aos_Assert_R(stmtCloseStream(MODEL_SAMPLE_VALUECONFIG), false);
	return true;   
}

bool 
TbModelSampleCorr::loadValue(VectorString &pVectorModelIdInfo)
{
//	bool nErr = false;
//	std::string strModelId;
//	MapStringToDataValueInfo_It dItr;
//    while (!SINGLETON(OtlAdapter)->SQLStmtFetch())
//    {
////		nErr = SINGLETON(OtlAdapter)->BindOutputByName(strModelId);
//		pVectorModelIdInfo.push_back(strModelId);
//    }
//    Aos_WriteLog(PubOpt::StringOpt::StringFormat("Load %s Info Total: %d",
//        MODEL_SAMPLE_VALUECONFIG, pVectorModelIdInfo.size()).c_str());
    return true;
}
