/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: ConditionCal.cpp
* 文件描述: 模型模式条件
*  作  者 : %林晓雨%
* 创建日期: 2016-8-31 10:45:59
*******************************************************************************/

#include "ConditionCal.h"

#include "AlarmLog.h"
#include "Communal.h"
#include "compiler.h"
#include "SelectionDef.h"
#include "SampleConditionInfo.h"
#include "public_function_library.h"

#include <math.h>

IMPLEMENT_SINGLETON(ConditionCal)

ConditionCal::ConditionCal()
{
	Init();
	SetStdWasp(97);
}

ConditionCal::~ConditionCal()
{

}

void
ConditionCal::calculateCondition(const long &lCalStampTime, MapStringToDataValueInfo &pMapDataValueInfo, SampleConditionInfo *pConditionInfo)
{
	return calculateArith(lCalStampTime, pMapDataValueInfo, pConditionInfo);
}

void 
ConditionCal::calculateArith(const long &lCalStampTime, MapStringToDataValueInfo &pMapDataValueInfo, SampleConditionInfo *pConditionInfo)
{
	std::string strLocVar = pConditionInfo->mLocalVar;                  //本地变量
	if (!strLocVar.empty()&&strLocVar.substr(strLocVar.size()-1,1) == ",")						
	{
		strLocVar = strLocVar.substr(0,strLocVar.size()-1);
	}
	if (strLocVar.substr(0,1) == ",")
	{
		strLocVar = strLocVar.substr(1,strLocVar.size()-1);
	}
	strLocVar = PubOpt::StringOpt::TrimString(strLocVar);

	std::string strExp = pConditionInfo->mExpression;
	strExp = PubOpt::StringOpt::TrimString(strExp);

	int iIndex = 0;
	std::string strOutVarVal = "";
	std::string strTemp, strICode, strValue;
	for(unsigned int i = 0; i< pConditionInfo->mOutFuncVarArray.size(); i++)             //外部变量+外部函数变量
	{
		strTemp = pConditionInfo->mOutFuncVarArray[i];
		strICode = strTemp;
		iIndex = strTemp.find("@");
		if (iIndex != -1)	
		{
			strICode = PubOpt::StringOpt::StringReplace(strICode,"@","_");
		}

		strOutVarVal += strICode;
		strOutVarVal += "=";
		strValue = getParamValue(pMapDataValueInfo, lCalStampTime, strTemp);
		strOutVarVal += strValue;
		strOutVarVal += ",";
	}
	//去掉最后的","(逗号)
	if (!strOutVarVal.empty())
	{
		strOutVarVal = strOutVarVal.substr(0,strOutVarVal.size()-1);     //外部变量
	}

	double fValue = 0;
	try
	{
		if(!strExp.empty())
		{
			fValue = calEngine(pConditionInfo->mTranOutVarAndFun, strLocVar, strOutVarVal, strExp);

            std::string tt = PubOpt::StringOpt::StringFormat(
            "calEngine mTranOutVarAndFun:%s,strLocVar:%s,strOutVarVal:%s,value %s=%f;",
            pConditionInfo->mTranOutVarAndFun.c_str(),
            strLocVar.c_str(),
            strOutVarVal.c_str(),
            pConditionInfo->mCondId.c_str(), fValue);
            Aos_WriteLog_D(tt.c_str());
		}
	}
	catch (...) 
	{
		pConditionInfo->mCondCalValue = 0;
	}

	checkIndexValue(fValue);
	pConditionInfo->mCondCalValue = fValue;
}

  

