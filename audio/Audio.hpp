#ifndef AUDIO_HPP
#define AUDIO_HPP
#include "../io/SoundFile.hpp"
#include "AudioSystem.hpp"
/* We need glm too */
#include <glm/glm.hpp>

#if defined(__ANDROID__) || defined(__ANDROID_API__)
#define SOUND_FORMAT_16BIT
#else
#endif

#ifdef SOUND_FORMAT_16BIT
typedef short SoundItem;
#define MONO_AUDIO AL_FORMAT_MONO16
#define STEREO_AUDIO AL_FORMAT_STEREO16
#else
typedef float SoundItem;
#define MONO_AUDIO AL_FORMAT_MONO_FLOAT32
#define STEREO_AUDIO AL_FORMAT_STEREO_FLOAT32
#endif

namespace Audio {

DEFINE_CLASS(AudoResource)
DEFINE_CLASS(AudioBuffer)
DEFINE_CLASS(AudioSource)

class AudioResource
{
	protected:
	virtual const char* getClassName() = 0;
	private:
	static sAudioSystem SYSTEM;
	public:
	virtual ~AudioResource() = default;
	sAudioSystem getSystem();
	static void initializeSystem(int samplerate);
};

class AudioBuffer : public virtual AudioResource
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
protected:
	virtual const char* getClassName();
};
class AudioSource : public virtual AudioResource
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
protected:
	virtual const char* getClassName();
};

}
#endif // AUDIO_HPP
