#include "Audio.hpp"
namespace Audio {

sAudioSystem AudioResource::SYSTEM = nullptr;
sAudioSystem AudioResource::getSystem()
{
	return SYSTEM;
}
void AudioResource::initializeSystem(int samplerate)
{
	SYSTEM = sAudioSystem(new AudioSystem(samplerate));
}
const char* AudioSource::getClassName()
{
	return "AudioSource";
}
const char* AudioBuffer::getClassName()
{
	return "AudioSource";
}

const ALuint& AudioBuffer::getBuffer() const { return buffer; }
const ALuint& AudioSource::getSource() const { return source; }
void AudioSource::setPosition(glm::vec3& pos) { setPosition(pos.x,pos.y,pos.z); }
void AudioSource::setPitch(float pitch)
{
	alSourcef(source, AL_PITCH, pitch);
	getSystem()->logError(getClassName(),"setPitch",alGetError());
}
void AudioSource::setGain(float gain)
{
	alSourcef(source, AL_GAIN, gain);
	getSystem()->logError(getClassName(),"setGain",alGetError());
}
void AudioSource::setPosition(float x, float y, float z)
{
	alSource3f(source, AL_POSITION, x, y, z);
	getSystem()->logError(getClassName(),"setPosition",alGetError());
}
void AudioSource::setRelativity(bool shouldBeRelative)
{
	alSourcei(source, AL_SOURCE_RELATIVE, shouldBeRelative);
	getSystem()->logError(getClassName(),"setRelativity",alGetError());
}
void AudioSource::setMinimumDistance(float minDist)
{
	alSourcef(source, AL_REFERENCE_DISTANCE, minDist);
	getSystem()->logError(getClassName(),"setMinimumDistance",alGetError());
}
void AudioSource::setAttenuation(float attenuation)
{
	alSourcef(source, AL_ROLLOFF_FACTOR, attenuation);
	getSystem()->logError(getClassName(),"setAttenuation",alGetError());
}

float AudioSource::getPitch(void) const
{
	ALfloat pitch;
	alGetSourcef(source, AL_PITCH, &pitch);

	return pitch;
}
float AudioSource::getGain(void) const
{
	ALfloat gain;
	alGetSourcef(source, AL_GAIN, &gain);

	return gain * 100.f;
}
glm::vec3 AudioSource::getPosition(void) const
{
	glm::vec3 position;
	alGetSource3f(source, AL_POSITION, &position.x, &position.y, &position.z);

	return position;
}
bool AudioSource::getRelativity(void) const
{
	ALint relative;
	alGetSourcei(source, AL_SOURCE_RELATIVE, &relative);

	return relative != 0;
}
float AudioSource::getMinimumDistance(void) const
{
	ALfloat distance;
	alGetSourcef(source, AL_REFERENCE_DISTANCE, &distance);

	return distance;
}
float AudioSource::getAttenuation(void) const
{
	ALfloat attenuation;
	alGetSourcef(source, AL_ROLLOFF_FACTOR, &attenuation);

	return attenuation;
}
ALint AudioSource::getStatus(void) const
{
	ALint status;
	alGetSourcei(source, AL_SOURCE_STATE, &status);
	return status;
}
void AudioSource::setLooping(bool looping)
{
	alSourcei(source, AL_LOOPING, looping);
	getSystem()->logError(getClassName(),"setLooping",alGetError());
}
bool AudioSource::getLooping(void) const
{
	ALint looping;
	alGetSourcei(source, AL_LOOPING, &looping);

	return looping != 0;
}

}
