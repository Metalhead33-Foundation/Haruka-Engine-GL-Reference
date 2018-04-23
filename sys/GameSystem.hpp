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
#include "proxy/ProxyAudioBuffer.hpp"
#include "proxy/ProxyAudioSource.hpp"

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
	/* Basic Managers */
	ShaderModuleManager moduleManager;
	ShaderProgramManager programManager;
	TextureManager textureManager;
	ModelManager modelManager;
	WidgetManager widgetManager;
	BufferManager bufferManager;
	SourceManager sourceManager;
	AuxiliaryEffectManager auxiliaryEffectManager;
	/* Effect Managers */
	ChorflangManager chorflangManager;
	CompressorManager compressorManager;
	DistortionManager distortionManager;
	EchoManager echoManager;
	EqualizerManager equalizerManager;
	ReverbManager reverbManager;
	FrequencyShifterManager frequencyShifterManager;
	PitchShifterManager pitchShifterManager;
	RingModulatorManager ringModulatorManager;
	VocalMorpherManager vocalMorpherManager;
	WahWahManager wahWahManager;
	/* Filter Managers */
	BandpassFilterManager bandpassManager;
	HighpassFilterManager highpassManager;
	LowpassFilterManager lowpassManager;
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

	void wait();
	/* Normal stuff */
	ModelReference queryModel(const ModelProxy& proxy);
	ShaderModuleReference queryShaderModule(const ShaderModuleProxy& proxy);
	ShaderProgramReference queryShaderProgram(const ShaderProgramProxy& proxy);
	TextureReference queryTexture(const TextureProxy& proxy);
	WidgetReference queryWidget(const WidgetProxy& proxy);
	BufferReference queryBuffer(const BufferProxy& key);
	SourceReference querySource(const SourceProxy& key);
	AuxiliaryEffectReference queryAuxiliarySlot(const AuxiliaryEffectProxy& proxy);

	ModelReference queryModel(const std::string& key);
	ShaderModuleReference queryShaderModule(const std::string& key);
	ShaderProgramReference queryShaderProgram(const std::string& key);
	TextureReference queryTexture(const std::string& key);
	WidgetReference queryWidget(const std::string& key);
	BufferReference queryBuffer(const std::string& key);
	SourceReference querySource(const std::string& key);
	AuxiliaryEffectReference queryAuxiliarySlot(const std::string& key);

	ModelReference commitModel(ModelProxy &proxy);
	ShaderModuleReference commitShaderModule(const ShaderModuleProxy& proxy);
	ShaderProgramReference commitShaderProgram(const ShaderProgramProxy& proxy);
	TextureReference commitTexture(const TextureProxy& proxy);
	WidgetReference commitWidget(const WidgetProxy& proxy);
	BufferReference commitBuffer(const BufferProxy& proxy);
	SourceReference commitSource(const SourceProxy& key);
	AuxiliaryEffectReference commitAuxiliarySlot(const AuxiliaryEffectProxy& key);
	/* Effects */
	ChorflangReference queryChorflangEffect(const ChorflangProxy& proxy);
	CompressorReference queryCompressorEffect(const CompressorProxy& proxy);
	DistortionReference queryDistortionEffect(const DistortionProxy& proxy);
	EchoReference queryEchoEffect(const EchoProxy& proxy);
	EqualizerReference queryEqualizerEffect(const EqualizerProxy& proxy);
	FrequencyShifterReference queryFrequencyShifter(const FrequencyShifterProxy& proxy);
	PitchShifterReference queryPitchShifter(const PitchShifterProxy& proxy);
	ReverbReference queryReverbEffect(const ReverbProxy& proxy);
	RingModulatorReference queryRingModulator(const RingModulatorProxy& proxy);
	VocalMorpherReference queryVocalMorpher(const VocalMorpherProxy& proxy);
	WahWahReference queryWahWahEffect(const WahWahProxy& proxy);
	BandpassFilterReference queryBandpassFilter(const BandpassFilterProxy& proxy);
	HighpassFilterReference queryHighpassFilter(const HighpassFilterProxy& proxy);
	LowpassFilterReference queryLowpassFilter(const LowpassFilterProxy& proxy);

	ChorflangReference queryChorflangEffect(const std::string& key);
	CompressorReference queryCompressorEffect(const std::string& key);
	DistortionReference queryDistortionEffect(const std::string& key);
	EchoReference queryEchoEffect(const std::string& key);
	EqualizerReference queryEqualizerEffect(const std::string& key);
	FrequencyShifterReference queryFrequencyShifter(const std::string& key);
	PitchShifterReference queryPitchShifter(const std::string& key);
	ReverbReference queryReverbEffect(const std::string& key);
	RingModulatorReference queryRingModulator(const std::string& key);
	VocalMorpherReference queryVocalMorpher(const std::string& key);
	WahWahReference queryWahWahEffect(const std::string& key);
	BandpassFilterReference queryBandpassFilter(const std::string& key);
	HighpassFilterReference queryHighpassFilter(const std::string& key);
	LowpassFilterReference queryLowpassFilter(const std::string& key);

	ChorflangReference commitChorflangEffect(const ChorflangProxy& proxy);
	CompressorReference commitCompressorEffect(const CompressorProxy& proxy);
	DistortionReference commitDistortionEffect(const DistortionProxy& proxy);
	EchoReference commitEchoEffect(const EchoProxy& proxy);
	EqualizerReference commitEqualizerEffect(const EqualizerProxy& proxy);
	FrequencyShifterReference commitFrequencyShifter(const FrequencyShifterProxy& proxy);
	PitchShifterReference commitPitchShifter(const PitchShifterProxy& proxy);
	ReverbReference commitReverbEffect(const ReverbProxy& proxy);
	RingModulatorReference commitRingModulator(const RingModulatorProxy& proxy);
	VocalMorpherReference commitVocalMorpher(const VocalMorpherProxy& proxy);
	WahWahReference commitWahWahEffect(const WahWahProxy& proxy);
	BandpassFilterReference commitBandpassFilter(const BandpassFilterProxy& proxy);
	HighpassFilterReference commitHighpassFilter(const HighpassFilterProxy& proxy);
	LowpassFilterReference commitLowpassFilter(const LowpassFilterProxy& proxy);
};


#endif // GAMESYSTEM_HPP
