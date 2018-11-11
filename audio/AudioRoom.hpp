#ifndef AUDIOROOM_HPP
#define AUDIOROOM_HPP
#include "AudioPositioner.hpp"
#include "AudioUnit.hpp"
#include <Harudio-Engine/Audio/AuxiliaryEffectSlot.hpp>
#include <Harudio-Engine/Audio/Effect/SimpleConvolver.hpp>
#include <Harudio-Engine/Audio/AudioMixer.hpp>

namespace Audio {

DEFINE_CLASS(Room)
class Room : public Playable
{
private:
	const sMixer mix;
	sAuxiliaryEffectSlot aux;
	FX::sSimpleConvolver conv;
	void replug();
	void setAuxiliaryEffectSlot(sAuxiliaryEffectSlot setto);
	Room();
public:
	static sRoom create();
	const sMixer getMixer() const;
	const sAuxiliaryEffectSlot getAuxiliaryEffectSlot() const;
	const FX::sSimpleConvolver getConvolver() const;
	const sPlayable getOutput() const;

	void createConvolver();
	void destroyConvolver();

	bool isPlaying() const;
	int getFramerate() const;
	int getChannelCount() const;
	long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);
};

}
#endif // AUDIOROOM_HPP
