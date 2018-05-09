#include "GlRasterDrawable.hpp"
namespace Gl {

size_t RasterDrawable::instances = 0;
sQuad RasterDrawable::QUAD = nullptr;

RasterDrawable::RasterDrawable()
{
	if(!instances) QUAD = sQuad(new Quad(false));
	++instances;
}
RasterDrawable::~RasterDrawable()
{
	--instances;
	if(!instances) QUAD = nullptr;
}
void RasterDrawable::render(const glm::mat4& model, Abstract::sShaderProgram shader)
{
	if(shader)
	{
		shader->setMat4("model", model);
		if(tex) shader->bindTexture(tex);
		QUAD->draw();
		glActiveTexture(GL_TEXTURE0);
	}
}
const Abstract::sTexture RasterDrawable::getTexture() const
{
	return tex;
}
void RasterDrawable::setTexture(Abstract::sTexture ntexture)
{
	tex = ntexture;
}

}
