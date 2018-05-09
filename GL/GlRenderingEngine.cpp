#include "GlRenderingEngine.hpp"
#include <stdexcept>
#include <dlfcn.h>
#include "GlShaderModule.hpp"
#include "GlShaderProgram.hpp"
#include "GlTexture.hpp"
#include "GlAnimatedTexture.hpp"
#include "GlFramebuffer.hpp"
#include "GlMesh.hpp"
#include <glm/gtc/matrix_transform.hpp>

Abstract::sRenderingEngine createGlEngine(Abstract::sSettingContainer settings, uint32_t sampleCount, uint32_t supersampleCount)
{
	return Abstract::sRenderingEngine(new Gl::RenderingEngine(settings,sampleCount,supersampleCount));
}


namespace Gl {

// QUAD_WID, QUAD_SCR;

sQuad RenderingEngine::QUAD_WID = nullptr;
sQuad RenderingEngine::QUAD_SCR = nullptr;

GLint RenderingEngine::VISUAL_ATTRIBUTES[] = { // GLX_RGBA,
								 // GLX_X_VISUAL_TYPE_EXT,
								 // GLX_TRUE_COLOR_EXT,
								 /*GLX_DEPTH_SIZE,
								 24,
								 GLX_RED_SIZE,
								 8,
								 GLX_BLUE_SIZE,
								 8,
								 GLX_GREEN_SIZE,
								 8,*/
								 GLX_DOUBLEBUFFER,
								 1,
								 None };
GLint RenderingEngine::CONTEXT_ATTRIBUTES[] = {
	GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
	GLX_CONTEXT_MINOR_VERSION_ARB, 3,
	//GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
	None
};

RenderingEngine::RenderingEngine(Abstract::sSettingContainer nsettings, uint32_t sampleCount, uint32_t supersampleCount)
	: settings(nsettings), twoDProjection(false)
{
	if (!gladLoadGLX(settings->sysWMinfo->info.x11.display,DefaultScreen(settings->sysWMinfo->info.x11.display))) throw std::runtime_error("Couldn't load GLX!!");
	/*XWindowAttributes attr;
	XGetWindowAttributes(settings->sysWMinfo->info.x11.display,settings->sysWMinfo->info.x11.window, &attr);
	vi = glXChooseVisual(settings->sysWMinfo->info.x11.display,
						 DefaultScreen(settings->sysWMinfo->info.x11.display),
						 VISUAL_ATTRIBUTES);
	if(!vi) throw std::runtime_error("Invalid GLX attributes!");
	// XVisualInfo vin; int n;
	// vi = XGetVisualInfo(settings->sysWMinfo->info.x11.display, VisualScreenMask | VisualIDMask, &vin, &n);
	// vin.screen = DefaultScreen(settings->sysWMinfo->info.x11.display);
	cnt = glXCreateContext(settings->sysWMinfo->info.x11.display,vi,0,true);*/
	int fbcount;
	GLXFBConfig *fbc = glXChooseFBConfig( settings->sysWMinfo->info.x11.display,
						DefaultScreen(settings->sysWMinfo->info.x11.display),
						VISUAL_ATTRIBUTES, &fbcount );
	if(!fbc) throw std::runtime_error("Failed to retrieve a framebuffer config");
	cnt = glXCreateContextAttribsARB(settings->sysWMinfo->info.x11.display,fbc[0],0,true,CONTEXT_ATTRIBUTES);
	if(!cnt) throw std::runtime_error("Couldn't create GLX context!");

	// Now that we have the context
	glXMakeCurrent(settings->sysWMinfo->info.x11.display, settings->sysWMinfo->info.x11.window, cnt);
	if (!gladLoadGL()) throw std::runtime_error("Couldn't load OpenGL!");
	glEnable(GL_MULTISAMPLE);
	glViewport(0,0,settings->w, settings->h);
	QUAD_WID = sQuad(new Quad(false));
	QUAD_SCR = sQuad(new Quad(true));
	framebuffer = Framebuffer::create(uint32_t(settings->w)*supersampleCount, uint32_t(settings->h)*supersampleCount,sampleCount);
}
void RenderingEngine::setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
	glViewport(x,y,w,h);
}
void RenderingEngine::renderFramebuffer(const Abstract::sShaderProgram shader)
{
	if(shader)
	{
		shader->useShader();
		shader->bindTexture(framebuffer);
		QUAD_SCR->draw();
		glActiveTexture(GL_TEXTURE0);
	}
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
	QUAD_WID = nullptr;
	QUAD_SCR = nullptr;
	glXMakeCurrent(settings->sysWMinfo->info.x11.display, None, NULL);
	glXDestroyContext(settings->sysWMinfo->info.x11.display, cnt);
}
void RenderingEngine::clearDepthBuffer()
{
	glClear( GL_DEPTH_BUFFER_BIT );
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
void RenderingEngine::clearBackground(unsigned char r, unsigned char g, unsigned char b)
{
	glClearColor(float(r) / float(255), float(g) / float(255), float(b) / float(255), 1 );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
Abstract::sFramebuffer RenderingEngine::createFramebuffer(uint32_t nwidth, uint32_t nheight, uint32_t nsamples)
{
	return Framebuffer::create(nwidth, nheight, nsamples);
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
Abstract::sAnimatedTexture RenderingEngine::createTextureFromGIF(Abstract::Texture::textureType ntype, Abstract::sFIO reada)
{
	return AnimatedTexture::create(ntype, reada);
}
Abstract::sFramebuffer RenderingEngine::getFramebuffer()
{
	return framebuffer;
}

}
