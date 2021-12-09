#include <QCoreApplication>

#include "log.h"
#include "Util.h"
#include "AlarmLog.h"
#include "SelectionDef.h"
#include "ServiceSelection.h"
#include "ServiceSelectionConfig.h"
#include "public_function_library.h"


// Displayed name of the service
//#define SERVICE_DISPLAY_NAME     "EIDSSampleSelection"

// Service start options.
#define SERVICE_START_TYPE       SERVICE_DEMAND_START

// List of service dependencies - "dep1\0dep2\0\0"
#define SERVICE_DEPENDENCIES     ""

// The name of the account under which the service should run
#define SERVICE_ACCOUNT          NULL

// The password to the service account name
#define SERVICE_PASSWORD         NULL

#include <iostream>


bool initMain(void)
{
    std::string strPath = PubOpt::SystemOpt::GetCurExePath();

    if (!SINGLETON(ServiceSelectionConfig)->initConfig(strPath + SAMPLESELE_CONFIG_FILE))
    {
        std::cerr <<"Init Public Config Failed."<<std::endl;
        return false;
    }

    std::string strModeName = SINGLETON(ServiceSelectionConfig)->getModeName();
    bool bLogIsEnable = SINGLETON(ServiceSelectionConfig)->isShowLog();
    if (!SINGLETON(Log)->InitLog(strPath + "log/", strModeName, bLogIsEnable))
    {
        std::cerr <<"Init Log Failed."<<std::endl;
        return false;
    }
    Aos_WriteLog("Initial LOG Environmental Success.");
    return true;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (!initMain())
    {
        return -1;
    }

    ServiceSelection* m_pOpt = new ServiceSelection();
    if (m_pOpt->InitService())
    {
        m_pOpt->ServiceStart();
    }

    return a.exec();
}
