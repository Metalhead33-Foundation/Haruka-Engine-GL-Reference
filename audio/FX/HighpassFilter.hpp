#ifndef HIGHPASSFILTER_HPP
#define HIGHPASSFILTER_HPP
#include "Filter.hpp"
namespace Audio {

DEFINE_CLASS(HighpassFilter)
class HighpassFilter : public Filter
{
private:
	HighpassFilter();
	HighpassFilter(const HighpassFilter& cpy);
public:
	static sHighpassFilter create();
	static sHighpassFilter create(sHighpassFilter cpy);
	void setGain(float gain);
	float getGain() const;
	void setLowFrequencyGain(float gain);
	float getLowFrequencyGain() const;
	ALenum getFilterType();
};

}

#endif // HIGHPASSFILTER_HPP
