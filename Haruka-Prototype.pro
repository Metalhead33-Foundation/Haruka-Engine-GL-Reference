TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG(release, debug|release): LIBS += -ldl -lassimp -lX11-xcb -lSDL2 -lX11 -lphysfs
CONFIG(debug, debug|release): LIBS += -ldl -lassimp -lX11-xcb -lSDL2 -lX11 -lphysfs

SOURCES += main.cpp \
    RenderWindow.cpp \
    FileHandle.cpp \
    PhysFsRead.cpp \
    StdStream.cpp \
    glad.c \
    glad_glx.c

HEADERS += \
    khrplatform.h \
    RenderWindow.hpp \
    Global.hpp \
    SettingContainer.hpp \
    FileHandle.hpp \
    AbstractFwrite.hpp \
    AbstractFread.hpp \
    PhysFsRead.hpp \
    StdStream.hpp \
    glad.h \
    glad_glx.h
