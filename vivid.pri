DEFINES += \
    VIVID_ROOT_PATH=\\\"$$PWD\\\" \

INCLUDEPATH += \
    $$PWD/include/ \
    $$PWD/dependencies/json/single_include \
    $$PWD/dependencies/glm

SOURCES += \
    $$PWD/src/color.cpp \
    $$PWD/src/colormap.cpp \
    $$PWD/src/colortable.cpp \
    $$PWD/src/functions.cpp \
    $$PWD/src/hcl.cpp \
    $$PWD/src/hex.cpp \
    $$PWD/src/hsl.cpp \
    $$PWD/src/hsv.cpp \
    $$PWD/src/index.cpp \
    $$PWD/src/lab.cpp \
    $$PWD/src/name.cpp \
    $$PWD/src/rgb.cpp \
    $$PWD/src/rgb32.cpp \
    $$PWD/src/rgb8.cpp \
    $$PWD/src/xyz.cpp

HEADERS += \
    $$PWD/include/vivid/color.h \
    $$PWD/include/vivid/colormap.h \
    $$PWD/include/vivid/colortable.h \
    $$PWD/include/vivid/conversion.h \
    $$PWD/include/vivid/encoding.h \
    $$PWD/include/vivid/functions.h \
    $$PWD/include/vivid/stream.h \
    $$PWD/include/vivid/types.h \
    $$PWD/include/vivid/vivid.h

DISTFILES += \
    $$PWD/res/colors.json \
    $$PWD/res/colormaps/blue-yellow.json \
    $$PWD/res/colormaps/cool-warm.json \
    $$PWD/res/colormaps/hsl.json \
    $$PWD/res/colormaps/hsl-pastel.json \
    $$PWD/res/colormaps/inferno.json \
    $$PWD/res/colormaps/magma.json \
    $$PWD/res/colormaps/plasma.json \
    $$PWD/res/colormaps/rainbow.json \
    $$PWD/res/colormaps/viridis.json \
    $$PWD/res/colormaps/vivid.json
