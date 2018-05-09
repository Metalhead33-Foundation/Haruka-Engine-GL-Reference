#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include "Global.hpp"
#include "ShaderProgram.hpp"
#include <glm/glm.hpp>

namespace Abstract {
DEFINE_CLASS(Drawable)
class Drawable
{
public:
	virtual ~Drawable() = default;
	virtual void render(const glm::mat4& model, sShaderProgram shader) = 0;
};

}
#endif // DRAWABLE_HPP
