/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: ConditionCal.h
* 文件描述: 模式条件计算
*  作  者 : %林晓雨%
* 创建日期: 2016-9-1 11:13:04
*******************************************************************************/

#ifndef __CONDITIONCAL_H__
#define __CONDITIONCAL_H__

#include "TypeDef.h"
#include "singleton.h"
#include "DataValueInfo.h"

struct SampleConditionInfo;
class ConditionCal
{
public:
	DECLARE_SINGLETON_INIT(ConditionCal)

public:
	void calculateCondition(const long &lCalStampTime, MapStringToDataValueInfo &pMapDataValueInfo, SampleConditionInfo *pConditionInfo);

private:
	void calculateArith(const long &lCalStampTime, MapStringToDataValueInfo &pMapDataValueInfo, SampleConditionInfo *pConditionInfo);
   
	std::string getParamValue(
			MapStringToDataValueInfo &pMapDataValueInfo,
			const long &lCalStampTime,
			std::string szChildId);

	void checkIndexValue(double &fIndexVal);

	bool judgeIsExcept(double fExceptVal);

	double calEngine(std::string szEngOutVar,
			std::string szEngLocVar,
			std::string szEngEvalVar,
			std::string szEngExp);

	double getDasValue(MapStringToDataValueInfo &pMapDataValueInfo, std::string szID);

	double getForeValue(MapStringToDataValueInfo &pMapDataValueInfo, std::string szID);

	bool getDasValue(MapStringToDataValueInfo &pMapDataValueInfo, std::string szID, std::string& szValue);
};
#endif
