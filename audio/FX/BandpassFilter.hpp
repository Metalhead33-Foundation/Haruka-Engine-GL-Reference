#ifndef BANDPASSFILTER_HPP
#define BANDPASSFILTER_HPP
#include "Filter.hpp"

namespace Audio {

DEFINE_CLASS(BandpassFilter)
class BandpassFilter : public Filter
{
private:
	BandpassFilter();
	BandpassFilter(const BandpassFilter& cpy);
public:
	static sBandpassFilter create();
	static sBandpassFilter create(sBandpassFilter cpy);
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
