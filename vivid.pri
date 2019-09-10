DEFINES += \
    VIVID_ROOT_PATH=\\\"$$PWD/\\\" \

INCLUDEPATH += \
    $$PWD/include/ \
    $$PWD/dependencies/json/single_include \
    $$PWD/dependencies/glm

SOURCES += \
    $$PWD/src/adobe.cpp \
    $$PWD/src/color.cpp \
    $$PWD/src/colormap.cpp \
    $$PWD/src/hex.cpp \
    $$PWD/src/hsl.cpp \
    $$PWD/src/hsv.cpp \
    $$PWD/src/index.cpp \
    $$PWD/src/interpolation.cpp \
    $$PWD/src/lab.cpp \
    $$PWD/src/lch.cpp \
    $$PWD/src/lrgb.cpp \
    $$PWD/src/name.cpp \
    $$PWD/src/rgb.cpp \
    $$PWD/src/rgb32.cpp \
    $$PWD/src/rgb8.cpp \
    $$PWD/src/srgb.cpp \
    $$PWD/src/types.cpp \
    $$PWD/src/utility.cpp \
    $$PWD/src/xyz.cpp

HEADERS += \
    $$PWD/include/vivid/color.h \
    $$PWD/include/vivid/colormap.h \
    $$PWD/include/vivid/conversion.h \
    $$PWD/include/vivid/data.h \
    $$PWD/include/vivid/fuzzy.h \
    $$PWD/include/vivid/interpolation.h \
    $$PWD/include/vivid/encoding.h \
    $$PWD/include/vivid/profiles.h \
    $$PWD/include/vivid/stream.h \
    $$PWD/include/vivid/types.h \
    $$PWD/include/vivid/utility.h \
    $$PWD/include/vivid/vivid.h

#  static color data and maps

HEADERS += \
    $$PWD/include/vivid/data/blue-yellow.h \
    $$PWD/include/vivid/data/cool-warm.h \
    $$PWD/include/vivid/data/hsl-pastel.h \
    $$PWD/include/vivid/data/hsl.h \
    $$PWD/include/vivid/data/inferno.h \
    $$PWD/include/vivid/data/magma.h \
    $$PWD/include/vivid/data/plasma.h \
    $$PWD/include/vivid/data/rainbow.h \
    $$PWD/include/vivid/data/turbo.h \
    $$PWD/include/vivid/data/viridis.h \
    $$PWD/include/vivid/data/vivid.h \
    $$PWD/include/vivid/data/xterm.h

