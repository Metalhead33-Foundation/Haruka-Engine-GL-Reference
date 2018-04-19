#include "GameSystem.hpp"
#include <sstream>
#include <assimp/Importer.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void GameSystem::RenderableMesh::draw(glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model)
{
	Abstract::sShaderProgram shader = this->shader;
	Abstract::sMesh mesh = this->mesh;
	if(shader && mesh) mesh->draw(shader, projection, view, model);
}

GameSystem::GameSystem(RenderingBackendFactoryFunction engineCreator, int w, int h,
					   int samplerate, size_t audioBufferSize, const char *title, int intendedFramerate)
	: MainSystem(w, h, title,intendedFramerate),
	  soundsys(Audio::sSystem(new Audio::System(samplerate, audioBufferSize))),
	  engine(engineCreator(window)),
	  modelImporter(new AssimpPhysFS())
{
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
	// modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
}

GameSystem::error_t GameSystem::update(STime& deltaTime)
{
	soundsys->processStreamedAudio();
	SDL_GetRelativeMouseState(&mouseX, &mouseY);
	camera.ProcessMouseMovement(float(mouseX),float(mouseY * -1),false);
	projectionMatrix = glm::perspective(glm::radians(camera.getZoom()), float(window->w) / float(window->h), 0.1f, 100.0f);
	viewMatrix = camera.GetViewMatrix();
	std::unique_lock<std::mutex> queue(commandMutex);
	while(!commandQueue.empty())
	{
		auto func = commandQueue.front();
		commandQueue.pop();
		queue.unlock();
		func();
		queue.lock();
	}
	queue.unlock();
	return SYSTEM_OKAY;
}
GameSystem::error_t GameSystem::render()
{
	engine->clearBackground();
	// engine->renderFrame();
	for(MeshIterator it = meshes.begin(); it != meshes.end();++it)
	{
		it->second.draw(projectionMatrix, viewMatrix, modelMatrix);
	}
	engine->switchBuffers();
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
	meshes.clear();
	textures.clear();
	shaderModules.clear();
	shaderPrograms.clear();
	audioBuffers.clear();
	audioSources.clear();
	return SYSTEM_OKAY;
}
Audio::sBuffer GameSystem::__createBuffer(const std::string& key, const std::string& path)
{
	Abstract::sFIO riidaa = PhysFS::FileHandle::openRead(path);
	Audio::sBuffer tmp = soundsys->createSoundBuffer(riidaa);
	audioBuffers.emplace(key, tmp);
	return tmp;
}
Audio::sSource GameSystem::__createStream(const std::string& key, const std::string& path, size_t buffNum)
{
	Abstract::sFIO riidaa = PhysFS::FileHandle::openRead(path);
	Audio::sSource tmp = soundsys->createStreamingAudio(riidaa, buffNum);
	audioSources.emplace(key, tmp);
	return tmp;
}
Audio::sSource GameSystem::__createSource(const std::string& key, const std::string& buffkey)
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
void GameSystem::__deleteBuffer(const std::string& key)
{
	BufferIterator it = audioBuffers.find(key);
	if(it != audioBuffers.end()) audioBuffers.erase(it);
}
void GameSystem::__deleteSource(const std::string& key)
{
	SourceIterator it = audioSources.find(key);
	if(it != audioSources.end()) audioSources.erase(it);
}
Abstract::sTexture GameSystem::__createTextureFromDDS(const std::string& key, const std::string& path, Abstract::Texture::textureType type)
{
	Abstract::sFIO riidaa = PhysFS::FileHandle::openRead(path);
	Abstract::sTexture tmp = engine->createTextureFromDDS(type, riidaa);
	textures.emplace(key, tmp);
	return tmp;
}
Abstract::sTexture GameSystem::__createTextureFromImage(const std::string& key, const std::string& path, Abstract::Texture::textureType type)
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
void GameSystem::__deleteTexture(const std::string& key)
{
	TextureIterator it = textures.find(key);
	if(it != textures.end()) textures.erase(it);
}
Abstract::sMesh GameSystem::queryMesh(const std::string& key)
{
	MeshIterator it = meshes.find(key);
	if(it == meshes.end()) return nullptr;
	else return it->second.mesh;
}
void GameSystem::__deleteMesh(const std::string& key)
{
	MeshIterator it = meshes.find(key);
	if(it != meshes.end()) meshes.erase(it);
}
Abstract::sMesh GameSystem::__createMeshFromAI(const std::string& key, aiMesh* mesh)
{
	if(!mesh) return nullptr;
	AiModelFactory::MeshCreateInfo info;
	AiModelFactory::ProcessAiMesh(info,mesh);
	Abstract::sMesh tmp = engine->createMesh(info);
	meshes.emplace(key, RenderableMesh{tmp, 0} );
	return tmp;
}
void GameSystem::__createMeshesFromModel(const std::string& key, const aiScene* model)
{
	if(!model) return;
	for(unsigned int i = 0; i < model->mNumMeshes;++i)
	{
		std::stringstream name;
		name << key << "." << model->mMeshes[i]->mName.C_Str();
		__createMeshFromAI(name.str(),model->mMeshes[i]);
		std::cout << key << "." << model->mMeshes[i]->mName.C_Str() << " - " << model->mMeshes[i]->mNumVertices << std::endl;
	}
}
void GameSystem::__createModel(const std::string& key, const std::string& path)
{
	Assimp::Importer importer;
	importer.SetIOHandler(modelImporter.get());
	const aiScene* scen = importer.ReadFile(path,aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_PreTransformVertices |
											aiProcess_CalcTangentSpace |
											aiProcess_GenSmoothNormals |
											aiProcess_Triangulate |
											aiProcess_FixInfacingNormals |
											aiProcess_FindInvalidData |
											aiProcess_ValidateDataStructure | 0

										 );
	if(!scen) std::cout << "Error loading model!" << importer.GetErrorString() << std::endl;
	std::cout << scen->mNumMeshes << std::endl;
	__createMeshesFromModel(key,scen);
}
Abstract::sShaderModule GameSystem::__createShaderModule(const std::string& key, const std::string& path, Abstract::ShaderModule::ShaderType ntype)
{
	Abstract::sFIO riidaa = PhysFS::FileHandle::openRead(path);
	Abstract::sShaderModule tmp = engine->createShaderModule(ntype, riidaa);
	shaderModules.emplace(key, tmp);
	return tmp;
}
Abstract::sShaderModule GameSystem::queryShaderModule(const std::string& key)
{
	ShaderModuleIterator it = shaderModules.find(key);
	if(it == shaderModules.end()) return nullptr;
		else return it->second;
}
void GameSystem::__deleteShaderModule(const std::string& key)
{
	ShaderModuleIterator it = shaderModules.find(key);
	if(it != shaderModules.end()) shaderModules.erase(it);
}
Abstract::sShaderProgram GameSystem::__createShaderProgram(const std::string& key)
{
	Abstract::sShaderProgram tmp = engine->createShaderProgram();
	shaderPrograms.emplace(key, tmp);
	return tmp;
}
Abstract::sShaderProgram GameSystem::queryShaderProgram(const std::string& key)
{
	ShaderProgramIterator it = shaderPrograms.find(key);
	if(it == shaderPrograms.end()) return nullptr;
		else return it->second;
}
void GameSystem::__deleteShaderProgram(const std::string& key)
{
	ShaderProgramIterator it = shaderPrograms.find(key);
	if(it != shaderPrograms.end()) shaderPrograms.erase(it);
}

