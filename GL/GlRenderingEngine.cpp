#include "GlRenderingEngine.hpp"
#include <stdexcept>
#include <dlfcn.h>
#include "GlShaderModule.hpp"
#include "GlShaderProgram.hpp"
#include "GlTexture.hpp"
#include "GlMesh.hpp"
#include <glm/gtc/matrix_transform.hpp>

Abstract::sRenderingEngine createGlEngine(Abstract::sSettingContainer settings)
{
	return Abstract::sRenderingEngine(new Gl::RenderingEngine(settings));
}


namespace Gl {

RenderingEngine::sQuad RenderingEngine::QUAD = nullptr;
RenderingEngine::Quad::Quad()
{
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &quadArrayId);
	glGenBuffers(1, &quadBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, quadBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(quadArrayId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
RenderingEngine::Quad::~Quad()
{
	glDeleteVertexArrays(1,&quadArrayId);
	glDeleteBuffers(1, &quadBufferId);
}
void RenderingEngine::Quad::draw()
{
	glBindVertexArray(quadArrayId);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

GLint RenderingEngine::att[] = { GLX_RGBA,
								 GLX_X_VISUAL_TYPE_EXT,
								 GLX_TRUE_COLOR_EXT,
								 GLX_DEPTH_SIZE,
								 24,
								 GLX_RED_SIZE,
								 8,
								 GLX_BLUE_SIZE,
								 8,
								 GLX_GREEN_SIZE,
								 8,
								 GLX_DOUBLEBUFFER,
								 None };

RenderingEngine::RenderingEngine(Abstract::sSettingContainer nsettings)
	: settings(nsettings), twoDProjection(false)
{
	if (!gladLoadGLX(settings->sysWMinfo->info.x11.display,DefaultScreen(settings->sysWMinfo->info.x11.display))) throw std::runtime_error("Couldn't load GLX!!");
	XWindowAttributes attr;
	XGetWindowAttributes(settings->sysWMinfo->info.x11.display,settings->sysWMinfo->info.x11.window, &attr);
	vi = glXChooseVisual(settings->sysWMinfo->info.x11.display,
						 DefaultScreen(settings->sysWMinfo->info.x11.display),
						 att);
	if(!vi) throw std::runtime_error("Invalid GLX attributes!");
	// XVisualInfo vin; int n;
	// vi = XGetVisualInfo(settings->sysWMinfo->info.x11.display, VisualScreenMask | VisualIDMask, &vin, &n);
	// vin.screen = DefaultScreen(settings->sysWMinfo->info.x11.display);
	cnt = glXCreateContext(settings->sysWMinfo->info.x11.display,vi,0,true);
	if(!cnt) throw std::runtime_error("Couldn't create GLX context!");
	glXMakeCurrent(settings->sysWMinfo->info.x11.display, settings->sysWMinfo->info.x11.window, cnt);
	if (!gladLoadGL()) throw std::runtime_error("Couldn't load OpenGL!");
	QUAD = sQuad(new Quad());
}
void RenderingEngine::renderWidget(const Abstract::WidgetProperties &widget, glm::mat4& projection, Abstract::sShaderProgram shader)
{
	ShaderProgram* gshdr = dynamic_cast<ShaderProgram*>(shader.get());
	if(!gshdr) return;
	gshdr->useShader();
	// Do the matrix stuff
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(widget.pos, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * widget.size.x, 0.5f * widget.size.y, 0.0f));
	model = glm::translate(model, glm::vec3(-0.5f * widget.size.x, -0.5f * widget.size.y, 0.0f));
	model = glm::scale(model, glm::vec3(widget.size, 1.0f));

	gshdr->setMat4("projection", projection);
	gshdr->setMat4("model", model);
	Texture* tex;
	tex = dynamic_cast<Texture*>(widget.texture.get());
	if(tex) {
		glActiveTexture(tex->getTextureId()); // active proper texture unit before binding
		glBindTexture(GL_TEXTURE_2D, tex->getTextureId());
		glUniform1i(glGetUniformLocation(gshdr->getShaderID(), tex->stringizeType()), 0);
	}
	// draw mesh
	QUAD->draw();

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}
Abstract::sMesh RenderingEngine::createMesh(Abstract::Mesh::ConstructorReference ref)
{
	return Mesh::createMesh(ref);
}
RenderingEngine::MeshCreator RenderingEngine::getMeshCreator() const
{
	return Mesh::createMesh;
}

RenderingEngine::~RenderingEngine()
{
	QUAD = nullptr;
	glXMakeCurrent(settings->sysWMinfo->info.x11.display, None, NULL);
	glXDestroyContext(settings->sysWMinfo->info.x11.display, cnt);
}
void RenderingEngine::switchBuffers()
{
	glXSwapBuffers(settings->sysWMinfo->info.x11.display, settings->sysWMinfo->info.x11.window);
}
void RenderingEngine::clearBackground()
{
	glClearColor(0, 0.5, 1, 1 );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderingEngine::renderFrame()
{
	switchBuffers();
}
void RenderingEngine::startup()
{
	GLfloat calaz[4] = { 0, 0.5, 1, 1 };

	glEnable(GL_DEPTH_TEST);
	glClearColor( calaz[0], calaz[1], calaz[2], calaz[3] );
	glClear( GL_COLOR_BUFFER_BIT );
}
void RenderingEngine::cleanup()
{
	;
}

Abstract::sShaderModule RenderingEngine::createShaderModule(Abstract::ShaderModule::ShaderType ntype, Abstract::sFIO reada)
{
	return ShaderModule::createShaderModule(ntype, reada);
}
Abstract::sShaderProgram RenderingEngine::createShaderProgram()
{
	return ShaderProgram::createShaderProgram();
}
Abstract::sTexture RenderingEngine::createTextureFromDDS(Abstract::Texture::textureType ntype, Abstract::sFIO reada)
{
	return Texture::createFromDDS(ntype, reada);
}
Abstract::sTexture RenderingEngine::createTextureFromImage(Abstract::Texture::textureType ntype, Abstract::sFIO reada)
{
	return Texture::createFromImage(ntype, reada);
}

}
