/*******************************************************************************
* Copyright（C）,2010-2015,DTXY Tech .Co.Ltd;
* 文 件 名: RDbOperationComplex.cpp
* 文件描述: 关系数据库操作类
*  作  者 : %林晓雨%，
* 创建日期: 2015-5-26 14:52:20
*******************************************************************************/

#include "RDbOperationComplex.h"
#include "public_function_library.h"

RDbOperationComplex::RDbOperationComplex()
{
    mQtOpt = NULL;
}
RDbOperationComplex::RDbOperationComplex(RsdbAdapter * QtOpt)
{
    mQtOpt = QtOpt;
}
RDbOperationComplex::~RDbOperationComplex(void)
{
}


bool 
RDbOperationComplex::stmtPrepare(const std::string &classname, const std::string &str_sql)
{
    bool nErr = mQtOpt->QtQuerySelect(str_sql);
    if (!nErr)
    {
        Aos_Assert_S(PubOpt::StringOpt::StringFormat("Prepare %s SQL ERROR: %s",  classname.c_str(), mQtOpt->GetErrorMessage().c_str()).c_str());
        return false;
    }
    return true;
}

void
RDbOperationComplex::stmtCloseStream()
{
    mQtOpt->SQLStmtCloseStream();
}


bool
RDbOperationComplex::stmtTransCommit(const std::string &classname)
{
    bool nErr = mQtOpt->QtCommit();
    if (!nErr)
    {
        Aos_Assert_S(PubOpt::StringOpt::StringFormat("Commit %s SQL ERROR: %s",
                                                     classname.c_str(), mQtOpt->GetErrorMessage().c_str()).c_str());
        return false;
    }
    return true;
}
bool RDbOperationComplex::stmtTransRollback(const std::string &classname)
{
    bool nErr = mQtOpt->QtRollback();
    if (!nErr)
    {
        Aos_Assert_S(PubOpt::StringOpt::StringFormat("Rollback %s SQL ERROR: %s",
                                                     classname.c_str(), mQtOpt->GetErrorMessage().c_str()).c_str());
        return false;
    }
    return true;
}
bool 
RDbOperationComplex::stmtHandPrepare(const std::string &classname, const std::string &str_sql)
{
    //bool nErr = SINGLETON(RsdbAdapter)->SQLStmtHandPrepare(buffer_size,str_sql);// 绑定查询SQL语句
    if (mQtOpt->m_query->isActive())
    {
        mQtOpt->QtQueryClear();
    }
    bool nErr = mQtOpt->QtQueryPrepare(str_sql);
    if (!nErr)
    {
        Aos_Assert_S(PubOpt::StringOpt::StringFormat("HandPrepare %s SQL ERROR: %s",
                                                     classname.c_str(), mQtOpt->GetErrorMessage().c_str()).c_str());
        return false;
    }
    return true;
}
bool 
RDbOperationComplex::stmtHandTransaction(const std::string &classname)
{
    bool nErr = mQtOpt->QtTransaction();
    if (!nErr)
    {
        Aos_Assert_S(PubOpt::StringOpt::StringFormat("HandTransaction %s SQL ERROR: %s",
                                                     classname.c_str(), mQtOpt->GetErrorMessage().c_str()).c_str());
        return false;
    }
    return true;
}
bool
RDbOperationComplex::stmtHandSubmit(const std::string &classname) 
{
    bool nErr;
    //nErr = stmtHandFlush(classname);
    nErr = stmtTransCommit(classname);
    return nErr;
}


void
RDbOperationComplex::stmtHandCloseStream(const std::string &classname)
{
    //bool nErr = SINGLETON(RsdbAdapter)->SQLStmtHandCloseStream();
    /*if (SINGLETON(RsdbAdapter)->m_query->isActive())
    {
        SINGLETON(RsdbAdapter)->QtQueryClear();
    }*/
    mQtOpt->QtQueryClear();
}
