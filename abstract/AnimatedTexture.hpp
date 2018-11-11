#ifndef ANIMATEDTEXTURE_HPP
#define ANIMATEDTEXTURE_HPP
#include "Texture.hpp"
#include "Animated.hpp"
namespace Abstract {

DEFINE_CLASS(AnimatedTexture)
class AnimatedTexture : public Texture, public virtual Animated
{
public:
	typedef sAnimatedImageContainer sAnimatedTextureConstructor;
	virtual ~AnimatedTexture() = default;
};

}
#endif // ANIMATEDTEXTURE_HPP
