#ifndef ABSTRACTIMAGECONTAINER_HPP
#define ABSTRACTIMAGECONTAINER_HPP
#include "Global.hpp"
#include <vector>
#include <cstdint>
namespace Abstract {

enum class ImgType : uint8_t {
	RGB24,
	RGBA32,
	DDX1,
	DDX3,
	DDX5
};
typedef std::vector<uint8_t> ByteBuffer;
typedef std::vector<uint32_t> WordBuffer;

struct Mipmap {
	uint32_t width,height;
	ByteBuffer pixelData;
};

DEFINE_STRUCT(ImageContainer)
struct ImageContainer {
	ImgType type;
	std::vector<Mipmap> mipmaps;
};

DEFINE_STRUCT(AnimatedImageContainer)
struct AnimatedImageContainer {
	ImgType type;
	uint32_t width,height;
	std::vector<WordBuffer> frames;
};

}
#endif // ABSTRACTIMAGECONTAINER_HPP
