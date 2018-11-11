#ifndef WIDGET_HPP
#define WIDGET_HPP
#include "../abstract/Drawable.hpp"
#include <unordered_map>

namespace GFX {

DEFINE_CLASS(Widget)
class Widget
{
public:
	typedef std::unordered_map<std::string,sWidget> SubwidgetMap;
	typedef SubwidgetMap::iterator SubwidgetIterator;
private:
	SubwidgetMap subwidgets;
	glm::vec2 pos; // Absolute position if top widget, relative within parent widget otherwise
	glm::vec2 size;
	float rotation;
	Abstract::sDrawable drawable;
	Abstract::sShaderProgram shader;

	glm::mat4 model;
	glm::mat4 origin;
protected:
	void updateModel(bool cascade=true);
	void updateModel(const glm::mat4 &norigin, bool cascade=true);
public:
	Widget();
	const glm::vec2& getPos() const;
	const glm::vec2& getSize() const;
	float getRotation() const;
	void setPos(const glm::vec2& npos, bool cascade=true);
	void setSize(const glm::vec2& nsize, bool cascade=false);
	void setRotation(float nrotation, bool cascade=false);
	const Abstract::sDrawable getDrawable() const;
	void setDrawable(Abstract::sDrawable ndrawable);
	const Abstract::sShaderProgram getShader() const;
	void setShader(Abstract::sShaderProgram nshader);
	void render(const glm::mat4& projection);
};

}
#endif // WIDGET_HPP
