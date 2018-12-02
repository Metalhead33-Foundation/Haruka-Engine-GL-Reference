#ifndef ABSTRACTTECHNIQUEPROTOTYPE_HPP
#define ABSTRACTTECHNIQUEPROTOTYPE_HPP
#include "../../abstract/ShaderProgram.hpp"
namespace Abstract {

DEFINE_CLASS(TechniquePrototype)
class TechniquePrototype {
protected:
	const Abstract::sShaderProgram shader;
public:
	TechniquePrototype(const Abstract::sShaderProgram shader);
	virtual ~TechniquePrototype() = default;
};

}

#endif // ABSTRACTTECHNIQUEPROTOTYPE_HPP
