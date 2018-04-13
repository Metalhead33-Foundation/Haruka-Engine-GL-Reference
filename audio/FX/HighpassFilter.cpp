#include "HighpassFilter.hpp"
namespace Audio {

HighpassFilter::HighpassFilter()
{
	alFilteri(filterID,AL_FILTER_TYPE,AL_FILTER_HIGHPASS);
}
ALenum HighpassFilter::getFilterType()
{
	return AL_FILTER_HIGHPASS;
}
void HighpassFilter::setGain(float gain)
{
	alFilterf(filterID, AL_HIGHPASS_GAIN, gain);
}
float HighpassFilter::getGain() const
{
	float tmp;
	alGetFilterf(filterID,AL_HIGHPASS_GAIN, &tmp);
	return tmp;
}
void HighpassFilter::setLowFrequencyGain(float gain)
{
	alFilterf(filterID, AL_HIGHPASS_GAINLF, gain);
}
float HighpassFilter::getLowFrequencyGain() const
{
	float tmp;
	alGetFilterf(filterID,AL_HIGHPASS_GAINLF, &tmp);
	return tmp;
}

}
