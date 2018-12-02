#include "Model.hpp"
namespace GFX {

Model::Model()
{

}
void Model::bind()
{
	for(auto it = meshes.begin(); it != meshes.end(); ++it) (*it).second->bind();
}
Model::MeshVector& Model::getMeshVector()
{
	return meshes;
}
void Model::setMeshVector(const MeshVector& nMeshes)
{
	meshes = nMeshes;
}
Model::MeshConstIterator Model::meshesBegin() const
{
	return meshes.begin();
}
Model::MeshConstIterator Model::meshesEnd() const
{
	return meshes.end();
}
void Model::addMesh(const std::string &name, Abstract::sMesh mesh)
{
	auto it = meshes.find(name);
	if(it == meshes.end()) meshes.insert(std::make_pair(name,mesh));
	else it->second = mesh;
}

}
