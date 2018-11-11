#ifndef MODEL_HPP
#define MODEL_HPP
#include "../abstract/Drawable.hpp"
#include "../abstract/Mesh.hpp"
#include "../abstract/Texture.hpp"
#include <vector>
#include <unordered_map>

namespace GFX {

class Model : public Abstract::Drawable
{
public:
	typedef std::unordered_map<std::string, Abstract::sMesh> MeshVector;
	typedef std::vector<Abstract::sTexture> TextureVector;
	typedef MeshVector::iterator MeshIterator;
	typedef TextureVector::iterator TextureIterator;
	typedef MeshVector::const_iterator MeshConstIterator;
	typedef TextureVector::const_iterator TextureConstIterator;
private:
	MeshVector meshes;
	TextureVector textures;
public:
	Model();
	void render(const glm::mat4& model, Abstract::sShaderProgram shader);
	MeshVector& getMeshVector();
	TextureVector& getTextureVector();
	void setMeshVector(const MeshVector& nMeshes);
	void setTextureVector(const TextureVector& nTextures);

	MeshConstIterator meshesBegin() const;
	MeshConstIterator meshesEnd() const;
	TextureConstIterator texturesBegin() const;
	TextureConstIterator texturesEnd() const;

	void addMesh(Abstract::sMesh mesh);
	void addTexture(Abstract::sTexture texture);

};

}
#endif // MODEL_HPP
