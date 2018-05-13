#ifndef GLKEYFRAMEANIMATION_HPP
#define GLKEYFRAMEANIMATION_HPP
#include "../abstract/KeyframeAnimation.hpp"
#include "GlMesh.hpp"

namespace Gl {

class KeyframeAnimation : public Abstract::KeyframeAnimation
{
private:
	FrameVector frames;
	GLuint VAO;
	GLsizei indexSize;
	bool bound;
public:
	KeyframeAnimation();
	~KeyframeAnimation();
	const FrameVector& getFrameVector() const;
	void bindFrames(size_t frame1, size_t frame2);
	void bindAnimation();
};

}
#endif // GLKEYFRAMEANIMATION_HPP
