/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: PModelCorrAnalysis.cpp
* 文件描述: 存储数据相关性分析结果
*  作  者 : %林晓雨%
* 创建日期: 2016-11-11 15:25:42
*******************************************************************************/

#include "PModelCorrAnalysis.h"

#include "Util.h"
#include "AlarmLog.h"
#include "DataValueInfo.h"
#include "RDbSQLAdapter.h"

PModelCorrAnalysis::PModelCorrAnalysis()
:
mBufferSize(0)
{
	mBufferSize = MODEL_CORR_BUFFER_SIZE;
}

PModelCorrAnalysis::~PModelCorrAnalysis(void)
{

}

bool 
PModelCorrAnalysis::saveModelCorrAnalysis(
		const std::string &strModelId,
		std::vector<std::string> &vId,
		std::vector<std::string> &vtPointId,
		std::vector<std::vector<double>> &vtTdata,
		std::vector<std::vector<double>> &vtT2data)
{
//	Aos_Assert_R(Util::otlIsConnect(), false);
    std::string strSql = SINGLETON(RDbSQLAdapter)->getInsertCorrAnalysisDataSQL();
	
//	Aos_Assert_R(vtPointId.size(), false);
//	BigStrings bPointId(vtPointId[0]);
//	//BigStrings	bPointId;
//	for (unsigned int i = 1; i < vtPointId.size(); i++)
//	//for (unsigned int i = 0; i < vtPointId.size(); i++)
//	{
//		//if (i != 0) bPointId.appendString("@");
//		bPointId.appendString("@");
//		bPointId.appendString(vtPointId[i]);

//		//std::string strCode = vtPointId[i];
//		//std::string strPointId;
//		//if (strCode == "D3_FLTE23")
//		//{
//		//	strPointId = "qlj_zc_D3_B4T2";
//		//}
//		//if (strCode == "D3_FLTE24")
//		//{
//		//	strPointId = "qlj_zc_D3_B5OT";
//		//}
//		//if (strCode == "D3_FLN01AM")
//		//{
//		//	strPointId = "qlj_zc_D3_B5T1";
//		//}
//		//if (strCode == "D3_PATE07")
//		//{
//		//	strPointId = "qlj_zc_D3_B6OT";
//		//}
//		//if (strCode == "D3_PATE08")
//		//{
//		//	strPointId = "qlj_zc_D3_B6T1";
//		//}
//		//if (strCode == "D3_PATE09")
//		//{
//		//	strPointId = "qlj_zc_D3_RP1";
//		//}
//		//if (strCode == "D3_PATE10")
//		//{
//		//	strPointId = "qlj_zc_D3_LP1GVT";
//		//}
//		//if (strCode == "D3_PATE11")
//		//{
//		//	strPointId = "qlj_zc_D3_OCOT";
//		//}
//		//if (strCode == "D3_PATE12")
//		//{
//		//	strPointId = "qlj_zc_D3_LOTE12";
//		//}

//		//bPointId.appendString(strPointId);
//	}

//	std::string strMsg;
//	BigStrings bTValue, bT2Value;
//	for (unsigned int i = 0; i < vtTdata.size(); i++)
//	{
//		bTValue.clearString();
//		toString(bTValue, vtTdata[i]);

//		bT2Value.clearString();
//		toString(bT2Value, vtT2data[i]);

//		Aos_Assert_R(stmtPrepare(MODEL_CPRR_ANALY_VALUE, strSql, mBufferSize), false);
//		Aos_Assert_R(bindVariable(vId[i], strModelId, i, bPointId, bTValue, bT2Value), false);
//		Aos_Assert_R(stmtTransCommit(MODEL_CPRR_ANALY_VALUE), false);
//		Aos_Assert_R(stmtCloseStream(MODEL_CPRR_ANALY_VALUE), false);
//	}
	return true;
}


//void
//PModelCorrAnalysis::toString(BigStrings &strMsg, std::vector<double> &rdata)
//{
//	std::string strNumber;
//	for (unsigned int j = 0; j < rdata.size(); j++)
//	{
//		strNumber = Util::Number2String<double>(rdata[j]);
//		if (!strMsg.getBigString().empty())
//		{
//			strMsg.appendString(",");
//		}
//		strMsg.appendString(strNumber);
//	}
//}

/*
bool 
PModelCorrAnalysis::bindVariable(
			 const std::string &strId,
			 const std::string &strModelId,
			 const int &orderId,
			 BigStrings &bPointId,
			 BigStrings &bTValue,
			 BigStrings &bT2Value)
{
	bool nErr = false;
	nErr = SINGLETON(OtlAdapter)->BindInputByName(strId);
	Aos_Assert_R(nErr, false);  

    nErr = SINGLETON(OtlAdapter)->BindInputByName(strModelId);
	Aos_Assert_R(nErr, false);

	nErr = SINGLETON(OtlAdapter)->BindInputByName(orderId);
	Aos_Assert_R(nErr, false);

	nErr = SINGLETON(OtlAdapter)->BindInputByName(bPointId.getBigString());
	Aos_Assert_R(nErr, false);

	nErr = SINGLETON(OtlAdapter)->BindInputByName(bTValue.getBigString());
	Aos_Assert_R(nErr, false);

	nErr = SINGLETON(OtlAdapter)->BindInputByName(bT2Value.getBigString());
	Aos_Assert_R(nErr, false);

	//Aos_Assert_R(stmtTransCommit(MODEL_CPRR_ANALY_VALUE), false);
	//Aos_Assert_R(stmtCloseStream(MODEL_CPRR_ANALY_VALUE), false);
    return true;
}
*/