void GameSystem::__attachShaderModule(const std::string& programKey, const std::string& moduleKey)
{
	ShaderProgramIterator progIt = shaderPrograms.find(programKey);
	if(progIt == shaderPrograms.end()) return;
	ShaderModuleIterator modIt = shaderModules.find(moduleKey);
	if(modIt == shaderModules.end()) return;
	progIt->second->pushModule(modIt->second);
}
void GameSystem::__attachShaderModule(const std::string& programKey, const std::vector<std::string>& moduleKeys)
{
	ShaderProgramIterator progIt = shaderPrograms.find(programKey);
	if(progIt == shaderPrograms.end()) return;
	for(std::vector<std::string>::const_iterator it = moduleKeys.begin(); it != moduleKeys.end();++it)
	{
		ShaderModuleIterator modIt = shaderModules.find(*it);
		if(modIt != shaderModules.end()) progIt->second->pushModule(modIt->second);
	}
}
void GameSystem::__attachShaderToMesh(const std::string& meshKey, const std::string& progKey)
{
	MeshIterator meshIt = meshes.find(meshKey);
	if(meshIt == meshes.end()) return;
	ShaderProgramIterator progIt = shaderPrograms.find(progKey);
	if(progIt == shaderPrograms.end()) return;
	meshIt->second.shader = progIt->second;
}
void GameSystem::__attachTextureToMesh(const std::string& meshKey, const std::string& texKey)
{
	MeshIterator meshIt = meshes.find(meshKey);
	if(meshIt == meshes.end()) return;
	TextureIterator texIt = textures.find(texKey);
	if(texIt == textures.end()) return;
	meshIt->second.mesh->getTextures().push_back(texIt->second);
}
void GameSystem::__attachTextureToMesh(const std::string& meshKey, const std::vector<std::string>& texKeys)
{
	MeshIterator meshIt = meshes.find(meshKey);
	if(meshIt == meshes.end()) return;
	if(texKeys.size())
	{
		Abstract::Mesh::TextureVector tempTextures(0);
		for(std::vector<std::string>::const_iterator it = texKeys.begin(); it != texKeys.end();++it)
		{
			TextureIterator texIt = textures.find(*it);
			if(texIt != textures.end()) tempTextures.push_back(texIt->second);
		}
		meshIt->second.mesh->setTextures(tempTextures);
	}
	else
	{
		meshIt->second.mesh->getTextures().clear();
	}
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
			case SDLK_ESCAPE:
				return SYSTEM_EXIT;
				break;
			case SDLK_w:
				camera.ProcessKeyboard(Camera::FORWARD, deltaTime.getSeconds());
				break;
			case SDLK_s:
				camera.ProcessKeyboard(Camera::BACKWARD, deltaTime.getSeconds());
				break;
			case SDLK_a:
				camera.ProcessKeyboard(Camera::LEFT, deltaTime.getSeconds());
				break;
			case SDLK_d:
				camera.ProcessKeyboard(Camera::RIGHT, deltaTime.getSeconds());
				break;
			default: break;
			}
			break;
		}
	default:
		break;
	}
	return SYSTEM_OKAY;
}

