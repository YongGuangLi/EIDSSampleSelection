/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: ServiceSelectionConfig.cpp
* 文件描述: 耗差性能计算配置文件管理类
*  作  者 : %林晓雨%，
* 创建日期: 2015-5-26 11:04:37
*******************************************************************************/
#include "ServiceSelectionConfig.h"

#include "Util.h"
#include "AlarmLog.h"
#include "load_config.h"
#include "SelectionDef.h"
#include "public_function_library.h"

IMPLEMENT_SINGLETON(ServiceSelectionConfig)

ServiceSelectionConfig::ServiceSelectionConfig(void)
: 
m_pConfigOpt(NULL),
mModeType(eSampleSelection),
mOpenDistributed(-1)
{
    m_pConfigOpt = new LoadConfig();
}

ServiceSelectionConfig::~ServiceSelectionConfig(void)
{
    if (NULL != m_pConfigOpt)
    {
        delete m_pConfigOpt;
        m_pConfigOpt = NULL;
    }
}

bool ServiceSelectionConfig::initConfig(const std::string &strFname)
{
    if (!m_pConfigOpt->ParseConfig(strFname))
    {
        return false;
    }
	 
	//std::string strExeFile = Util::GetExeFileName();
	//if (strExeFile != "EIDSSampleSelection.exe")
	std::string strType = GetType();
	if (strType == SAMPLE_BASE_TYPE_CORRANALYSIS)
	{
		mModeType = eSampleCorrAnalysis;   
	}			  
	else
	{
		mModeType = eSampleSelection;
	}
    return true;
}

std::string 
ServiceSelectionConfig::GetType(void)   const
{
	std::string strType = 
		m_pConfigOpt->GetValueByKey(SAMPLE_BASE_CONFIG, SAMPLE_BASE_TYPE);
	if (strType.empty())
	{
		return SAMPLE_BASE_TYPE_SELECTION;
	}
	return strType;
}

std::string ServiceSelectionConfig::getRsdbType(void)   const
{
	std::string strType = 
		m_pConfigOpt->GetValueByKey(DATA_BASE, DATA_BASE_RSDB_TYPE);
	if (strType.empty())
	{
		return SAMPLESELE_ORACLE;
	}
	return strType;
}

std::string ServiceSelectionConfig::getRsdbTypeParmKey(void)  const
{
	std::string strType = getRsdbType();
	if (strType != SAMPLESELE_SQLSERVER)
	{
        return MYSQL_CONFIG;
	}
	return SQLSERVER_CONFIG;
}

std::string ServiceSelectionConfig::getSessionName(void)
{
    std::string strReturn = m_pConfigOpt->GetValueByKey(MYSQL_CONFIG, RDB_SESSION_NAME_KEY);
    return strReturn;
}

std::string ServiceSelectionConfig::getUserName(void)
{
    std::string strReturn = m_pConfigOpt->GetValueByKey(MYSQL_CONFIG, RDB_USER_NAME_KEY);
    return strReturn;
}

std::string ServiceSelectionConfig::getPassWD(void)
{
    std::string strReturn = m_pConfigOpt->GetValueByKey(MYSQL_CONFIG, RDB_PASSWD_KEY);
    return strReturn;
}

std::string ServiceSelectionConfig::getRsdbIp(void)
{
    std::string strReturn = m_pConfigOpt->GetValueByKey(MYSQL_CONFIG, IP1);

    return strReturn;
}

std::string ServiceSelectionConfig::getRsdbPort(void)
{
    std::string strReturn = m_pConfigOpt->GetValueByKey(MYSQL_CONFIG, PORT);
    return strReturn;
}

string ServiceSelectionConfig::getXdbIp()
{
    std::string strReturn = m_pConfigOpt->GetValueByKey(XDB_CONFIG, IP1);
    return strReturn;
}

string ServiceSelectionConfig::getXdbPort()
{
    std::string strReturn = m_pConfigOpt->GetValueByKey(XDB_CONFIG, PORT);
    return strReturn;
}

std::string ServiceSelectionConfig::getNameSpace(void)	const
{
	std::string strKey = getRsdbTypeParmKey();
	std::string strNameSpace = 
		m_pConfigOpt->GetValueByKey(strKey, RDB_NAMESPACE_KEY);
	if (strNameSpace.empty()) return "";
	return strNameSpace;
}

std::string ServiceSelectionConfig::getLogPath(void)
{
    std::string strPath = m_pConfigOpt->GetValueByKey(LOG_CONFIG, LOG_PATH_KEY);
    if (strPath.empty())
    {
        strPath = LOG_PATH_DEFAULT_VALUE;
    }
    return strPath;
}

