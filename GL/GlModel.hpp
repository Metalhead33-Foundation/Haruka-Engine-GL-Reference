#ifndef GLMODEL_HPP
#define GLMODEL_HPP
#include "../abstract/Model.hpp"
#include "GlMesh.hpp"
namespace Gl {

class Model : public Abstract::Model
{
private:
	Model();
	Model(ConstructorPointer constr);
	Model(ConstructorReference constr);
public:
	static Abstract::sModel createEmptyModel();
	static Abstract::sModel createModel(ConstructorPointer constr);
	static Abstract::sModel createModel(ConstructorReference constr);
	void draw(Abstract::sShaderProgram shader);
	void addMesh(Abstract::sMesh mesh);
};

}
#endif // GLMODEL_HPP
