INCLUDEPATH += $$PWD/../Core/
DEPENDPATH += $$PWD/../Core/

win32:debug {
        LIBS += -L$$PWD/../ECorePlugin -lECorePlugin
}else{
        LIBS += -L$$PWD/../ECorePlugind -lECorePlugind
}
