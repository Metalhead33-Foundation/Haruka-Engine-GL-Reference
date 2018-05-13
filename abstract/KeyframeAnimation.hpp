#ifndef KEYFRAMEANIMATION_HPP
#define KEYFRAMEANIMATION_HPP
#include "Mesh.hpp"
namespace Abstract {

DEFINE_CLASS(KeyframeAnimation)
class KeyframeAnimation
{
public:
	typedef std::vector<sMesh> FrameVector;
	virtual ~KeyframeAnimation() = default;
	virtual const FrameVector& getFrameVector() const = 0;
	virtual void bindFrames(size_t frame1, size_t frame2) = 0;
	virtual void bindAnimation() = 0;
};

}

#endif // KEYFRAMEANIMATION_HPP
