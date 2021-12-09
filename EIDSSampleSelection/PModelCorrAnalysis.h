/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: PModelCorrAnalysis.h
* 文件描述: 存储数据相关性分析结果
*  作  者 : %林晓雨%
* 创建日期: 2016-11-11 15:26:04
*******************************************************************************/

#ifndef __PMODELCORRANALYSIS_H__
#define __PMODELCORRANALYSIS_H__


#include "TypeDef.h"
#include "DataValueInfo.h"
#include "RDbOperationComplex.h"

#define MODEL_CORR_BUFFER_SIZE            20
#define MODEL_CPRR_ANALY_VALUE 			"PModelCorrAnalysis"

class PModelCorrAnalysis : public RDbOperationComplex
{
private:
	int					mBufferSize;
public:
    PModelCorrAnalysis();
    virtual ~PModelCorrAnalysis(void);
public:
	bool saveModelCorrAnalysis(
			const std::string &strModelId,
			std::vector<std::string> &vId,
			std::vector<std::string> &vtPointId,
			std::vector<std::vector<double>> &vtTdata,
			std::vector<std::vector<double>> &vtT2data);

private:
//	bool bindVariable(
//			const std::string &strId,
//			const std::string &strModelId,
//			const int &orderId,
//			BigStrings &strPointId,
//			BigStrings &strTValue,
//			BigStrings &strT2Value);

//	void toString(BigStrings &strMsg, std::vector<double> &rdata);
};

#endif
