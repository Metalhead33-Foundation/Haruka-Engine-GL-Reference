#ifndef BILLBOARD_HPP
#define BILLBOARD_HPP
#include "../abstract/Drawable.hpp"
namespace GFX {

class Billboard
{
private:
	Abstract::sDrawable drawable;
	Abstract::sShaderProgram shader;

	glm::mat4 model;
	static glm::vec3 CameraRight_worldspace;
	static glm::vec3 CameraUp_worldspace;

	glm::vec3 pos;
	glm::vec2 size;
public:
	Billboard();
	void render(const glm::mat4& projection);

	const glm::mat4& getModel() const;
	const glm::vec3& getPos() const;
	const glm::vec2 &getSize() const;
	void setPos(const glm::vec3& npos);
	void setSize(const glm::vec2 &nsize);
	void setModel(const glm::mat4& nmodel);

	float getHeight() const;
	float getWidth() const;
	void setHeight(float setto);
	void setWidth(float setto);
	static void updateWorldspace(const glm::mat4& viewMatrix);

	Abstract::sDrawable getDrawable() const;
	Abstract::sShaderProgram getShader() const;
	void setDrawable(Abstract::sDrawable setto);
	void setShader(Abstract::sShaderProgram setto);
};

}
#endif // BILLBOARD_HPP
