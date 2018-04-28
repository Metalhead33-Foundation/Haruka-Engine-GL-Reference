TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
# QMAKE_CXXFLAGS_DEBUG += -Werror

CONFIG(release, debug|release): LIBS += -ldl -lassimp -lX11-xcb -lSDL2 -lX11 -lphysfs -lfreeimage -lfreeimageplus -lsndfile -lsamplerate -lgif -pthread
CONFIG(debug, debug|release): LIBS += -ldl -lassimp -lX11-xcb -lSDL2 -lX11 -lphysfs -lfreeimage -lfreeimageplus -lsndfile -lsamplerate -lgif -pthread

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
    io/AiModelFactory.cpp \
    audio/StreamedAudio.cpp \
    audio/SoundBuffer.cpp \
    audio/SoundSource.cpp \
    audio/Audio.cpp \
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
    audio/FX/LowpassFilter.cpp \
    audio/FX/HighpassFilter.cpp \
    audio/FX/BandpassFilter.cpp \
    audio/AL/OpenALWrapper.cpp \
    audio/FX/ReverbEffect.cpp \
    audio/FX/ChorusEffect.cpp \
    audio/FX/DistortionEffect.cpp \
    audio/FX/EchoEffect.cpp \
    audio/FX/FlangerEffect.cpp \
    audio/FX/FrequencyShifterEffect.cpp \
    audio/FX/VocalMorpherEffect.cpp \
    audio/FX/PitchShifterEffect.cpp \
    audio/FX/RingModulatorEffect.cpp \
    audio/FX/WahWahEffect.cpp \
    audio/FX/CompressorEffect.cpp \
    audio/FX/EqualizerEffect.cpp \
    audio/FX/AuxiliaryEffectSlot.cpp \
    sys/Camera.cpp \
    sys/ResourceManager.cpp \
    sys/proxy/ProxyTexture.cpp \
    sys/proxy/ProxyShaderModule.cpp \
    sys/proxy/ProxyWidget.cpp \
    sys/proxy/ProxyShaderProgram.cpp \
    sys/proxy/ProxyModel.cpp \
    sys/proxy/ProxyAudioBuffer.cpp \
    sys/fxproxy/ReverbProxy.cpp \
    sys/fxproxy/ChorflangProxy.cpp \
    sys/fxproxy/EqualizerProxy.cpp \
    sys/fxproxy/WahWahProxy.cpp \
    sys/fxproxy/VocalMorpherProxy.cpp \
    sys/fxproxy/RingModulatorProxy.cpp \
    sys/fxproxy/PitchShifterProxy.cpp \
    sys/fxproxy/FrequencyShifterProxy.cpp \
    sys/fxproxy/EchoProxy.cpp \
    sys/fxproxy/DistortionProxy.cpp \
    sys/fxproxy/CompressorProxy.cpp \
    sys/fxproxy/BandpassFilterProxy.cpp \
    sys/fxproxy/HighpassFilterProxy.cpp \
    sys/fxproxy/LowpassFilterProxy.cpp \
    sys/proxy/AuxiliaryEffectProxy.cpp \
    sys/proxy/ProxyAudioSource.cpp \
    GL/GlFramebuffer.cpp \
    GL/GlAnimatedTexture.cpp \
    io/GifIO.cpp \
    sys/proxy/ProxyAnimatedTexture.cpp \
    GL/GlVectorWidget.cpp

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
    io/PhysFsFileHandle.hpp \
    abstract/FIO.hpp \
    io/AiModelFactory.hpp \
    audio/SoundBuffer.hpp \
    audio/SoundSource.hpp \
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
    audio/FX/LowpassFilter.hpp \
    audio/FX/HighpassFilter.hpp \
    audio/FX/BandpassFilter.hpp \
    audio/AL/efx.h \
    audio/AL/al.h \
    audio/AL/alc.h \
    audio/AL/alext.h \
    audio/AL/OpenALWrapper.hpp \
    audio/FX/ReverbEffect.hpp \
    audio/FX/ChorusEffect.hpp \
    audio/FX/DistortionEffect.hpp \
    audio/FX/EchoEffect.hpp \
    audio/FX/FlangerEffect.hpp \
    audio/FX/FrequencyShifterEffect.hpp \
    audio/FX/VocalMorpherEffect.hpp \
    audio/FX/PitchShifterEffect.hpp \
    audio/FX/RingModulatorEffect.hpp \
    audio/FX/WahWahEffect.hpp \
    audio/FX/CompressorEffect.hpp \
    audio/FX/EqualizerEffect.hpp \
    audio/FX/ChorflangEffect.hpp \
    audio/FX/WaveformEffect.hpp \
    audio/FX/AuxiliaryEffectSlot.hpp \
    audio/FX/AllEffects.hpp \
    sys/Camera.hpp \
    abstract/Future.hpp \
    abstract/HashTrait.hpp \
    sys/ResourceManager.hpp \
    sys/proxy/ProxyTexture.hpp \
    sys/proxy/ProxyShaderModule.hpp \
    sys/proxy/ProxyWidget.hpp \
    sys/proxy/ProxyShaderProgram.hpp \
    sys/proxy/ProxyModel.hpp \
    sys/proxy/ProxyAudioBuffer.hpp \
    sys/fxproxy/ReverbProxy.hpp \
    sys/fxproxy/ChorflangProxy.hpp \
    sys/fxproxy/EqualizerProxy.hpp \
    sys/fxproxy/WahWahProxy.hpp \
    sys/fxproxy/VocalMorpherProxy.hpp \
    sys/fxproxy/RingModulatorProxy.hpp \
    sys/fxproxy/PitchShifterProxy.hpp \
    sys/fxproxy/FrequencyShifterProxy.hpp \
    sys/fxproxy/EchoProxy.hpp \
    sys/fxproxy/DistortionProxy.hpp \
    sys/fxproxy/CompressorProxy.hpp \
    sys/fxproxy/BandpassFilterProxy.hpp \
    sys/fxproxy/HighpassFilterProxy.hpp \
    sys/fxproxy/LowpassFilterProxy.hpp \
    sys/fxproxy/AllEffects.hpp \
    sys/fxproxy/AllFilters.hpp \
    sys/proxy/AuxiliaryEffectProxy.hpp \
    sys/proxy/ProxyAudioSource.hpp \
    GL/GlFramebuffer.hpp \
    abstract/Framebuffer.hpp \
    abstract/AnimatedTexture.hpp \
    GL/GlAnimatedTexture.hpp \
    io/GifIO.hpp \
    sys/proxy/ProxyAnimatedTexture.hpp \
    io/rbvi.h \
    GL/GlVectorWidget.hpp \
    abstract/VectorWidget.hpp
