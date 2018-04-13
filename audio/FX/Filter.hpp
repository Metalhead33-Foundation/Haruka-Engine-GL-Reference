#ifndef FILTER_HPP
#define FILTER_HPP
#include "../Audio.hpp"
namespace Audio {

DEFINE_CLASS(Filter)
class Filter
{
protected:
	ALuint filterID;
public:
	Filter();
	virtual ~Filter();
	ALuint& getFilter();
	virtual ALenum getFilterType() = 0;
};

}
#endif // FILTER_HPP
