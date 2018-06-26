#ifndef AUDIOUNIT_HPP
#define AUDIOUNIT_HPP
#include "AudioReplugger.hpp"
#include <Harudio-Engine/Audio/AudioSource.hpp>
#include <Harudio-Engine/Audio/AuxiliaryEffectSlot.hpp>
#include <Harudio-Engine/Audio/Effect/Resampler.hpp>

namespace Audio {

DEFINE_CLASS(Unit)
class Unit
{
public:
	friend class System;
private:
	sSource src;
	sAuxiliaryEffectSlot aux;
	sResampler smpl;
	sReplugger replugger;
	void replug();
protected:
	static int globalFramerate;
	void setSource(sSource setto);
	void setAuxiliaryEffectSlot(sAuxiliaryEffectSlot setto);
	void setResampler(sResampler setto);
	Unit(const sSource src, const sReplugger replugger);
	Unit(const Unit& cpy, const sSource src);
public:
	static sUnit create(const sSource src, const sReplugger replugger);
	static sUnit create(const Audio::sUnit cpy, const sSource src);
	const sPlayable getOutput() const;
	const sSource getSource() const;
	const sAuxiliaryEffectSlot getAuxiliaryEffectSlot() const;
	const sResampler getResampler() const;
	const sReplugger getReplugger() const;
	void setReplugger(const sReplugger replugger);

	void createAuxiliaryEffectSlot();

	void setSpeed(float setto);
	float getSpeed() const;

	void addEffect(sEffect playable, float wetness=1.0f);
	void setEffectWetness(float wetness, sEffect playable);
	void removeEffect(sEffect playable);
};

}


#endif // AUDIOUNIT_HPP
