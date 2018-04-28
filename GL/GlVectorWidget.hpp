#ifndef GLVECTORWIDGET_HPP
#define GLVECTORWIDGET_HPP
#include "../abstract/VectorWidget.hpp"
#include "glad_glx.h"
#include "../io/rbvi.h"
#include <vector>

namespace Gl {

DEFINE_CLASS(VectorWidget)
class VectorWidget : public Abstract::VecorWidget
{
public:
	struct RenderableVector
	{
		GLuint imageVAO;
		GLuint imageVBO;
		GLuint imageEBO;
		glm::vec4 colourA;
		glm::vec4 colourB;
		bool colourCentering;
		void draw(Abstract::sShaderProgram prog, const glm::mat4& model, const glm::mat4& projection);
		RenderableVector(RbviLayerHeader& layHead, RbviHeader& header, Abstract::sFIO readah);
		GLint indices;
		~RenderableVector();
	};
	typedef std::vector<RenderableVector> LayerVector;
	typedef LayerVector::iterator LayerIterator;
private:
	LayerVector layers;
	glm::vec2 size,originalSize;
	glm::vec2 pos;
	float rotation;
	VectorWidget(Abstract::sFIO readah);
public:
	static Abstract::sVectorWidget create(Abstract::sFIO readah);
	const glm::vec2& getSize(void) const;
	const glm::vec2& getPos(void) const;
	float getRotation(void) const;

	void setSize(const glm::vec2& nsize);
	void setPos(const glm::vec2& npos);
	void setRotation(float nrotation);
	void draw(Abstract::sShaderProgram prog, const glm::mat4& projection);
	void defaultSize();
	void scale(const glm::vec2& scaler);
	void snapToWidth(float x);
	void snapToHeight(float y);
};

}
#endif // GLVECTORWIDGET_HPP
