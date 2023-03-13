QT += core sql
QT -= gui

CONFIG += c++11

TARGET = EIDSSampleSelection
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

MOC_DIR = $$OUT_PWD/tmp/moc
OBJECTS_DIR = $$OUT_PWD/tmp/obj
UI_DIR = $$OUT_PWD/tmp/ui
RCC_DIR = $$OUT_PWD/tmp/qrc

SOURCES += main.cpp \
    AlarmLog.cpp \
    ConditionCal.cpp \
    ModelSelectionMgr.cpp \
    PModelCorrAnalysis.cpp \
    PModelSampleTime.cpp \
    PModelSampleTimeCon.cpp \
    PublicFunction.cpp \
    RDbOperationComplex.cpp \
    RDbOperationSimple.cpp \
    RDbSQLAdapter.cpp \
    ServiceSelection.cpp \
    ServiceSelectionConfig.cpp \
    StartupServer.cpp \
    StartupServerSelection.cpp \
    TbModelCondition.cpp \
    TbModelMonitPoint.cpp \
    TbModelSampleCorr.cpp \
    TbModelSampleTime.cpp \
    TbModelSampleTimeCon.cpp \
    TesterGetFile.cpp \
    CorrAnalAlgoFun.cpp \
    CorMatrix.cpp \
    CorrelationAnalysis.cpp \
    RsdbAdapter.cpp \
    Util.cpp \
    XdbThrift.cpp \
    xdb_types.cpp \
    RtdbOpt.cpp

DISTFILES +=

HEADERS += \
    AlarmLog.h \
    Communal.h \
    ConditionCal.h \
    DataValueInfo.h \
    ModelSelectionMgr.h \
    PModelCorrAnalysis.h \
    PModelSampleTime.h \
    PModelSampleTimeCon.h \
    PublicFunction.h \
    RDbHead.h \
    RDbOperationComplex.h \
    RDbOperationSimple.h \
    RDbSQLAdapter.h \
    SampleConditionInfo.h \
    SampleTimeConInfo.h \
    SampleTimeInfo.h \
    SelectionDef.h \
    ServiceSelection.h \
    ServiceSelectionConfig.h \
    StartupServer.h \
    StartupServerSelection.h \
    TbModelCondition.h \
    TbModelMonitPoint.h \
    TbModelSampleCorr.h \
    TbModelSampleTime.h \
    TbModelSampleTimeCon.h \
    TesterGetFile.h \
    TypeDef.h \
    CorrAnalAlgoFun.h \
    CorMatrix.h \
    CorrelationAnalysis.h \
    RsdbAdapter.h \
    Util.h \
    XdbThrift.h \
    xdb_types.h \
    RtdbOpt.h


unix:!macx: LIBS += -L$$PWD/../common/lib -lcommon

INCLUDEPATH += $$PWD/../common/inc
DEPENDPATH += $$PWD/../common/inc

unix:!macx: LIBS += -L$$PWD/../compiler/lib -lcompiler

INCLUDEPATH += $$PWD/../compiler/inc
DEPENDPATH += $$PWD/../compiler/inc

unix:!macx: LIBS += -L$$PWD/../waspcn/lib/ -lwaspcn

INCLUDEPATH += $$PWD/../waspcn/inc
DEPENDPATH += $$PWD/../waspcn/inc

unix:!macx: LIBS += -L$$PWD/../boost/lib -lboost_thread -lboost_filesystem
INCLUDEPATH += $$PWD/../boost/include
DEPENDPATH += $$PWD/../boost/include

LIBS += -ldl -lpthread


unix:!macx: LIBS += -L$$PWD/../thrift-0.13.0/lib/ -lthrift

INCLUDEPATH += $$PWD/../thrift-0.13.0/include
DEPENDPATH += $$PWD/../thrift-0.13.0/include
