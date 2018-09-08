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

struct Mipmap {
	uint32_t width,height;
	std::vector<uint8_t> pixelData;
};

DEFINE_STRUCT(ImageContainer)
struct ImageContainer {
	ImgType type;
	std::vector<Mipmap> mipmaps;
};

}
#endif // ABSTRACTIMAGECONTAINER_HPP
