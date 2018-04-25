#ifndef GLMESH_HPP
#define GLMESH_HPP
#include "../abstract/Mesh.hpp"
#include "GlTexture.hpp"
#include "GlShaderProgram.hpp"
#include <glm/mat4x4.hpp>

namespace Gl {

DEFINE_CLASS(Mesh)
class Mesh : public Abstract::Mesh
{
private:
	GLuint VAO, VBO, EBO;
	GLsizei indexSize;
	void setupMesh();
	Mesh(ConstructorReference constr);
public:
	~Mesh();
	static Abstract::sMesh createMesh(ConstructorReference constr);
	const GLuint& getVAO() const;
	const GLuint& getVBO() const;
	const GLuint& getEBO() const;
	void bind();
};

}
#endif // GLMESH_HPP
