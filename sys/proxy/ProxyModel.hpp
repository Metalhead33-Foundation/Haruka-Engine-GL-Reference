#pragma once
#include "ProxyShaderProgram.hpp"
#include "ProxyTexture.hpp"
#include "../../abstract/Mesh.hpp"
#include "../../io/AiModelFactory.hpp"

DEFINE_CLASS(ModelProxy)
DEFINE_CLASS(ModelManager)
typedef Reference<ModelProxy> ModelReference;

class ModelProxy
{
public:
	friend class ModelManager;
	struct RenderMesh {
		Abstract::sMesh mesh;
		Abstract::sShaderProgram shader;
		std::vector<Abstract::sTexture> textures;
		void draw(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model) const;
		void attachTexture(TextureReference tex);
		void detachTexture(TextureReference tex);
		void attachShader(ShaderProgramReference progref);
		void detachShader();
	};
	typedef std::unordered_map<std::string,RenderMesh> MeshHash;
	typedef MeshHash::iterator MeshIterator;
private:
	const std::string Id;
	glm::mat4 modelPosition;
	MeshHash meshes;
	std::string loadPath;
public:
	ModelProxy();
	ModelProxy(const std::string& id);

	void draw(const glm::mat4& projection, const glm::mat4& view) const;
	glm::mat4& getModelPosition();
	void setModelPosition(glm::mat4& npos);
	void attachTexture(const std::string& meshKey, TextureReference tex);
	void detachTexture(const std::string& meshKey, TextureReference tex);
	void attachShader(const std::string& meshKey, ShaderProgramReference progref);
	void detachShader(const std::string& meshKey);

	const std::string& getLoadPath();
	void setLoadPath(const std::string& path);
};
class ModelManager : public ResourceManager
{
public:
	friend class ModelProxy;
	typedef MapTrait<ModelProxy,std::string> ModelMap;
	typedef ModelMap::iterator ModelIterator;
private:
	ModelMap modmp;
public:
	ModelManager();
	~ModelManager();
	ModelReference query(const ModelProxy& proxy);
	ModelReference commit(const ModelProxy& proxy);
	void draw(const glm::mat4 &projection, const glm::mat4 &view);
};
