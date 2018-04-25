#ifndef GLTEXTURE_HPP
#define GLTEXTURE_HPP
#include "../abstract/Texture.hpp"
#include "glad_glx.h"
#include "../abstract/FIO.hpp"
#include <array>
namespace Gl {

DEFINE_CLASS(ShaderProgram)
DEFINE_CLASS(Texture)
class Texture : public Abstract::Texture
{
public:
	friend class ShaderProgram;
private:
	GLuint textureID;
	uint32_t width,height,linearSize,mipMapCount;
	const textureType type;
	Texture(textureType ntype);
public:
	~Texture();
	static Abstract::sTexture createFromDDS(textureType ntype, Abstract::sFIO reada);
	static Abstract::sTexture createFromImage(textureType ntype, Abstract::sFIO reada);

	uint32_t getWidth() { return width; }
	uint32_t getHeight() { return height; }
	uint32_t getLinearSize() { return linearSize; }
	uint32_t getMipMapCount() { return mipMapCount; }
	const GLuint& getTextureId() const { return textureID; }
	const textureType& getTextureType() const { return type; }
	static const char* __stringizeType(textureType typus);
	const char* stringizeType();
	void bindTextureSide();

	static const std::array<const char*,texture_MAX> TEX_TYPES;
};

}
#endif // GLTEXTURE_HPP
