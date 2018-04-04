#ifndef MODEL_HPP
#define MODEL_HPP
#include "Mesh.hpp"

namespace Abstract {

DEFINE_CLASS(Model)
class Model
{
public:
	typedef std::vector<sMesh> MeshVector;
	typedef MeshVector::iterator MeshIterator;
	typedef std::shared_ptr<MeshVector> sMeshVector;
protected:
	sMeshVector meshes;
public:
	virtual ~Model() = default;
	virtual void draw(sShaderProgram shader) = 0;
};

}
#endif // MODEL_HPP
