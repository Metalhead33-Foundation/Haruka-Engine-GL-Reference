#include "GlModel.hpp"
namespace Gl {

Model::Model()
{
	;
}
Model::Model(ConstructorPointer constr)
{
	for(ConstructorIterator it = constr->begin(); it != constr->end(); ++it)
	{
		meshes.push_back(Mesh::createMesh(*it));
	}
}
Model::Model(ConstructorReference constr)
{
	for(ConstructorIterator it = constr.begin(); it != constr.end(); ++it)
	{
		meshes.push_back(Mesh::createMesh(*it));
	}
}
void Model::draw(Abstract::sShaderProgram shader)
{
	for(MeshIterator it = meshes.begin(); it != meshes.end(); ++it)
	{
		it->get()->draw(shader);
	}
}
void Model::addMesh(Abstract::sMesh mesh)
{
	meshes.push_back(mesh);
}
Abstract::sModel Model::createEmptyModel()
{
	return Abstract::sModel(new Model());
}
Abstract::sModel Model::createModel(ConstructorPointer constr)
{
	return Abstract::sModel(new Model(constr));
}
Abstract::sModel Model::createModel(ConstructorReference constr)
{
	return Abstract::sModel(new Model(constr));
}

}
