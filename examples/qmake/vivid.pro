CONFIG += \
    c++1z \
    console

CONFIG -= app_bundle

DEFINES += \
    QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp
#    strong_types.cpp
#     convert_maps.cpp

DESTDIR = $$PWD/build/install/

#  dependencies

include( $$PWD/../../vivid.pri )

#  install

package.path = $${DESTDIR}
package.files += vivid.exe
package.CONFIG = no_check_exist

INSTALLS += package

resources.path = $${DESTDIR}/res/
resources.files += $${DISTFILES}

INSTALLS += resources
