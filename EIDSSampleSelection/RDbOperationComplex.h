/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: RDbOperation.h
* 文件描述: 关系数据库操作类
*  作  者 : %林晓雨%，
* 创建日期: 2015-5-26 14:47:28
*******************************************************************************/

#ifndef __RDBOPERATIONCOMPLEX_H__
#define __RDBOPERATIONCOMPLEX_H__

#include <string>
#include "AlarmLog.h"
#include "RDbHead.h"
#include "RsdbAdapter.h"
#define in1_SIZE 50
#define ROW_COUNT 2000
#define MAX_PROC_RESULT_LENGTH                  1024
class RDbOperationComplex
{
public:
	std::string mStrErrorMessage;  
	RsdbAdapter * mQtOpt;

	RDbOperationComplex();
	RDbOperationComplex(RsdbAdapter * QtOpt);

	~RDbOperationComplex();
	/* 
	 * 功能描述:   执行查询SQL语句
	 * 输入参数: 无
	 * 输出参数: 无
	 * 返回值: true(成功)、false(失败)
	*/
	void stmtCloseStream();

	/* 
	 * 功能描述:  提交数据
	 * 输入参数: 无
	 * 输出参数: 无
	 * 返回值: true(成功)、false(失败)
	*/
	bool stmtTransCommit(const std::string &classname);
	bool stmtTransRollback(const std::string &classname);
	/* 
	 * 功能描述:  绑定查询SQL语句
	 * 输入参数: 无
	 * 输出参数: 无
	 * 返回值: true(成功)、false(失败)
	*/
	bool stmtPrepare(const std::string &classname, const std::string &str_sql);

/*******************************************************************************
* 函 数 名: 
* 函数描述: 批量提交语句绑定
* 参数说明: 
*    入 参: 
*    出 参: 
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : %王凯%，15802613961
* 创建日期: 2016-12-13 10:06:52
*******************************************************************************/
	bool stmtHandPrepare(const std::string &classname, const std::string &str_sql);

	bool stmtHandTransaction(const std::string &classname);


/*******************************************************************************
* 函 数 名: 
* 函数描述: 刷新并提交数据
* 参数说明: 
*    入 参: 
*    出 参: 
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : %王凯%，15802613961
* 创建日期: 2016-12-22 16:15:20
*******************************************************************************/
	bool stmtHandSubmit(const std::string &classname); 
/*******************************************************************************
* 函 数 名: 
* 函数描述: 关闭流
* 参数说明: 
*    入 参: 
*    出 参: 
* 返 回 值:
*    成 功:
*    失 败:	
*  作  者 : %王凯%，15802613961
* 创建日期: 2016-12-13 10:10:48
*******************************************************************************/
	void stmtHandCloseStream(const std::string &classname);
};
#endif
