#include "RsdbAdapter.h"
#include "AlarmLog.h"
#include "public_function_library.h"


RsdbAdapter::RsdbAdapter(void)
    :
      m_ConnName(HELA_QT_DEFAULT_CONNECTION),
      m_IsConn(false),
      m_strErrorMessage("")
{
    //	 otl_connect::otl_initialize();
    m_query = NULL;
}
RsdbAdapter::RsdbAdapter(const std::string &sId)
    :
      m_ConnName(sId),
      m_query(NULL),
      m_IsConn(false),
      m_strErrorMessage("")
{
    if (m_ConnName.empty())
    {
        m_ConnName = HELA_QT_DEFAULT_CONNECTION;
    }
}
RsdbAdapter::~RsdbAdapter(void)
{
    if(m_query == NULL)
    {
        delete m_query;
        m_query = NULL;
    }
}
void RsdbAdapter::SetStreamBufferSize(int buffer_size)
{
    if(buffer_size<=0||buffer_size>100000)
    {
        m_stream_buffer_size=50;
        return;
    }
    m_stream_buffer_size=buffer_size;
}
int RsdbAdapter::GetStreamBufferSize()
{
    return m_stream_buffer_size;
}



bool					  
RsdbAdapter::SQLDirectExecute(const std::string &strSQL)
{
    //如果SQL语句 、PL/SQL 块或存储过程调用中不含有任何绑定变量，则可以称之为静态的
    //m_query->prepare(QString::fromStdString(strSQL));
    m_query->exec(QString(strSQL.c_str()));
    if (m_query->lastError().isValid())
    {
        std::string error = std::string(m_query->lastError().text().toLocal8Bit());
        //m_query->lastError().text().toStdString();
        return false;
    }
    else
    {
        //qDebug()<<m_query->numRowsAffected();
        return true;
    }
    return false;
}


std::string
RsdbAdapter::GetErrorMessage()
{
    return m_strErrorMessage;
}



void
RsdbAdapter::SQLStmtCloseStream()
{
    m_query->clear();
}



std::string 
RsdbAdapter::StringFormat(const char* pszFormat, ...)
{
    std::string strRet;
    if (NULL == pszFormat)
    {
        return strRet;
    }
    char szTmp[1024] = {0};
    va_list val;
    va_start(val, pszFormat);
#ifdef WIN32
    if (0 > vsnprintf_s(szTmp, 1024, 1024, pszFormat, val))
#else
    if (0 > vsnprintf(szTmp, 1024, pszFormat, val))
#endif
    {
        return strRet;
    }
    va_end(val);
    strRet = static_cast<std::string>(szTmp);
    return strRet;
}




bool RsdbAdapter::QtConnect(const DBServerInfo &stServerInfo)
{
    qDebug()<<"Available drivers:";
    QStringList drivers=QSqlDatabase::drivers();
    foreach(QString driver,drivers)
        qDebug()<<driver;

    //arg(QString::fromStdString(stServerInfo.strPasswd))
    QString strConnName(m_ConnName.c_str());
    m_strRsdbType = PubOpt::StringOpt::StringUpper(stServerInfo.strRsdbType);
    if (SQL_SERVERCE == m_strRsdbType)
    {
        /*if(QSqlDatabase::contains(strConnName))
            m_rsdb = QSqlDatabase::addDatabase("QODBC");
        else */
        m_rsdb = QSqlDatabase::addDatabase("QODBC", strConnName);
        QString dsn = QString("DRIVER={SQL SERVER};\
                              SERVER=%1;\
                DATABASE=%2;\
        UID=%3;\
        PWD=%4;").arg(QString(stServerInfo.strIp.c_str()))\
        .arg(QString(stServerInfo.strSessionName.c_str()))\
                .arg(QString(stServerInfo.strUserName.c_str()))\
                .arg(QString(stServerInfo.strPasswd.c_str()));

        m_strErrorMessage = std::string(dsn.toLocal8Bit());
        Aos_WriteLog(m_strErrorMessage.c_str());
        m_rsdb.setDatabaseName(dsn);
    }
    else if(ORACLE == m_strRsdbType)
    {
        //if(QSqlDatabase::contains(strConnName))
        //	m_rsdb = QSqlDatabase::addDatabase("QOCI"); //QOCI
        //else
        m_rsdb = QSqlDatabase::addDatabase("QOCI", strConnName);

        m_rsdb.setHostName(QString(stServerInfo.strIp.c_str()));
        m_rsdb.setPort(stServerInfo.iPort);
        m_rsdb.setDatabaseName(QString(stServerInfo.strSessionName.c_str()));
        m_rsdb.setUserName(QString(stServerInfo.strUserName.c_str()));
        m_rsdb.setPassword(QString(stServerInfo.strPasswd.c_str()));

    } else if(MYSQL == m_strRsdbType)
    {
        m_rsdb = QSqlDatabase::addDatabase("QMYSQL",strConnName);
        m_rsdb.setHostName(QString(stServerInfo.strIp.c_str()));
        m_rsdb.setPort(stServerInfo.iPort);
        m_rsdb.setDatabaseName(QString(stServerInfo.strSessionName.c_str()));
        m_rsdb.setUserName(QString(stServerInfo.strUserName.c_str()));
        m_rsdb.setPassword(QString(stServerInfo.strPasswd.c_str()));
    }

    if (!m_rsdb.open())
    {
        //qDebug()<<m_Rdb.lastError().databaseText();
        m_strErrorMessage = std::string(m_rsdb.lastError().text().toLocal8Bit());
        Aos_WriteLog(m_strErrorMessage.c_str());
        return false;
    }

    m_IsConn = true;
    if (m_query != NULL)
        delete m_query;
    m_query = new QSqlQuery(m_rsdb);

    //m_strErrorMessage = std::string("Rtdb (QT) Connect Success");
    //Aos_WriteLog(m_strErrorMessage.c_str());
    return true;
}

