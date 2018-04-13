#include "LowpassFilter.hpp"
namespace Audio {

LowpassFilter::LowpassFilter()
{
	alFilteri(filterID,AL_FILTER_TYPE,AL_FILTER_LOWPASS);
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
