!contains(DEFINES, __SETTINGSBINDER__){
DEFINES += __SETTINGSBINDER__

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

SOURCES += \
    $$PWD/bindedsettings.cpp \
    $$PWD/simplereflex.cpp \
    $$PWD/ssaver.cpp \
    $$PWD/lightbinding.cpp
HEADERS += \
    $$PWD/bindedsettings.h \
    $$PWD/lightbinding.h \
    $$PWD/simplereflex.h \
    $$PWD/ssaver.h
}

HEADERS += \
    $$PWD/autosaver.h \
    $$PWD/lightbindings/actions.h \
    $$PWD/lightbindings/buttongroups.h \
    $$PWD/lightbindings/checkboxes.h \
    $$PWD/lightbindings/comboboxes.h \
    $$PWD/lightbindings/lineedits.h \
    $$PWD/lightbindings/notsupported.h \
    $$PWD/lightbindings/radiobuttons.h \
    $$PWD/lightbindings/spinboxes.h

