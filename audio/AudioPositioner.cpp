#include "AudioPositioner.hpp"

namespace Audio {
AudioPositioner::AudioPositioner()
	: panner(Audio::PositionalPanner::createPositionPanner())
{
	;
}
void AudioPositioner::onAudioReplug(const sPlayable ply)
{
	panner->setInput(ply);
}
const sPositionalPanner AudioPositioner::getPanner() const
{
	return panner;
}
void AudioPositioner::onPositionChange(const glm::vec3& pos)
{
	panner->setSource(pos);
}

}
