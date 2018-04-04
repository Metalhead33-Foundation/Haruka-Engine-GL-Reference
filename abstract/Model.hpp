#ifndef MODEL_HPP
#define MODEL_HPP
#include "Mesh.hpp"
// #include <unordered_map>

namespace Abstract {

DEFINE_CLASS(Model)
class Model
{
public:
	typedef Mesh::ConstructorArrayPointer ConstructorPointer;
	typedef Mesh::ConstructorArrayReference ConstructorReference;
	typedef Mesh::ConstructorIterator ConstructorIterator;

	typedef std::vector<sMesh> MeshVector;
	typedef MeshVector::iterator MeshIterator;
	typedef sModel (*EmptyModelCreator)(void);
protected:
	MeshVector meshes;
public:
	virtual ~Model() = default;
	virtual void draw(sShaderProgram shader) = 0;
	virtual void addMesh(sMesh mesh) = 0;
	// virtual sTexture findTexture(const std::string& path) = 0;
};

}
#endif // MODEL_HPP
