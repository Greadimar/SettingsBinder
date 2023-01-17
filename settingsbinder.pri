!contains(DEFINES, __SETTINGSBINDER__){
DEFINES += __SETTINGSBINDER__

CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14

SOURCES += \
    $$PWD/bindedsettings.cpp \
    $$PWD/sbvariantsaver.cpp \
    $$PWD/simplereflex.cpp \
    $$PWD/lightbinding.cpp
HEADERS += \
    $$PWD/bindedsettings.h \
    $$PWD/lightbinding.h \
    $$PWD/sbvariantsaver.h \
    $$PWD/simplereflex.h


HEADERS += \
    $$PWD/lightbindings/actions.h \
    $$PWD/lightbindings/buttongroups.h \
    $$PWD/lightbindings/checkboxes.h \
    $$PWD/lightbindings/comboboxes.h \
    $$PWD/lightbindings/lineedits.h \
    $$PWD/lightbindings/notsupported.h \
    $$PWD/lightbindings/radiobuttons.h \
    $$PWD/lightbindings/spinboxes.h \
    $$PWD/sbautosaver.h
}
!exists(../CommonTools/CommonTools.pri){
    message("SettingsBinder: CommonTools not found")
}
contains(DEFINES, __HEXEDIT__){
    $$PWD/lightbindings/hexedits.h
}

HEADERS += \
    $$PWD/chronosupport.h

SOURCES += \
    $$PWD/chronosupport.cpp

