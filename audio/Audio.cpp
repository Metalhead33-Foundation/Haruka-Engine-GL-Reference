#include "Audio.hpp"
#include "AudioUtil.hpp"

namespace Audio {

Buffer::Buffer()
{
	alGenBuffers(1, &buffer);
}
Source::Source()
	: filter(nullptr), auxiliaryEffectSlot(nullptr)
{
	alGenSources(1, &source);
}
Buffer::~Buffer()
{
	alDeleteBuffers(1, &buffer);
}
Source::~Source()
{
	if(getStatus() != AL_STOPPED) alSourceStop(source);
	alDeleteSources( 1, &source );
}

const ALuint& Buffer::getBuffer() const { return buffer; }
const ALuint& Source::getSource() const { return source; }
void Source::setPosition(glm::vec3& pos) { setPosition(pos.x,pos.y,pos.z); }
void Source::setPitch(float pitch)
{
	alSourcef(source, AL_PITCH, pitch);
}
void Source::setGain(float gain)
{
	alSourcef(source, AL_GAIN, gain);
}
void Source::setPosition(float x, float y, float z)
{
	alSource3f(source, AL_POSITION, x, y, z);
}
void Source::setRelativity(bool shouldBeRelative)
{
	alSourcei(source, AL_SOURCE_RELATIVE, shouldBeRelative);
}
void Source::setMinimumDistance(float minDist)
{
	alSourcef(source, AL_REFERENCE_DISTANCE, minDist);
}
void Source::setAttenuation(float attenuation)
{
	alSourcef(source, AL_ROLLOFF_FACTOR, attenuation);
}

float Source::getPitch(void) const
{
	ALfloat pitch;
	alGetSourcef(source, AL_PITCH, &pitch);

	return pitch;
}
float Source::getGain(void) const
{
	ALfloat gain;
	alGetSourcef(source, AL_GAIN, &gain);

	return gain * 100.f;
}
glm::vec3 Source::getPosition(void) const
{
	glm::vec3 position;
	alGetSource3f(source, AL_POSITION, &position.x, &position.y, &position.z);

	return position;
}
bool Source::getRelativity(void) const
{
	ALint relative;
	alGetSourcei(source, AL_SOURCE_RELATIVE, &relative);

	return relative != 0;
}
float Source::getMinimumDistance(void) const
{
	ALfloat distance;
	alGetSourcef(source, AL_REFERENCE_DISTANCE, &distance);

	return distance;
}
float Source::getAttenuation(void) const
{
	ALfloat attenuation;
	alGetSourcef(source, AL_ROLLOFF_FACTOR, &attenuation);

	return attenuation;
}
ALint Source::getStatus(void) const
{
	ALint status;
	alGetSourcei(source, AL_SOURCE_STATE, &status);
	return status;
}
void Source::setLooping(bool looping)
{
	alSourcei(source, AL_LOOPING, looping);
}
bool Source::getLooping(void) const
{
	ALint looping;
	alGetSourcei(source, AL_LOOPING, &looping);

	return looping != 0;
}
void Source::updateEffects()
{
	alSourcei(source, AL_DIRECT_FILTER, AL_FILTER_NULL);
	alSource3i(source,AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, 0, AL_FILTER_NULL);
	if(filter)
	{
		if(auxiliaryEffectSlot)
		{
			alSource3i(source,AL_AUXILIARY_SEND_FILTER, auxiliaryEffectSlot->getAuxiliaryEffectSlot(), 0, filter->getFilter());
		}
		alSourcei(source, AL_DIRECT_FILTER, filter->getFilter());
	}
	else
	{
		if(auxiliaryEffectSlot)
		{
			alSource3i(source,AL_AUXILIARY_SEND_FILTER, auxiliaryEffectSlot->getAuxiliaryEffectSlot(), 0, AL_FILTER_NULL);
		}
	}
}
void Source::setFilter(sFilter nfilter)
{
	filter = nfilter;
	updateEffects();
}
sFilter Source::getFilter() const
{
	return filter;
}
void Source::setAuxiliaryEffectSlot(sAuxiliaryEffectSlot aux)
{
	auxiliaryEffectSlot = aux;
	updateEffects();
}
sAuxiliaryEffectSlot Source::getAuxiliaryEffectSlot() const
{
	return auxiliaryEffectSlot;
}

}
