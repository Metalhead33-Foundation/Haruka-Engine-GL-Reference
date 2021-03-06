#ifndef GLTEXTURE_HPP
#define GLTEXTURE_HPP
#include "../abstract/Texture.hpp"
#include "glad_glx.h"
#include "../abstract/FIO.hpp"
#include <array>
namespace Gl {

DEFINE_CLASS(ShaderProgram)
DEFINE_CLASS(Framebuffer)
DEFINE_CLASS(Texture)
class Texture : public Abstract::Texture
{
public:
	friend class ShaderProgram;
	friend class Framebuffer;
private:
	GLuint textureID;
	uint32_t width,height,linearSize,mipMapCount;
	const textureType type;
	Texture(textureType ntype);
public:
	~Texture(); // sTextureConstructor
	static Abstract::sTexture create(textureType ntype, sTextureConstructor constructor);

	uint32_t getWidth() const { return width; }
	uint32_t getHeight() const { return height; }
	uint32_t getLinearSize() const { return linearSize; }
	uint32_t getMipMapCount() const { return mipMapCount; }
	const GLuint& getTextureId() const { return textureID; }
	textureType getTextureType() const { return type; }
	static const char* __stringizeType(textureType typus);
	const char* stringizeType() const;
	void bindTextureSide();

	static const std::array<const char*,texture_MAX> TEX_TYPES;
};

}
#endif // GLTEXTURE_HPP
