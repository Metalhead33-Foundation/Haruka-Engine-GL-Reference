#ifndef GLTEXTURE_HPP
#define GLTEXTURE_HPP
#include "Texture.hpp"
#include "glad_glx.h"
#include "AbstractFread.hpp"

class GlTexture : public Texture
{
private:
	GLuint textureID;
	uint32_t width,height,linearSize,mipMapCount;
	const textureType type;
public:
	GlTexture(textureType ntype);
	~GlTexture();
	static sTexture createFromDDS(textureType ntype, sAbstractFread reada);
	static sTexture createFromImage(textureType ntype, sAbstractFread reada);

	uint32_t getWidth() { return width; }
	uint32_t getHeight() { return height; }
	uint32_t getLinearSize() { return linearSize; }
	uint32_t getMipMapCount() { return mipMapCount; }
	const GLuint& getTextureId() const { return textureID; }
	const textureType& getTextureType() const { return type; }
};

#endif // GLTEXTURE_HPP
