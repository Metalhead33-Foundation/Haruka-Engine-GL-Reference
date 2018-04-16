#ifndef GAMESYSTEM_HPP
#define GAMESYSTEM_HPP
#include "MainSystem.hpp"
#include "../abstract/RenderingEngine.hpp"
#include "../audio/System.hpp"
#include "../io/PhysFsFileHandle.hpp"
#include "../io/AiModelFactory.hpp"
#include "../io/AssimpIO.hpp"
#include "Camera.hpp"
#include <assimp/scene.h>
#include <unordered_map>

class GameSystem : public MainSystem
{
public:
	struct RenderableMesh
	{
		Abstract::sMesh mesh;
		Abstract::sShaderProgram shader;
		void draw(glm::mat4& projectionMatrix, glm::mat4& view, glm::mat4& model);
	};
	typedef std::unordered_map<std::string, Audio::sBuffer> BufferHash;
	typedef std::unordered_map<std::string, Audio::sSource> SourceHash;
	typedef BufferHash::iterator BufferIterator;
	typedef SourceHash::iterator SourceIterator;

	typedef std::unordered_map<std::string, Abstract::sTexture> TextureHash;
	typedef TextureHash::iterator TextureIterator;
	typedef std::unordered_map<std::string, RenderableMesh> MeshHash;
	typedef MeshHash::iterator MeshIterator;
	typedef std::unordered_map<std::string, Abstract::sShaderModule> ShaderModuleHash;
	typedef std::unordered_map<std::string, Abstract::sShaderProgram> ShaderProgramHash;
	typedef ShaderModuleHash::iterator ShaderModuleIterator;
	typedef ShaderProgramHash::iterator ShaderProgramIterator;
private:
	const Abstract::sRenderingEngine engine;
	const Audio::sSystem soundsys;
	const sAssimpPhysFS modelImporter;
	BufferHash audioBuffers;
	SourceHash audioSources;
	TextureHash textures;
	MeshHash meshes;
	ShaderModuleHash shaderModules;
	ShaderProgramHash shaderPrograms;
	Camera camera;
	int mouseX, mouseY;
	glm::mat4 projectionMatrix, viewMatrix, modelMatrix;

	Abstract::sMesh createMeshFromAI(const std::string& key, aiMesh* mesh);
	void createMeshesFromModel(const std::string& key, const aiScene* model);
public:
	GameSystem(RenderingBackendFactoryFunction engineCreator, int w, int h, int samplerate, size_t audioBufferSize, const char* title);
	error_t update(STime& deltaTime);
	error_t render();
	error_t startup();
	error_t cleanup();
	error_t processWindowEvent(const SDL_Event& ev, STime& deltaTime);

	Audio::sBuffer createBuffer(const std::string& key, const std::string& path);
	Audio::sSource createStream(const std::string& key, const std::string& path, size_t buffNum=2);
	Audio::sSource createSource(const std::string& key, const std::string& buffkey);

	Audio::sBuffer queryBuffer(const std::string& key);
	Audio::sSource querySource(const std::string& key);
	void deleteBuffer(const std::string& key);
	void deleteSource(const std::string& key);

	Abstract::sTexture createTextureFromDDS(const std::string& key, const std::string& path, Abstract::Texture::textureType type);
	Abstract::sTexture createTextureFromImage(const std::string& key, const std::string& path, Abstract::Texture::textureType type);
	Abstract::sTexture queryTexture(const std::string& key);
	void deleteTexture(const std::string& key);

	void createModel(const std::string& key, const std::string& path);
	Abstract::sMesh queryMesh(const std::string& key);
	void deleteMesh(const std::string& key);
	void attachTextureToMesh(const std::string& meshKey, const std::string& texKey);
	void attachTextureToMesh(const std::string& meshKey, const std::vector<std::string>& texKeys);
	void attachShaderToMesh(const std::string& meshKey, const std::string& progKey);

	Abstract::sShaderModule createShaderModule(const std::string& key, const std::string& path, Abstract::ShaderModule::ShaderType ntype);
	Abstract::sShaderModule queryShaderModule(const std::string& key);
	void deleteShaderModule(const std::string& key);
	Abstract::sShaderProgram createShaderProgram(const std::string& key);
	Abstract::sShaderProgram queryShaderProgram(const std::string& key);
	void deleteShaderProgram(const std::string& key);

	void attachShaderModule(const std::string& programKey, const std::string& moduleKey);
	void attachShaderModule(const std::string& programKey, const std::vector<std::string>& moduleKeys);

};

#endif // GAMESYSTEM_HPP
