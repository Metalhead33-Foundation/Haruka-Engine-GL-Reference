#include "System.hpp"
#include "../io/SoundFile.hpp"

namespace Audio {

void System::checkStreams()
{
	for(auto it = streams.begin(); it != streams.end();)
	{
		if(it->expired()) it = streams.erase(it);
		else
		{
			const Sound::sStreamer stream = it->lock();
			stream->checkQueue();
			++it;
		}
	}
}
void System::setListenerPosition(const glm::vec3& pos)
{
	if(listenerPos == pos) return;
	listenerPos = pos;
	for(auto it = units.begin(); it != units.end();)
	{
		if(it->expired()) it = units.erase(it);
		else
		{
			const sPositioner unit = it->lock();
			unit->getPanner()->setDirection(pos);
			++it;
		}
	}
}

}
