#ifndef VECTORWIDGET_HPP
#define VECTORWIDGET_HPP
#include "FIO.hpp"
#include "ShaderProgram.hpp"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace Abstract {

DEFINE_CLASS(VectorWidget)
class VectorWidget
{
public:
	virtual ~VectorWidget() default;
	virtual const glm::vec2& getSize(void) const = 0;
	virtual const glm::vec2& getPos(void) const = 0;
	virtual float getRotation(void) const = 0;

	virtual void setSize(const glm::vec2& nsize) = 0;
	virtual void setPos(const glm::vec2& npos) = 0;
	virtual void setRotation(float nrotation) = 0;
	virtual void draw(sShaderProgram prog, const glm::mat4& projection) = 0;
	virtual void defaultSize() = 0;
	virtual void scale(const glm::vec2& scaler) = 0;
	virtual void snapToWidth(float x) = 0;
	virtual void snapToHeight(float y) = 0;
};

}
#endif // VECTORWIDGET_HPP
