#ifndef GAMESYSTEM_HPP
#define GAMESYSTEM_HPP
#include "MainSystem.hpp"
#include "../abstract/RenderingEngine.hpp"
#include "../audio/System.hpp"
#include "../io/PhysFsFileHandle.hpp"
#include "../io/AiModelFactory.hpp"
#include "../io/AssimpIO.hpp"
#include <assimp/scene.h>
#include <unordered_map>

class GameSystem : public MainSystem
{
public:
	typedef std::unordered_map<std::string, Audio::sBuffer> BufferHash;
	typedef std::unordered_map<std::string, Audio::sSource> SourceHash;
	typedef BufferHash::iterator BufferIterator;
	typedef SourceHash::iterator SourceIterator;

	typedef std::unordered_map<std::string, Abstract::sTexture> TextureHash;
	typedef TextureHash::iterator TextureIterator;
	typedef std::unordered_map<std::string, Abstract::sMesh> MeshHash;
	typedef MeshHash::iterator MeshIterator;
private:
	const Abstract::sRenderingEngine engine;
	const Audio::sSystem soundsys;
	const sAssimpPhysFS modelImporter;
	BufferHash audioBuffers;
	SourceHash audioSources;
	TextureHash textures;
	MeshHash meshes;

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

};

#endif // GAMESYSTEM_HPP
