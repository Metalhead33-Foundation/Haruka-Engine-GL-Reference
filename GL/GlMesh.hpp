#ifndef GLMESH_HPP
#define GLMESH_HPP
#include "../abstract/Mesh.hpp"
#include "../abstract/Bone.hpp"
#include "GlTexture.hpp"
#include "GlShaderProgram.hpp"
#include "GlVertexArray.hpp"
#include "GlVertexBufferObject.hpp"
#include "GlIndexBuffer.hpp"
#include <glm/mat4x4.hpp>

namespace Gl {

DEFINE_CLASS(Mesh)
DEFINE_CLASS(KeyframeAnimation)
class Mesh : public Abstract::Mesh
{
public:
	friend class KeyframeAnimation;
private:
	VertexArray VAO;
	VertexBufferObject VBO;
	IndexBuffer EBO;
	void setupMesh();
	Mesh(ConstructorReference constr);
public:
	~Mesh();
	static Abstract::sMesh createMesh(ConstructorReference constr);
	void bind();
	void applySkeleton(const Abstract::Skeleton& skeleton) const;
	void applySkeleton(const Abstract::sSkeleton skeleton) const;
};

}
#endif // GLMESH_HPP
