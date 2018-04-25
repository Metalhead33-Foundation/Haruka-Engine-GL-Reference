#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP
#include "../abstract/SettingContainer.hpp"
#include <cstdlib>
#include "glad_glx.h"
#include "../abstract/RenderingEngine.hpp"
namespace Gl {

DEFINE_CLASS(RenderingEngine)
class RenderingEngine : public Abstract::RenderingEngine
{
public:
	struct Quad
	{
		GLuint quadArrayId;
		GLuint quadBufferId;
		Quad();
		~Quad();
		void draw();
	};
	typedef std::shared_ptr<Quad> sQuad;
private:
	const Abstract::sSettingContainer settings;
	XVisualInfo* vi;
	GLXContext cnt;

	bool twoDProjection;
	static sQuad QUAD;
public:
	RenderingEngine(Abstract::sSettingContainer nsettings);
	~RenderingEngine();
	void switchBuffers();
	void clearBackground();
	static GLint att[];
	Abstract::sShaderModule createShaderModule(Abstract::ShaderModule::ShaderType ntype, Abstract::sFIO reada);
	Abstract::sShaderProgram createShaderProgram();
	Abstract::sTexture createTextureFromDDS(Abstract::Texture::textureType ntype, Abstract::sFIO reada);
	Abstract::sTexture createTextureFromImage(Abstract::Texture::textureType ntype, Abstract::sFIO reada);
	Abstract::sMesh createMesh(Abstract::Mesh::ConstructorReference ref);
	void renderWidget(const Abstract::WidgetProperties& widget, glm::mat4& projection, Abstract::sShaderProgram shader);
	MeshCreator getMeshCreator() const;
	void renderMesh(const Abstract::sMesh mesh, const Abstract::sShaderProgram shader, const Abstract::Mesh::TextureVector& textures, const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model);

	void renderFrame();
	void startup();
	void cleanup();
};

}

extern "C" {
Abstract::sRenderingEngine createGlEngine(Abstract::sSettingContainer settings);
}
#endif // RENDERWINDOW_HPP
