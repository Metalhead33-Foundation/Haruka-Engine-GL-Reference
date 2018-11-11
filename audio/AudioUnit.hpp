#ifndef AUDIOUNIT_HPP
#define AUDIOUNIT_HPP
#include <Harudio-Engine/Audio/AudioSource.hpp>
#include <Harudio-Engine/Audio/AuxiliaryEffectSlot.hpp>
#include <Harudio-Engine/Audio/Effect/Resampler.hpp>

namespace Audio {

DEFINE_CLASS(Unit)
class Unit : public Playable
{
public:
	friend class System;
	friend class Room;
private:
	sSource src;
	sAuxiliaryEffectSlot aux;
	sResampler smpl;
	void replug();
protected:
	static int globalFramerate;
	void setSource(sSource setto);
	void setAuxiliaryEffectSlot(sAuxiliaryEffectSlot setto);
	void setResampler(sResampler setto);
	Unit(const sSource src);
	Unit(const Unit& cpy, const sSource src);
public:
	static sUnit create(const sSource src);
	static sUnit create(const Audio::sUnit cpy, const sSource src);
	const sPlayable getOutput() const;
	const sSource getSource() const;
	const sAuxiliaryEffectSlot getAuxiliaryEffectSlot() const;
	const sResampler getResampler() const;

	void createAuxiliaryEffectSlot();

	void setSpeed(float setto);
	float getSpeed() const;

	void addEffect(sEffect playable, float wetness=1.0f);
	void setEffectWetness(float wetness, sEffect playable);
	void removeEffect(sEffect playable);

	bool isPlaying() const;
	int getFramerate() const;
	int getChannelCount() const;
	long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);
};

}


#endif // AUDIOUNIT_HPP
