#ifndef AUDIOREPLUGGER_HPP
#define AUDIOREPLUGGER_HPP
#include <Harudio-Engine/Audio/AudioPlayable.hpp>

namespace Audio {

DEFINE_CLASS(Replugger)
class Replugger
{
public:
	virtual ~Replugger() = default;
	virtual void onAudioReplug(const sPlayable ply) = 0;
};

}

#endif // AUDIOREPLUGGER_HPP