bool ServiceSelectionConfig::isShowLog(void)
{
    std::string strIsEnable = m_pConfigOpt->GetValueByKey(LOG_CONFIG, LOG_IS_SHOW);
    if ("1" != strIsEnable)
    {
        return false;
    }
    return true;
}


ServiceSelectionConfig::E 
ServiceSelectionConfig::getModeType(void) const
{
	return mModeType;
}  

std::string 
ServiceSelectionConfig::getBaseKey(void) const
{
	std::string strBaseKey;
	if (mModeType == eSampleSelection)
	{
		return PubOpt::StringOpt::StringFormat(SAMPLESELE_CONFIG, SAMPLE_BASE_CONFIG);
	}
	return PubOpt::StringOpt::StringFormat(SAMPLECORR_CONFIG, SAMPLE_BASE_CONFIG);
}




std::string
ServiceSelectionConfig::getServiceName() 
{	
	std::string strBaseKey = getBaseKey();
	std::string strServiceName = m_pConfigOpt->GetValueByKey(strBaseKey, SAMPLE_PARM_SERVICE_NAME);
	if (strServiceName.empty())
	{
		E type = getModeType();
		if (type == ServiceSelectionConfig::eSampleSelection)
		{
			strServiceName = SAMPLESELE_SERVICE_NAME;
		}
		else
		{
			strServiceName = SAMPLECORR_SERVICE_NAME;
		}
	}
	return strServiceName;
}

std::string
ServiceSelectionConfig::getServiceDisplayName() const
{
	std::string strBaseKey = getBaseKey();
	std::string name = m_pConfigOpt->GetValueByKey(strBaseKey, SAMPLE_PARM_SERVICE_DISPLAY_NAME);
	if (name.empty())
	{
		E type = getModeType();
		if (type == eSampleSelection)
		{
			name = SAMPLESELE_SERVICE_NAME;
		}
		else
		{
			name = SAMPLECORR_SERVICE_NAME;
		}
	}
	return name;
}


std::string ServiceSelectionConfig::getModeName(void)
{
	std::string strBaseKey = getBaseKey();
	std::string strModeName = m_pConfigOpt->GetValueByKey(strBaseKey, SAMPLE_BASE_MODE_NAME_KEY);
	if (strModeName.empty())
	{
		return SAMPLE_BASE_MODE_NAME_DEFAULT_VALUE;
	}
	return strModeName;
}


std::string 
ServiceSelectionConfig::getParmKey(void) const
{
	if (mModeType == eSampleSelection)
	{
		return PubOpt::StringOpt::StringFormat(SAMPLESELE_CONFIG, SAMPLE_PARM_CONFIG);
	}
	return PubOpt::StringOpt::StringFormat(SAMPLECORR_CONFIG, SAMPLE_PARM_CONFIG);
}


bool
ServiceSelectionConfig::openServiceAlarm() const
{
	std::string strParmKey = getParmKey();
	std::string name =  m_pConfigOpt->GetValueByKey(strParmKey, SAMPLE_FILE_OPEN_ALARM);
	if (name == "true")
	{
		return true;
	}
	return false;
}


std::string 
ServiceSelectionConfig::getVerionNumber() const
{
	std::string strParmKey = getParmKey();
	std::string versionNo = m_pConfigOpt->GetValueByKey(strParmKey, SAMPLE_VERSION_NUMBER);
	if (versionNo.empty())
	{
		return SAMPLE_VERSION_NUMBER_DEFVALUE;
	}
	return versionNo;
}

int ServiceSelectionConfig::getRtdbIsLongNameType(void) const
{
	std::string strValue = m_pConfigOpt->GetValueByKey(DATA_BASE, DATA_BASE_IS_LONG_NAME_KEY);
	if(strValue.empty())
	{
		return atoi(DATA_BASE_IS_LONG_NAME_DEFAULT_VALUE);
	}
	return atoi(strValue.c_str());
}


int
ServiceSelectionConfig::openDistributed()
{
    if (mOpenDistributed >= 0)
        return mOpenDistributed;

	std::string strParmKey = getParmKey();
	std::string strVal = m_pConfigOpt->GetValueByKey(strParmKey, SAMPLE_OPEN_DISTRIBUTED);
	if (strVal == "1")
	{
		mOpenDistributed = 1;
	}
	else
	{
		mOpenDistributed = 0;
	}

	strVal = getDistributedSets();
    if (strVal.empty())
        mOpenDistributed = 0;
	return mOpenDistributed;
}


std::string 
ServiceSelectionConfig::getDistributedSets() const
{
	std::string strParmKey = getParmKey();
	std::string strVal = m_pConfigOpt->GetValueByKey(strParmKey, SAMPLE_DISTRIBUTED_SETS);
	return strVal;
}
