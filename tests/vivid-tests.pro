CONFIG += \
    c++1z \
    console

CONFIG -= app_bundle

DEFINES += \
    QT_DEPRECATED_WARNINGS

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/conversion.cpp

HEADERS += \
    $$PWD/catch.hpp \
    $$PWD/utility.h

include( $$PWD/../vivid.pri )
