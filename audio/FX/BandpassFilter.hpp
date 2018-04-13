#ifndef BANDPASSFILTER_HPP
#define BANDPASSFILTER_HPP
#include "Filter.hpp"

namespace Audio {

class BandpassFilter : public Filter
{
public:
	BandpassFilter();
	void setGain(float gain);
	float getGain() const;
	void setHighFrequencyGain(float gain);
	float getHighFrequencyGain() const;
	void setLowFrequencyGain(float gain);
	float getLowFrequencyGain() const;
	ALenum getFilterType();
};

}

#endif // BANDPASSFILTER_HPP
