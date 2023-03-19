INCLUDEPATH += $$PWD/../Core/
DEPENDPATH += $$PWD/../Core/

CONFIG(debug, debug|release) {
msvc {
        LIBS += -L$$PWD/../Lib/ECorePlugind_msvc -lECorePlugind
}else{
        LIBS += -L$$PWD/../Lib/ECorePlugind -lECorePlugind
}

}else{

msvc {
        LIBS += -L$$PWD/../Lib/ECorePlugin_msvc -lECorePlugin
}else{
        LIBS += -L$$PWD/../Lib/ECorePlugin -lECorePlugin
}

}

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
