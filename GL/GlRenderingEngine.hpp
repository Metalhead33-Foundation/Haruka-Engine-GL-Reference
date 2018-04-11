#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP
#include "../abstract/SettingContainer.hpp"
#include <cstdlib>
#include "glad_glx.h"
#include "../abstract/RenderingEngine.hpp"
namespace Gl {

class RenderingEngine : public Abstract::RenderingEngine
{
private:
	const Abstract::sSettingContainer settings;
	XVisualInfo* vi;
	GLXContext cnt;

public:
	RenderingEngine(Abstract::pSettingContainer nsettings);
	~RenderingEngine();
	void switchBuffers();
	static GLint att[];
	Abstract::sShaderModule createShaderModule(Abstract::ShaderModule::ShaderType ntype, Abstract::sFIO reada);
	Abstract::sShaderProgram createShaderProgram();
	Abstract::sTexture createTextureFromDDS(Abstract::Texture::textureType ntype, Abstract::sFIO reada);
	Abstract::sTexture createTextureFromImage(Abstract::Texture::textureType ntype, Abstract::sFIO reada);

	void renderFrame();
	void startup();
	void cleanup();

	static Abstract::pRenderingEngine createGlEngine(Abstract::pSettingContainer settings);
};

}
#endif // RENDERWINDOW_HPP
