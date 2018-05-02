#include "GlFont.hpp"
#include "GlTexture.hpp"
#define FONT_PADDING 2

namespace  Gl {

uint32_t Font::findCharacter(char32_t character)
{
	auto it = characterOffsets.find(character);
	if(it != characterOffsets.end()) return it->second;
	else return 0;
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
	rWidth = width;
	rHeight = height;
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
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &curwidth);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &curheight);
	rWidth = curwidth;
	rHeight = curheight;
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
	characterOffsets.emplace(lettah,trueOffset);
	return trueOffset;
}
Font::OffsetString Font::createOffsetString(const std::string& str)
{
	OffsetString tmp(str.size(),0);
	for(size_t it = 0; it < str.size(); ++it)
	{
		tmp[it] = emplaceLetter(char32_t(str[it]));
	}
	return  tmp;
}
Font::OffsetString Font::createOffsetString(const std::u16string& str)
{
	OffsetString tmp(str.size(),0);
	for(size_t it = 0; it < str.size(); ++it)
	{
		tmp[it] = emplaceLetter(char32_t(str[it]));
	}
	return  tmp;
}
Font::OffsetString Font::createOffsetString(const std::u32string& str)
{
	OffsetString tmp(str.size(),0);
	for(size_t it = 0; it < str.size(); ++it)
	{
		tmp[it] = emplaceLetter(str[it]);
	}
	return  tmp;
}
Font::OffsetString Font::createOffsetString(const std::wstring& str)
{
	OffsetString tmp(str.size(),0);
	for(size_t it = 0; it < str.size(); ++it)
	{
		tmp[it] = emplaceLetter(char32_t(str[it]));
	}
	return  tmp;
}
uint32_t Font::emplaceLetter(char lettah)
{
	return emplaceLetter(char32_t(lettah));
}
uint32_t Font::emplaceLetter(char16_t lettah)
{
	return emplaceLetter(char32_t(lettah));
}
uint32_t Font::emplaceLetter(char32_t lettah)
{
	auto it = characterOffsets.find(lettah);
	if(it == characterOffsets.end()) return addLetter(lettah);
	else return it->second;
}
uint32_t Font::emplaceLetter(wchar_t lettah)
{
	return emplaceLetter(char32_t(lettah));
}
Font::GlyphReference Font::getGlyph(uint32_t offset) const
{
	return characters[offset];
}
const char* Font::stringizeType()
{
	return Gl::Texture::TEX_TYPES[Gl::Texture::texture_diffuse];
}
void Font::bindTextureSide()
{
	glActiveTexture(FontTex);
	glBindTexture(GL_TEXTURE_2D, FontTex);
}

void Font::renderText(const Abstract::sShaderProgram shader, const OffsetString& text,
					  const glm::vec2& pos,const glm::mat4& projection)
{
	if(shader)
	{
		GLuint VAO, VBO;
		glGenVertexArrays(1,&VAO);
		glGenBuffers(1,&VBO);
		GLfloat orgVertices[] = {
			// Pos      // Tex
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(orgVertices), orgVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glm::vec2 screenPos = pos;
		for(auto it = text.begin(); it != text.end(); ++it)
		{
			const Glyph& glyph = characters[*it];
			glm::vec2 locPos = screenPos;
			glm::vec2 locSize;
			locSize.x = glyph.attributes.Size.x;
			locSize.y = glyph.attributes.Size.y;
			locPos.x += glyph.attributes.Bearing.x;
			locPos.y += glyph.attributes.Bearing.y;
			float texBeginX = float(glyph.offsetWidth) / float(rWidth);
			float texBeginY = 0.00f;
			float texEndX = float(glyph.offsetWidth + glyph.attributes.Size.x) / float(rWidth);
			float texEndY = 1.00f;

			GLfloat newVertices[] = {
				// Pos      // Tex
				0.0f, 1.0f, texBeginX, texEndY,
				1.0f, 0.0f, texEndX, texBeginY,
				0.0f, 0.0f, texBeginX, texBeginY,

				0.0f, 1.0f, texBeginX, texEndY,
				1.0f, 1.0f, texEndX, texEndY,
				1.0f, 0.0f, texEndX, texBeginY
			};
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(newVertices), newVertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			shader->useShader();
			bindTextureSide();
			shader->bindTexture();
			glm::mat4 model;
			model = glm::translate(model, glm::vec3(locPos, 0.0f));
			model = glm::translate(model, glm::vec3(0.5f * locSize.x, 0.5f * locSize.y, 0.0f));
			model = glm::translate(model, glm::vec3(-0.5f * locSize.x, -0.5f * locSize.y, 0.0f));
			model = glm::scale(model, glm::vec3(locSize, 1.0f));
			shader->setMat4("projection", projection);
			shader->setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			screenPos.x += glyph.attributes.Advance.x;
		}
		glDeleteVertexArrays(1,&VAO);
		glDeleteBuffers(1,&VBO);
	}
}


}
