CONFIG += \
    c++1z \
    console

CONFIG -= app_bundle

DEFINES += \
    QT_DEPRECATED_WARNINGS

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/test_conversion_fuzzy.cpp \
    $$PWD/test_conversion_manual.cpp \
    $$PWD/test_profiles.cpp

HEADERS += \
    $$PWD/catch.hpp \
    $$PWD/utility.h

include( $$PWD/../vivid.pri )
