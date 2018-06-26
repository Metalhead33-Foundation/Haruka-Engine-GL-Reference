#ifndef AUDIOPOSITIONER_HPP
#define AUDIOPOSITIONER_HPP
#include "AudioReplugger.hpp"
#include "PositionalMutuals.hpp"
#include <Harudio-Engine/Audio/Effect/PositionalPanner.hpp>

namespace Audio {
DEFINE_CLASS(AudioPositioner)
class AudioPositioner : public Replugger, public Cascaded
{
private:
	const sPositionalPanner panner;
protected:
	void onPositionChange(const glm::vec3& pos);
public:
	AudioPositioner();
	void onAudioReplug(const sPlayable ply);
	const sPositionalPanner getPanner() const;
};
}
#endif // AUDIOPOSITIONER_HPP
