#ifndef GLMESH_HPP
#define GLMESH_HPP
#include "../abstract/Mesh.hpp"
#include "GlTexture.hpp"
#include "GlShaderProgram.hpp"
#include <glm/mat4x4.hpp>

namespace Gl {

class Mesh : public Abstract::Mesh
{
private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
	Mesh(ConstructorReference constr);
public:
	static Abstract::sMesh createMesh(ConstructorReference constr);
	const GLuint& getVAO() const;
	const GLuint& getVBO() const;
	const GLuint& getEBO() const;
	void draw(Abstract::sShaderProgram shader, glm::mat4& projection, glm::mat4& view, glm::mat4& model);
};

}
#endif // GLMESH_HPP
