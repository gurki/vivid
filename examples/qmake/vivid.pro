CONFIG += \
    c++1z \
    console

CONFIG -= app_bundle

DEFINES += \
    QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp

dependency_path = $$PWD/../../../
include( $${dependency_path}/vivid/vivid.pri )


#  install

DESTDIR = $$PWD/build/install/

package.path = $${DESTDIR}
package.files += vivid.exe
package.CONFIG = no_check_exist

INSTALLS += package
