#ifndef AUDIO_HPP
#define AUDIO_HPP
#include "../abstract/Global.hpp"
#include "../io/SoundFile.hpp"
#include <vector>
/* OpenAL headers */
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
/* We need glm too */
#include <glm/glm.hpp>

namespace Audio {

DEFINE_CLASS(AudioBuffer)
DEFINE_CLASS(AudioSource)

class AudioBuffer
{
protected:
	ALuint buffer;
public:
	virtual ~AudioBuffer() = default;
	// virtual size_t generateAudio(std::vector<float>& target, int channels, int sampleRate) = 0;
	virtual int getFormat() = 0;
	virtual int getChannelCount() = 0;
	virtual int getSamplerate() = 0;
	virtual sf_count_t getFrameCount() = 0;
	const ALuint& getBuffer() const;
};
class AudioSource
{
protected:
	ALuint source;
public:
	virtual ~AudioSource() = default;
	// virtual size_t generateAudio(std::vector<float>& target, int channels, int sampleRate) = 0;
	virtual void play() = 0;
	virtual void pause() = 0;
	virtual void stop() = 0;

	/* Setters */
	const ALuint& getSource() const;
	void setPitch(float pitch);
	void setGain(float gain);
	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3& pos);
	void setRelativity(bool shouldBeRelative);
	void setMinimumDistance(float minDist);
	void setAttenuation(float attenuation);

	/* Getters */
	float getPitch(void) const;
	float getGain(void) const;
	glm::vec3 getPosition(void) const;
	bool getRelativity(void) const;
	float getMinimumDistance(void) const;
	float getAttenuation(void) const;
	ALint getStatus(void) const;
};

}
#endif // AUDIO_HPP
