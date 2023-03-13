/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: RDbSQLAdapter.cpp
* 文件描述: 关系数据库SQL适配器类
*  作  者 : %林晓雨%
* 创建日期: 2016-10-31 10:31:20
*******************************************************************************/

#include "RDbSQLAdapter.h"

#include "Util.h"
#include "RDbHead.h"
#include "SelectionDef.h"

IMPLEMENT_SINGLETON(RDbSQLAdapter)

RDbSQLAdapter::RDbSQLAdapter()
:
mRdb(""),
mRdbNameSpace("")
{
	mRdb = SINGLETON(ServiceSelectionConfig)->getRsdbType();
	mRdbNameSpace = SINGLETON(ServiceSelectionConfig)->getNameSpace();
	if (!mRdbNameSpace.empty())
	{
		mRdbNameSpace = PubOpt::StringOpt::StringFormat("%s.", mRdbNameSpace.c_str());
	}
}


RDbSQLAdapter::~RDbSQLAdapter()
{

}

std::string 
RDbSQLAdapter::getModelSampleTimeSQL()
{
	if (!SINGLETON(ServiceSelectionConfig)->openDistributed())
	{
		return getModelSampleTimeSQLPriv();
	}
	return getModelSampleTimeDisSQLPriv();
}

std::string
RDbSQLAdapter::getModelSampleTimeSQLPriv()
{
    return g_strModelSampleTimeSQL;
}


std::string
RDbSQLAdapter::getModelSampleTimeDisSQLPriv()
{
	VectorString ltRet;
	std::string stringSets;
	std::string strSets = SINGLETON(ServiceSelectionConfig)->getDistributedSets();
//	Util::StringSplit(strSets, ltRet, ",");
	for (unsigned int i = 0 ; i < ltRet.size(); i++)
	{
		if (stringSets.empty())
		{
			stringSets = PubOpt::StringOpt::StringFormat("'%s'", ltRet[i].c_str());
		}
		else
		{
			stringSets = PubOpt::StringOpt::StringFormat("%s,'%s'", stringSets.c_str(), ltRet[i].c_str()); 
		}
	}

	std::string strSql;
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		strSql = PubOpt::StringOpt::StringFormat(g_strModelSampleTimeDistributedSQL.c_str(), stringSets.c_str());
	}
	else
	{
		strSql = PubOpt::StringOpt::StringFormat(g_strModelSampleTimeDistributedSvr2SQL.c_str(), 
			mRdbNameSpace.c_str(), mRdbNameSpace.c_str(), stringSets.c_str());
	}
	return strSql;
}


std::string 
RDbSQLAdapter::getIsConnectSQL()
{
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		return g_strIsConnectSQL;
	}
	return g_strIsConnectSvr2SQL;
}


std::string 
RDbSQLAdapter::getRdbSysDateSQL()
{
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		return g_strRdbSysDateSQL;
	}
	return g_strRdbSysDateSvr2SQL;
}


std::string
RDbSQLAdapter::getSysGuidSQL()
{
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		return g_strSysGuidSQL;
	}
	return g_strSysGuidSvr2SQL;
}

std::string
RDbSQLAdapter::getSampleTimeConSQL(const std::string &strSampleTimeId)
{
	std::string strSql;
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		strSql = PubOpt::StringOpt::StringFormat(g_strSampleTimeConSQL.c_str(), strSampleTimeId.c_str());
		return strSql;
	}
	
	strSql = PubOpt::StringOpt::StringFormat(
        g_strSampleTimeConSvr2SQL.c_str(), strSampleTimeId.c_str());
	return strSql;
}

std::string
RDbSQLAdapter::getModelConditionSQL(const std::string &strModelId)
{
	std::string strSql;
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		strSql = PubOpt::StringOpt::StringFormat(
			g_strModelConditionSQL.c_str(), strModelId.c_str());
		return strSql;
	}

	strSql = PubOpt::StringOpt::StringFormat(
		g_strModelConditionSvr2SQL.c_str(), mRdbNameSpace.c_str(), strModelId.c_str());
	return strSql;
}
					

