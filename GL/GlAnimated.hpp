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
	virtual ~Animated() = default;
	uint32_t getFrameCount() const;
	uint32_t getCurrentFrame() const;
	void switchFrame(uint32_t newFrame);
	float getFrameSwitchRate();
	void setFrameSwitchRate(float newRate);
	void goForward(float forward);
};

}
#endif // GLANIMATED_HPP
