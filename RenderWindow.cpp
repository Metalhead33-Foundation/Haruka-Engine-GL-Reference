#include "RenderWindow.hpp"
#include <stdexcept>
#include <dlfcn.h>

GLint RenderWindow::att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

RenderWindow::RenderWindow(sSettingContainer nsettings)
	: settings(nsettings)
{
	if (!gladLoadGLX(settings->sysWMinfo->info.x11.display,DefaultScreen(settings->sysWMinfo->info.x11.display))) throw std::runtime_error("Couldn't load GLX!!");
	vi = glXChooseVisual(settings->sysWMinfo->info.x11.display,0,att);
	cnt = glXCreateContext(settings->sysWMinfo->info.x11.display,vi,0,true);
	glXMakeCurrent(settings->sysWMinfo->info.x11.display, settings->sysWMinfo->info.x11.window, cnt);
	if (!gladLoadGL()) throw std::runtime_error("Couldn't load OpenGL!");
}
RenderWindow::~RenderWindow()
{
	glXMakeCurrent(settings->sysWMinfo->info.x11.display, None, NULL);
	glXDestroyContext(settings->sysWMinfo->info.x11.display, cnt);
}
void RenderWindow::switchBuffers()
{
	glXSwapBuffers(settings->sysWMinfo->info.x11.display, settings->sysWMinfo->info.x11.window);
}
