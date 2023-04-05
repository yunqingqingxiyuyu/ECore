QT += gui widgets

QT += designer

TEMPLATE = lib
DEFINES += CORE_LIBRARY

CONFIG += c++11


CONFIG += debug_and_release

CONFIG(debug, debug|release) {
    TARGET = ECored
msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
    DESTDIR = $$PWD/../Lib/ECored_msvc

}else{
    DESTDIR = $$PWD/../Lib/ECored
}

} else {
    TARGET = ECore
msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
    DESTDIR = $$PWD/../Lib/ECore_msvc

}else{
    DESTDIR = $$PWD/../Lib/ECore
}
}

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
    ecalendartimewidget.cpp \
    ecalendartimewidget_p.cpp \
    edatetimeedit.cpp \
    edatetimeedit_p.cpp \
    elineedit.cpp \
    elineedit_p.cpp \
    eloadingwidget.cpp \
    eloadingwidget_p.cpp \
    esecretcombobox.cpp \
    esecretcombobox_p.cpp \
    esingleton.cpp \
    etimewidget.cpp \
    etimewidget_p.cpp \
    etreemodel.cpp \
    etreemodel_p.cpp \
    etreewidget.cpp \
    etreewidget_p.cpp \
    ewidgetitem.cpp \
    ewidgetitem_p.cpp

HEADERS += \
    core_global.h \
    ecalendartimewidget.h \
    ecalendartimewidget_p.h \
    edatetimeedit.h \
    edatetimeedit_p.h \
    elineedit.h \
    elineedit_p.h \
    eloadingwidget.h \
    eloadingwidget_p.h \
    esecretcombobox.h \
    esecretcombobox_p.h \
    esingleton.h \
    etimewidget.h \
    etimewidget_p.h \
    etreemodel.h \
    etreemodel_p.h \
    etreewidget.h \
    etreewidget_p.h \
    etreewidgetitem.h \
    ewidgetitem.h \
    ewidgetitem_p.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
