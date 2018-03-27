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
    glad_glx.c \
    GlShaderModule.cpp \
    GlShaderProgram.cpp \
    GlTexture.cpp

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
    glad_glx.h \
    ShaderModule.hpp \
    GlShaderModule.hpp \
    GlShaderProgram.hpp \
    ShaderProgram.hpp \
    Texture.hpp \
    GlTexture.hpp
