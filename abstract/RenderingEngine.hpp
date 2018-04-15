#ifndef RENDERINGENGINE_HPP
#define RENDERINGENGINE_HPP
#include "SettingContainer.hpp"
#include <cstdlib>
#include "ShaderModule.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "FIO.hpp"

namespace Abstract {

DEFINE_CLASS(RenderingEngine)
class RenderingEngine
{
protected:
	Abstract::sSettingContainer settings;
public:
	virtual ~RenderingEngine() = default;
	virtual void switchBuffers() = 0;
	virtual sShaderModule createShaderModule(ShaderModule::ShaderType ntype, sFIO reada) = 0;
	virtual sShaderProgram createShaderProgram() = 0;
	virtual sTexture createTextureFromDDS(Texture::textureType ntype, sFIO reada) = 0;
	virtual sTexture createTextureFromImage(Texture::textureType ntype, sFIO reada) = 0;
	virtual sMesh createMesh(Mesh::ConstructorReference ref) = 0;

	virtual void renderFrame() = 0;
	virtual void startup() = 0;
	virtual void cleanup() = 0;
};

}
extern "C" {
typedef Abstract::sRenderingEngine (*RenderingBackendFactoryFunction)(Abstract::sSettingContainer);
}

#endif // RENDERINGENGINE_HPP
