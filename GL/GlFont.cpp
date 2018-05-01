#include "GlFont.hpp"
#define FONT_PADDING 2

namespace  Gl {

char32_t Font::CharacterRegion::end() const
{
	return start + offsetMap.size() - 1;
}
bool Font::CharacterRegion::isPartOfRegion(char32_t character) const
{
	return character >= start && character <= end();
}
uint32_t Font::CharacterRegion::getOffsetIndex(char32_t character) const
{
	return offsetMap[character - start];
}
uint32_t Font::findCharacter(char32_t character)
{
	if(characterRegions[lastRegion].isPartOfRegion(character))
		return characterRegions[lastRegion].getOffsetIndex(character);
	else if(character < characterRegions[lastRegion].start)
	{
		for(size_t it = lastRegion; it > 0; --it)
		{
			if(characterRegions[it].isPartOfRegion(character))
			{
				lastRegion = it;
				return characterRegions[it].getOffsetIndex(character);
			}
		}
	}
	else for(size_t it = lastRegion; it < characterRegions.size(); ++it)
	{
		if(characterRegions[it].isPartOfRegion(character))
		{
			lastRegion = it;
			return characterRegions[it].getOffsetIndex(character);
		}
	}
	return 0;
}

sFont Font::create(Abstract::sFIO readah, int nheight)
{
	return sFont(new Font(readah,nheight));
}
Font::Font(Abstract::sFIO readah, int nheight)
	: fontIO(FontIO::create(readah)), width(1), height(nheight + FONT_PADDING)
{
	fontIO->setLetterSize(0,nheight);
	glGenTextures(1, &FontTex);
	glGenFramebuffers(1, &FontFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, FontFramebuffer);
	glBindTexture(GL_TEXTURE_2D, FontTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GLsizei(width), GLsizei(height), 0, GL_RGB,
				 GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FontTex, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
Font::~Font()
{
	glDeleteTextures(1, &FontTex);
	glDeleteFramebuffers(1, &FontFramebuffer);
}
void Font::expandByWidth(GLuint eWidth)
{
	GLint curwidth, curheight;
	GLuint nFramebuffer, nTexture;
	glBindTexture(GL_TEXTURE_2D, FontTex);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &curwidth);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &curheight);
	glBindTexture(GL_TEXTURE_2D, 0);
	glGenTextures(1, &nTexture);
	glGenFramebuffers(1, &nFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, nFramebuffer);
	glBindTexture(GL_TEXTURE_2D, nTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GLsizei(curwidth + eWidth), GLsizei(curheight), 0, GL_RGB,
				 GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, nFramebuffer, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, FontFramebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, nFramebuffer);
	glBlitFramebuffer(0,0,curwidth,curheight,0,0,curwidth,curheight,GL_COLOR_BUFFER_BIT,GL_NEAREST);
	glDeleteTextures(1, &FontTex);
	FontTex = nTexture;
	glDeleteFramebuffers(1, &FontFramebuffer);
	FontFramebuffer = nFramebuffer;
	// width += eWidth + FONT_PADDING;
}
GLuint Font::addCharacterToTexture(const FontIO::Glyph& gylph)
{
	GLuint orwidth = width + FONT_PADDING;
	GLint curwidth;
	glBindTexture(GL_TEXTURE_2D, FontTex);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &curwidth);
	if(curwidth < (orwidth + gylph.Size.x)) expandByWidth( orwidth + gylph.Size.x); // If we need to expand...
	glBindTexture(GL_TEXTURE_2D,FontTex);
	glTexSubImage2D(GL_TEXTURE_2D,0,orwidth,0,
					gylph.Size.x, gylph.Size.y, GL_RED, GL_UNSIGNED_BYTE, gylph.pixels.data());
	glBindTexture(GL_TEXTURE_2D,0);
	width = orwidth;
	return orwidth;
}
uint32_t Font::addLetter(char32_t lettah)
{
	FontIO::Glyph gylph;
	fontIO->loadCharacter(lettah,gylph);
	uint32_t trueOffset = characters.size();
	Glyph letter;
	letter.attributes.Advance = gylph.Advance;
	letter.attributes.Bearing = gylph.Bearing;
	letter.attributes.Size = gylph.Size;
	letter.offsetWidth = addCharacterToTexture(gylph);
	characters.push_back(letter);
	bool inserted = false;
	for(auto it = characterRegions.begin(); it != characterRegions.end(); ++it)
	{
		if(it->start == (lettah + 1))
		{
			it->start = lettah;
			std::vector<uint32_t> tmp = it->offsetMap;
			it->offsetMap[0] = trueOffset;
			it->offsetMap.resize(it->offsetMap.size() + 1);
			memcpy(&it->offsetMap[1],tmp.data(),tmp.size() * sizeof(uint32_t));
			inserted = true;
			break;
		}
		else if(it->end() == (lettah - 1))
		{
			it->offsetMap.push_back(trueOffset);
			inserted = true;
			break;
		}
	}
	if(!inserted)
	{
		CharacterRegion reg;
		reg.start = lettah;
		reg.offsetMap.push_back(trueOffset);
		characterRegions.push_back(reg);
	}
	return trueOffset;
}
Font::OffsetString Font::createOffsetString(const std::string& str)
{
	OffsetString tmp(str.size(),0);
	for(size_t it = 0; it < str.size(); ++it)
	{
		tmp[it] = findCharacter(char32_t(str[it]));
	}
	return  tmp;
}
Font::OffsetString Font::createOffsetString(const std::u16string& str)
{
	OffsetString tmp(str.size(),0);
	for(size_t it = 0; it < str.size(); ++it)
	{
		tmp[it] = findCharacter(char32_t(str[it]));
	}
	return  tmp;
}
Font::OffsetString Font::createOffsetString(const std::u32string& str)
{
	OffsetString tmp(str.size(),0);
	for(size_t it = 0; it < str.size(); ++it)
	{
		tmp[it] = findCharacter(str[it]);
	}
	return  tmp;
}
Font::OffsetString Font::createOffsetString(const std::wstring& str)
{
	OffsetString tmp(str.size(),0);
	for(size_t it = 0; it < str.size(); ++it)
	{
		tmp[it] = findCharacter(char32_t(str[it]));
	}
	return  tmp;
}
/*void Font::emplaceLetter(char lettah)
{
	FontIO::Glyph tmp;
	fontIO->loadCharacter(lettah,tmp);
	fontmap.emplace(char32_t(lettah),tmp);
}
void Font::emplaceLetter(char16_t lettah)
{
	FontIO::Glyph tmp;
	fontIO->loadCharacter(lettah,tmp);
	fontmap.emplace(char32_t(lettah),tmp);
}
void Font::emplaceLetter(char32_t lettah)
{
	FontIO::Glyph tmp;
	fontIO->loadCharacter(lettah,tmp);
	fontmap.emplace(lettah,tmp);
}
void Font::emplaceLetter(wchar_t lettah)
{
	FontIO::Glyph tmp;
	fontIO->loadCharacter(lettah,tmp);
	fontmap.emplace(char32_t(lettah),tmp);
}*/

}
