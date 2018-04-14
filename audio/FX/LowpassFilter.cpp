#include "LowpassFilter.hpp"
namespace Audio {

LowpassFilter::LowpassFilter()
{
	alFilteri(filterID,AL_FILTER_TYPE,AL_FILTER_LOWPASS);
}
LowpassFilter::LowpassFilter(const LowpassFilter& cpy)
{
	alFilteri(filterID,AL_FILTER_TYPE,AL_FILTER_LOWPASS);
	setGain(cpy.getGain());
	setHighFrequencyGain(cpy.getHighFrequencyGain());
}
sLowpassFilter LowpassFilter::create()
{
	return sLowpassFilter(new LowpassFilter());
}
sLowpassFilter LowpassFilter::create(sLowpassFilter cpy)
{
	if(cpy) return sLowpassFilter(new LowpassFilter(*cpy));
	else return sLowpassFilter(new LowpassFilter());
}
ALenum LowpassFilter::getFilterType()
{
	return AL_FILTER_LOWPASS;
}
void LowpassFilter::setGain(float gain)
{
	alFilterf(filterID, AL_LOWPASS_GAIN, gain);
}
float LowpassFilter::getGain() const
{
	float tmp;
	alGetFilterf(filterID,AL_LOWPASS_GAIN, &tmp);
	return tmp;
}
void LowpassFilter::setHighFrequencyGain(float gain)
{
	alFilterf(filterID, AL_LOWPASS_GAINHF, gain);
}
float LowpassFilter::getHighFrequencyGain() const
{
	float tmp;
	alGetFilterf(filterID,AL_LOWPASS_GAINHF, &tmp);
	return tmp;
}

}
