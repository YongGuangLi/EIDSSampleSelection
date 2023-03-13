/*******************************************************************************
* Copyright（C）,2016-2021,TacKer Tech .Co.Ltd;
* 文 件 名: RsdbAdapter.h
* 文件描述: 关系数据库通用操作接口类
*  作  者 : 王凯，15802613961
* 创建日期: 2016-9-28 15:01:25
*******************************************************************************/

#ifndef __RSDB_ADAPTER_H__
#define __RSDB_ADAPTER_H__

//#include "singleton.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStringList>
#include <QTime>
#include <QDate>
#include <QVariantList>
#include <QSqlRecord>
#include <QSqlDriver>

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdarg.h>

//using namespace std;
#define OTL_ODBC // Compile OTL 4/ODBC
//#define OTL_ORA9I
#define OTL_STL
#define OTL_STREAM_READ_ITERATOR_ON
#define OTL_STREAM_POOLING_ON


#define OTL_MAX_LONG_SIZE 10000*1024

#define HELA_QT_DEFAULT_CONNECTION			"qt_sql_default_connection"
#define SQL_SERVERCE      "SQLSERVER" 
#define ORACLE			  "ORACLE"
#define MYSQL			  "MYSQL"
#define StaticBuff		1

#define MAX_STREAM_BUFFER_SIZE                  50

// 数据库连接信息
typedef struct DBServerInfo
{
	std::string strUserName;        //数据库用户名
	std::string strPasswd;          //数据库密码
	std::string strSessionName;     //会话名
	std::string strRsdbType;
	std::string strIp;
	int         iPort;    //端口号
}*P_DB_SERVER_INFO;

class RsdbAdapter
{
private:
    std::string mConnName;
public:
    RsdbAdapter(void);
    RsdbAdapter(const std::string &sId);
    ~RsdbAdapter(void);
public:

	std::string					m_strErrorMessage;

	std::string					m_strRsdbType;

	int m_stream_buffer_size;

public:
	QSqlQuery *m_query;
	QSqlDatabase m_rsdb;
	std::string	 m_ConnName;
	bool		 m_IsConn;
	//QSqlQuery db22;
public:
	bool QtConnect(const DBServerInfo &stServerInfo);

	bool QtIsConnect();

	void QtDisConnect();

	bool QtQuerySelect(const std::string &strSQL);
	bool QtQueryPrepare(const std::string &strSQL);
	bool QtQueryPrepare(const QString &strSQL);
	bool QtExec();
	std::string QtErr();
	bool QtExecBatch();
	bool QtTransaction();
	bool QtCommit();
	bool QtRollback();
    void QtbindValue(int ipos,const QVariant &val);
	void QtbindOutValue( int ipos,const QVariant &val );
	std::string GetOutputStrBoundValueByPos(const int &nPos);
	//************************************
	// Method:    QtQueryClear
	// FullName:  RsdbAdapter::QtQueryClear
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void QtQueryClear();

	bool QtGetResultIsValid();


	std::string GetErrorMessage();

    bool SQLDirectExecute(const std::string &strSQL);

    bool  SQLStmtFetch();

    void SQLStmtCloseStream();

    bool SQLStmtHandPrepare(const int buffer_size, const std::string &str_sql);

    bool SQLStmtHandFlush();

    int  SQLStmtHandFetch();

    bool SQLStmtHandCloseStream();

	void SetStreamBufferSize(int buffer_size);
    int	 GetStreamBufferSize();
private:
	std::string StringFormat(const char* pszFormat, ...);
	
};

#endif//__RSDB_ADAPTER_H__
