#include "Filter.hpp"

namespace Audio {

Filter::Filter()
{
	alGenFilters(1, &filterID);
}
Filter::~Filter()
{
	alDeleteFilters(1, &filterID);
}
ALuint& Filter::getFilter()
{
	return filterID;
}

}
