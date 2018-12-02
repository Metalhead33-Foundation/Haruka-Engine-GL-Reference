#include "AbstractTechniquePrototype.hpp"
#include <stdexcept>

namespace Abstract {

TechniquePrototype::TechniquePrototype(const Abstract::sShaderProgram shader)
	: shader(shader)
{
	if(!shader) throw std::runtime_error("This technique expected a shader program, but got a null pointer instead!");
	if(!shader->isValid()) throw std::runtime_error("This technique requires a succesfully compiled shader to work!");
}

}
