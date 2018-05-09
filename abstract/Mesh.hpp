#ifndef MESH_HPP
#define MESH_HPP
#include "Vertex.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include <unordered_map>
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
	};
	typedef MeshConstructor& ConstructorReference;
	typedef std::unordered_map<std::string,MeshConstructor> ConstructorArray;
	typedef ConstructorArray::iterator ConstructorIterator;
	typedef ConstructorArray& ConstructorArrayReference;
	typedef std::shared_ptr<ConstructorArray> ConstructorArrayPointer;

	typedef sMesh (*MeshCreatorFunction)(ConstructorReference);
protected:
	VertexVector vertices;
	IndexVector indices;
public:
	virtual ~Mesh() = default;
	virtual void bind() = 0;
};

}
#endif // MESH_HPP
