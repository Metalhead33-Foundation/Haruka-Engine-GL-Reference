#include "Context.hpp"
namespace Audio {

Context::Context(int nSamplerate)
{
	ALCint contextAttr[] = {ALC_FREQUENCY,nSamplerate,0};
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

}
