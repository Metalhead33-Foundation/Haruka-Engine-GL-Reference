#ifndef RENDERINGENGINE_HPP
#define RENDERINGENGINE_HPP
#include "SettingContainer.hpp"
#include <cstdlib>
#include "ShaderModule.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "AnimatedTexture.hpp"
#include "Framebuffer.hpp"
#include "Mesh.hpp"
#include "FIO.hpp"
#include "Font.hpp"

namespace Abstract {
DEFINE_STRUCT(WidgetProperties)
struct WidgetProperties {
	sTexture texture;
	glm::vec2 size;
	glm::vec2 pos;
	float rotation;
};

DEFINE_CLASS(RenderingEngine)
class RenderingEngine
{
protected:
	Abstract::sSettingContainer settings;
public:
	typedef Mesh::MeshCreatorFunction MeshCreator;
	virtual ~RenderingEngine() = default;
	virtual void switchBuffers() = 0;
	virtual void clearDepthBuffer() = 0;
	virtual sShaderModule createShaderModule(ShaderModule::ShaderType ntype, sFIO reada) = 0;
	virtual sShaderProgram createShaderProgram() = 0;
	virtual sTexture createTexture(Texture::textureType ntype, sImageContainer constructor) = 0;
	virtual sAnimatedTexture createTextureFromGIF(Texture::textureType ntype, sAnimatedImageContainer constructor) = 0;
	virtual sMesh createMesh(Mesh::ConstructorReference ref) = 0;
	virtual void clearBackground() = 0;
	virtual void clearBackground(unsigned char r, unsigned char g, unsigned char b) = 0;
	virtual void renderFramebuffer(const sShaderProgram shader) = 0;
	virtual void setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) = 0;
	virtual sFramebuffer createFramebuffer(uint32_t nwidth, uint32_t nheight, uint32_t nsamples = 0) = 0;
	virtual sFramebuffer getFramebuffer() = 0;

	virtual MeshCreator getMeshCreator() const = 0;

	virtual void renderFrame() = 0;
	virtual void startup() = 0;
	virtual void cleanup() = 0;
};

}

typedef Abstract::sRenderingEngine (*RenderingBackendFactoryFunction)(Abstract::sSettingContainer,uint32_t,uint32_t);
DEFINE_STRUCT(BackendFactory)
struct BackendFactory
{
	RenderingBackendFactoryFunction create;
	std::string name;
	std::string description;
};
typedef void (*BackendFactoryInitializer)(pBackendFactory);

#endif // RENDERINGENGINE_HPP
