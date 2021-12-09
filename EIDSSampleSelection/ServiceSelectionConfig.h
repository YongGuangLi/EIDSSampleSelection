/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名:  ServiceSelectionConfig.cpp
* 文件描述: 耗差性能计算配置文件管理类
*  作  者 : 林晓雨，
* 创建日期: 2015-05-12 16:03:33
*******************************************************************************/
#ifndef __SERVICESELECTIONCONFIG_H__
#define __SERVICESELECTIONCONFIG_H__

#include "singleton.h"

#define SYSDIR_CONFIG_FILE							("xy_eids_cfg.cfg")
#define SAMPLESELE_CONFIG_FILE						("eids_sample_selection_config.cfg")
#define RTDB_CONFIG_FILE							("rtdb.ini")

#define SAMPLESELE_CONFIG							"SampleSelection%s"
#define SAMPLECORR_CONFIG							"SampleCorrAnalysis%s"

#define SAMPLE_BASE_CONFIG							"Base"
#define SAMPLE_BASE_TYPE							"Type"
#define SAMPLE_BASE_TYPE_SELECTION					"Selection"
#define SAMPLE_BASE_TYPE_CORRANALYSIS				"CorrAnalysis"
#define SAMPLE_BASE_MODE_NAME_KEY					"ModeName"
#define SAMPLE_BASE_MODE_NAME_DEFAULT_VALUE			"SampleSelection"

#define MYSQL_CONFIG								"MYSQL"
#define SQLSERVER_CONFIG							"SQLServer"
#define RDB_SESSION_NAME_KEY						"SessionName"
#define RDB_USER_NAME_KEY							"UserName"
#define RDB_PASSWD_KEY								"PassWD"
#define RDB_NAMESPACE_KEY							"NameSpace"
#define RDB_SESSION_NAME_DEFAULT_VALUE				"ORCL190"
#define RDB_USER_NAME_DEFAULT_VALUE					"ECD"
#define RDB_PASSWD_DEFAULT_VALUE					"ECD"
#define PORT									    "Port"
#define IP1                                          "Ip"

#define LOG_CONFIG									"LogPath"
#define LOG_PATH_KEY								"FilePath"
#define LOG_IS_SHOW									"IsShow"
#define LOG_PATH_DEFAULT_VALUE						"D:/log"

#define SAMPLE_PARM_CONFIG							"Parm"
#define SAMPLE_PARM_SERVICE_NAME					"ServiceName"
#define SAMPLE_PARM_SERVICE_DISPLAY_NAME			"ServiceDisplayName"  

#define SAMPLE_FILE_OPEN_ALARM						"OpenServiceAlarm"
#define SAMPLE_VERSION_NUMBER						"VersionNumber"
#define SAMPLE_OPEN_DISTRIBUTED						"OpenDistributed"
#define SAMPLE_DISTRIBUTED_SETS						"DistributedSets"
												
#define SAMPLE_VERSION_NUMBER_DEFVALUE				"V6.0.20160430"

#define DATA_BASE									"DataBase"
#define	DATA_BASE_IS_LONG_NAME_KEY					"Is_Long_Name"
#define DATA_BASE_RSDB_TYPE							"RSDB_TYPE"

#define	DATA_BASE_IS_LONG_NAME_DEFAULT_VALUE		"0"	


#include <string>

class LoadConfig;

class ServiceSelectionConfig
{
    DECLARE_SINGLETON_INIT(ServiceSelectionConfig)
public:
	enum E
	{
		eSampleSelection = 0,
		eSampleCorrAnalysis = 1

	};
    // 功能描述：初始化公共配制信息
    bool initConfig(const std::string &strFname);
public:
    // 功能描述: 获取OCI连接会话名称
    std::string getSessionName(void);
    // 功能描述: 获取OCI连接用户名
    std::string getUserName(void);
    // 功能描述: 获取OCI连接密码
    std::string getPassWD(void);

    std::string getRsdbIp(void);

    std::string getRsdbPort(void);


	bool isSysPath() {return false;}
public:
    // 功能描述：获取日志路径
    std::string getLogPath(void);
    // 功能描述: 获取日志开关
    bool isShowLog(void);
	// 功能描述: log文件前缀
	std::string getModeName(void);
	// 功能描述: 开启服务告警功能 
	bool openServiceAlarm() const;
	// 功能描述: 获取版本
	std::string getVerionNumber() const;
	// 功能描述: 是否是短点名
	int getRtdbIsLongNameType(void) const;
	// 功能描述: 获取关系数据库
	std::string getRsdbType(void) const;
	// 功能描述: sql server数据库命名空间
	std::string getNameSpace(void) const;
	// 功能描述: 获取服务注册名
	std::string getServiceName(void);
	// 功能描述: 获取服务注册描述
	std::string	getServiceDisplayName(void) const;
	// 功能描述: 获取服务模式
	ServiceSelectionConfig::E  getModeType(void) const;
	// 功能描述: 开启分布步部署服务
	int openDistributed();
	// 功能描述: 当OpenDistributed=1时，此属性才有效；当前服务处理的机组集合,多个','号分隔
	std::string getDistributedSets() const;
	// 功能描述: 获取类型
	std::string GetType(void)   const;
private:
	std::string getRsdbTypeParmKey(void) const;

	std::string getBaseKey(void) const;

	std::string getParmKey(void) const;
private:
    LoadConfig* m_pConfigOpt;           // 配制文件操作对象
	E			 mModeType;
	int			 mOpenDistributed;
};

#endif
