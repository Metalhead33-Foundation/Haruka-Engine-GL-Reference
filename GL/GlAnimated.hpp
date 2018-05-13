#ifndef GLANIMATED_HPP
#define GLANIMATED_HPP
#include "../abstract/Animated.hpp"
namespace Gl {

class Animated : public virtual Abstract::Animated
{
protected:
	uint32_t currFrame;
	float frameSwitchRate;
	float timer;
public:
	virtual ~Animated() = 0;
	uint32_t getFrameCount();
	uint32_t getCurrentFrame();
	void switchFrame(uint32_t newFrame);
	float getFrameSwitchRate();
	void setFrameSwitchRate(float newRate);
	void goForward(float forward);
};

}
#endif // GLANIMATED_HPP
