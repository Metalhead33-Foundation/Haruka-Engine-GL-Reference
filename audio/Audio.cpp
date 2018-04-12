#include "Audio.hpp"
namespace Audio {

sContext Resource::SYSTEM = nullptr;
sContext Resource::getSystem()
{
	return SYSTEM;
}
ALenum Resource::ChannelCount2Format(int channelCount)
{
	if(channelCount == 2) return STEREO_AUDIO;
	else return MONO_AUDIO;
}
void Resource::initializeSystem(sContext nsystem)
{
	SYSTEM = nsystem;
}

Buffer::Buffer()
{
	alGenBuffers(1, &buffer);
}
Source::Source()
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

const char* Source::getClassName()
{
	return "AudioSource";
}
const char* Buffer::getClassName()
{
	return "AudioSource";
}

const ALuint& Buffer::getBuffer() const { return buffer; }
const ALuint& Source::getSource() const { return source; }
void Source::setPosition(glm::vec3& pos) { setPosition(pos.x,pos.y,pos.z); }
void Source::setPitch(float pitch)
{
	alSourcef(source, AL_PITCH, pitch);
	getSystem()->logError(getClassName(),"setPitch",alGetError());
}
void Source::setGain(float gain)
{
	alSourcef(source, AL_GAIN, gain);
	getSystem()->logError(getClassName(),"setGain",alGetError());
}
void Source::setPosition(float x, float y, float z)
{
	alSource3f(source, AL_POSITION, x, y, z);
	getSystem()->logError(getClassName(),"setPosition",alGetError());
}
void Source::setRelativity(bool shouldBeRelative)
{
	alSourcei(source, AL_SOURCE_RELATIVE, shouldBeRelative);
	getSystem()->logError(getClassName(),"setRelativity",alGetError());
}
void Source::setMinimumDistance(float minDist)
{
	alSourcef(source, AL_REFERENCE_DISTANCE, minDist);
	getSystem()->logError(getClassName(),"setMinimumDistance",alGetError());
}
void Source::setAttenuation(float attenuation)
{
	alSourcef(source, AL_ROLLOFF_FACTOR, attenuation);
	getSystem()->logError(getClassName(),"setAttenuation",alGetError());
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
	getSystem()->logError(getClassName(),"setLooping",alGetError());
}
bool Source::getLooping(void) const
{
	ALint looping;
	alGetSourcei(source, AL_LOOPING, &looping);

	return looping != 0;
}

}
