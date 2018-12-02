#ifndef WIDGET2D_HPP
#define WIDGET2D_HPP
#include"SimpleWidgetViewWrapper.hpp"

DEFINE_CLASS(Widget2D)
class Widget2D : public SimpleWidgetViewWrapper
{
private:
	glm::vec2 pos; // Absolute position on screen
	glm::vec2 size;
	float rotation;
	void updateModel();
public:
	Widget2D();
	const glm::vec2& getPos() const;
	const glm::vec2& getSize() const;
	float getRotation() const;

	void setPos(const glm::vec2& setto, bool update=true);
	void setSize(const glm::vec2& setto, bool update=true);
	void setRotation(float setto, bool update=true);
};

#endif // WIDGET2D_HPP
