#include "GameSystem.hpp"
#include "ResourceManager.hpp"
#include <sstream>
#include <assimp/Importer.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

GameSystem::GameSystem(RenderingBackendFactoryFunction engineCreator, int w, int h,
					   int samplerate, size_t audioBufferSize, const char *title,
					   int intendedFramerate, int canvasLayers)
	: MainSystem(w, h, title,intendedFramerate),
	  soundsys(Audio::sSystem(new Audio::System(samplerate, audioBufferSize))),
	  engine(engineCreator(window)),
	  modelImporter(new AssimpPhysFS()), widgetManager(canvasLayers)
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
	modelManager.draw(projectionMatrix, viewMatrix);
	widgetManager.draw(screenProjection);
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
void GameSystem::pushCommand(Lambda lambda)
{
	commandQueue.push(lambda);
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

ModelReference GameSystem::queryModel(const ModelProxy& proxy)
{
	return modelManager.query(proxy);
}
ModelReference GameSystem::commitModel(ModelProxy& proxy)
{
	return modelManager.commit(proxy);
}
ShaderModuleReference GameSystem::queryShaderModule(const ShaderModuleProxy& proxy)
{
	return moduleManager.query(proxy);
}
ShaderModuleReference GameSystem::commitShaderModule(const ShaderModuleProxy& proxy)
{
	return moduleManager.commit(proxy);
}
ShaderProgramReference GameSystem::queryShaderProgram(const ShaderProgramProxy& proxy)
{
	return programManager.query(proxy);
}
ShaderProgramReference GameSystem::commitShaderProgram(const ShaderProgramProxy& proxy)
{
	return programManager.commit(proxy);
}
TextureReference GameSystem::queryTexture(const TextureProxy& proxy)
{
	return textureManager.query(proxy);
}
TextureReference GameSystem::commitTexture(const TextureProxy& proxy)
{
	return textureManager.commit(proxy);
}
WidgetReference GameSystem::queryWidget(const WidgetProxy& proxy)
{
	return widgetManager.query(proxy);
}
WidgetReference GameSystem::commitWidget(const WidgetProxy& proxy)
{
	return widgetManager.commit(proxy);
}
ModelReference GameSystem::queryModel(const std::string& key)
{
	return modelManager.query(key);
}
ShaderModuleReference GameSystem::queryShaderModule(const std::string& key)
{
	return moduleManager.query(key);
}
ShaderProgramReference GameSystem::queryShaderProgram(const std::string& key)
{
	return programManager.query(key);
}
TextureReference GameSystem::queryTexture(const std::string& key)
{
	return textureManager.query(key);
}
WidgetReference GameSystem::queryWidget(const std::string& key)
{
	return widgetManager.query(key);
}
