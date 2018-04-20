#include "GameSystem.hpp"
#include "ResourceManager.hpp"
#include <sstream>
#include <assimp/Importer.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

GameSystem::GameSystem(RenderingBackendFactoryFunction engineCreator, int w, int h,
					   int samplerate, size_t audioBufferSize, const char *title, int intendedFramerate)
	: MainSystem(w, h, title,intendedFramerate),
	  soundsys(Audio::sSystem(new Audio::System(samplerate, audioBufferSize))),
	  engine(engineCreator(window)),
	  modelImporter(new AssimpPhysFS())
{
	ResourceManager::SYS = this;
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
}
GameSystem::~GameSystem()
{
	ResourceManager::SYS = nullptr;
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
		func(this);
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
const Abstract::sRenderingEngine GameSystem::getEngine() const
{
	return engine;
}
const Audio::sSystem GameSystem::getSoundsys() const
{
	return soundsys;
}
const sAssimpPhysFS GameSystem::getModelImporter() const
{
	return modelImporter;
}
