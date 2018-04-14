#include "Context.hpp"
namespace Audio {

Context::Context(int nSamplerate)
{
	ALCint contextAttr[] = {ALC_FREQUENCY,nSamplerate,ALC_MAX_AUXILIARY_SENDS,1,0};
	device = alcOpenDevice( NULL );
	context = alcCreateContext( device, contextAttr );
	alcMakeContextCurrent( context );
}
Context::~Context()
{
	alcMakeContextCurrent( 0 );
	alcDestroyContext( context );
	alcCloseDevice( device );
}
void Context::makeCurrent()
{
	alcMakeContextCurrent( context );
}
void Context::process()
{
	alcProcessContext(context);
}
void Context::suspend()
{
	alcSuspendContext(context);
}
bool Context::isExtensionPresent(const char* extName)
{
	return alcIsExtensionPresent(device,extName) != 0;
}
bool Context::isExtensionPresent(const std::string& sxtName)
{
	return isExtensionPresent(sxtName.c_str());
}
const char* Context::getDeviceName()
{
	return alcGetString(device,ALC_DEVICE_SPECIFIER);
}
const char* Context::getExtensionList()
{
	return alcGetString(device,ALC_EXTENSIONS);
}

}
