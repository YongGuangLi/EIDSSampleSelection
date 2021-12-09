/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: RDbSQLAdapter.h
* 文件描述: 关系数据库SQL适配器类
*  作  者 : %林晓雨%，
* 创建日期: 2015-5-28 10:47:25
*******************************************************************************/
#ifndef __RDBSQLADAPTER_H__
#define __RDBSQLADAPTER_H__

#include "TypeDef.h"
#include "DataValueInfo.h"	
#include "singleton.h"

class RDbSQLAdapter
{
public:
	DECLARE_SINGLETON_INIT(RDbSQLAdapter)

private:
	std::string  mRdb;
	std::string  mRdbNameSpace;

public:
	std::string getSysGuidSQL();

	std::string GetVersionSQL();

	std::string getIsConnectSQL();

	std::string getMonitPointSQL();

	std::string getRdbSysDateSQL();

	std::string getModelSampleTimeSQL();

	std::string getModelSampleCorrSQL();

	std::string getInsertModelSampleTimeSQL();

	std::string getInsertModelSampleTimeConSQL();

	std::string getDeleteSampleTimeSQL(const std::string &strId);

	std::string getDeleteSampleTimeConSQL(const std::string &strId);
	
	std::string getModelConditionSQL(const std::string &strModelId);

	std::string getSampleTimeConSQL(const std::string &strSampleTimeId);

	std::string getDeleteSampleTimeStateSQL(const std::string &strModelId);

	std::string getDeleteSampleTimeConStateSQL(const std::string &strModelId);

	std::string getUpdateModelSampleTimeState0SQL(const std::string &strModelId);

	std::string getUpdateModelSampleTimeStateSQL(const std::string &strSampleTimeId, const int &iState);

	std::string getCorrMointPointSQL(const std::string &strModelId);

	std::string getCorrSampleTimeSQL(const std::string &strModelId);

	std::string getUpdateSampleTimeCorrStateSQL(const std::string &strCorrState, const std::string &strModelId);

	std::string getInsertCorrAnalysisDataSQL();

	std::string getDeleteCorrAnalysisDataSQL(const std::string &strModelId);

	std::string getUpdateSampleCorrStateSQL(const std::string &strId, const std::string &strState,  const std::string &strCondState);

private:
	std::string getModelSampleTimeSQLPriv();

	std::string getModelSampleTimeDisSQLPriv();
};

#endif
