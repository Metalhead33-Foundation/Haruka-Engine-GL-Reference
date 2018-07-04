#ifndef GLMESH_HPP
#define GLMESH_HPP
#include "../abstract/Mesh.hpp"
#include "../abstract/Bone.hpp"
#include "GlTexture.hpp"
#include "GlShaderProgram.hpp"
#include <glm/mat4x4.hpp>

namespace Gl {

DEFINE_CLASS(Mesh)
DEFINE_CLASS(KeyframeAnimation)
class Mesh : public Abstract::Mesh
{
public:
	friend class KeyframeAnimation;
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
	void applySkeleton(const Abstract::Skeleton &skeleton) const;
};

}
#endif // GLMESH_HPP
