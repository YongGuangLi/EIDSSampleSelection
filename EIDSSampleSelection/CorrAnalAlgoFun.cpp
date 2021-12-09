/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: CorrAnalAlgoFun.cpp
* 文件描述: 数据相关性算法
*  作  者 : %林晓雨%
* 创建日期: 2016-11-4 15:57:07
*******************************************************************************/

#include "CorrAnalAlgoFun.h"
#include "CorrelationAnalysis.h"

IMPORT_TYPE bool CorrAnalCalculate(
		   std::vector<std::vector<double>> &vData, 
		   std::vector<std::vector<double>> &vTdata,
		   std::vector<std::vector<double>> &vT2data,
		   std::string &strErrorMsg)
{
	strErrorMsg.clear();
	CorrelationAnalysis corrAnalObj;
	bool rslt = corrAnalObj.Calculate(vData, vTdata, vT2data);
	if (!rslt)
	{
	   strErrorMsg = corrAnalObj.GetStrErrorMessage();
	}
	return rslt;
}
