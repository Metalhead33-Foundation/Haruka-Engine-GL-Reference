#ifndef MODEL_HPP
#define MODEL_HPP
#include "../abstract/Mesh.hpp"
#include <unordered_map>

namespace GFX {

DEFINE_CLASS(Model)
class Model
{
public:
	typedef std::unordered_map<std::string, Abstract::sMesh> MeshVector;
	typedef MeshVector::iterator MeshIterator;
	typedef MeshVector::const_iterator MeshConstIterator;
private:
	MeshVector meshes;
public:
	Model();
	void bind();
	MeshVector& getMeshVector();
	void setMeshVector(const MeshVector& nMeshes);

	MeshConstIterator meshesBegin() const;
	MeshConstIterator meshesEnd() const;

	void addMesh(const std::string& name, Abstract::sMesh mesh);

};

}
#endif // MODEL_HPP
