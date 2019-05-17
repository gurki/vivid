CONFIG += \
    c++1z \
    console

CONFIG -= app_bundle

DEFINES += \
    QT_DEPRECATED_WARNINGS

SOURCES += \
    $$PWD/main.cpp \
    direct-conversions.cpp

HEADERS += \
    $$PWD/catch.hpp \
    utility.h

include( $$PWD/../vivid.pri )
