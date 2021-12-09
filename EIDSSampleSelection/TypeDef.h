/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: TypeDef.h
* 文件描述: 
*  作  者 : %林晓雨%，
* 创建日期: 2015-6-3 9:13:12
*******************************************************************************/
															 
#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "SampleTimeInfo.h"
#include "SampleTimeConInfo.h"
#include "SampleConditionInfo.h"

#include <map>
#include <list>	
#include <vector>

typedef  std::vector<std::string>						VectorString;
typedef  VectorString::iterator							VectorString_It;

typedef  std::map<std::string, std::string>				MapStringToString;
typedef  MapStringToString::iterator					MapStringToString_It;

typedef std::vector<SampleTimeConInfo *>				VectorSampleTimeConInfo;
typedef VectorSampleTimeConInfo::iterator				VectorSampleTimeConInfo_It;
  
typedef std::map<std::string, SampleConditionInfo*>     MapStringToSampleConditionInfo;
typedef MapStringToSampleConditionInfo::iterator		MapStringToSampleConditionInfo_It;

typedef std::vector<SampleTimeInfo *>					VectorSampleTimeInfo;
typedef VectorSampleTimeInfo::iterator					VectorSampleTimeInfo_It;

typedef std::map<std::string, VectorSampleTimeInfo>		MapStringToVectorSampleTimeInfo;
typedef MapStringToVectorSampleTimeInfo::iterator		MapStringToVectorSampleTimeInfo_It;

#endif//__TYPEDEF_H__
