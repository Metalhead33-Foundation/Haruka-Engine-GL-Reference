#ifndef MODEL_HPP
#define MODEL_HPP
#include "Drawable.hpp"
#include "Mesh.hpp"
#include <unordered_map>
namespace Abstract {
DEFINE_CLASS(Model)
class Model : public Drawable
{
public:
	typedef Mesh::TextureVector TextureVector;
	typedef const TextureVector& TextureCollection;
	typedef std::unordered_map<std::string,sMesh> MeshMap;
	typedef const MeshMap& MeshCollection;

	virtual ~Model() = default;
	virtual TextureCollection getTextures() const = 0;
	virtual void setTextures(TextureCollection ntextures) = 0;
	virtual MeshCollection getMeshes() const = 0;
	virtual void setMeshes(MeshCollection nmeshes) = 0;
};

}
#endif // MODEL_HPP
