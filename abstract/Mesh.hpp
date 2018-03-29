#ifndef MESH_HPP
#define MESH_HPP
#include "Vertex.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include <vector>

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
protected:
	VertexVector vertices;
	IndexVector indices;
	TextureVector textures;
public:
	virtual ~Mesh() = default;
	virtual void draw(sShaderProgram shader) = 0;
};

#endif // MESH_HPP
