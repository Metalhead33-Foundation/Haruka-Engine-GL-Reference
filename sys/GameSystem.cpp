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
					   int intendedFramerate, int canvasLayers, uint32_t sampleCount, Abstract::sFIO frameVertShader, Abstract::sFIO frameFragShader)
	: MainSystem(w, h, title,intendedFramerate),
	  soundsys(Audio::sSystem(new Audio::System(samplerate, audioBufferSize))),
	  engine(engineCreator(window,sampleCount)),
	  modelImporter(new AssimpPhysFS()), widgetManager(canvasLayers), frameRenderer(nullptr)
{
	ResourceManager::SYS = this;
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
	if(frameVertShader && frameFragShader) {
	Abstract::sShaderModule vert = engine->createShaderModule(Abstract::ShaderModule::VERTEX_SHADER,frameVertShader);
	Abstract::sShaderModule frag = engine->createShaderModule(Abstract::ShaderModule::FRAGMENT_SHADER,frameFragShader);
	frameRenderer = engine->createShaderProgram();
	frameRenderer->pushModule(frag);
	frameRenderer->pushModule(vert);
	frameRenderer->linkShaders();
	}
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
	// engine->renderFrame();
	if(frameRenderer) engine->getFramebuffer()->bind();
	engine->clearBackground();
	modelManager.draw(projectionMatrix, viewMatrix);
	engine->clearDepthBuffer();
	widgetManager.draw(screenProjection);
	if(frameRenderer)
	{
		engine->getFramebuffer()->unbind();
		engine->clearBackground();
		engine->renderFramebuffer(frameRenderer);
	}
	engine->switchBuffers();
	return SYSTEM_OKAY;
}
GameSystem::error_t GameSystem::startup()
{
	engine->startup();
	/*std::cout << "Audio Device Name: " << soundsys->getDeviceName() << std::endl;
	std::cout << "Audio Extension List: " << soundsys->getExtensionList() << std::endl;*/
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
	std::unique_lock<std::mutex> queue(commandMutex);
	commandQueue.push(lambda);
	queue.unlock();
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
BufferReference GameSystem::queryBuffer(const BufferProxy& key)
{
	return bufferManager.query(key);
}
SourceReference GameSystem::querySource(const SourceProxy& key)
{
	return sourceManager.query(key);
}
BufferReference GameSystem::queryBuffer(const std::string& key)
{
	return bufferManager.query(key);
}
SourceReference GameSystem::querySource(const std::string& key)
{
	return sourceManager.query(key);
}
BufferReference GameSystem::commitBuffer(const BufferProxy& proxy)
{
	return bufferManager.commit(proxy);
}
SourceReference GameSystem::commitSource(const SourceProxy& key)
{
	return sourceManager.commit(key);
}
AuxiliaryEffectReference GameSystem::queryAuxiliarySlot(const AuxiliaryEffectProxy& proxy)
{
	return auxiliaryEffectManager.query(proxy);
}
AuxiliaryEffectReference GameSystem::queryAuxiliarySlot(const std::string& key)
{
	return auxiliaryEffectManager.query(key);
}
AuxiliaryEffectReference GameSystem::commitAuxiliarySlot(const AuxiliaryEffectProxy& key)
{
	return auxiliaryEffectManager.commit(key);
}
ChorflangReference GameSystem::queryChorflangEffect(const ChorflangProxy& proxy)
{
	return chorflangManager.query(proxy);
}
CompressorReference GameSystem::queryCompressorEffect(const CompressorProxy& proxy)
{
	return compressorManager.query(proxy);
}
DistortionReference GameSystem::queryDistortionEffect(const DistortionProxy& proxy)
{
	return distortionManager.query(proxy);
}
EchoReference GameSystem::queryEchoEffect(const EchoProxy& proxy)
{
	return echoManager.query(proxy);
}
EqualizerReference GameSystem::queryEqualizerEffect(const EqualizerProxy& proxy)
{
	return equalizerManager.query(proxy);
}
FrequencyShifterReference GameSystem::queryFrequencyShifter(const FrequencyShifterProxy& proxy)
{
	return frequencyShifterManager.query(proxy);
}
PitchShifterReference GameSystem::queryPitchShifter(const PitchShifterProxy& proxy)
{
	return pitchShifterManager.query(proxy);
}
ReverbReference GameSystem::queryReverbEffect(const ReverbProxy& proxy)
{
	return reverbManager.query(proxy);
}
RingModulatorReference GameSystem::queryRingModulator(const RingModulatorProxy& proxy)
{
	return ringModulatorManager.query(proxy);
}
VocalMorpherReference GameSystem::queryVocalMorpher(const VocalMorpherProxy& proxy)
{
	return vocalMorpherManager.query(proxy);
}
WahWahReference GameSystem::queryWahWahEffect(const WahWahProxy& proxy)
{
	return wahWahManager.query(proxy);
}
BandpassFilterReference GameSystem::queryBandpassFilter(const BandpassFilterProxy& proxy)
{
	return bandpassManager.query(proxy);
}
HighpassFilterReference GameSystem::queryHighpassFilter(const HighpassFilterProxy& proxy)
{
	return highpassManager.query(proxy);
}
LowpassFilterReference GameSystem::queryLowpassFilter(const LowpassFilterProxy& proxy)
{
	return lowpassManager.query(proxy);
}

ChorflangReference GameSystem::queryChorflangEffect(const std::string& key)
{
	return chorflangManager.query(key);
}
CompressorReference GameSystem::queryCompressorEffect(const std::string& key)
{
	return compressorManager.query(key);
}
DistortionReference GameSystem::queryDistortionEffect(const std::string& key)
{
	return distortionManager.query(key);
}
EchoReference GameSystem::queryEchoEffect(const std::string& key)
{
	return echoManager.query(key);
}
EqualizerReference GameSystem::queryEqualizerEffect(const std::string& key)
{
	return equalizerManager.query(key);
}
FrequencyShifterReference GameSystem::queryFrequencyShifter(const std::string& key)
{
	return frequencyShifterManager.query(key);
}
PitchShifterReference GameSystem::queryPitchShifter(const std::string& key)
{
	return pitchShifterManager.query(key);
}
ReverbReference GameSystem::queryReverbEffect(const std::string& key)
{
	return reverbManager.query(key);
}
RingModulatorReference GameSystem::queryRingModulator(const std::string& key)
{
	return ringModulatorManager.query(key);
}
VocalMorpherReference GameSystem::queryVocalMorpher(const std::string& key)
{
	return vocalMorpherManager.query(key);
}
WahWahReference GameSystem::queryWahWahEffect(const std::string& key)
{
	return wahWahManager.query(key);
}
BandpassFilterReference GameSystem::queryBandpassFilter(const std::string& key)
{
	return bandpassManager.query(key);
}
HighpassFilterReference GameSystem::queryHighpassFilter(const std::string& key)
{
	return highpassManager.query(key);
}
LowpassFilterReference GameSystem::queryLowpassFilter(const std::string& key)
{
	return lowpassManager.query(key);
}

ChorflangReference GameSystem::commitChorflangEffect(const ChorflangProxy& proxy)
{
	return chorflangManager.commit(proxy);
}
CompressorReference GameSystem::commitCompressorEffect(const CompressorProxy& proxy)
{
	return compressorManager.commit(proxy);
}
DistortionReference GameSystem::commitDistortionEffect(const DistortionProxy& proxy)
{
	return distortionManager.commit(proxy);
}
EchoReference GameSystem::commitEchoEffect(const EchoProxy& proxy)
{
	return echoManager.commit(proxy);
}
EqualizerReference GameSystem::commitEqualizerEffect(const EqualizerProxy& proxy)
{
	return equalizerManager.commit(proxy);
}
FrequencyShifterReference GameSystem::commitFrequencyShifter(const FrequencyShifterProxy& proxy)
{
	return frequencyShifterManager.commit(proxy);
}
PitchShifterReference GameSystem::commitPitchShifter(const PitchShifterProxy& proxy)
{
	return pitchShifterManager.commit(proxy);
}
ReverbReference GameSystem::commitReverbEffect(const ReverbProxy& proxy)
{
	return reverbManager.commit(proxy);
}
RingModulatorReference GameSystem::commitRingModulator(const RingModulatorProxy& proxy)
{
	return ringModulatorManager.commit(proxy);
}
VocalMorpherReference GameSystem::commitVocalMorpher(const VocalMorpherProxy& proxy)
{
	return vocalMorpherManager.commit(proxy);
}
WahWahReference GameSystem::commitWahWahEffect(const WahWahProxy& proxy)
{
	return wahWahManager.commit(proxy);
}
BandpassFilterReference GameSystem::commitBandpassFilter(const BandpassFilterProxy& proxy)
{
	return bandpassManager.commit(proxy);
}
HighpassFilterReference GameSystem::commitHighpassFilter(const HighpassFilterProxy& proxy)
{
	return highpassManager.commit(proxy);
}
LowpassFilterReference GameSystem::commitLowpassFilter(const LowpassFilterProxy& proxy)
{
	return lowpassManager.commit(proxy);
}

void GameSystem::wait()
{
	bool waiting = true;
	pushCommand(
				[waiting](pGameSystem sys) mutable -> bool
	{
		waiting = false;
		return waiting;
	}
	);
	while(waiting);
}
