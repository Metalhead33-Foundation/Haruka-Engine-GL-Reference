#ifndef MESH_HPP
#define MESH_HPP
#include "Vertex.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include <vector>
#include <glm/glm.hpp>

namespace Abstract {

DEFINE_CLASS(Mesh)
class Mesh
{
public:
	typedef std::vector<Vertex> VertexVector;
	typedef VertexVector::iterator VertexIterator;
	typedef std::vector<uint32_t> IndexVector;
	typedef IndexVector::iterator IndexIterator;
	typedef std::vector<sTexture> TextureVector;
	typedef TextureVector::iterator TextureIterator;

	typedef std::shared_ptr<VertexVector> sVertexVector;
	typedef std::shared_ptr<IndexVector> sIndexVector;
	typedef std::shared_ptr<TextureVector> sTextureVector;

	struct MeshConstructor
	{
		sVertexVector vec;
		sIndexVector ind;
		TextureVector tex;
	};
	typedef MeshConstructor& ConstructorReference;
	typedef std::vector<MeshConstructor> ConstructorArray;
	typedef std::vector<MeshConstructor>::iterator ConstructorIterator;
	typedef ConstructorArray& ConstructorArrayReference;
	typedef std::shared_ptr<ConstructorArray> ConstructorArrayPointer;

	typedef sMesh (*MeshCreatorFunction)(ConstructorReference);
protected:
	VertexVector vertices;
	IndexVector indices;
	TextureVector textures;
public:
	virtual ~Mesh() = default;
	virtual void draw(sShaderProgram shader, glm::mat4& projection, glm::mat4& view, glm::mat4& model) = 0;
	TextureVector& getTextures() { return textures; }
	void setTextures(TextureVector& text) { textures = text; }
};

}
#endif // MESH_HPP
