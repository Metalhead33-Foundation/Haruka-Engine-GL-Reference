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
#include "proxy/ProxyShaderModule.hpp"
#include "proxy/ProxyShaderProgram.hpp"
#include "proxy/ProxyTexture.hpp"
#include "proxy/ProxyModel.hpp"
#include "proxy/ProxyWidget.hpp"

DEFINE_CLASS(GameSystem)

class GameSystem : public MainSystem
{
public:
	friend class ResourceManager;
	typedef std::function<void(pGameSystem)> Lambda;
	typedef std::queue<Lambda> CommandQueue;
private:
	const Abstract::sRenderingEngine engine;
	const Audio::sSystem soundsys;
	const sAssimpPhysFS modelImporter;
	Camera camera;
	int mouseX, mouseY;
	glm::mat4 projectionMatrix, viewMatrix, modelMatrix;

	CommandQueue commandQueue;
	std::mutex commandMutex;
	void pushCommand(Lambda lambda);

	ShaderModuleManager moduleManager;
	ShaderProgramManager programManager;
	TextureManager textureManager;
	ModelManager modelManager;
	WidgetManager widgetManager;
public:
	GameSystem(RenderingBackendFactoryFunction engineCreator, int w, int h, int samplerate,
			   size_t audioBufferSize, const char* title, int intendedFramerate=60,
			   int canvasLayers=8);
	~GameSystem();
	error_t update(STime& deltaTime);
	error_t render();
	error_t startup();
	error_t cleanup();
	error_t processWindowEvent(const SDL_Event& ev, STime& deltaTime);

	const Abstract::sRenderingEngine getEngine() const;
	const Audio::sSystem getSoundsys() const;
	const sAssimpPhysFS getModelImporter() const;

	ModelReference queryModel(const ModelProxy& proxy);
	ModelReference commitModel(ModelProxy &proxy);
	ShaderModuleReference queryShaderModule(const ShaderModpuleProxy& proxy);
	ShaderModuleReference commitShaderModule(const ShaderModpuleProxy& proxy);
	ShaderProgramReference queryShaderProgram(const ShaderProgramProxy& proxy);
	ShaderProgramReference commitShaderProgram(const ShaderProgramProxy& proxy);
	TextureReference queryTexture(const TextureProxy& proxy);
	TextureReference commitTexture(const TextureProxy& proxy);
	WidgetReference queryWidget(const WidgetProxy& proxy);
	WidgetReference commitWidget(const WidgetProxy& proxy);
};


#endif // GAMESYSTEM_HPP
