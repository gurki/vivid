CONFIG += \
    c++1z \
    console

CONFIG -= app_bundle

DEFINES += \
    QT_DEPRECATED_WARNINGS \
    VIVID_ROOT_PATH=\\\"$$_PRO_FILE_PWD_\\\"

SOURCES += \
    main.cpp \
    src/colormap.cpp \
    src/ciexyz.cpp \
    src/cielab.cpp \
    src/hsv.cpp \
    src/rgb8.cpp \
    src/rgb.cpp \
    src/cielch.cpp

HEADERS += \
    include/vivid/colormap.h \
    include/vivid/conversion.h

INCLUDEPATH += \
    $$PWD/include/ \
    $$PWD/dependencies/json/single_include \
    $$PWD/dependencies/glm

DISTFILES += \
    res/colormaps/inferno.json \
    res/colormaps/magma.json \
    res/colormaps/plasma.json \
    res/colormaps/viridis.json

#  default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
