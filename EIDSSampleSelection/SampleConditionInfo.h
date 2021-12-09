/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: SampleConditionInfo.h
* 文件描述: 模型模式条件
*  作  者 : %林晓雨%
* 创建日期: 2016-8-31 10:15:27
*******************************************************************************/

#ifndef __SAMPLECONDITIONINFO_H__
#define __SAMPLECONDITIONINFO_H__

#include "public_function_library.h"
#include <vector>

struct SampleConditionInfo
{
	std::string				mCondId;	//监视条件Id
	std::string				mName;		//模式名称
	std::string				mLocalVar;	//内部变量
	std::string				mOutVarAndFunc;//外部变量
	std::string				mExpression;//计算条件

	std::string				mTranOutVarAndFun;   //函数名称中存放的 "@"格式转换成 "_"格式,形成新的外部变量与函数名称
	std::vector<std::string>mOutFuncVarArray;     //外部函数变量+外部变量

	double					mCondCalValue;

	SampleConditionInfo()
	:
	mCondId(""),
	mName(""),
	mLocalVar(""),
	mOutVarAndFunc(""),
	mExpression(""),
	mTranOutVarAndFun("")
	{

	}

	~SampleConditionInfo()
	{
		mOutFuncVarArray.clear();
	}


	//解析出指标的外部变量
	void setOutVarAndFunc(const std::string pOutVar)
	{
		if (pOutVar.empty()) return;

		std::string strOutVar = pOutVar;											//输出变量
		//if (!strOutVar.empty())
		//{
		//	if(strOutVar.substr(strOutVar.size()-1,1) == ",")
		//	{
		//		strOutVar = strOutVar + mIndexCode;
		//	}
		//	else
		//	{
		//		strOutVar = strOutVar + "," + mIndexCode;
		//	}
		//}
		//else
		//{
		//	strOutVar = "," + mIndexCode;
		//}

		mOutVarAndFunc = strOutVar;

		//数据库中存放的是 "@"格式的 要转换成 "_"格式
		//将指标本身也作为外部变量加入到外部变量串中，防止公式中引用了自己的指标
		//（这种情况下，保证指标的计算顺序，解析dll将指标本身在变量串中去掉了）在计算时出错
		strOutVar = PubOpt::StringOpt::StringReplace(strOutVar,"@","_");

		mTranOutVarAndFun = strOutVar;
		ParseOutVarFunc();
	}

	///*----------------------------------------------------------------------------*/
	////	功能描述:	解析出指标的外部变量与函数，以单个形式保存在内存中
	///*----------------------------------------------------------------------------*/
	void ParseOutVarFunc()
	{
		int iOfLen = 0;
		std::string strICode;
		//取外部函数成员名称
		std::string strOutVarFunc = mOutVarAndFunc;
		strOutVarFunc = PubOpt::StringOpt::TrimString(strOutVarFunc);
		if (!strOutVarFunc.empty())
		{
			if (strOutVarFunc.substr(strOutVarFunc.size()-1,1) != ",")     //右边没有",",加","
			{
				strOutVarFunc += ",";
			}
			if (strOutVarFunc.substr(0,1) == ",")      //左边有",",就去掉","
			{
				strOutVarFunc = strOutVarFunc.substr(1,strOutVarFunc.size()-1);
			}
			while (strOutVarFunc.find(",") != std::string::npos&&strOutVarFunc.find(",")!=strOutVarFunc.size())
			{
				iOfLen = strOutVarFunc.find(",");
				strICode = strOutVarFunc.substr(0,iOfLen);
				strOutVarFunc = strOutVarFunc.substr(iOfLen+1,strOutVarFunc.size()-iOfLen-1);
				strICode = PubOpt::StringOpt::TrimString(strICode);
				if(!strICode.empty()) mOutFuncVarArray.push_back(strICode);
			}
		}

		std::string strTemp = mTranOutVarAndFun;
		//去掉外部变量与函数组合对象前面与最后的","(逗号)
		if (!strTemp.empty())
		{
			if (strTemp.substr(strTemp.size()-1,1) == ",")     //右边有",",就去掉","
			{
				strTemp = strTemp.substr(1,strTemp.size()-1);   //外部变量与函数
			}
			if (strTemp.substr(0,1) == ",")      //左边有",",就去掉","
			{
				strTemp = strTemp.substr(1,strTemp.size()-1);
			}

			mTranOutVarAndFun = strTemp; //外部函数变量+外部变量
			strTemp.clear();
		}
	}
};
#endif
