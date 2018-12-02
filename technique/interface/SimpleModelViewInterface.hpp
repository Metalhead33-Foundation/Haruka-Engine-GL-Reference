#ifndef SIMPLEMODELVIEWINTERFACE_HPP
#define SIMPLEMODELVIEWINTERFACE_HPP
#include "../../gfx/Model.hpp"
#include "../../abstract/Texture.hpp"

DEFINE_CLASS(SimpleModelViewInterface)
class SimpleModelViewInterface {
public:
	virtual ~SimpleModelViewInterface() = default;
	virtual void run(const GFX::sModel& model, const glm::mat4& modelMatrix,
					 const Abstract::sTexture& texture) = 0;
};

#endif // SIMPLEMODELVIEWINTERFACE_HPP
