#pragma once
#include "Global.hpp"
#include "FIO.hpp"
namespace Abstract {

DEFINE_CLASS(Framebuffer)
DEFINE_CLASS(ShaderProgram)
DEFINE_CLASS(Texture)
class Texture
{
public:
	friend class ShaderProgram;
	friend class Framebuffer;
public:
	virtual ~Texture() = default;
	virtual uint32_t getWidth() const = 0;
	virtual uint32_t getHeight() const = 0;
	virtual uint32_t getLinearSize() const = 0;
	virtual uint32_t getMipMapCount() const = 0;
	enum textureType
	{
		texture_diffuse = 0,
		texture_specular,
		texture_normal,
		texture_height,
		texture_MAX
	};
	virtual textureType getTextureType() const = 0;
	virtual const char* stringizeType() const = 0;
	virtual void bindTextureSide() = 0;

	typedef sTexture (*TextureCreator)(textureType, Abstract::sFIO);
};

}
