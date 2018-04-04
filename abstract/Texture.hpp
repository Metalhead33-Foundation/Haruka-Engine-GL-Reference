#pragma once
#include "Global.hpp"
#include "FIO.hpp"
namespace Abstract {

DEFINE_CLASS(Texture)
class Texture
{
public:
	virtual ~Texture() = default;
	virtual uint32_t getWidth() = 0;
	virtual uint32_t getHeight() = 0;
	virtual uint32_t getLinearSize() = 0;
	virtual uint32_t getMipMapCount() = 0;
	enum textureType
	{
		texture_diffuse,
		texture_specular,
		texture_normal,
		texture_height,
	};
	virtual const textureType& getTextureType() const = 0;

	typedef sTexture (*TextureCreator)(textureType, Abstract::sFIO);
};

}
