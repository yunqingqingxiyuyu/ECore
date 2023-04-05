CONFIG += plugin debug_and_release

CONFIG(debug, debug|release) {
msvc {
#注意，此处会自动在名字后面+d
    TARGET =$$qtLibraryTarget(ECorePlugin)
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
    DESTDIR = $$PWD/../Lib/ECorePlugind_msvc

}else{
    TARGET =$$qtLibraryTarget(ECorePlugind)
    DESTDIR = $$PWD/../Lib/ECorePlugind
}

} else {
msvc {
    TARGET = $$qtLibraryTarget(ECorePlugin)
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
    DESTDIR = $$PWD/../Lib/ECorePlugin_msvc

}else{
    TARGET = $$qtLibraryTarget(ECorePlugin)
    DESTDIR = $$PWD/../Lib/ECorePlugin
}
}

QT += gui widgets uiplugin

TEMPLATE = lib

DEFINES += PLUGIN_LIBRARY
DEFINES += CORE_LIBRARY

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}


LIBS        += -L.

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
    elineeditplugin.cpp \
    etimewidgetplugin.cpp \
    plugincollection.cpp



HEADERS += \
    Plugin_global.h \
    elineeditplugin.h \
    etimewidgetplugin.h \
    plugincollection.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}

win32 {
        target.path = $$[QT_INSTALL_PLUGINS]/designer
}


!isEmpty(target.path): INSTALLS += target

include($$PWD/Plugin.pri)

RESOURCES += \
    icons.qrc

