#include "GlAnimated.hpp"

namespace Gl {

void Animated::goForward(float forward)
{
	timer += forward;
	while(timer >= frameSwitchRate)
	{
		++currFrame;
		timer -= frameSwitchRate;
	}
	currFrame %= getFrameCount();
}
uint32_t Animated::getCurrentFrame()
{
	return currFrame;
}
void Animated::switchFrame(uint32_t newFrame)
{
	currFrame = newFrame % getFrameCount();
}
float Animated::getFrameSwitchRate()
{
	return frameSwitchRate;
}
void Animated::setFrameSwitchRate(float newRate)
{
	frameSwitchRate = newRate;
}

}
