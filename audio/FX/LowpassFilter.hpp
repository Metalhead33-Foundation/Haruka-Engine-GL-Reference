#ifndef LOWPASSFILTER_HPP
#define LOWPASSFILTER_HPP
#include "Filter.hpp"

namespace Audio {

DEFINE_CLASS(LowpassFilter)
class LowpassFilter : public Filter
{
private:
	LowpassFilter();
	LowpassFilter(const LowpassFilter& cpy);
public:
	static sLowpassFilter create();
	static sLowpassFilter create(sLowpassFilter cpy);
	void setGain(float gain);
	float getGain() const;
	void setHighFrequencyGain(float gain);
	float getHighFrequencyGain() const;
	ALenum getFilterType();
};

}

#endif // LOWPASSFILTER_HPP
