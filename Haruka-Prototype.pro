TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG(release, debug|release): LIBS += -ldl -lassimp -lX11-xcb -lSDL2 -lX11 -lphysfs -lfreeimage -lfreeimageplus -lsndfile -lsamplerate -pthread
CONFIG(debug, debug|release): LIBS += -ldl -lassimp -lX11-xcb -lSDL2 -lX11 -lphysfs -lfreeimage -lfreeimageplus -lsndfile -lsamplerate -pthread

SOURCES += main.cpp \
    GL/GlShaderModule.cpp \
    GL/GlShaderProgram.cpp \
    GL/glad.c \
    GL/glad_glx.c \
    GL/GlTexture.cpp \
    io/AssimpIO.cpp \
    io/FreeImageIoExt.cpp \
    io/SoundFile.cpp \
    io/StdStream.cpp \
    audio/Samplerate.cpp \
    GL/GlMesh.cpp \
    io/PhysFsFileHandle.cpp \
    GL/GlModel.cpp \
    io/AiModelFactory.cpp \
    audio/StreamedAudio.cpp \
    audio/SoundBuffer.cpp \
    audio/SoundSource.cpp \
    audio/Audio.cpp \
    audio/OpenALWrapper.cpp \
    sys/Clock.cpp \
    sys/MainSystem.cpp \
    GL/GlRenderingEngine.cpp \
    sys/GameSystem.cpp \
    sys/STime.cpp \
    audio/Context.cpp \
    audio/System.cpp \
    audio/AudioUtil.cpp \
    audio/FX/Effect.cpp \
    audio/FX/Filter.cpp \
    audio/FX/AuxiliaryEventSlot.cpp \
    audio/FX/LowpassFilter.cpp \
    audio/FX/HighpassFilter.cpp \
    audio/FX/BandpassFilter.cpp

HEADERS += \
    GL/glad.h \
    GL/glad_glx.h \
    GL/GlShaderModule.hpp \
    GL/GlShaderProgram.hpp \
    GL/GlTexture.hpp \
    abstract/Texture.hpp \
    abstract/ShaderModule.hpp \
    abstract/ShaderProgram.hpp \
    GL/khrplatform.h \
    abstract/SettingContainer.hpp \
    abstract/Global.hpp \
    io/AssimpIO.hpp \
    io/FreeImageIoExt.hpp \
    io/SoundFile.hpp \
    io/StdStream.hpp \
    audio/Samplerate.hpp \
    audio/StreamedAudio.hpp \
    io/sndfile.hh \
    audio/Audio.hpp \
    abstract/Vertex.hpp \
    abstract/Mesh.hpp \
    GL/GlMesh.hpp \
    abstract/Model.hpp \
    io/PhysFsFileHandle.hpp \
    abstract/FIO.hpp \
    GL/GlModel.hpp \
    io/AiModelFactory.hpp \
    audio/SoundBuffer.hpp \
    audio/SoundSource.hpp \
    audio/OpenALWrapper.hpp \
    audio/al.h \
    audio/alc.h \
    audio/alext.h \
    audio/efx.h \
    sys/Clock.hpp \
    sys/MainSystem.hpp \
    abstract/RenderingEngine.hpp \
    GL/GlRenderingEngine.hpp \
    sys/GameSystem.hpp \
    sys/STime.hpp \
    audio/Context.hpp \
    audio/System.hpp \
    audio/AudioUtil.hpp \
    audio/FX/Effect.hpp \
    audio/FX/Filter.hpp \
    audio/FX/AuxiliaryEventSlot.hpp \
    audio/FX/LowpassFilter.hpp \
    audio/FX/HighpassFilter.hpp \
    audio/FX/BandpassFilter.hpp
