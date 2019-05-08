CONFIG += \
    c++1z \
    console

CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    src/colormap.cpp \
    src/conversion.cpp

HEADERS += \
    include/vivid/colormap.h \
    include/vivid/conversion.h

INCLUDEPATH += \
    $$PWD/include/ \
    $$PWD/dependencies/json/single_include \
    $$PWD/dependencies/glm

#  default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

