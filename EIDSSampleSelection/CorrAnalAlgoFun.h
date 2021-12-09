/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: CorrAnalAlgoFun.h
* 文件描述: 数据相关性算法
*  作  者 : %林晓雨%
* 创建日期: 2016-11-4 15:56:59
*******************************************************************************/

#ifndef __CORRANALALGOFUN_H__
#define __CORRANALALGOFUN_H__

#include <vector>
#include <string>

#ifdef WIN32
#ifndef IMPORT_TYPE
#define IMPORT_TYPE extern "C" __declspec(dllexport)
#endif
#else
#ifndef IMPORT_TYPE
#define IMPORT_TYPE extern "C"
#endif
#endif


IMPORT_TYPE bool CorrAnalCalculate(
			   std::vector<std::vector<double>> &vData, 
			   std::vector<std::vector<double>> &vTdata,
			   std::vector<std::vector<double>> &vT2data,
			   std::string &strErrorMsg); 

#endif
