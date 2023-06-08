QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    addtime.cpp \
    config.cpp \
    main.cpp \
    countdown.cpp \
    setting.cpp \
    timeitem.cpp

HEADERS += \
    about.h \
    addtime.h \
    config.h \
    countdown.h \
    setting.h \
    timeitem.h

FORMS += \
    about.ui \
    addtime.ui \
    countdown.ui \
    setting.ui \
    timeitem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
 resources.qrc

CONFIG += \
    resources_big

RC_ICONS = resources/icon/logo.ico
VERSION = 0.1.0
RC_LANG = 0x0004
QMAKE_TARGET_COMPANY = jlqwer
QMAKE_TARGET_PRODUCT = CountDown
QMAKE_TARGET_COPYRIGHT = Copyright(C)  2023  jlqwer
