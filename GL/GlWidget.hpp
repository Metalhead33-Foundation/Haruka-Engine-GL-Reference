#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP
#include "../abstract/Widget.hpp"
#include "GlTexture.hpp"
#include "GlShaderProgram.hpp"
namespace Gl {

class Widget : public Abstract::Widget
{
public:
	struct Quad
	{
		GLuint quadArrayId;
		GLuint quadBufferId;
		Quad();
		~Quad();
		void draw();
	};
	typedef std::shared_ptr<Quad> sQuad;
private:
	int height;
	int width;
	glm::vec2 size;
	Abstract::sTexture texture;
	static sQuad QUAD;

	Widget(int height, int width, Abstract::sTexture tex = nullptr);
public:
	static Abstract::sWidget create(int height, int width, Abstract::sTexture tex = nullptr);

	void setTexture(Abstract::sTexture tex);
	Abstract::sTexture getTexture();
	void setWidth(int width);
	void setHeight(int height);
	int getWidth() const;
	int getHeight() const;
	void draw(Abstract::sShaderProgram shader, glm::vec2& position,
			  glm::mat4& projection);
	static void initializeQuad();
	static void deinitializeQuad();
};

}

#endif // GLWIDGET_HPP
