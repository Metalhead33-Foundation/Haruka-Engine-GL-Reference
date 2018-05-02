#ifndef FONT_HPP
#define FONT_HPP
#include "Global.hpp"
#include "ShaderProgram.hpp"
#include "FIO.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <map>

namespace Abstract {

DEFINE_CLASS(Font)
class Font
{
public:
struct GlyphAttributes {
	uint32_t pixOffset; // offset in width
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	glm::ivec2 Advance;    // Offset to advance to next glyph
	};
	typedef std::map<char32_t, GlyphAttributes> FontMap;
	typedef FontMap::iterator FontIterator;
	typedef std::basic_string<uint32_t> OffsetString;
protected:
	FontMap fontmap;
public:
	virtual ~Font() = default;

	virtual OffsetString createOffsetString(const std::string& str) = 0;
	virtual OffsetString createOffsetString(const std::u16string& str) = 0;
	virtual OffsetString createOffsetString(const std::u32string& str) = 0;
	virtual OffsetString createOffsetString(const std::wstring& str) = 0;

	virtual uint32_t emplaceLetter(char lettah) = 0;
	virtual uint32_t emplaceLetter(char16_t lettah) = 0;
	virtual uint32_t emplaceLetter(char32_t lettah) = 0;
	virtual uint32_t emplaceLetter(wchar_t lettah) = 0;
	virtual void bindTextureSide() = 0;
	virtual const char* stringizeType() = 0;
	virtual void renderText(const sShaderProgram shader, const OffsetString& text, const glm::vec2& pos,const glm::mat4& projection) = 0;
};
typedef std::pair<sFont, Font::OffsetString> RenderableString;

}

#endif // FONT_HPP
