#include "BandpassFilter.hpp"

namespace Audio {

BandpassFilter::BandpassFilter()
{
	alFilteri(filterID,AL_FILTER_TYPE,AL_FILTER_BANDPASS);
}
BandpassFilter::BandpassFilter(const BandpassFilter& cpy)
{
	alFilteri(filterID,AL_FILTER_TYPE,AL_FILTER_BANDPASS);
	setGain(cpy.getGain());
	setHighFrequencyGain(cpy.getHighFrequencyGain());
	setLowFrequencyGain(cpy.getLowFrequencyGain());
}
sBandpassFilter BandpassFilter::create()
{
	return sBandpassFilter(new BandpassFilter());
}
sBandpassFilter BandpassFilter::create(sBandpassFilter cpy)
{
	if(cpy) return sBandpassFilter(new BandpassFilter(*cpy));
	else return sBandpassFilter(new BandpassFilter());
}
ALenum BandpassFilter::getFilterType()
{
	return AL_FILTER_BANDPASS;
}
void BandpassFilter::setGain(float gain)
{
	alFilterf(filterID, AL_LOWPASS_GAIN, gain);
}
float BandpassFilter::getGain() const
{
	float tmp;
	alGetFilterf(filterID,AL_LOWPASS_GAIN, &tmp);
	return tmp;
}
void BandpassFilter::setHighFrequencyGain(float gain)
{
	alFilterf(filterID, AL_LOWPASS_GAINHF, gain);
}
float BandpassFilter::getHighFrequencyGain() const
{
	float tmp;
	alGetFilterf(filterID,AL_LOWPASS_GAINHF, &tmp);
	return tmp;
}
void BandpassFilter::setLowFrequencyGain(float gain)
{
	alFilterf(filterID, AL_HIGHPASS_GAINLF, gain);
}
float BandpassFilter::getLowFrequencyGain() const
{
	float tmp;
	alGetFilterf(filterID,AL_HIGHPASS_GAINLF, &tmp);
	return tmp;
}

}
