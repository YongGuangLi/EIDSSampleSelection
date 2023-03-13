/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: RDbOperationSimple.cpp
* 文件描述: 关系数据库简单操作实现类
*  作  者 : %林晓雨%，
* 创建日期: 2015-5-28 9:41:18
*******************************************************************************/

#include "RDbOperationSimple.h"

#include "Util.h"
#include "TypeDef.h"
#include "SelectionDef.h"
#include "RDbSQLAdapter.h"
#include "RDbOperationComplex.h"
#include "public_function_library.h"

IMPLEMENT_SINGLETON(RDbOperationSimple)

RDbOperationSimple::RDbOperationSimple(void)
:
mStrErrorMessage("")
{
}

RDbOperationSimple::~RDbOperationSimple(void)
{
}

std::string 
RDbOperationSimple::getSysGuid()
{	
    QString strRand = QUuid::createUuid().toString();
    strRand = strRand.remove('{');
    strRand = strRand.remove('}');
    return strRand.toStdString();
}


bool
RDbOperationSimple::deleteSampleTimeById(const std::string &strId)
{
    //初始删选记录
    std::string strSql = SINGLETON(RDbSQLAdapter)->getDeleteSampleTimeSQL(strId);
    bool nErr = Util::SQLDirectExecute(strSql);// 绑定查询SQL语句
    if (!nErr)
    {
        mStrErrorMessage = PubOpt::StringOpt::StringFormat("Prepare deleteSampleTime SQL ERROR: %s", strSql.c_str());
        Aos_Assert_S(mStrErrorMessage.c_str());
        return false;
    }

    //手工筛选条件
//    strSql = SINGLETON(RDbSQLAdapter)->getDeleteSampleTimeConSQL(strId);
//    nErr = Util::SQLDirectExecute(strSql);// 绑定查询SQL语句
//    if (!nErr)
//    {
//        mStrErrorMessage = PubOpt::StringOpt::StringFormat("Prepare deleteSampleTimeCon SQL ERROR: %s",strSql.c_str());
//        Aos_Assert_S(mStrErrorMessage.c_str());
//        return false;
//    }
	return true;
}

bool
RDbOperationSimple::updateSampleTimeStateToZero(const std::string &Id)
{
    //执行静态的SQL语句
    //状态(0:计算完成 1:计算中 2:新插入 3:计算失败 4:未计算)
    std::string strSql = SINGLETON(RDbSQLAdapter)->getUpdateModelSampleTimeState0SQL(Id);
    bool nErr = Util::SQLDirectExecute(strSql);// 绑定查询SQL语句
    if (!nErr)
    {
        mStrErrorMessage = PubOpt::StringOpt::StringFormat("Prepare updateSampleTimeStateToZero SQL ERROR: %s",strSql.c_str());
        Aos_Assert_S(mStrErrorMessage.c_str());
        return false;
    }
	return true;
}

bool					  
RDbOperationSimple::updateSampleTimeStateToOne(const std::string &strSampleTimeId)
{
    //执行静态的SQL语句
    int iState = 1;
	std::string strSql = SINGLETON(RDbSQLAdapter)->getUpdateModelSampleTimeStateSQL(strSampleTimeId, iState);
    bool nErr = Util::SQLDirectExecute(strSql);// 绑定查询SQL语句
    if (!nErr)
    {
        mStrErrorMessage = PubOpt::StringOpt::StringFormat("Prepare updateSampleTimeStateToOne SQL ERROR: %s",  strSql.c_str());
        Aos_Assert_S(mStrErrorMessage.c_str());
        return false;
    }
	return true;
}


bool					  
RDbOperationSimple::updateSampleTimeStateToSix(const std::string &strSampleTimeId)
{
	//执行静态的SQL语句
	//状态(0:计算完成 1:计算中 2:新插入 3:计算失败 4:未计算 5:初始化 6：筛选条件过严)
	int iState = 6;
	std::string strSql = SINGLETON(RDbSQLAdapter)->getUpdateModelSampleTimeStateSQL(strSampleTimeId, iState);
    bool nErr = Util::SQLDirectExecute(strSql);// 绑定查询SQL语句
    if (!nErr)
    {
        mStrErrorMessage = PubOpt::StringOpt::StringFormat("Prepare updateSampleTimeStateToSix SQL ERROR: %s",strSql.c_str());
        Aos_Assert_S(mStrErrorMessage.c_str());
        return false;
    }
	return true;
}


