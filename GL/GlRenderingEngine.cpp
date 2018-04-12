#include "GlRenderingEngine.hpp"
#include <stdexcept>
#include <dlfcn.h>
#include "GlShaderModule.hpp"
#include "GlShaderProgram.hpp"
#include "GlTexture.hpp"


Abstract::sRenderingEngine createGlEngine(Abstract::sSettingContainer settings)
{
	return Abstract::sRenderingEngine(new Gl::RenderingEngine(settings));
}


namespace Gl {

GLint RenderingEngine::att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

RenderingEngine::RenderingEngine(Abstract::sSettingContainer nsettings)
	: settings(nsettings)
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
}

RenderingEngine::~RenderingEngine()
{
	glXMakeCurrent(settings->sysWMinfo->info.x11.display, None, NULL);
	glXDestroyContext(settings->sysWMinfo->info.x11.display, cnt);
}
void RenderingEngine::switchBuffers()
{
	glXSwapBuffers(settings->sysWMinfo->info.x11.display, settings->sysWMinfo->info.x11.window);
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
