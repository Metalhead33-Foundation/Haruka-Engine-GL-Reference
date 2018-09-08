#ifndef ANIMATEDCUBEMAP_HPP
#define ANIMATEDCUBEMAP_HPP
#include "Animated.hpp"
#include "Cubemap.hpp"
namespace Abstract {

DEFINE_CLASS(AnimatedCubemap)
class AnimatedCubemap : public Cubemap, public virtual Animated
{
public:
	typedef sAnimatedImageContainer sAnimatedTextureConstructor;
	friend class ShaderProgram;
	virtual ~AnimatedCubemap() = default;
};

}
#endif // ANIMATEDCUBEMAP_HPP