std::string
RDbSQLAdapter::getMonitPointSQL()
{
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		return g_strMonitPointSQL;
	}

	std::string strSql = PubOpt::StringOpt::StringFormat(
		g_strMonitPointSvr2SQL.c_str(), mRdbNameSpace.c_str());
	return strSql;
}

std::string 
RDbSQLAdapter::getInsertModelSampleTimeSQL()
{
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		return g_strInsertModelSampleTimeSQL;
	}
	
	std::string strSql = PubOpt::StringOpt::StringFormat(
		g_strInsertModelSampleTimeSvr2SQL.c_str(), mRdbNameSpace.c_str());
	return strSql;
}


std::string 
RDbSQLAdapter::getInsertModelSampleTimeConSQL()
{
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		return g_strInsertModelSampleTimeConSQL;
	}

	std::string strSql = PubOpt::StringOpt::StringFormat(
		g_strInsertModelSampleTimeConSvr2SQL.c_str(), mRdbNameSpace.c_str());
	return strSql;
}


std::string
RDbSQLAdapter::getDeleteSampleTimeSQL(const std::string &strId)
{
	std::string strSql;
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		strSql = PubOpt::StringOpt::StringFormat(
			g_strDeleteSampleTimeSQL.c_str(), strId.c_str());
		return strSql;
	}

	strSql = PubOpt::StringOpt::StringFormat(
		g_strDeleteSampleTimeSvr2SQL.c_str(), mRdbNameSpace.c_str(), strId.c_str());
	return strSql;
}

std::string
RDbSQLAdapter::getDeleteSampleTimeConSQL(const std::string &strSampleTimeId)
{		   
	//手工筛选条件表
	std::string strSql;
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		strSql = PubOpt::StringOpt::StringFormat(
			g_strDeleteSampleTimeConSQL.c_str(), strSampleTimeId.c_str());
		return strSql;
	}

	strSql = PubOpt::StringOpt::StringFormat(
		g_strDeleteSampleTimeConSvr2SQL.c_str(), mRdbNameSpace.c_str(), strSampleTimeId.c_str());
	return strSql;
}


std::string
RDbSQLAdapter::getUpdateModelSampleTimeStateSQL(const std::string &strSampleTimeId, const int &iState)
{
	std::string strSql;
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		strSql = PubOpt::StringOpt::StringFormat(
			g_strUpdateModelSampleTimeStateSQL.c_str(), iState, strSampleTimeId.c_str());
		return strSql;
	}

	strSql = PubOpt::StringOpt::StringFormat(g_strUpdateModelSampleTimeStateSvr2SQL.c_str(), 
		mRdbNameSpace.c_str(), iState, strSampleTimeId.c_str());
	return strSql;
}


std::string
RDbSQLAdapter::getUpdateModelSampleTimeState0SQL(const std::string &strModelId)
{
	std::string strSql;
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		strSql = PubOpt::StringOpt::StringFormat(
			g_strUpdateModelSampleTimeState0SQL.c_str(), strModelId.c_str());
		return strSql;
	}

	strSql = PubOpt::StringOpt::StringFormat(g_strUpdateModelSampleTimeState0Svr2SQL.c_str(), 
		mRdbNameSpace.c_str(), strModelId.c_str());
	return strSql;
}

std::string
RDbSQLAdapter::getDeleteSampleTimeConStateSQL(const std::string &strModelId)
{
	std::string strSql;
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		strSql = PubOpt::StringOpt::StringFormat(
			g_strDeleteSampleTimeConState2SQL.c_str(), strModelId.c_str());
        qDebug()<<QString::fromStdString(strSql);
		return strSql;
	}

	strSql = PubOpt::StringOpt::StringFormat(g_strDeleteSampleTimeConState2Svr2SQL.c_str(), 
		mRdbNameSpace.c_str(), mRdbNameSpace.c_str(), strModelId.c_str());
	return strSql;
}


std::string
RDbSQLAdapter::getDeleteSampleTimeStateSQL(const std::string &strModelId)
{
	std::string strSql;
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		strSql = PubOpt::StringOpt::StringFormat(
			g_strDeleteSampleTimeState2SQL.c_str(), strModelId.c_str());
		return strSql;
	}

	strSql = PubOpt::StringOpt::StringFormat(
		g_strDeleteSampleTimeState2Svr2SQL.c_str(),  mRdbNameSpace.c_str(), strModelId.c_str());
	return strSql;
}

