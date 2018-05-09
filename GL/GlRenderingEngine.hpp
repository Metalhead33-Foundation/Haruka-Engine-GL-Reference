#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP
#include "../abstract/SettingContainer.hpp"
#include <cstdlib>
#include "glad_glx.h"
#include "../abstract/RenderingEngine.hpp"
#include "GlQuad.hpp"
namespace Gl {

DEFINE_CLASS(RenderingEngine)
class RenderingEngine : public Abstract::RenderingEngine
{
public:
private:
	const Abstract::sSettingContainer settings;
	XVisualInfo* vi;
	GLXContext cnt;
	Abstract::sFramebuffer framebuffer;

	bool twoDProjection;
	static sQuad QUAD_SCR;
public:
	RenderingEngine(Abstract::sSettingContainer nsettings,uint32_t sampleCount, uint32_t supersampleCount);
	~RenderingEngine();
	void switchBuffers();
	void clearDepthBuffer();
	void clearBackground();
	void clearBackground(unsigned char r, unsigned char g, unsigned char b);
	static GLint VISUAL_ATTRIBUTES[];
	static GLint CONTEXT_ATTRIBUTES[];
	Abstract::sShaderModule createShaderModule(Abstract::ShaderModule::ShaderType ntype, Abstract::sFIO reada);
	Abstract::sShaderProgram createShaderProgram();
	Abstract::sTexture createTextureFromDDS(Abstract::Texture::textureType ntype, Abstract::sFIO reada);
	Abstract::sTexture createTextureFromImage(Abstract::Texture::textureType ntype, Abstract::sFIO reada);
	Abstract::sAnimatedTexture createTextureFromGIF(Abstract::Texture::textureType ntype, Abstract::sFIO reada);
	Abstract::sMesh createMesh(Abstract::Mesh::ConstructorReference ref);
	MeshCreator getMeshCreator() const;
	Abstract::sFramebuffer createFramebuffer(uint32_t nwidth, uint32_t nheight, uint32_t nsamples = 0);
	void renderFramebuffer(const Abstract::sShaderProgram shader);
	Abstract::sFramebuffer getFramebuffer();
	void setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

	void renderFrame();
	void startup();
	void cleanup();
};

}

extern "C" {
Abstract::sRenderingEngine createGlEngine(Abstract::sSettingContainer settings,uint32_t sampleCount, uint32_t supersampleCount);
}
#endif // RENDERWINDOW_HPP
