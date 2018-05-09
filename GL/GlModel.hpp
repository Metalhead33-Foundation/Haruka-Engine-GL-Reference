#ifndef GLMODEL_HPP
#define GLMODEL_HPP
#include "../abstract/Model.hpp"
#include "GlMesh.hpp"
namespace Gl {

class Model : public Abstract::Model
{
private:
	TextureVector textures;
	MeshMap meshes;
public:
	Model();
	TextureCollection getTextures() const;
	void setTextures(TextureCollection ntextures);
	MeshCollection getMeshes() const ;
	void setMeshes(MeshCollection nmeshes);
	void render(const glm::mat4& model, Abstract::sShaderProgram shader);
};

}
#endif // GLMODEL_HPP
