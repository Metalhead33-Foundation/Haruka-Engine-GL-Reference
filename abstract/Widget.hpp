#ifndef WIDGET_HPP
#define WIDGET_HPP
#include "Vertex.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include <vector>
#include <glm/glm.hpp>

namespace Abstract {

DEFINE_CLASS(Widget)
class Widget
{
public:
	virtual ~Widget() = default;
	virtual void setTexture(sTexture tex) = 0;
	virtual sTexture getTexture() = 0;
	virtual void setWidth(int width) = 0;
	virtual void setHeight(int height) = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
	virtual void draw(sShaderProgram shader, glm::vec2& position,
					  glm::mat4& projection) = 0;
};
}
#endif // WIDGET_HPP
