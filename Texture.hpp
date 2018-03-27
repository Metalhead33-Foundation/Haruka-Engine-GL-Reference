#pragma once
#include "Global.hpp"

DEFINE_CLASS(Texture)
class Texture
{
public:
	virtual ~Texture() {;}
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
};
