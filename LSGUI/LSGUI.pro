QT += core \
    quick
QT += gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MyThreadSend.cpp \
    backendemu2.cpp \
    backendhitplot.cpp \
    backendstripprf.cpp \
    backendtimingprf.cpp \
    febdialog.cpp \
    histogram.cpp \
    main.cpp \
    mainwindow.cpp \
    mythread.cpp \
    mythread_be_dataprocess.cpp \
    mythread_be_dataprocplotc.cpp \
    mythread_be_dataprocplotd.cpp \
    mythread_be_update.cpp \
    mythread_cb_update.cpp \
    mythread_lb_update.cpp \
    mythread_remoteprog.cpp \
    qcustomplot.cpp \
    realtimev2.cpp \
    sendframe.cpp \
    timingprofile.cpp

HEADERS += \
    MyThreadSend.h \
    YasinLanLib.h \
    backendemu2.h \
    backendhitplot.h \
    backendstripprf.h \
    backendtimingprf.h \
    febdialog.h \
    histogram.h \
    mainwindow.h \
    mythread.h \
    mythread_be_dataprocess.h \
    mythread_be_dataprocplotc.h \
    mythread_be_dataprocplotd.h \
    mythread_be_update.h \
    mythread_cb_update.h \
    mythread_lb_update.h \
    mythread_remoteprog.h \
    qcustomplot.h \
    realtimev2.h \
    sendframe.h \
    specstrings_strict.h \
    timingprofile.h

FORMS += \
    backendemu2.ui \
    backendhitplot.ui \
    backendstripprf.ui \
    backendtimingprf.ui \
    febdialog.ui \
    histogram.ui \
    mainwindow.ui \
    realtimev2.ui \
    timingprofile.ui

TRANSLATIONS += \
    LSGUI_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/../Library/x64/ -lYasinLanLib

INCLUDEPATH += $$PWD/../Library/x64
DEPENDPATH += $$PWD/../Library/x64

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Library/x64/ -lYasinLanLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Library/x64/ -lYasinLanLib

INCLUDEPATH += $$PWD/../Library/x64
DEPENDPATH += $$PWD/../Library/x64

win32: LIBS += -L$$PWD/../Library/x64/ -lYasinLanLib

INCLUDEPATH += $$PWD/../Library/x64
DEPENDPATH += $$PWD/../Library/x64
CONFIG+= static
