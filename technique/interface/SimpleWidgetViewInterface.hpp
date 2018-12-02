#ifndef SIMPLEWIDGETVIEWINTERFACE_HPP
#define SIMPLEWIDGETVIEWINTERFACE_HPP
#include "../../abstract/VertexProvider.hpp"
#include "../../abstract/Texture.hpp"
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
DEFINE_CLASS(SimpleWidgetViewInterface)
class SimpleWidgetViewInterface {
	public:
	virtual ~SimpleWidgetViewInterface() = default;
	virtual void run(const glm::mat4& model, const glm::mat4& projection,
					 const Abstract::sTexture& texture) = 0;
};
#endif // SIMPLEWIDGETVIEWINTERFACE_HPP
