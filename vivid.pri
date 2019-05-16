DEFINES += \
    VIVID_ROOT_PATH=\\\"$$PWD\\\" \

INCLUDEPATH += \
    $$PWD/include/ \
    $$PWD/dependencies/json/single_include \
    $$PWD/dependencies/glm

SOURCES += \
    $$PWD/src/functions.cpp \
    $$PWD/src/hcl.cpp \
    $$PWD/src/index.cpp \
    $$PWD/src/colormap.cpp \
    $$PWD/src/hsv.cpp \
    $$PWD/src/lab.cpp \
    $$PWD/src/name.cpp \
    $$PWD/src/rgb8.cpp \
    $$PWD/src/rgb.cpp \
    $$PWD/src/colortable.cpp \
    $$PWD/src/rgb32.cpp \
    $$PWD/src/hsl.cpp \
    $$PWD/src/hex.cpp \
    $$PWD/src/xyz.cpp

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
