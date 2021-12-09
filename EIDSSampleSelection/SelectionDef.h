/*******************************************************************************
* Copyright（C）,2010-2016,DTXY Tech .Co.Ltd;
* 文 件 名: SelectionDef.h
* 文件描述: 报警宏定义
*  作  者 : %林晓雨%
* 创建日期: 2016-7-26 10:15:12
*******************************************************************************/

#ifndef __SELECTIONDEF_H__
#define __SELECTIONDEF_H__

#define SAMPLESELE_ERROR_CHECK_PRETREAD_ID			"此甄别测点[%s]不包含在tb_pub_point POINT_KIND = 0中;"
#define SAMPLESELE_ERROR_PARSEEXPRESSION			"公式解析失败"
#define	SAMPLESELE_ERROR_PUBSETINFO					"机组指标为空"
#define	SAMPLESELE_ERROR_INDEXINFO					"耗差指标为空"
#define	SAMPLESELE_ERROR_POINTSOURCE				"实时数据库全点名为空"
#define SAMPLESELE_ERROR_RTDB_CONF					"实始化实时数据库失败,请检查配置文件%s:"

#define SAMPLESELE_ERROR_STEADY						"tb_pub_point中无D%s_steady指标配置."

#define IDS_INDEX_CONFIG_ERROR						"计算指标[指标编号:%s]出错,可能是变量串中的对象不存在或者计算公式配置错误造成,请检查指标公式配置,该指标值已用其默认值代替 \n [指标计算公式:]%s \n [指标变量串赋值:]%s"
#define IDS_PROGRAM									"调用计算引擎申请计算错误,公式验证错误,请检查指标的配置公式,ID:;"
#define IDS_CALCULATE								"调用计算引擎计算指标错误 指标ID:%s;"
#define IDS_INDEX_CONFVAR_ERROR						"计算指标[指标编号:%s]出错,可能是变量串中的对象不存在或者计算公式配置错误造成,请检查指标公式配置,该指标值已用其默认值代替 \n [指标计算公式:]%s \n [指标变量串:]%s"
#define IDS_NOT_CONFIG_SETS							"指标没有配置机组号,指标编号:%s;"


#define SAMPLECORR_SERVICE_NAME						"EIDSSampleCorrAnalysis"
#define SAMPLESELE_SERVICE_NAME						"EIDSSampleSelection"

#define SAMPLESELE_ORACLE							"Oracle"
#define SAMPLESELE_SQLSERVER						"SqlServer"

#endif

