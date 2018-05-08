#ifndef WIDGET_HPP
#define WIDGET_HPP
#include "Global.hpp"
#include "ShaderProgram.hpp"
#include <glm/glm.hpp>
#include <unordered_map>

namespace Abstract {
DEFINE_CLASS(Widget)
class Widget
{
public:
	typedef std::unordered_map<std::string, sWidget> SubwidgetList;
	typedef SubwidgetList::iterator SubwidgetIterator;

	virtual ~Widget() = default;
	virtual const glm::vec2& getPosition() const = 0;
	virtual const glm::vec2& getSize() const = 0;
	virtual float getRotation() const = 0;
	virtual void setPosition(const glm::vec2& npos) = 0;
	virtual void setSize(const glm::vec2& nsize) = 0;
	virtual void setRotation(float nrotation) = 0;

	virtual void render(const glm::mat4& projection, sShaderProgram shader) = 0;

	virtual const SubwidgetList& getSubwidgetList() const = 0;
	virtual SubwidgetIterator findSubwidget(const std::string& key) const = 0;
	virtual SubwidgetIterator eraseSubwidget(SubwidgetIterator it) const = 0;
	virtual SubwidgetIterator eraseSubwidget(const std::string& key) const = 0;
	virtual SubwidgetIterator beginSubwidgetIteration() const = 0;
	virtual SubwidgetIterator endSubwidgetIteration() const = 0;
	virtual void insertSubwidget(const std::string& key, sWidget widget) const = 0;
};

}
#endif // WIDGET_HPP