bool					  
RDbOperationSimple::updateSampleTimeStateToThree(const std::string &strSampleTimeId)
{
	//执行静态的SQL语句
	//状态(0:计算完成 1:计算中 2:新插入 3:计算失败 4:未计算 5:初始化 6：筛选条件过严)
	int iState = 3;
    std::string strSql = SINGLETON(RDbSQLAdapter)->getUpdateModelSampleTimeStateSQL(strSampleTimeId, iState);
    bool nErr = Util::SQLDirectExecute(strSql);// 绑定查询SQL语句
    if (!nErr)
    {
        mStrErrorMessage = PubOpt::StringOpt::StringFormat("Prepare updateSampleTimeStateToThree SQL ERROR: %s", strSql.c_str());
        Aos_Assert_S(mStrErrorMessage.c_str());
        return false;
    }
	return true;
}

bool
RDbOperationSimple::deleteSampleTimeState2ByModelId(const std::string &strModelId)
{
    //手工筛选条件
    std::string strSql = SINGLETON(RDbSQLAdapter)->getDeleteSampleTimeConStateSQL(strModelId);
    bool nErr = Util::SQLDirectExecute(strSql);// 绑定查询SQL语句
    if (!nErr)
    {
        mStrErrorMessage = PubOpt::StringOpt::StringFormat("Prepare DeleteSampleTimeConState SQL ERROR: %s", strSql.c_str());
        Aos_Assert_S(mStrErrorMessage.c_str());
        return false;
    }

    //诊断模型样本时间段
    strSql = SINGLETON(RDbSQLAdapter)->getDeleteSampleTimeStateSQL(strModelId);
    nErr = Util::SQLDirectExecute(strSql);// 绑定查询SQL语句
    if (!nErr)
    {
        mStrErrorMessage = PubOpt::StringOpt::StringFormat("Prepare deleteSampleTimeState2ByModelId SQL ERROR: %s",  strSql.c_str());
        Aos_Assert_S(mStrErrorMessage.c_str());
        return false;
    }
	return true;
}

bool
RDbOperationSimple::updateCorrProcessingStatus(const std::string &strModelId)
{
	// 0:计算完成  1:计算中  2:计算失败  3:未计算(需要计算)
	bool rslt = updateSampleTimeCorrStatePriv("1", strModelId);
	if (!rslt) return false;
	//状态(0:未计算 1:计算完成 2:计算中 3:计算失败 4:数据相关性分析完成  5:数据相关性分析失败  6:数据相关性分析计算中)
	return updateSampleCorrStatePriv(strModelId, "6", "1");
}

bool
RDbOperationSimple::updateCorrFailedStatus(const std::string &strModelId)
{
	// 0:计算完成  1:计算中  2:计算失败  3:未计算(需要计算)
	bool rslt = updateSampleTimeCorrStatePriv("2", strModelId);
	if (!rslt) return false;
	//状态(0:未计算 1:计算完成 2:计算中 3:计算失败 4:数据相关性分析完成  5:数据相关性分析失败  6:数据相关性分析计算中)
	return updateSampleCorrStatePriv(strModelId, "5", "6");
}

bool
RDbOperationSimple::updateCorrFinishStatus(const std::string &strModelId)
{
  	// 0:计算完成  1:计算中  2:计算失败  3:未计算(需要计算)
	bool rslt = updateSampleTimeCorrStatePriv("0", strModelId);
	if (!rslt) return false;
	//状态(0:未计算 1:计算完成 2:计算中 3:计算失败 4:数据相关性分析完成  5:数据相关性分析失败  6:数据相关性分析计算中)
	return updateSampleCorrStatePriv(strModelId, "4", "6");
}


