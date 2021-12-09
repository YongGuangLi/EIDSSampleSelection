/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: DataValueInfo.h
* 文件描述: 数据类
*  作  者 : %林晓雨%，
* 创建日期: 2015-6-2 9:08:41
*******************************************************************************/

#ifndef __DATAVALUEINFO_H__
#define __DATAVALUEINFO_H__

#include <map>
#include <list>
#include <iostream>
#include "AlarmLog.h"
#include "public_function_library.h"

class DataValueInfo  
{
public:
	DataValueInfo(void)
	{
		mStrCode = "";
		mCurrVal = 0;
		mPointSource = "";
		//mCategoryId = "";
		mForeVal = 0;
		mSourceIdRtdbIsExist = true;
	}

	virtual ~DataValueInfo()
	{
		clear();
	}
private:
	double						mCurrVal;          		//当前值,指标值(采集原始值)

public:
	std::string					mStrCode;          		//点、指标编号											
	std::string 				mPointSource;			//全点名
	//std::string					mCategoryId;			//模型分类ID

	double    					mForeVal;          		//公式计算上一个周期的值

	std::list<double>			mOriginalValues;		//采集原始数据
	bool						mSourceIdRtdbIsExist;   //此实时数据库中是否有此点

	void clear()
	{
		mOriginalValues.clear();
	}
	std::string toString()
	{
		//std::string strMsg = PubOpt::StringOpt::StringFormat(
		//	"mStrCode:%s, mCurrVal:%f, mPointSource:%s, mForeVal:%f, mError:%d;", 
		//	mStrCode.c_str(), mCurrVal, mPointSource.c_str(), mForeVal, mError); 
		//return strMsg;
	}

	void setCurrVar(const double vv)
	{
		mCurrVal = vv;
	}

	double getCurrVar()
	{
		return mCurrVal;
	}

	void moveToOriginalValues(const double vv)
	{
		mOriginalValues.push_back(vv);
	}

	// 功能描述: 下移采集原始值列表
	bool nextOriginaValue()
	{
		if(mStrCode.substr(0,1) == "M")	 
		{
			return true;
		}

		double vv = 0;
		if (!mOriginalValues.empty())
		{
			vv = mOriginalValues.front();
			mOriginalValues.pop_front();
			setCurrVar(vv);
			return true;
		}
		Aos_Assert_S("Miss");
		setCurrVar(vv);  
		return false;
	}

};

typedef std::map<std::string, DataValueInfo *>		MapStringToDataValueInfo;
typedef MapStringToDataValueInfo::iterator			MapStringToDataValueInfo_It;
#endif