#ifndef AUDIO_HPP
#define AUDIO_HPP
#include "../io/SoundFile.hpp"
#include "Context.hpp"
/* We need glm too */
#include <glm/glm.hpp>

namespace Audio {

DEFINE_CLASS(Buffer)
DEFINE_CLASS(Source)
DEFINE_CLASS(System)

class Buffer
{
protected:
	ALuint buffer;
public:
	Buffer();
	virtual ~Buffer();
	// virtual size_t generateAudio(std::vector<float>& target, int channels, int sampleRate) = 0;
	virtual int getFormat() = 0;
	virtual int getChannelCount() = 0;
	virtual int getSamplerate() = 0;
	virtual sf_count_t getFrameCount() = 0;
	const ALuint& getBuffer() const;
	static ALenum ChannelCount2Format(int channelCount);
};
class Source
{
protected:
	ALuint source;
public:
	Source();
	virtual ~Source();
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
	void setLooping(bool looping);

	/* Getters */
	float getPitch(void) const;
	float getGain(void) const;
	glm::vec3 getPosition(void) const;
	bool getRelativity(void) const;
	float getMinimumDistance(void) const;
	float getAttenuation(void) const;
	ALint getStatus(void) const;
	bool getLooping(void) const;
};

}
#endif // AUDIO_HPP