bool					  
RDbOperationSimple::updateSampleTimeCorrStatePriv(const std::string &strCorrState, const std::string &strModelId)
{	
//	if (!Util::otlIsConnect())
//        return false;

	//执行静态的SQL语句
	// 0:计算完成  1:计算中  2:计算失败  3:未计算(需要计算)
//	std::string strSql = SINGLETON(RDbSQLAdapter)->getUpdateSampleTimeCorrStateSQL(strCorrState, strModelId);
//	bool nErr = SINGLETON(OtlAdapter)->SQLDirectExecute(strSql);// 绑定查询SQL语句
//	if (!nErr)
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat("Prepare updateSampleTimeCorrStatePriv SQL ERROR: %s",
//			SINGLETON(OtlAdapter)->GetErrorMessage().c_str()).c_str();
//		Aos_Assert_S(mStrErrorMessage.c_str());
//		return false;
//	}
	return true;
}


bool
RDbOperationSimple::deleteCorrAnalysisData(const std::string &strModelId)
{
//	if (!Util::otlIsConnect())
//        return false;

	//执行静态的SQL语句
//	std::string strSql = SINGLETON(RDbSQLAdapter)->getDeleteCorrAnalysisDataSQL(strModelId);
//	bool nErr = SINGLETON(OtlAdapter)->SQLDirectExecute(strSql);// 绑定查询SQL语句
//	if (!nErr)
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat("Prepare deleteCorrAnalysisData SQL ERROR: %s",
//			SINGLETON(OtlAdapter)->GetErrorMessage().c_str()).c_str();
//		Aos_Assert_S(mStrErrorMessage.c_str());
//		return false;
//	}
	return true;
}

bool					  
RDbOperationSimple::updateSampleCorrStatePriv(const std::string &strModelId, const std::string &strState,  const std::string &strCondState)
{	
//	if (!Util::otlIsConnect())
//        return false;

	//执行静态的SQL语句
	//状态(0:未计算 1:计算完成 2:计算中 3:计算失败 4:数据相关性分析完成  5:数据相关性分析失败  6:数据相关性分析计算中)
//	std::string strSql = SINGLETON(RDbSQLAdapter)->getUpdateSampleCorrStateSQL(strModelId, strState, strCondState);
//	bool nErr = SINGLETON(OtlAdapter)->SQLDirectExecute(strSql);// 绑定查询SQL语句
//	if (!nErr)
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat("Prepare updateSampleCorrState SQL ERROR: %s",
//			SINGLETON(OtlAdapter)->GetErrorMessage().c_str()).c_str();
//		Aos_Assert_S(mStrErrorMessage.c_str());
//		return false;
//	}
	return true;
}




bool
RDbOperationSimple::SubmitToControlProcessService()
{
	return UpdateVersionNumber();
}

bool
RDbOperationSimple::UpdateVersionNumber()
{
//	if (!Util::otlIsConnect())
//        return false;

    std::string strSql = SINGLETON(RDbSQLAdapter)->GetVersionSQL();

	//调用存储过程时，buffer_size缓冲区设小或等于1时，v_result存储过程返回值变量才能读取"true";
	int buffer_size = 1;
//	bool nErr = SINGLETON(OtlAdapter)->SQLStmtPrepare(buffer_size, strSql);// 绑定查询SQL语句
//	if (!nErr)
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat("UpdateVersionNumber SQL ERROR:%s",
//			SINGLETON(OtlAdapter)->GetErrorMessage().c_str()).c_str();
//		return false;
//	}

//	std::string strServiceName = SINGLETON(ServiceSelectionConfig)->getServiceName();
//	nErr = SINGLETON(OtlAdapter)->BindInputByName(strServiceName);
//	if (!nErr)
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat("UpdateVersionNumber SQL ERROR:%s",
//			SINGLETON(OtlAdapter)->GetErrorMessage().c_str()).c_str();
//		return false;
//	}

//	std::string strVersionNo = SINGLETON(ServiceSelectionConfig)->getVerionNumber();
//	nErr = SINGLETON(OtlAdapter)->BindInputByName(strVersionNo);
//	if (!nErr)
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat("UpdateVersionNumber SQL ERROR:%s",
//			SINGLETON(OtlAdapter)->GetErrorMessage().c_str()).c_str();
//		return false;
//	}

//	std::string logFile = SINGLETON(ServiceSelectionConfig)->getLogPath();
//	nErr = SINGLETON(OtlAdapter)->BindInputByName(logFile);
//	if (!nErr)
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat("UpdateVersionNumber SQL ERROR:%s",
//			SINGLETON(OtlAdapter)->GetErrorMessage().c_str()).c_str();
//		return false;
//	}

    std::string strResult;
//	nErr = SINGLETON(OtlAdapter)->BindOutputByName(strResult);
//	if (!nErr)                                                  // 执行查询SQL语句
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat("UpdateVersionNumber SQL ERROR:%s",
//			SINGLETON(OtlAdapter)->GetErrorMessage().c_str()).c_str();
//		return false;
//	}

//	nErr = SINGLETON(OtlAdapter)->OtlTransCommit();
//	if (!nErr)
//	{
//		Aos_Assert_S(PubOpt::StringOpt::StringFormat("Commit UpdateVersionNumber SQL ERROR: %s",
//			SINGLETON(OtlAdapter)->GetErrorMessage().c_str()).c_str());
//		return false;
//	}

//	nErr = SINGLETON(OtlAdapter)->SQLStmtCloseStream();
//	if (!nErr)                                                  // 执行查询SQL语句
//	{
//		mStrErrorMessage = PubOpt::StringOpt::StringFormat("Execute UpdateVersionNumber SQL ERROR: %s",
//			SINGLETON(OtlAdapter)->GetErrorMessage().c_str());
//		Aos_Assert_S(mStrErrorMessage.c_str());
//		return false;
//	}

	if (strResult != "true")
	{
		mStrErrorMessage = PubOpt::StringOpt::StringFormat(
			"UpdateVersionNumber SQL ERROR: V_RESULT,%s;", 
			strResult.c_str());
		Aos_Assert_S(mStrErrorMessage.c_str());
		return false;
	}
	return true;
}
