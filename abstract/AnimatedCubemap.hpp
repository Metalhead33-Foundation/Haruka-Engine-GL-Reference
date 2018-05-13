#ifndef ANIMATEDCUBEMAP_HPP
#define ANIMATEDCUBEMAP_HPP
#include "Animated.hpp"
#include "Cubemap.hpp"
namespace Abstract {

DEFINE_CLASS(AnimatedCubemap)
class AnimatedCubemap : public Cubemap, public virtual Animated
{
public:
	friend class ShaderProgram;
public:
	virtual ~AnimatedCubemap() = default;
};

}
#endif // ANIMATEDCUBEMAP_HPP
