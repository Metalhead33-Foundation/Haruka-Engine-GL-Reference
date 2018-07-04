#include "Model.hpp"
namespace GFX {

Model::Model()
{

}
void Model::render(const glm::mat4& model, Abstract::sShaderProgram shader)
{
	if(shader)
	{
		shader->useShader();
		shader->setMat4("model",model);
		for(auto it = textures.begin(); it != textures.end(); ++it) shader->bindTexture(*it);
		for(auto it = meshes.begin(); it != meshes.end(); ++it) (*it)->bind();
	}
}
Model::MeshVector& Model::getMeshVector()
{
	return meshes;
}
Model::TextureVector& Model::getTextureVector()
{
	return textures;
}
void Model::setMeshVector(const MeshVector& nMeshes)
{
	meshes = nMeshes;
}
void Model::setTextureVector(const TextureVector& nTextures)
{
	textures = nTextures;
}
Model::MeshConstIterator Model::meshesBegin() const
{
	return meshes.begin();
}
Model::MeshConstIterator Model::meshesEnd() const
{
	return meshes.end();
}
Model::TextureConstIterator Model::texturesBegin() const
{
	return textures.begin();
}
Model::TextureConstIterator Model::texturesEnd() const
{
	return textures.end();
}
void Model::addMesh(Abstract::sMesh mesh)
{
	meshes.push_back(mesh);
}
void Model::addTexture(Abstract::sTexture texture)
{
	textures.push_back(texture);
}

}
