#ifndef GLRASTERDRAWABLE_HPP
#define GLRASTERDRAWABLE_HPP
#include "../abstract/RasterDrawable.hpp"
#include "GlQuad.hpp"

namespace Gl {

class RasterDrawable : public Abstract::RasterDrawable
{
private:
	Abstract::sTexture tex;
	static size_t instances;
	static sQuad QUAD;
public:
	RasterDrawable();
	~RasterDrawable();
	void render(const glm::mat4& model, Abstract::sShaderProgram shader);
	const Abstract::sTexture getTexture() const;
	void setTexture(Abstract::sTexture ntexture);
};

}
#endif // GLRASTERDRAWABLE_HPP
