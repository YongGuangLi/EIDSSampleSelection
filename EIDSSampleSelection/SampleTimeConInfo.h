/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: SampleTimeConInfo.h
* 文件描述: 样本时间段过滤条件
*  作  者 : %林晓雨%
* 创建日期: 2016-8-31 8:53:29
*******************************************************************************/
#ifndef __SAMPLETIMECONINFO_H__
#define __SAMPLETIMECONINFO_H__

#include <string>
#include "AlarmLog.h"
#include "public_function_library.h"
#include <string.h>
struct SampleTimeConInfo
{
	enum E
	{
		eOpr_Gt = 1,		//>
		eOpr_Ge = 2,		//>=
		eOpr_Lt = 3,		//<
		eOpr_Le = 4,		//<=
		eOpr_Invalid = 5
	};

	E toEnum(const std::string &opr)
	{
		if (strcmp(opr.c_str(), ">") == 0) return eOpr_Gt;
		if (strcmp(opr.c_str(), ">=") == 0) return eOpr_Ge;
		if (strcmp(opr.c_str(), "<") == 0) return eOpr_Lt;
		if (strcmp(opr.c_str(), "<=") == 0) return eOpr_Le;
		return eOpr_Invalid;
	}

	std::string toString(E opr)
	{
		std::string strOpr;
		switch(opr)
		{
		case eOpr_Gt:
			 strOpr = ">";
			 break;
		case eOpr_Ge:
			 strOpr = ">=";
			 break;
		case eOpr_Lt:
			 strOpr = "<";
			 break;
		case eOpr_Le:
			 strOpr = "<=";
			 break;
		default:
			 strOpr = "";
			 break;
		}
		return strOpr;
	}

	std::string				mMonitPointId;		//模型测点数据
	E						mUpperLimitCond;	//上限条件(<,<=)
	double					mUpperLimitValue;	//上限值
	E						mLowerLimitCond;	//下限条件(>,>=)
	double					mLowerLimitValue;	//下限值

	 SampleTimeConInfo()
	 :
	 mMonitPointId(""),
	 mUpperLimitCond(eOpr_Invalid),
	 mUpperLimitValue(0),
	 mLowerLimitCond(eOpr_Invalid),
	 mLowerLimitValue(0)
	 {

	 }

	 ~SampleTimeConInfo()
	 {

	 }
			  
	 bool judgeManualCondition(const long &lCalStampTime, const double &fVal)
	 {			
//Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("lCalStampTime:%s;", PubOpt::SystemOpt::DateTmToStr(lCalStampTime).c_str()).c_str());
		 std::string strLog;
		 //判断下限条件	 下限条件(>,>=)
		 switch(mLowerLimitCond)
		 {
		 case eOpr_Gt:
			  if (fVal > mLowerLimitValue)
			  {
//Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("fVal(%f) > mLowerLimitValue(%f)", fVal, mLowerLimitValue).c_str());
				  break;
			  }
//Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("fVal(%f) <= mLowerLimitValue(%f)", fVal, mLowerLimitValue).c_str());
			  return false;

		 case eOpr_Ge:
			  if (fVal >= mLowerLimitValue) 
			  {				   
//Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("fVal(%f) >= mLowerLimitValue(%f)", fVal, mLowerLimitValue).c_str());
				  break;
			  }
//Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("fVal(%f) < mLowerLimitValue(%f)", fVal, mLowerLimitValue).c_str());
			  return false;
			  
		 default:
			  if (mLowerLimitCond != eOpr_Invalid)
			  {
				  strLog = PubOpt::StringOpt::StringFormat("tb_eids_model_sample_time_con mMonitPointId:%s,上下限条件错误!", mMonitPointId.c_str());
				  Aos_Assert_S(strLog.c_str());
				  return false;
			  }
		 }

		 //判断上限条件	  上限条件(<,<=)
		 switch(mUpperLimitCond)
		 {
		 case eOpr_Lt:
			  if (fVal < mUpperLimitValue) 
			  {
//Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("fVal(%f) < mUpperLimitValue(%f)", fVal, mUpperLimitValue).c_str());
				  break;
			  }
//Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("fVal(%f) >= mUpperLimitValue(%f)", fVal, mUpperLimitValue).c_str());
			  return false;

		 case eOpr_Le:
			 if (fVal <= mUpperLimitValue) 
			 {
//Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("fVal(%f) <= mUpperLimitValue(%f)", fVal, mUpperLimitValue).c_str());
				 break;
			 }
//Aos_WriteLog_D(PubOpt::StringOpt::StringFormat("fVal(%f) > mUpperLimitValue(%f)", fVal, mUpperLimitValue).c_str());
			 return false;

		 default:
			 if (mUpperLimitCond != eOpr_Invalid)
			 {
				 strLog = PubOpt::StringOpt::StringFormat("tb_eids_model_sample_time_con mMonitPointId:%s,上下限条件错误!", mMonitPointId.c_str());
				 Aos_Assert_S(strLog.c_str());
				 return false;
			 }
		 }
		 return true;
	 }
};
#endif