bool RsdbAdapter::QtIsConnect()
{
    /*bool bStatue = m_rsdb.isOpen();
    if(!bStatue)
    {
        if(m_query != NULL)
        {
            delete m_query;
            m_query = NULL;
        }

    }
    return bStatue;*/

    if (!m_IsConn)
        return false;
    //if (m_rsdb.isValid()) return true;
    std::string strSql="select 1 from dual";
    if (SQLDirectExecute(strSql))
        return true;
    m_IsConn = false;
    return false;
}

void RsdbAdapter::QtDisConnect()
{
    /*if(m_query != NULL)
    {
        delete m_query;
        m_query = NULL;
    }
    m_rsdb.close();*/

    m_IsConn = false;
    if(m_query != NULL)
    {
        delete m_query;
        m_query = NULL;
    }
    m_strErrorMessage.clear();

    QString strConnName(m_ConnName.c_str());
    QSqlDatabase::removeDatabase(strConnName);
    m_rsdb.close();
}

bool RsdbAdapter::QtQuerySelect( const std::string &strSQL )
{
    //m_query->prepare(QString::fromStdString(strSQL));
    m_query->prepare(QString(strSQL.c_str()));
    m_query->exec();
    if (m_query->lastError().isValid())
    {
        //m_strErrorMessage = m_query->lastError().text().toStdString();
        m_strErrorMessage = std::string(m_query->lastError().text().toLocal8Bit());
        return false;
    }
    else
    {
        qDebug()<<m_query->numRowsAffected();
        return true;
    }
}
bool RsdbAdapter::QtQueryPrepare( const std::string &strSQL )
{
    //m_query->prepare(QString::fromStdString(strSQL));
    QString qstr = QString(strSQL.c_str());
    m_query->prepare(qstr);
    if (m_query->lastError().isValid())
    {
        //m_strErrorMessage = m_query->lastError().text().toStdString();
        m_strErrorMessage = std::string(m_query->lastError().text().toLocal8Bit());
        return false;
    }
    else
    {
        return true;
    }
}
bool RsdbAdapter::QtQueryPrepare( const QString &strSQL )
{
    m_query->prepare(strSQL);
    if (m_query->lastError().isValid())
    {
        //m_strErrorMessage = m_query->lastError().text().toStdString();
        m_strErrorMessage = std::string(m_query->lastError().text().toLocal8Bit());
        return false;
    }
    else
    {
        return true;
    }
}
std::string RsdbAdapter::QtErr()
{
    m_strErrorMessage = std::string(m_query->lastError().text().toLocal8Bit());
    return m_strErrorMessage;
}
bool RsdbAdapter::QtExec()
{
    bool is_ok;
    is_ok = m_query->exec();
    if (m_query->lastError().isValid())
    {
        m_strErrorMessage = std::string(m_query->lastError().text().toLocal8Bit());
    }
    return is_ok;
}
bool RsdbAdapter::QtExecBatch()
{
    bool is_ok;
    is_ok = m_query->execBatch();
    if (m_query->lastError().isValid())
    {
        //m_query->lastError().text();
        m_strErrorMessage = std::string(m_query->lastError().text().toLocal8Bit());
    }

    return is_ok;
}
bool RsdbAdapter::QtTransaction()
{
    //LINXIAOYU
    return true;
    bool is_ok = QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions);
    if(!is_ok)
        return true;
    return m_rsdb.transaction();
}
bool RsdbAdapter::QtCommit()
{
    return m_rsdb.commit();
}
bool RsdbAdapter::QtRollback()
{
    return m_rsdb.rollback();
}
bool RsdbAdapter::QtGetResultIsValid()
{
    if (!m_query->isActive())
        return false;
    return m_query->isValid();
}
bool
RsdbAdapter::SQLStmtFetch()
{
    /*if (!m_autoio.good()) return 0;
    return m_autoio.eof();*/
    return m_query->next();
}
std::string
RsdbAdapter::GetOutputStrBoundValueByPos(const int &nPos)
{
    QString strOutput = m_query->boundValue(nPos).toString();
    std::string strVal = strOutput.toStdString();
    return strVal;
}
void RsdbAdapter::QtbindOutValue( int ipos,const QVariant &val )
{
    //QString strInput(pszInput);
    m_query->bindValue(ipos, val, QSql::Out);
}

void RsdbAdapter::QtbindValue( int ipos,const QVariant &val )
{
    m_query->bindValue(ipos,val);
}
void RsdbAdapter::QtQueryClear()
{
    m_query->clear();
}
