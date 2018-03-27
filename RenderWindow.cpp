#include "RenderWindow.hpp"
GLint RenderWindow::att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

RenderWindow::RenderWindow(sSettingContainer nsettings)
	: settings(nsettings)
{
	vi = glXChooseVisual(settings->sysWMinfo->info.x11.display,0,att);
	cnt = glXCreateContext(settings->sysWMinfo->info.x11.display,vi,0,true);
	glXMakeCurrent(settings->sysWMinfo->info.x11.display, settings->sysWMinfo->info.x11.window, cnt);
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
