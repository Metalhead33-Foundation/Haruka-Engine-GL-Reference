#ifndef GLTEXTURE_HPP
#define GLTEXTURE_HPP
#include "../abstract/Texture.hpp"
#include "glad_glx.h"
#include "../abstract/AbstractFIO.hpp"

class GlTexture : public Texture
{
private:
	GLuint textureID;
	uint32_t width,height,linearSize,mipMapCount;
	const textureType type;
	GlTexture(textureType ntype);
public:
	~GlTexture();
	static sTexture createFromDDS(textureType ntype, sAbstractFIO reada);
	static sTexture createFromImage(textureType ntype, sAbstractFIO reada);

	uint32_t getWidth() { return width; }
	uint32_t getHeight() { return height; }
	uint32_t getLinearSize() { return linearSize; }
	uint32_t getMipMapCount() { return mipMapCount; }
	const GLuint& getTextureId() const { return textureID; }
	const textureType& getTextureType() const { return type; }

	static const char* __stringizeType(textureType typus);
	const char* stringizeType();
};

#endif // GLTEXTURE_HPP
