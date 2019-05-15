CONFIG += \
    c++1z \
    console

CONFIG -= app_bundle

DEFINES += \
    QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp

include( $$PWD/../../vivid.pri )
