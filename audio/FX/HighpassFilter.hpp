#ifndef HIGHPASSFILTER_HPP
#define HIGHPASSFILTER_HPP
#include "Filter.hpp"
namespace Audio {

class HighpassFilter : public Filter
{
public:
	HighpassFilter();
	void setGain(float gain);
	float getGain() const;
	void setLowFrequencyGain(float gain);
	float getLowFrequencyGain() const;
	ALenum getFilterType();
};

}

#endif // HIGHPASSFILTER_HPP
