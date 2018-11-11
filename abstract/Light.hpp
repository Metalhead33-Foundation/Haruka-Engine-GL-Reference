#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <glm/vec3.hpp>
namespace Abstract {

struct AmbientLight {
	glm::vec3 colour;
	float intensity;
};

struct DirectionalLight
{
	glm::vec3 colour;
	glm::vec3 direction;
	float diffuseIntensity;
};

}

#endif // LIGHT_HPP
