DEFINES += \
    VIVID_ROOT_PATH=\\\"$$PWD\\\"

INCLUDEPATH += \
    $$PWD/include/ \
    $$PWD/dependencies/json/single_include \
    $$PWD/dependencies/glm

SOURCES += \
    $$PWD/src/functions.cpp \
    $$PWD/src/index.cpp \
    $$PWD/src/colormap.cpp \
    $$PWD/src/ciexyz.cpp \
    $$PWD/src/cielab.cpp \
    $$PWD/src/hsv.cpp \
    $$PWD/src/rgb8.cpp \
    $$PWD/src/rgb.cpp \
    $$PWD/src/cielch.cpp \
    $$PWD/src/colortable.cpp \
    $$PWD/src/xterm.cpp \
    $$PWD/src/rgb32.cpp \
    $$PWD/src/hsl.cpp \
    $$PWD/src/hex.cpp

HEADERS += \
    $$PWD/include/vivid/functions.h \
    $$PWD/include/vivid/vivid.h \
    $$PWD/include/vivid/colormap.h \
    $$PWD/include/vivid/conversion.h \
    $$PWD/include/vivid/colortable.h \
    $$PWD/include/vivid/types.h

DISTFILES += \
    $$PWD/res/colors.json \
    $$PWD/res/colormaps/inferno.json \
    $$PWD/res/colormaps/magma.json \
    $$PWD/res/colormaps/plasma.json \
    $$PWD/res/colormaps/viridis.json


#  install

resources.files = $${DESTDIR}/res/*
resources.path = data/

INSTALLS += resources