Future<Audio::sBuffer> GameSystem::createBuffer(const std::string& key, const std::string& path)
{
	Future<Audio::sBuffer> futur;
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([futur,key,path,this](){
		futur.store(__createBuffer(key,path));
	  });
	queue.unlock();
	return futur;
}
Future<Audio::sSource> GameSystem::createStream(const std::string& key, const std::string& path, size_t buffNum)
{
	Future<Audio::sSource> futur;
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([futur,key,path,buffNum,this](){
		futur.store(__createStream(key,path,buffNum));
	  });
	queue.unlock();
	return futur;
}
Future<Audio::sSource> GameSystem::createSource(const std::string& key, const std::string& buffkey)
{
	Future<Audio::sSource> futur;
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([futur,key,buffkey,this](){
		futur.store(__createSource(key,buffkey));
	  });
	queue.unlock();
	return futur;
}
void GameSystem::deleteBuffer(const std::string& key)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([key,this](){
		__deleteBuffer(key);
	  });
	queue.unlock();
}
void GameSystem::deleteSource(const std::string& key)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([key,this](){
		__deleteSource(key);
	  });
	queue.unlock();
}
Future<Abstract::sTexture> GameSystem::createTextureFromDDS(const std::string& key, const std::string& path, Abstract::Texture::textureType type)
{
	Future<Abstract::sTexture> futur;
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([futur,key,path,type,this](){
		futur.store(__createTextureFromDDS(key,path,type));
	  });
	queue.unlock();
	return futur;
}
Future<Abstract::sTexture> GameSystem::createTextureFromImage(const std::string& key, const std::string& path, Abstract::Texture::textureType type)
{
	Future<Abstract::sTexture> futur;
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([futur,key,path,type,this](){
		futur.store(__createTextureFromImage(key,path,type));
	  });
	queue.unlock();
	return futur;
}
void GameSystem::deleteTexture(const std::string& key)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([key,this](){
		__deleteTexture(key);
	  });
	queue.unlock();
}
void GameSystem::createModel(const std::string& key, const std::string& path)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([key,path,this](){
		__createModel(key,path);
	  });
	queue.unlock();
}
void GameSystem::deleteMesh(const std::string& key)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([key,this](){
		__deleteMesh(key);
	  });
	queue.unlock();
}
void GameSystem::attachTextureToMesh(const std::string& meshKey, const std::string& texKey)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([meshKey,texKey,this](){
		__attachTextureToMesh(meshKey,texKey);
	  });
	queue.unlock();
}
void GameSystem::attachTextureToMesh(const std::string& meshKey, const std::vector<std::string>& texKeys)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([meshKey,texKeys,this](){
		__attachTextureToMesh(meshKey,texKeys);
	  });
	queue.unlock();
}
void GameSystem::attachShaderToMesh(const std::string& meshKey, const std::string& progKey)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([meshKey,progKey,this](){
		__attachShaderToMesh(meshKey,progKey);
	  });
	queue.unlock();
}
Future<Abstract::sShaderModule> GameSystem::createShaderModule(const std::string& key, const std::string& path, Abstract::ShaderModule::ShaderType ntype)
{
	Future<Abstract::sShaderModule> futur;
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([futur,key,path,ntype,this](){
		futur.store(__createShaderModule(key,path,ntype));
	  });
	queue.unlock();
	return futur;
}
void GameSystem::deleteShaderModule(const std::string& key)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([key,this](){
		__deleteShaderModule(key);
	  });
	queue.unlock();
}
Future<Abstract::sShaderProgram> GameSystem::createShaderProgram(const std::string& key)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	Future<Abstract::sShaderProgram> futur;
	commandQueue.push([futur,key,this](){
		futur.store(__createShaderProgram(key));
	  });
	return futur;
	queue.unlock();
}
void GameSystem::deleteShaderProgram(const std::string& key)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([key,this](){
		__deleteShaderProgram(key);
	  });
	queue.unlock();
}
void GameSystem::attachShaderModule(const std::string& programKey, const std::string& moduleKey)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([programKey,moduleKey,this](){
		__attachShaderModule(programKey,moduleKey);
	  });
	queue.unlock();
}
void GameSystem::attachShaderModule(const std::string& programKey, const std::vector<std::string>& moduleKeys)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([programKey,moduleKeys,this](){
		__attachShaderModule(programKey,moduleKeys);
	  });
	queue.unlock();
}
void GameSystem::__linkShaders(const std::string& programKey)
{
	Abstract::sShaderProgram shad = queryShaderProgram(programKey);
	if(shad) shad->linkShaders();
}
void GameSystem::linkShaders(const std::string& programKey)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([programKey,this](){
		__linkShaders(programKey);
	  });
	queue.unlock();
}
