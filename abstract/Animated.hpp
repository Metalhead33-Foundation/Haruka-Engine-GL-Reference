#ifndef ANIMATED_HPP
#define ANIMATED_HPP
#include "Global.hpp"
namespace Abstract {

DEFINE_CLASS(Animated)
class Animated
{
public:
	virtual ~Animated() = default;
	virtual uint32_t getFrameCount() const = 0;
	virtual uint32_t getCurrentFrame() const = 0;
	virtual void switchFrame(uint32_t newFrame) = 0;
	virtual float getFrameSwitchRate() = 0;
	virtual void setFrameSwitchRate(float newRate) = 0;
	virtual void goForward(float forward) = 0;
};

}
#endif // ANIMATED_HPP
