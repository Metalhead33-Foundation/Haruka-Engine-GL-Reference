#ifndef GLFONT_HPP
#define GLFONT_HPP
#include "../abstract/Font.hpp"
#include "../io/FontIO.hpp"
#include "glad_glx.h"
#include <unordered_map>

namespace  Gl {

DEFINE_CLASS(Font)
class Font : public Abstract::Font
{
public:
	struct Glyph {
	GlyphAttributes attributes;
	GLuint offsetWidth;
	};
	typedef const Glyph& GlyphReference;
	typedef std::vector<Glyph> GlyphVector;
	typedef GlyphVector::iterator GlyphIterator;
	typedef std::unordered_map<char32_t,uint32_t> OffsetHash;
	typedef OffsetHash::iterator OffsetIterator;
private:
	const sFontIO fontIO;
	GLuint FontTex, FontFramebuffer;
	GLuint width,height;
	GLuint rWidth,rHeight;

	GlyphVector characters;
	OffsetHash characterOffsets;

	Font(Abstract::sFIO readah, int nheight);
	void expandByWidth(GLuint eWidth);
	GLuint addCharacterToTexture(const FontIO::Glyph& gylph);
	uint32_t addLetter(char32_t lettah);
public:
	~Font();
	static sFont create(Abstract::sFIO readah, int nheight);

	uint32_t findCharacter(char32_t character);
	OffsetString createOffsetString(const std::string& str);
	OffsetString createOffsetString(const std::u16string& str);
	OffsetString createOffsetString(const std::u32string& str);
	OffsetString createOffsetString(const std::wstring& str);

	uint32_t emplaceLetter(char lettah);
	uint32_t emplaceLetter(char16_t lettah);
	uint32_t emplaceLetter(char32_t lettah);
	uint32_t emplaceLetter(wchar_t lettah);
	void bindTextureSide();
	const char* stringizeType();

	GlyphReference getGlyph(uint32_t offset) const;
	void renderText(const Abstract::sShaderProgram shader, const OffsetString& text, const glm::vec2& pos,const glm::mat4& projection);

	// void renderText(char32_t lettah, glm::ivec2& bottomLeft, glm::mat4& projection);
};

}

#endif // GLFONT_HPP
