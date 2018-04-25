#ifndef PROXYMODEL_HPP
#define PROXYMODEL_HPP
#include "ProxyShaderProgram.hpp"
#include "ProxyTexture.hpp"
#include "../../abstract/Mesh.hpp"
#include "../../abstract/RenderingEngine.hpp"
#include "../../io/AiModelFactory.hpp"
#include "../../abstract/RenderingEngine.hpp"
#include <assimp/Importer.hpp>

DEFINE_CLASS(ModelProxy)
DEFINE_CLASS(ModelManager)
typedef Reference<ModelProxy> ModelReference;

class ModelProxy : public Proxy
{
public:
	friend class ModelManager;
	typedef Abstract::RenderingEngine::MeshCreator MeshCreator;
	struct RenderMesh {
		Abstract::sMesh mesh;
		Abstract::sShaderProgram shader;
		std::vector<Abstract::sTexture> textures;
		AiModelFactory::MeshCreateInfo createInfo;
		void draw(Abstract::sRenderingEngine engine, const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model) const;
		void attachTexture(TextureReference tex);
		void detachTexture(TextureReference tex);
		void attachShader(ShaderProgramReference progref);
		void detachShader();
		void construct(aiMesh* rawmesh);
		void build(MeshCreator creator);
		RenderMesh();
		RenderMesh(const RenderMesh& cpy);
		RenderMesh(Abstract::sMesh nmesh);
	};
	typedef std::unordered_map<std::string,RenderMesh> MeshHash;
	typedef MeshHash::iterator MeshIterator;
private:
	glm::mat4 modelPosition;
	MeshHash meshes;
	std::string loadPath;
	bool constuct(Assimp::IOSystem* importer);
	bool isConstructed;
public:
	ModelProxy();
	ModelProxy(const ModelProxy& cpy);
	ModelProxy(const std::string& id);
	ModelProxy(const std::string& id, const std::string& loadpath);

	void draw(Abstract::sRenderingEngine engine, const glm::mat4& projection, const glm::mat4& view) const;
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
	typedef ModelMap::HashIterator ModelIterator;
private:
	ModelMap modmp;
public:
	ModelManager() = default;
	~ModelManager() = default;
	ModelReference query(const ModelProxy& proxy);
	ModelReference query(const std::string& key);
	ModelReference commit(ModelProxy& proxy);
	void draw(const glm::mat4 &projection, const glm::mat4 &view);
	bool loadModel(ModelProxy& model);
};
#endif // PROXYMODEL_HPP
