#include "AudioUtil.hpp"
namespace Audio {

ALenum ChannelCount2Format(int channelCount) {
	if(channelCount == 2) return STEREO_AUDIO;
	else return MONO_AUDIO;
}

}
