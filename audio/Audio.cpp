#include "Audio.hpp"
namespace Audio {

const ALuint& AudioBuffer::getBuffer() const { return buffer; }
const ALuint& AudioSource::getSource() const { return source; }
void AudioSource::setPosition(glm::vec3& pos) { setPosition(pos.x,pos.y,pos.z); }
void AudioSource::setPitch(float pitch)
{
	alSourcef(source, AL_PITCH, pitch);
}
void AudioSource::setGain(float gain)
{
	alSourcef(source, AL_GAIN, gain);
}
void AudioSource::setPosition(float x, float y, float z)
{
	alSource3f(source, AL_POSITION, x, y, z);
}
void AudioSource::setRelativity(bool shouldBeRelative)
{
	alSourcei(source, AL_SOURCE_RELATIVE, shouldBeRelative);
}
void AudioSource::setMinimumDistance(float minDist)
{
	alSourcef(source, AL_REFERENCE_DISTANCE, minDist);
}
void AudioSource::setAttenuation(float attenuation)
{
	alSourcef(source, AL_ROLLOFF_FACTOR, attenuation);
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

}
