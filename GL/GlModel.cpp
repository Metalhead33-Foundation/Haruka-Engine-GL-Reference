#include "GlModel.hpp"

namespace Gl {

Model::Model()
{

}
Model::TextureCollection Model::getTextures() const
{
	return textures;
}
void Model::setTextures(TextureCollection ntextures)
{
	textures = ntextures;
}
Model::MeshCollection Model::getMeshes() const
{
	return meshes;
}
void Model::setMeshes(MeshCollection nmeshes)
{
	meshes = nmeshes;
}
void Model::render(const glm::mat4& model, Abstract::sShaderProgram shader)
{
	if(shader)
	{
		shader->useShader();
		shader->setMat4("model", model);
		for(auto it = textures.begin(); it != textures.end(); ++it)
		{
			shader->bindTexture(*it);
		}
		for(auto it = meshes.begin(); it != meshes.end(); ++it)
		{
			if(it->second) it->second->bind();
		}
		glActiveTexture(GL_TEXTURE0);
	}
}

}
