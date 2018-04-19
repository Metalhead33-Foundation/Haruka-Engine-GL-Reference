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
#include <queue>
#include <functional>
#include "../abstract/Future.hpp"
#include <mutex>

class GameSystem : public MainSystem
{
public:
	typedef std::queue<std::function<void(void)>> CommandQueue;

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

	Abstract::sMesh __createMeshFromAI(const std::string& key, aiMesh* mesh);
	void __createMeshesFromModel(const std::string& key, const aiScene* model);

	CommandQueue commandQueue;
	std::mutex commandMutex;

	Audio::sBuffer __createBuffer(const std::string& key, const std::string& path);
	Audio::sSource __createStream(const std::string& key, const std::string& path, size_t buffNum=2);
	Audio::sSource __createSource(const std::string& key, const std::string& buffkey);
	void __deleteBuffer(const std::string& key);
	void __deleteSource(const std::string& key);
	Abstract::sTexture __createTextureFromDDS(const std::string& key, const std::string& path, Abstract::Texture::textureType type);
	Abstract::sTexture __createTextureFromImage(const std::string& key, const std::string& path, Abstract::Texture::textureType type);
	void __deleteTexture(const std::string& key);
	void __createModel(const std::string& key, const std::string& path);
	void __deleteMesh(const std::string& key);
	void __attachTextureToMesh(const std::string& meshKey, const std::string& texKey);
	void __attachTextureToMesh(const std::string& meshKey, const std::vector<std::string>& texKeys);
	void __attachShaderToMesh(const std::string& meshKey, const std::string& progKey);
	Abstract::sShaderModule __createShaderModule(const std::string& key, const std::string& path, Abstract::ShaderModule::ShaderType ntype);
	void __deleteShaderModule(const std::string& key);
	Abstract::sShaderProgram __createShaderProgram(const std::string& key);
	void __deleteShaderProgram(const std::string& key);
	void __attachShaderModule(const std::string& programKey, const std::string& moduleKey);
	void __attachShaderModule(const std::string& programKey, const std::vector<std::string>& moduleKeys);
	void __linkShaders(const std::string& programKey);
public:
	GameSystem(RenderingBackendFactoryFunction engineCreator, int w, int h, int samplerate, size_t audioBufferSize, const char* title, int intendedFramerate=60);
	error_t update(STime& deltaTime);
	error_t render();
	error_t startup();
	error_t cleanup();
	error_t processWindowEvent(const SDL_Event& ev, STime& deltaTime);

	Audio::sBuffer queryBuffer(const std::string& key);
	Audio::sSource querySource(const std::string& key);
	Abstract::sTexture queryTexture(const std::string& key);
	Abstract::sMesh queryMesh(const std::string& key);
	Abstract::sShaderModule queryShaderModule(const std::string& key);
	Abstract::sShaderProgram queryShaderProgram(const std::string& key);

	Future<Audio::sBuffer> createBuffer(const std::string& key, const std::string& path);
	Future<Audio::sSource> createStream(const std::string& key, const std::string& path, size_t buffNum=2);
	Future<Audio::sSource> createSource(const std::string& key, const std::string& buffkey);
	void deleteBuffer(const std::string& key);
	void deleteSource(const std::string& key);
	Future<Abstract::sTexture> createTextureFromDDS(const std::string& key, const std::string& path, Abstract::Texture::textureType type);
	Future<Abstract::sTexture> createTextureFromImage(const std::string& key, const std::string& path, Abstract::Texture::textureType type);
	void deleteTexture(const std::string& key);
	void createModel(const std::string& key, const std::string& path);
	void deleteMesh(const std::string& key);
	void attachTextureToMesh(const std::string& meshKey, const std::string& texKey);
	void attachTextureToMesh(const std::string& meshKey, const std::vector<std::string>& texKeys);
	void attachShaderToMesh(const std::string& meshKey, const std::string& progKey);
	Future<Abstract::sShaderModule> createShaderModule(const std::string& key, const std::string& path, Abstract::ShaderModule::ShaderType ntype);
	void deleteShaderModule(const std::string& key);
	Future<Abstract::sShaderProgram> createShaderProgram(const std::string& key);
	void deleteShaderProgram(const std::string& key);
	void attachShaderModule(const std::string& programKey, const std::string& moduleKey);
	void attachShaderModule(const std::string& programKey, const std::vector<std::string>& moduleKeys);
	void linkShaders(const std::string& programKey);
};

#endif // GAMESYSTEM_HPP
