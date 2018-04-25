#pragma once
#include "Global.hpp"
#include "FIO.hpp"
namespace Abstract {

DEFINE_CLASS(ShaderProgram)
DEFINE_CLASS(Texture)
class Texture
{
public:
	friend class ShaderProgram;
public:
	virtual ~Texture() = default;
	virtual uint32_t getWidth() = 0;
	virtual uint32_t getHeight() = 0;
	virtual uint32_t getLinearSize() = 0;
	virtual uint32_t getMipMapCount() = 0;
	enum textureType
	{
		texture_diffuse = 0,
		texture_specular,
		texture_normal,
		texture_height,
		texture_MAX
	};
	virtual const textureType& getTextureType() const = 0;
	virtual const char* stringizeType() = 0;
	virtual void bindTextureSide() = 0;

	typedef sTexture (*TextureCreator)(textureType, Abstract::sFIO);
};

}
