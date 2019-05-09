CONFIG += \
    c++1z \
    console

CONFIG -= app_bundle

DEFINES += \
    QT_DEPRECATED_WARNINGS \
    VIVID_ROOT_PATH=\\\"$$_PRO_FILE_PWD_\\\"

SOURCES += \
    main.cpp

include( $$PWD/vivid.pri )

#  default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
