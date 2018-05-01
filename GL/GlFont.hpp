#ifndef GLFONT_HPP
#define GLFONT_HPP
#include "../abstract/Font.hpp"
#include "../io/FontIO.hpp"
#include "glad_glx.h"
#include <map>

namespace  Gl {

DEFINE_CLASS(Font)
class Font : public Abstract::Font
{
public:
	struct Glyph {
	GlyphAttributes attributes;
	GLuint offsetWidth;
	};
	typedef std::vector<Glyph> GlyphVector;
	typedef GlyphVector::iterator GlyphIterator;
	struct CharacterRegion
	{
		char32_t start;
		char32_t end() const;
		std::vector<uint32_t> offsetMap; // Offsets within the GlyphVector
		bool isPartOfRegion(char32_t character) const;
		uint32_t getOffsetIndex(char32_t character) const;
	};
	typedef std::vector<CharacterRegion> RegionVector;
	typedef RegionVector::iterator RegionIterator;
private:
	const sFontIO fontIO;
	GLuint FontTex, FontFramebuffer;
	GLuint width,height;

	GlyphVector characters;
	RegionVector characterRegions;
	size_t lastRegion;

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

	void emplaceLetter(char lettah);
	void emplaceLetter(char16_t lettah);
	void emplaceLetter(char32_t lettah);
	void emplaceLetter(wchar_t lettah);

	// void renderText(char32_t lettah, glm::ivec2& bottomLeft, glm::mat4& projection);
};

}

#endif // GLFONT_HPP
