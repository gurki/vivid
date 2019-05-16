DEFINES += \
    VIVID_ROOT_PATH=\\\"$$PWD\\\" \

INCLUDEPATH += \
    $$PWD/include/ \
    $$PWD/dependencies/json/single_include \
    $$PWD/dependencies/glm

SOURCES += \
    $$PWD/src/*

HEADERS += \
    $$PWD/include/vivid/*

DISTFILES += \
    $$PWD/res/*
