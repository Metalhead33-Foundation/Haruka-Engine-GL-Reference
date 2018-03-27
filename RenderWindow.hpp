#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP
#include "SettingContainer.hpp"
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>

class RenderWindow
{
private:
	const sSettingContainer settings;
	XVisualInfo* vi;
	GLXContext cnt;
public:
	RenderWindow(sSettingContainer nsettings);
	~RenderWindow();
	void switchBuffers();
	static GLint att[];

};

#endif // RENDERWINDOW_HPP
