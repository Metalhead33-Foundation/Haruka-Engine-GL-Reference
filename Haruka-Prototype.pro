TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG(release, debug|release): LIBS += -ldl -lassimp -lX11-xcb -lSDL2 -lX11 -lphysfs -lfreeimage -lfreeimageplus -lsndfile -lsamplerate
CONFIG(debug, debug|release): LIBS += -ldl -lassimp -lX11-xcb -lSDL2 -lX11 -lphysfs -lfreeimage -lfreeimageplus -lsndfile -lsamplerate

SOURCES += main.cpp \
    GL/GlShaderModule.cpp \
    GL/GlShaderProgram.cpp \
    GL/glad.c \
    GL/glad_glx.c \
    GL/GlTexture.cpp \
    GL/RenderWindow.cpp \
    io/AssimpIO.cpp \
    io/FileHandle.cpp \
    io/FreeImageIoExt.cpp \
    io/PhysFsRead.cpp \
    io/SoundFile.cpp \
    io/StdStream.cpp \
    audio/Samplerate.cpp \
    audio/StreamedAudio.cpp

HEADERS += \
    GL/glad.h \
    GL/glad_glx.h \
    GL/GlShaderModule.hpp \
    GL/GlShaderProgram.hpp \
    GL/GlTexture.hpp \
    GL/RenderWindow.hpp \
    abstract/AbstractFread.hpp \
    abstract/AbstractFwrite.hpp \
    abstract/Texture.hpp \
    abstract/ShaderModule.hpp \
    abstract/ShaderProgram.hpp \
    GL/khrplatform.h \
    abstract/SettingContainer.hpp \
    abstract/Global.hpp \
    io/AssimpIO.hpp \
    io/FileHandle.hpp \
    io/FreeImageIoExt.hpp \
    io/PhysFsRead.hpp \
    io/SoundFile.hpp \
    io/StdStream.hpp \
    audio/Samplerate.hpp \
    audio/StreamedAudio.hpp
