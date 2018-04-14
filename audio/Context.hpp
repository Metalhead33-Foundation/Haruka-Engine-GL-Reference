#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP
#include <vector>
#include <deque>
#include "../abstract/Global.hpp"
/* OpenAL headers */
#include "AL/OpenALWrapper.hpp"

namespace Audio {

DEFINE_CLASS(Context)
class Context
{
private:
	ALCdevice* device;
	ALCcontext* context;
public:
	Context(int nSamplerate);
	virtual ~Context();
	void makeCurrent();
	void process();
	void suspend();
};

}
#endif // AUDIOSYSTEM_HPP
