#include "FontIO.hpp"
#include <stdexcept>
#include <cstring>

FontIO::FontIO(Abstract::sFIO readah)
	: fio(readah), lib(nullptr), face(nullptr), stroker(nullptr)
{
	if(FT_Init_FreeType(&lib) != 0) throw std::runtime_error("Failed to initialize the FreeType library!");
	fio->seek(0);
	memset(&stream,0,sizeof(stream));
	stream.read = &FontRead;
	stream.close = &FontClose;
	stream.descriptor.pointer = fio.get();
	stream.pos = 0;
	stream.base = NULL;
	stream.size = fio->size();
	FT_Open_Args args;
	args.flags = FT_OPEN_STREAM;
	args.stream = &stream;
	args.driver = 0;
	if(FT_Open_Face(lib,&args,0,&face) != 0) throw std::runtime_error("Failed to load font!");
	if(FT_Stroker_New(lib,&stroker) != 0) throw std::runtime_error("Failed to create stroker!");
	if(FT_Select_Charmap(face, FT_ENCODING_UNICODE) != 0) throw std::runtime_error("Failed to set to Unicode!");
}
sFontIO FontIO::create(Abstract::sFIO readah)
{
	return sFontIO(new FontIO(readah));
}
FontIO::~FontIO()
{
	if(stroker) FT_Stroker_Done(stroker);
	if(face) FT_Done_Face(face);
	if(lib) FT_Done_FreeType(lib);
}

void FontIO::setLetterSize(int width, int height)
{
	FT_Set_Pixel_Sizes(face, width, height);
}
const FT_Face FontIO::getFontFace() const
{
	return face;
}

unsigned long FontIO::FontRead( FT_Stream stream, unsigned long offset,
								unsigned char*  buffer, unsigned long count)
{
	if(!stream) return 0;
	if(!stream->descriptor.pointer) return 0;
	Abstract::pFIO file = reinterpret_cast<Abstract::pFIO>(stream->descriptor.pointer);
	file->seek(offset);
	if(buffer && count)
	{
		return file->read(buffer,count);
	}
	else return 0;
}
void FontIO::FontClose(FT_Stream)
{
	;
}
int FontIO::loadCharacter(FT_ULong charcode, Glyph& gylph) const
{
	int ret = FT_Load_Char(face,charcode,FT_LOAD_RENDER);
	gylph.Size.x = face->glyph->bitmap.width;
	gylph.Size.y = face->glyph->bitmap.rows;
	gylph.Bearing.x = face->glyph->bitmap_left;
	gylph.Bearing.y = face->glyph->bitmap_top;
	gylph.Advance.x = face->glyph->advance.x;
	gylph.Advance.y = face->glyph->advance.y;
	gylph.pixels.resize(gylph.Size.x * gylph.Size.y);
	memcpy(gylph.pixels.data(),face->glyph->bitmap.buffer,gylph.pixels.size());
	return ret;
}
int FontIO::loadCharacter(char charcode, Glyph& gylph) const
{
	return loadCharacter(FT_ULong(charcode),gylph);
}
int FontIO::loadCharacter(char16_t charcode, Glyph& gylph) const
{
	return loadCharacter(FT_ULong(charcode),gylph);
}
int FontIO::loadCharacter(char32_t charcode, Glyph& gylph) const
{
	return loadCharacter(FT_ULong(charcode),gylph);
}
int FontIO::loadCharacter(wchar_t charcode, Glyph& gylph) const
{
	return loadCharacter(FT_ULong(charcode),gylph);
}
