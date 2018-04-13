#ifndef LOWPASSFILTER_HPP
#define LOWPASSFILTER_HPP
#include "Filter.hpp"

namespace Audio {

class LowpassFilter : public Filter
{
public:
	LowpassFilter();
	void setGain(float gain);
	float getGain() const;
	void setHighFrequencyGain(float gain);
	float getHighFrequencyGain() const;
	ALenum getFilterType();
};

}

#endif // LOWPASSFILTER_HPP
