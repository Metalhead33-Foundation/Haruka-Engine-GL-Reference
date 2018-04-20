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

DEFINE_CLASS(GameSystem)
DEFINE_CLASS(ResourceManager)

class GameSystem : public MainSystem
{
public:
	friend class ResourceManager;
	typedef std::function<void(pGameSystem)> Lambda;
	typedef std::queue<Lambda> CommandQueue;
	/*struct RenderableMesh
	{
		Abstract::sMesh mesh;
		Abstract::sShaderProgram shader;
		void draw(glm::mat4& projectionMatrix, glm::mat4& view, glm::mat4& model);
	};
	struct RenderableWidget
	{
		Abstract::sWidget widget;
		Abstract::sShaderProgram shader;
		void draw(glm::mat4& projectionMatrix);
	};*/
private:
	/*const Abstract::sRenderingEngine engine;
	const Audio::sSystem soundsys;
	const sAssimpPhysFS modelImporter;
	Camera camera;
	int mouseX, mouseY;
	glm::mat4 projectionMatrix, viewMatrix, modelMatrix;

	Abstract::sMesh __createMeshFromAI(const std::string& key, aiMesh* mesh);
	void __createMeshesFromModel(const std::string& key, const aiScene* model);*/

	CommandQueue commandQueue;
	std::mutex commandMutex;
	void pushCommand(Lambda lambda);
public:
	GameSystem(RenderingBackendFactoryFunction engineCreator, int w, int h, int samplerate, size_t audioBufferSize, const char* title, int intendedFramerate=60);
	~GameSystem();
	error_t update(STime& deltaTime);
	error_t render();
	error_t startup();
	error_t cleanup();
	error_t processWindowEvent(const SDL_Event& ev, STime& deltaTime);

	const Abstract::sRenderingEngine getEngine() const;
	const Audio::sSystem getSoundsys() const;
	const sAssimpPhysFS getModelImporter() const;
};


#endif // GAMESYSTEM_HPP
