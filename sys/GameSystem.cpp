#include "GameSystem.hpp"
#include <sstream>
#include <assimp/Importer.hpp>

GameSystem::GameSystem(RenderingBackendFactoryFunction engineCreator, int w, int h, int samplerate, size_t audioBufferSize, const char *title)
	: MainSystem(w, h, title),
	  soundsys(Audio::sSystem(new Audio::System(samplerate, audioBufferSize))),
	  engine(engineCreator(window)),
	  modelImporter(new AssimpPhysFS())
{

}

GameSystem::error_t GameSystem::update(STime& deltaTime)
{
	soundsys->processStreamedAudio();
	return SYSTEM_OKAY;
}
GameSystem::error_t GameSystem::render()
{
	engine->renderFrame();
	return SYSTEM_OKAY;
}
GameSystem::error_t GameSystem::startup()
{
	engine->startup();
	std::cout << "Audio Device Name: " << soundsys->getDeviceName() << std::endl;
	std::cout << "Audio Extension List: " << soundsys->getExtensionList() << std::endl;
	return SYSTEM_OKAY;
}
GameSystem::error_t GameSystem::cleanup()
{
	engine->cleanup();
	return SYSTEM_OKAY;
}
Audio::sBuffer GameSystem::createBuffer(const std::string& key, const std::string& path)
{
	Abstract::sFIO riidaa = PhysFS::FileHandle::openRead(path);
	Audio::sBuffer tmp = soundsys->createSoundBuffer(riidaa);
	audioBuffers.emplace(key, tmp);
	return tmp;
}
Audio::sSource GameSystem::createStream(const std::string& key, const std::string& path, size_t buffNum)
{
	Abstract::sFIO riidaa = PhysFS::FileHandle::openRead(path);
	Audio::sSource tmp = soundsys->createStreamingAudio(riidaa, buffNum);
	audioSources.emplace(key, tmp);
	return tmp;
}
Audio::sSource GameSystem::createSource(const std::string& key, const std::string& buffkey)
{
	BufferIterator it;
	Audio::sSource tmp;
	if(buffkey.length()) audioBuffers.find(buffkey);
	else it = audioBuffers.end();
	if(it == audioBuffers.end())
	{
		tmp = soundsys->createSoundSource();
	}
	else
	{
		tmp = soundsys->createSoundSource(it->second);
	}
	audioSources.emplace(key, tmp);
	return tmp;
}
Audio::sBuffer GameSystem::queryBuffer(const std::string& key)
{
	BufferIterator it = audioBuffers.find(key);
	if(it == audioBuffers.end()) return nullptr;
	else return it->second;
}
Audio::sSource GameSystem::querySource(const std::string& key)
{
	SourceIterator it = audioSources.find(key);
	if(it == audioSources.end()) return nullptr;
	else return it->second;
}
void GameSystem::deleteBuffer(const std::string& key)
{
	BufferIterator it = audioBuffers.find(key);
	if(it != audioBuffers.end()) audioBuffers.erase(it);
}
void GameSystem::deleteSource(const std::string& key)
{
	SourceIterator it = audioSources.find(key);
	if(it != audioSources.end()) audioSources.erase(it);
}
Abstract::sTexture GameSystem::createTextureFromDDS(const std::string& key, const std::string& path, Abstract::Texture::textureType type)
{
	Abstract::sFIO riidaa = PhysFS::FileHandle::openRead(path);
	Abstract::sTexture tmp = engine->createTextureFromDDS(type, riidaa);
	textures.emplace(key, tmp);
	return tmp;
}
Abstract::sTexture GameSystem::createTextureFromImage(const std::string& key, const std::string& path, Abstract::Texture::textureType type)
{
	Abstract::sFIO riidaa = PhysFS::FileHandle::openRead(path);
	Abstract::sTexture tmp = engine->createTextureFromImage(type, riidaa);
	textures.emplace(key, tmp);
	return tmp;
}
Abstract::sTexture GameSystem::queryTexture(const std::string& key)
{
	TextureIterator it = textures.find(key);
	if(it == textures.end()) return nullptr;
	else return it->second;
}
void GameSystem::deleteTexture(const std::string& key)
{
	TextureIterator it = textures.find(key);
	if(it != textures.end()) textures.erase(it);
}
Abstract::sMesh GameSystem::queryMesh(const std::string& key)
{
	MeshIterator it = meshes.find(key);
	if(it == meshes.end()) return nullptr;
	else return it->second;
}
void GameSystem::deleteMesh(const std::string& key)
{
	MeshIterator it = meshes.find(key);
	if(it != meshes.end()) meshes.erase(it);
}
Abstract::sMesh GameSystem::createMeshFromAI(const std::string& key, aiMesh* mesh)
{
	AiModelFactory::MeshCreateInfo info;
	AiModelFactory::ProcessAiMesh(info,mesh);
	Abstract::sMesh tmp = engine->createMesh(info);
	meshes.emplace(key, tmp);
	return tmp;
}
void GameSystem::createMeshesFromModel(const std::string& key, const aiScene* model)
{
	for(unsigned int i = 0; i < model->mNumMeshes;++i)
	{
		std::stringstream name;
		name << key << "." << model->mMeshes[i]->mName.C_Str();
		createMeshFromAI(name.str(),model->mMeshes[i]);
	}
}
void GameSystem::createModel(const std::string& key, const std::string& path)
{
	Assimp::Importer importer;
	importer.SetIOHandler(modelImporter.get());
	const aiScene* scen = importer.ReadFile(path,0);
	createMeshesFromModel(key,scen);
}

GameSystem::error_t GameSystem::processWindowEvent(const SDL_Event& ev, STime &deltaTime)
{
	switch (ev.type)
	{
		case SDL_WINDOWEVENT:
		{
			switch(ev.window.event)
			{
				case SDL_WINDOWEVENT_CLOSE:
					return SYSTEM_EXIT;
					break;
				default:
					break;
			}
			break;
		}
		case SDL_KEYDOWN:
		{
			switch(ev.key.keysym.sym)
			{
			default: break;
			}
			break;
		}
	default:
		break;
	}
	return SYSTEM_OKAY;
}
