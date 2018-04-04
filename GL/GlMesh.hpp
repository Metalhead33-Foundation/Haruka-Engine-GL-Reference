#ifndef GLMESH_HPP
#define GLMESH_HPP
#include "../abstract/Mesh.hpp"
#include "GlTexture.hpp"
#include "GlShaderProgram.hpp"

class GlMesh : public Mesh
{
private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
	GlMesh(ConstructorReference constr);
public:
	static sMesh createMesh(ConstructorReference constr);
	const GLuint& getVAO() const;
	const GLuint& getVBO() const;
	const GLuint& getEBO() const;
	void draw(sShaderProgram shader);
};

#endif // GLMESH_HPP
