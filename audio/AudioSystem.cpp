#include "AudioSystem.hpp"
namespace Audio {

AudioSystem::AudioSystem(int nSamplerate)
{
	ALCint contextAttr[] = {ALC_FREQUENCY,nSamplerate,0};
	device = alcOpenDevice( NULL );
	context = alcCreateContext( device, contextAttr );
}
AudioSystem::~AudioSystem()
{
	alcDestroyContext( context );
	alcCloseDevice( device );
}
const char* AudioSystem::translateError(ALenum err)
{
	switch(err)
	{
	case AL_NO_ERROR:
		return "AL_NO_ERROR: No error.";
		break;
	case AL_INVALID_NAME:
		return "AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function.";
		break;
	case AL_INVALID_ENUM:
		return "AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function.";
		break;
	case AL_INVALID_VALUE:
		return "AL_INVALID_ENUM: an invalid value was passed to an OpenAL function.";
		break;
	case AL_INVALID_OPERATION:
		return "AL_INVALID_ENUM: the requested operation is not valid.";
		break;
	case AL_OUT_OF_MEMORY:
		return "AL_INVALID_ENUM: the requested operation resulted in OpenAL running out of memory.";
		break;
	default:
		return "This is not an error.";
		break;
	};
}
void AudioSystem::logError(const char* classname, const char* operation, ALenum error)
{
	if(error != AL_NO_ERROR) {
	errors.push_back( { classname, operation, translateError(error) }  );
	ErrorLog tmplog = errors.back();
	std::cout << "Logged OpenAL Error:" << std::endl << tmplog.classname << "." <<
			  tmplog.operation << " - " << tmplog.error << std::endl;
	}
}

}
