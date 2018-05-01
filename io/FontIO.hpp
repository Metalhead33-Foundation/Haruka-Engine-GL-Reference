#ifndef FONTIO_HPP
#define FONTIO_HPP
#include "../abstract/FIO.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_SYSTEM_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_BITMAP_H
#include FT_STROKER_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

DEFINE_CLASS(FontIO)
class FontIO
{
public:
struct Glyph {
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	glm::ivec2 Advance;    // Offset to advance to next glyph
	std::vector<uint8_t> pixels;
};
private:
	const Abstract::sFIO fio;
	FT_Library lib;
	FT_Face face;
	FT_Stroker stroker;
	FT_StreamRec_ stream;
	FontIO(Abstract::sFIO readah);
public:
	static sFontIO create(Abstract::sFIO readah);
	~FontIO();
	static unsigned long FontRead( FT_Stream stream, unsigned long   offset, unsigned char*  buffer, unsigned long count);
	static void FontClose(FT_Stream);
	void setLetterSize(int width, int height);
	const FT_Face getFontFace() const;
	int loadCharacter(FT_ULong charcode, Glyph& gylph) const;
	int loadCharacter(char charcode, Glyph& gylph) const;
	int loadCharacter(char16_t charcode, Glyph& gylph) const;
	int loadCharacter(char32_t charcode, Glyph& gylph) const;
	int loadCharacter(wchar_t charcode, Glyph& gylph) const;
};

#endif // FONTIO_HPP
