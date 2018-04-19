#include "GameSystem.hpp"
#include <sstream>
#include <assimp/Importer.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void GameSystem::RenderableMesh::draw(glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model)
{
	// Abstract::sShaderProgram shader = this->shader;
	// Abstract::sMesh mesh = this->mesh;
	if(shader && mesh) mesh->draw(shader, projection, view, model);
}
void GameSystem::RenderableWidget::draw(glm::mat4& projectionMatrix)
{
	if(shader && widget) widget->draw(shader,pos,projectionMatrix);
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
	for(WidgetIterator it = widgets.begin(); it != widgets.end();++it)
	{
		it->second.draw(screenProjection);
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
Audio::sBuffer GameSystem::__createBuffer(const std::string& key, Abstract::sFIO reedah)
{
	Audio::sBuffer tmp = soundsys->createSoundBuffer(reedah);
	return tmp;
}
Audio::sSource GameSystem::__createStream(const std::string& key, Abstract::sFIO reedah, size_t buffNum)
{
	Audio::sSource tmp = soundsys->createStreamingAudio(reedah, buffNum);
	return tmp;
}
Audio::sSource GameSystem::__createSource(const std::string& key, Audio::sBuffer buff)
{
	Audio::sSource tmp;
	if(buff)
	{
		tmp = soundsys->createSoundSource(buff);
	}
	else
	{
		tmp = soundsys->createSoundSource();
	}
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
Abstract::sTexture GameSystem::__createTextureFromDDS(const std::string& key, Abstract::sFIO reedah, Abstract::Texture::textureType type)
{
	Abstract::sTexture tmp = engine->createTextureFromDDS(type, reedah);
	return tmp;
}
Abstract::sTexture GameSystem::__createTextureFromImage(const std::string& key, Abstract::sFIO reedah, Abstract::Texture::textureType type)
{
	Abstract::sTexture tmp = engine->createTextureFromImage(type, reedah);
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
Abstract::sShaderModule GameSystem::__createShaderModule(const std::string& key, Abstract::sFIO reedah, Abstract::ShaderModule::ShaderType ntype)
{
	Abstract::sShaderModule tmp = engine->createShaderModule(ntype, reedah);
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

void GameSystem::__attachShaderModule(Abstract::sShaderProgram prog, Abstract::sShaderModule mod)
{
	if(prog && mod) prog->pushModule(mod);
}
void GameSystem::__attachShaderToMesh(const std::string& meshKey, Abstract::sShaderProgram prog)
{
	MeshIterator meshIt = meshes.find(meshKey);
	if(meshIt == meshes.end()) return;
	meshIt->second.shader = prog;
}
void GameSystem::__attachTextureToMesh(const std::string &meshKey, Abstract::sTexture tex)
{
	MeshIterator meshIt = meshes.find(meshKey);
	if(meshIt == meshes.end()) return;
	if(meshIt->second.mesh && tex) meshIt->second.mesh->getTextures().push_back(tex);
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
	Abstract::sFIO reedah = PhysFS::FileHandle::openRead(path);
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([futur,key,reedah,this](){
		futur.store(__createBuffer(key,reedah));
	  });
	audioBuffers.emplace(key, futur);
	queue.unlock();
	return futur;
}
Future<Audio::sSource> GameSystem::createStream(const std::string& key, const std::string& path, size_t buffNum)
{
	Future<Audio::sSource> futur;
	Abstract::sFIO reedah = PhysFS::FileHandle::openRead(path);
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([futur,key,reedah,buffNum,this](){
		futur.store(__createStream(key,reedah,buffNum));
	  });
	audioSources.emplace(key, futur);
	queue.unlock();
	return futur;
}
Future<Audio::sSource> GameSystem::createSource(const std::string& key, const std::string& buffkey)
{
	Future<Audio::sSource> futur;
	BufferIterator it = audioBuffers.find(buffkey);
	if(it == audioBuffers.end())
	{
		std::unique_lock<std::mutex> queue(commandMutex);
		commandQueue.push([futur,key,this](){
			futur.store(__createSource(key,nullptr));
		  });
		audioSources.emplace(key, futur);
		queue.unlock();
	}
	else
	{
		Future<Audio::sBuffer> buff = it->second;
		std::unique_lock<std::mutex> queue(commandMutex);
		commandQueue.push([futur,key,buff,this](){
			futur.store(__createSource(key,buff));
		  });
		audioSources.emplace(key, futur);
		queue.unlock();
	}
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
	Abstract::sFIO reedah = PhysFS::FileHandle::openRead(path);
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([futur,key,reedah,type,this](){
		futur.store(__createTextureFromDDS(key,reedah,type));
	  });
	textures.emplace(key, futur);
	queue.unlock();
	return futur;
}
Future<Abstract::sTexture> GameSystem::createTextureFromImage(const std::string& key, const std::string& path, Abstract::Texture::textureType type)
{
	Future<Abstract::sTexture> futur;
	Abstract::sFIO reedah = PhysFS::FileHandle::openRead(path);
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([futur,key,reedah,type,this](){
		futur.store(__createTextureFromImage(key,reedah,type));
	  });
	textures.emplace(key, futur);
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
	TextureIterator texIt = textures.find(texKey);
	if(texIt == textures.end()) return;
	Future<Abstract::sTexture> tex = texIt->second;
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([meshKey,tex,this](){
		__attachTextureToMesh(meshKey,tex);
	  });
	queue.unlock();
}
void GameSystem::attachTextureToMesh(const std::string& meshKey, const std::vector<std::string>& texKeys)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	for(size_t i = 0; i < texKeys.size();++i) {
		TextureIterator texIt = textures.find(texKeys[i]);
		if(texIt != textures.end()) {
		Future<Abstract::sTexture> tex = texIt->second;
		commandQueue.push([meshKey,tex,this](){
			__attachTextureToMesh(meshKey,tex);
		  });
		}
	}
	queue.unlock();
}
void GameSystem::attachShaderToMesh(const std::string& meshKey, const std::string& progKey)
{
	ShaderProgramIterator progIt = shaderPrograms.find(progKey);
	if(progIt == shaderPrograms.end()) return;
	Future<Abstract::sShaderProgram> prog = progIt->second;
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([meshKey,prog,this](){
		__attachShaderToMesh(meshKey,prog);
	  });
	queue.unlock();
}
Future<Abstract::sShaderModule> GameSystem::createShaderModule(const std::string& key, const std::string& path, Abstract::ShaderModule::ShaderType ntype)
{
	Future<Abstract::sShaderModule> futur;
	Abstract::sFIO reedah = PhysFS::FileHandle::openRead(path);
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([futur,key,reedah,ntype,this](){
		futur.store(__createShaderModule(key,reedah,ntype));
	  });
	shaderModules.emplace(key, futur);
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
	shaderPrograms.emplace(key, futur);
	queue.unlock();
	return futur;
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
	ShaderProgramIterator progIt = shaderPrograms.find(programKey);
	if(progIt == shaderPrograms.end()) return;
	ShaderModuleIterator modIt = shaderModules.find(moduleKey);
	if(modIt == shaderModules.end()) return;
	Future<Abstract::sShaderProgram> prog = progIt->second;
	Future<Abstract::sShaderModule> mod = modIt->second;
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([prog,mod,this](){
		__attachShaderModule(prog,mod);
	  });
	queue.unlock();
}
void GameSystem::attachShaderModule(const std::string& programKey, const std::vector<std::string>& moduleKeys)
{
	ShaderProgramIterator it = shaderPrograms.find(programKey);
	if(it == shaderPrograms.end()) return;
	Future<Abstract::sShaderProgram> prog = it->second;
	std::unique_lock<std::mutex> queue(commandMutex);
	for(size_t i = 0; i < moduleKeys.size();++i) {
		ShaderModuleIterator modIt = shaderModules.find(moduleKeys[i]);
		if(modIt != shaderModules.end()) {
		Future<Abstract::sShaderModule> mod = modIt->second;
		commandQueue.push([prog,mod,this](){
			__attachShaderModule(prog,mod);
		  });
		}
	}
	queue.unlock();
}
void GameSystem::__linkShaders(Abstract::sShaderProgram prog)
{
	if(prog) prog->linkShaders();
}
void GameSystem::linkShaders(const std::string& programKey)
{
	ShaderProgramIterator it = shaderPrograms.find(programKey);
	if(it == shaderPrograms.end()) return;
	Future<Abstract::sShaderProgram> prog = it->second;
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([prog,this](){
		__linkShaders(prog);
	  });
	queue.unlock();
}
Abstract::sWidget GameSystem::queryWidget(const std::string& key)
{
	WidgetIterator it = widgets.find(key);
	if(it == widgets.end()) return nullptr;
	else return it->second.widget;
}
Abstract::sWidget GameSystem::__createWidget(const std::string& key)
{
	Abstract::sWidget tmp = engine->createWidget(0,0,nullptr);
	widgets.emplace(key, RenderableWidget{tmp, 0, { 0, 0 } } );
	return tmp;
}
void GameSystem::__attachShaderToWidget(const std::string& widgetKey, Abstract::sShaderProgram shader)
{
	WidgetIterator it = widgets.find(widgetKey);
	if(it == widgets.end()) return;
	it->second.shader = shader;
}
Future<Abstract::sWidget> GameSystem::createWidget(const std::string& key)
{
	Future<Abstract::sWidget> futur;
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([key,futur,this](){
		futur.store(__createWidget(key));
	  });
	queue.unlock();
	return futur;
}
void GameSystem::attachShaderToWidget(const std::string& widgetKey, const std::string& shaderKey)
{
	ShaderProgramIterator progIt = shaderPrograms.find(shaderKey);
	if(progIt == shaderPrograms.end()) return;
	Future<Abstract::sShaderProgram> shdr = progIt->second;
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([widgetKey,shdr,this](){
		__attachShaderToWidget(widgetKey,shdr);
	  });
	queue.unlock();
}
void GameSystem::setWidgetPos(const std::string& key, int x, int y)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([key,x,y,this](){
	WidgetIterator widgIt = widgets.find(key);
	if(widgIt == widgets.end()) return;
	widgIt->second.pos.x = x;
	widgIt->second.pos.y = y;
	});
	queue.unlock();
}
void GameSystem::setWidgetPosX(const std::string& key, int x)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([key,x,this](){
	WidgetIterator widgIt = widgets.find(key);
	if(widgIt == widgets.end()) return;
	widgIt->second.pos.x = x;
	});
	queue.unlock();
}
void GameSystem::setWidgetPosY(const std::string& key, int y)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([key,y,this](){
	WidgetIterator widgIt = widgets.find(key);
	if(widgIt == widgets.end()) return;
	widgIt->second.pos.y = y;
	});
	queue.unlock();
}
void GameSystem::__attachTextureToWidget(const std::string& widgetKey, Abstract::sTexture texture)
{
	Abstract::sWidget widget = queryWidget(widgetKey);
	if(widget) widget->setTexture(texture);
}
void GameSystem::attachTextureToWidget(const std::string& widgetKey, const std::string& textureKey)
{
	TextureIterator texIt = textures.find(textureKey);
	if(texIt == textures.end()) return;
	Future<Abstract::sTexture> tex = texIt->second;
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([widgetKey,tex,this](){
		__attachTextureToWidget(widgetKey,tex);
	  });
	queue.unlock();
}
void GameSystem::setWidgetSize(const std::string& key, int x, int y)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([key,x,y,this](){
	WidgetIterator widgIt = widgets.find(key);
	if(widgIt == widgets.end()) return;
	widgIt->second.widget->setHeight(y);
	widgIt->second.widget->setWidth(x);
	});
	queue.unlock();
}
void GameSystem::setWidgetSizeX(const std::string& key, int x)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([key,x,this](){
	WidgetIterator widgIt = widgets.find(key);
	if(widgIt == widgets.end()) return;
	widgIt->second.widget->setWidth(x);
	});
	queue.unlock();
}
void GameSystem::setWidgetSizeY(const std::string& key, int y)
{
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push([key,y,this](){
	WidgetIterator widgIt = widgets.find(key);
	if(widgIt == widgets.end()) return;
	widgIt->second.widget->setHeight(y);
	});
	queue.unlock();
}