std::string 
ConditionCal::getParamValue(
			   MapStringToDataValueInfo &pMapDataValueInfo,
			   const long &lCalStampTime,
			   std::string szChildId)
{
	double fValue = 0;
	double fTemp = 0;  
	double fFirParam = 0;
	double fSecParam = 0;
	std::string strValue, strTemp, strICode, strInfo;
	time_t t;

	std::string strEleUpper;
	std::string strFirParam, strSecParam,strTarType;

	std::string strUpperParam = szChildId;
	strUpperParam = PubOpt::StringOpt::StringUpper(strUpperParam);
	strUpperParam = PubOpt::StringOpt::TrimString(strUpperParam);

	std::string strLocalParam = szChildId;
	strLocalParam = PubOpt::StringOpt::TrimString(strLocalParam);

	if (strLocalParam.empty())                                   
	{
		strValue = "0";
		return strValue;
	}

	int iIndex = strLocalParam.find("@");
	if (iIndex != -1)  //外部函数变量为实时点、耗差指标、手工指标、绩效指标	
	{
		if(M_SUB == strUpperParam.substr(0,4))    //自减函数	SUB(M1_FH) SUB@M1_FH  SUB_M1_FH
		{
			//AfxExtractSubString(strICode,strLocalParam,1,'@');			//自减指标id
			strICode = PubOpt::StringOpt::StringSplit(strLocalParam, 1, "@");
			strEleUpper = PubOpt::StringOpt::TrimString(strICode);
			//SUB函数中指标当前值
			fSecParam = getDasValue(pMapDataValueInfo, strICode);
			//SUB函数中指标上一周期值
			fFirParam = getForeValue(pMapDataValueInfo,strICode);
			//指标值
			fValue = fSecParam - fFirParam;
		}
		else if(M_NOW == strUpperParam.substr(0,4))
		{
			//NOW(0)表示当前时间
			//系统时间 "小时.分"
			t = lCalStampTime;
			fValue = PubOpt::SystemOpt::GetHour(t);
			fTemp = PubOpt::SystemOpt::GetMinute(t);
			fValue = fValue + fTemp/100;
		}
		//YEAR(0)表示当前时间的年，MONTH(0)表示当前时间的月，DAY(0)表示当前时间的日
		else if(M_YEAR == strUpperParam.substr(0,5))
		{
			t = lCalStampTime;
			fValue = PubOpt::SystemOpt::GetYear(t);
		}
		else if(M_MONTH == strUpperParam.substr(0,6))
		{
			t = lCalStampTime;
			fValue = PubOpt::SystemOpt::GetMonth(t);
		}
		else if(M_WEEK == strUpperParam.substr(0,5))
		{
			t = lCalStampTime;
			fValue = PubOpt::SystemOpt::GetDayOfWeek(t);         // 1:礼拜天 2:礼拜一 。。。7:礼拜六
		}
		else if(M_DAY == strUpperParam.substr(0,4))
		{
			t = lCalStampTime;
			fValue = PubOpt::SystemOpt::GetDay(t);
		}

		//PERIODTIME(0)  最后一次计算周期与上一次计算的时间差 秒为单位
		//系统实时计算周期 单位秒
		else if(M_PERIODTIME == strUpperParam.substr(0,11))
		{
			fValue = 60;
		}

		else if(M_LOG==strUpperParam.substr(0,4))
		{
			strICode = PubOpt::StringOpt::StringSplit(strLocalParam, 1, "@");
			getDasValue(pMapDataValueInfo, strICode, strValue);
			fTemp = atof(strValue.c_str());
			fValue = log(fTemp);
		}
		strValue = PubOpt::StringOpt::StringFormat("%.06f",fValue);
	}
	else      //外部变量中
	{
		
		if (!getDasValue(pMapDataValueInfo,strLocalParam, strValue))
		{
			std::string strInfo = PubOpt::StringOpt::StringFormat("没有取到指标%s的值,元素指标%s的值用当前指标值或实时值代替,函数组合体%s",
				strLocalParam.c_str(), strLocalParam.c_str(), strLocalParam.c_str());  
			Aos_Assert_S(strInfo.c_str());
		}
		
	}
	return strValue;
}


void 
ConditionCal::checkIndexValue(double &fIndexVal)
{
	double fValue = 0;
	if (!judgeIsExcept(fIndexVal))
	{
		fIndexVal = 0;
	}
}

bool 
ConditionCal::judgeIsExcept(double fExceptVal)
{
	bool bExcept = true;
	std::string strTemp;
	strTemp= PubOpt::StringOpt::StringFormat("%f",fExceptVal);
	if (strcmp(strTemp.c_str(),"1.#QNAN0")==0||strcmp(strTemp.c_str(),"-1.#INF00")==0||
		strcmp(strTemp.c_str(),"1.#INF00")==0||strcmp(strTemp.c_str(),"1.#SNAN0")==0||
		strcmp(strTemp.c_str(),"-1.#IND00")==0||strcmp(strTemp.c_str(),"-nan")==0)
	{
		bExcept = false;
	}
	return bExcept;
}


double 
ConditionCal::calEngine(std::string szEngOutVar,
					   std::string szEngLocVar,
					   std::string szEngEvalVar,
					   std::string szEngExp)
{
	double fVal = 0;

	static char* CbTag=NULL;
	static char* CbError=NULL;

	try
	{
		PROGRAM(const_cast<char*>(szEngOutVar.c_str()),const_cast<char*>(szEngLocVar.c_str()),const_cast<char*>(szEngExp.c_str()),&CbTag,&CbError);
	}
	catch(...)
	{
		Aos_Assert_S(IDS_PROGRAM);
	}

	if (CbTag == NULL)
	{
		Aos_Assert_S(IDS_PROGRAM);
		return 0;
	}

	try
	{
		CALCULATE(CbTag,const_cast<char*>(szEngEvalVar.c_str()),&fVal,&CbError);
	}
	catch(...)
	{
		Aos_Assert_S(IDS_CALCULATE);
	}

	RealseRec(CbTag,CbError);
	if (CbTag != NULL)
	{
		delete []CbTag;
		CbTag = NULL;
	}
	if (CbError != NULL)
	{
		delete []CbError;
		CbError = NULL;
	}
	return fVal;
}

	 
double 
ConditionCal::getDasValue(MapStringToDataValueInfo &pMapDataValueInfo, std::string szID)
{
	double fValue = 0;
	MapStringToDataValueInfo_It iter = pMapDataValueInfo.find(szID);
	if (iter != pMapDataValueInfo.end())
	{
		fValue = iter->second->getCurrVar();
	}
	return fValue;
}


double 
ConditionCal::getForeValue(MapStringToDataValueInfo &pMapDataValueInfo, std::string szID)
{
	double fValue = 0;
	MapStringToDataValueInfo_It iter = pMapDataValueInfo.find(szID);
	if (iter != pMapDataValueInfo.end())
	{
		fValue = iter->second->mForeVal;
	}

	return fValue;
}


bool 
ConditionCal::getDasValue(MapStringToDataValueInfo &pMapDataValueInfo, std::string szID,std::string& szValue)
{
	bool b = false;
	std::string strValue = "0";
	MapStringToDataValueInfo_It iter = pMapDataValueInfo.find(szID);
	if (iter != pMapDataValueInfo.end())
	{
		b = true;
		strValue = PubOpt::StringOpt::StringFormat("%.06f", iter->second->getCurrVar());
	}
	szValue = strValue;
	return b;
}

