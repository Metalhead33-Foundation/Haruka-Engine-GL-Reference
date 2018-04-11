#ifndef OPENALWRAPPER_HPP
#define OPENALWRAPPER_HPP
/* OpenAL headers */
#include "alext.h"

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

bool loadAL();

#endif // OPENALWRAPPER_HPP
