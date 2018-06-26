#ifndef AUDIOPOSITIONER_HPP
#define AUDIOPOSITIONER_HPP
#include "AudioReplugger.hpp"
#include <Harudio-Engine/Audio/Effect/PositionalPanner.hpp>

namespace Audio {
DEFINE_CLASS(AudioPositioner)
class AudioPositioner : public Replugger
{
private:
	const sPositionalPanner panner;
public:
	AudioPositioner();
	void onAudioReplug(const sPlayable ply);
	const sPositionalPanner getPanner() const;
};
}
#endif // AUDIOPOSITIONER_HPP
