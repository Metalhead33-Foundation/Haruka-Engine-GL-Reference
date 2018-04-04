#ifndef GLMESH_HPP
#define GLMESH_HPP
#include "../abstract/Mesh.hpp"
#include "GlTexture.hpp"
#include "GlShaderProgram.hpp"

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
	void draw(Abstract::sShaderProgram shader);
};

}
#endif // GLMESH_HPP
