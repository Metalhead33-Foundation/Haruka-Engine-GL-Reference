#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include "Global.hpp"
#include "ShaderProgram.hpp"
#include <glm/glm.hpp>
#include <unordered_map>

namespace Abstract {
DEFINE_CLASS(Widget)
class Drawable
{
public:
	virtual ~Drawable() = default;
	virtual void render(const glm::mat4& projection, const glm::mat4& model, float rotation, sShaderProgram shader) = 0;
};

}
#endif // DRAWABLE_HPP
