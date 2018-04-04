#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP
#include "../abstract/SettingContainer.hpp"
#include <cstdlib>
#include "glad_glx.h"

class RenderWindow
{
private:
	const Abstract::sSettingContainer settings;
	XVisualInfo* vi;
	GLXContext cnt;

public:
	RenderWindow(Abstract::sSettingContainer nsettings);
	~RenderWindow();
	void switchBuffers();
	static GLint att[];

};

#endif // RENDERWINDOW_HPP