std::string
RDbSQLAdapter::getCorrMointPointSQL(const std::string &strModelId)
{
	std::string strSql;
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		strSql = PubOpt::StringOpt::StringFormat(
			g_strCorrMonitPointSQL.c_str(), strModelId.c_str());
		return strSql;
	}
	strSql = PubOpt::StringOpt::StringFormat(
		g_strCorrMonitPointSvr2SQL.c_str(), mRdbNameSpace.c_str(),
		mRdbNameSpace.c_str(), strModelId.c_str(), mRdbNameSpace.c_str());
	return strSql;
}


std::string 
RDbSQLAdapter::getCorrSampleTimeSQL(const std::string &strModelId)
{
	std::string strSql;
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		strSql = PubOpt::StringOpt::StringFormat(g_strCorrModelSampleTimeSQL.c_str(), strModelId.c_str());
		return strSql;
	}
	
	strSql = PubOpt::StringOpt::StringFormat(
		g_strCorrModelSampleTimeSvr2SQL.c_str(), mRdbNameSpace.c_str(), strModelId.c_str());
	return strSql;
}


std::string
RDbSQLAdapter::getUpdateSampleTimeCorrStateSQL(const std::string &strCorrState, const std::string &strId)
{
	std::string strSql;
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		strSql = PubOpt::StringOpt::StringFormat(
			g_strCorrUpdateSampleTimeCorrStateSQL.c_str(),
			strCorrState.c_str(), strId.c_str());
		return strSql;
	}
	strSql = PubOpt::StringOpt::StringFormat(
		g_strCorrUpdateSampleTimeCorrStateSvr2SQL.c_str(),
		mRdbNameSpace.c_str(), strCorrState.c_str(), strId.c_str());
	return strSql;
}

std::string
RDbSQLAdapter::getInsertCorrAnalysisDataSQL()
{
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		return g_strCorrInsertCorrAnalysisDataSQL;
	}

	std::string strSql = PubOpt::StringOpt::StringFormat(
		g_strCorrInsertCorrAnalysisDataSvr2SQL.c_str(), mRdbNameSpace.c_str());
	return strSql;
}


std::string
RDbSQLAdapter::getDeleteCorrAnalysisDataSQL(const std::string &strModelId)
{
	std::string strSql;
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		strSql = PubOpt::StringOpt::StringFormat(
			g_strCorrDeleteCorrAnalysisDataSQL.c_str(), strModelId.c_str());
		return strSql;
	}

	strSql = PubOpt::StringOpt::StringFormat(
		g_strCorrDeleteCorrAnalysisDataSvr2SQL.c_str(), mRdbNameSpace.c_str(), strModelId.c_str());
	return strSql;
}



std::string
RDbSQLAdapter::getUpdateSampleCorrStateSQL(const std::string &strId, const std::string &strState, const std::string &strCondState)
{
	std::string strSql;
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		strSql = PubOpt::StringOpt::StringFormat(
			g_strCorrUpdateSampleCorrStateSQL.c_str(),
			strState.c_str(), strId.c_str(), strCondState.c_str());
		return strSql;
	}

	strSql = PubOpt::StringOpt::StringFormat(
		g_strCorrUpdateSampleCorrStateSvr2SQL.c_str(),
		mRdbNameSpace.c_str(),strState.c_str(), strId.c_str(), strCondState.c_str());
	return strSql;
}

std::string
RDbSQLAdapter::getModelSampleCorrSQL()
{
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		return g_strModelSampleCorrSQL;
	}

	std::string strSql = PubOpt::StringOpt::StringFormat(
		g_strModelSampleCorrSvr2SQL.c_str(), mRdbNameSpace.c_str());
	return strSql;	
}


std::string
RDbSQLAdapter::GetVersionSQL()
{
	if (mRdb != SAMPLESELE_SQLSERVER)
	{
		return g_strInsertVersionSQL;
	}
	return "";
}
