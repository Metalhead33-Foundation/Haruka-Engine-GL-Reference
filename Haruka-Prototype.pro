TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
# QMAKE_CXXFLAGS_DEBUG += -Werror
INCLUDEPATH += "/usr/include/freetype2"

CONFIG(release, debug|release): LIBS += -ldl -lassimp -lX11-xcb -lSDL2 -lX11 -lphysfs -lfreeimage -lfreeimageplus -lfreetype -lsndfile -L/usr/local/lib -lHarudioEngine -lgif -pthread
CONFIG(debug, debug|release): LIBS += -ldl -lassimp -lX11-xcb -lSDL2 -lX11 -lphysfs -lfreeimage -lfreeimageplus -lfreetype -lsndfile -L/usr/local/lib -lHarudioEngine -lgif -pthread

SOURCES += main.cpp \
    audio/System.cpp \
    gfx/Widget.cpp \
    GL/glad_glx.c \
    GL/glad.c \
    GL/GlAnimated.cpp \
    GL/GlAnimatedCubemap.cpp\
    GL/GlAnimatedTexture.cpp \
    GL/GlCubeMap.cpp \
    GL/GlFont.cpp \
    GL/GlFramebuffer.cpp \
    GL/GlKeyframeAnimation.cpp \
    GL/GlMesh.cpp \
    GL/GlQuad.cpp \
    GL/GlRasterDrawable.cpp \
    GL/GlRenderingEngine.cpp \
    GL/GlShaderModule.cpp \
    GL/GlShaderProgram.cpp \
    GL/GlTexture.cpp \
    io/AiModelFactory.cpp \
    io/AssimpIO.cpp \
    io/FontIO.cpp \
    io/FreeImageIoExt.cpp \
    io/GifIO.cpp \
    io/PhysFsFileHandle.cpp \
    io/PhysFSSystem.cpp \
    io/StdStream.cpp \
    sys/Camera.cpp \
    sys/Clock.cpp \
    sys/GameSystem.cpp \
    sys/MainSystem.cpp \
    sys/proxy/AuxiliaryEffectProxy.cpp \
    sys/proxy/ProxyAnimatedTexture.cpp \
    sys/proxy/ProxyAudioBuffer.cpp \
    sys/proxy/ProxyAudioSource.cpp \
    sys/proxy/ProxyModel.cpp \
    sys/proxy/ProxyShaderModule.cpp \
    sys/proxy/ProxyShaderProgram.cpp \
    sys/proxy/ProxyTexture.cpp \
    sys/proxy/ProxyWidget.cpp \
    sys/ResourceManager.cpp \
    sys/STime.cpp \
    audio/AudioUnit.cpp \
    audio/AudioPositioner.cpp \
    audio/AudioRoom.cpp \
    gfx/Model.cpp \
    GL/GlBufferObject.cpp \
    GL/GlVertexArray.cpp \
    GL/GlVertexBufferObject.cpp \
    GL/GlIndexBuffer.cpp \
    gfx/Billboard.cpp \
    io/ImgIo.cpp

HEADERS += \
    abstract/Animated.hpp \
    abstract/AnimatedCubemap.hpp \
    abstract/AnimatedTexture.hpp \
    abstract/Bone.hpp \
    abstract/Cubemap.hpp \
    abstract/Drawable.hpp \
    abstract/FIO.hpp \
    abstract/FIOSys.hpp \
    abstract/Font.hpp \
    abstract/Framebuffer.hpp \
    abstract/Future.hpp \
    abstract/Global.hpp \
    abstract/HashTrait.hpp \
    abstract/KeyframeAnimation.hpp \
    abstract/Mesh.hpp \
    abstract/RasterDrawable.hpp \
    abstract/RenderingEngine.hpp \
    abstract/SettingContainer.hpp \
    abstract/ShaderModule.hpp \
    abstract/ShaderProgram.hpp \
    abstract/TextBox.hpp \
    abstract/Texture.hpp \
    abstract/Vertex.hpp \
    audio/System.hpp \
    gfx/Widget.hpp \
    GL/glad_glx.h \
    GL/glad.h \
    GL/GlAnimated.hpp \
    GL/GlAnimatedCubemap.hpp \
    GL/GlAnimatedTexture.hpp \
    GL/GlCubeMap.hpp \
    GL/GlFont.hpp \
    GL/GlFramebuffer.hpp \
    GL/GlKeyframeAnimation.hpp \
    GL/GlMesh.hpp \
    GL/GlQuad.hpp \
    GL/GlRasterDrawable.hpp \
    GL/GlRenderingEngine.hpp \
    GL/GlShaderModule.hpp \
    GL/GlShaderProgram.hpp \
    GL/GlTexture.hpp \
    GL/khrplatform.h \
    io/AiModelFactory.hpp \
    io/AssimpIO.hpp \
    io/FontIO.hpp \
    io/FreeImageIoExt.hpp \
    io/GifIO.hpp \
    io/PhysFsFileHandle.hpp \
    io/PhysFSSystem.hpp \
    io/rbvi.h \
    io/ShaderPreprocessorInput.hpp\
    io/StdStream.hpp \
    sys/Camera.hpp \
    sys/Clock.hpp \
    sys/GameSystem.hpp \
    sys/MainSystem.hpp \
    sys/proxy/AuxiliaryEffectProxy.hpp \
    sys/proxy/ProxyAnimatedTexture.hpp \
    sys/proxy/ProxyAudioBuffer.hpp \
    sys/proxy/ProxyAudioSource.hpp \
    sys/proxy/ProxyModel.hpp \
    sys/proxy/ProxyShaderModule.hpp \
    sys/proxy/ProxyShaderProgram.hpp \
    sys/proxy/ProxyTexture.hpp \
    sys/proxy/ProxyWidget.hpp \
    sys/ResourceManager.hpp \
    sys/STime.hpp \
    audio/AudioUnit.hpp \
    audio/AudioPositioner.hpp \
    audio/AudioRoom.hpp \
    gfx/Model.hpp \
    GL/GlBufferObject.hpp \
    GL/GlVertexArray.hpp \
    GL/GlVertexBufferObject.hpp \
    GL/GlIndexBuffer.hpp \
    gfx/Billboard.hpp \
    abstract/AbstractImageContainer.hpp \
    io/ImgIo.hpp
