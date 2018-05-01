#include "ProxyWidget.hpp"
#include "../GameSystem.hpp"

WidgetProxy::WidgetProxy()
	: Proxy(""), shader(nullptr), layer(0), isVector(false), vector(nullptr), loadPath("")
{
	;
}
WidgetProxy::WidgetProxy(const WidgetProxy& cpy)
	: Proxy(cpy.Id), properties(cpy.properties), shader(cpy.shader), layer(cpy.layer), isVector(cpy.isVector),
	  vector(cpy.vector), loadPath(cpy.loadPath)
{
	;
}
WidgetProxy::WidgetProxy(const std::string& id, unsigned int nlayer, bool vec)
	: Proxy(id), shader(nullptr), layer(nlayer), isVector(vec), vector(nullptr), loadPath("")
{
	;
}
WidgetProxy::WidgetProxy(const std::string& id, unsigned int nlayer, Abstract::sTexture tex)
	: Proxy(id), shader(nullptr), layer(nlayer), isVector(false), vector(nullptr), loadPath("")
{
	properties.texture = tex;
}
WidgetProxy::WidgetProxy(const std::string& id, unsigned int nlayer, Abstract::sAnimatedTexture tex)
	: Proxy(id), shader(nullptr), layer(nlayer), isVector(false), vector(nullptr), loadPath("")
{
	properties.texture = tex;
}
WidgetProxy::WidgetProxy(const std::string& id, unsigned int nlayer, TextureReference tex)
	: Proxy(id), shader(nullptr), layer(nlayer), isVector(false), vector(nullptr), loadPath("")
{
	ReadReference<TextureProxy> texture(tex);
	properties.texture = texture->getTexture();
}
WidgetProxy::WidgetProxy(const std::string& id, unsigned int nlayer, AnimatedTextureReference tex)
	: Proxy(id), shader(nullptr), layer(nlayer), isVector(false), vector(nullptr), loadPath("")
{
	ReadReference<AnimatedTextureProxy> texture(tex);
	properties.texture = texture->getTexture();
}
WidgetProxy::WidgetProxy(const std::string& id, unsigned int nlayer, const std::string& path)
	: Proxy(id), shader(nullptr), layer(nlayer), isVector(true), vector(nullptr), loadPath(path)
{
	;
}
WidgetProxy::WidgetProxy(const std::string& id, unsigned int nlayer, const char* path)
	: Proxy(id), shader(nullptr), layer(nlayer), isVector(true), vector(nullptr), loadPath(path)
{
	;
}
const std::string& WidgetProxy::getLoadPath(void) const
{
	return loadPath;
}
void WidgetProxy::setLoadPath(const std::string& path)
{
	loadPath = path;
}
const Abstract::sShaderProgram WidgetProxy::getShader() const
{
	return shader;
}
void WidgetProxy::setRotation(float rotation)
{
	properties.rotation = rotation;
}
float WidgetProxy::getRotation()
{
	return properties.rotation;
}
void WidgetProxy::defaultSize()
{
	if(properties.texture)
	{
		properties.size.x = properties.texture->getWidth();
		properties.size.y = properties.texture->getHeight();
	}
}
void WidgetProxy::scale(const glm::vec2& scaler)
{
	properties.size *= scaler;
}
void WidgetProxy::snapToWidth(float x)
{
	properties.size.y = (properties.size.y / properties.size.x) * x;
	properties.size.x = x;
}
void WidgetProxy::snapToHeight(float y)
{
	properties.size.x = (properties.size.x / properties.size.y) * y;
	properties.size.y = y;
}
void WidgetProxy::setShader(ShaderProgramReference shadr)
{
	ReadReference<ShaderProgramProxy> shdr(shadr);
	std::cout << "[WIDGETS/SHADERS] Attaching the shader \"" << shdr->getId() << "\" ("
			  << shdr->getProgram().get() << ") to the widget \"" << Id << "\"." << std::endl;
	shader = shdr->getProgram();
}
const Abstract::sTexture WidgetProxy::getTexture() const
{
	return properties.texture;
}
void WidgetProxy::setTexture(TextureReference text)
{
	ReadReference<TextureProxy> texture(text);
	std::cout << "[WIDGETS/TEXTURES] Attaching the textuer \"" << texture->getId() << "\" ("
			  << texture->getTexture().get() << ") to the widget \"" << Id << "\"." << std::endl;
	properties.texture = texture->getTexture();
}
void WidgetProxy::setTexture(AnimatedTextureReference text)
{
	ReadReference<AnimatedTextureProxy> texture(text);
	std::cout << "[WIDGETS/TEXTURES] Attaching the animated textuer \"" << texture->getId() << "\" ("
			  << texture->getTexture().get() << ") to the widget \"" << Id << "\"." << std::endl;
	properties.texture = texture->getTexture();
}
const glm::vec2 &WidgetProxy::getSize() const
{
	return properties.size;
}
void WidgetProxy::setSize(const glm::vec2& setto)
{
	properties.size = setto;
}
const std::string& WidgetProxy::getId() const
{
	return Id;
}
const glm::vec2 &WidgetProxy::getPos() const
{
	return properties.pos;
}
void WidgetProxy::setPos(const glm::vec2& setto)
{
	properties.pos = setto;
}

WidgetManager::WidgetManager(unsigned int canvasNum)
	: layers(canvasNum)
{
	;
}
WidgetManager::~WidgetManager()
{
	;
}

void WidgetManager::draw(glm::mat4& projection)
{
	for(auto canvasIt = layers.begin(); canvasIt != layers.end(); ++canvasIt)
	{
		for(auto widgIt = canvasIt->begin(); widgIt != canvasIt->end(); ++widgIt)
		{
			ReadReference<WidgetProxy> widget(*widgIt);

			if(widget->getShader()) {
			if(widget->isVector)
			{
				if(widget->vector) widget->vector->draw(widget->shader,projection);
			}
			else SYS->getEngine()->renderWidget(widget->properties,projection,widget->shader);
			}
		}
	}
}
WidgetReference WidgetManager::query(const std::string& key)
{
	auto it = widgmp.find(key);
	WidgetReference ref;
	if(it == widgmp.end())
	{
		ref = WidgetReference();
	}
	else
	{
		ref = it->second;
	}
	widgmp.finish();
	return ref;
}
WidgetReference WidgetManager::query(const WidgetProxy& proxy)
{
	auto it = widgmp.find(proxy.Id);
	WidgetReference ref;
	if(it == widgmp.end())
	{
		ref = WidgetReference();
	}
	else
	{
		ref = it->second;
	}
	widgmp.finish();
	return ref;
}
WidgetReference WidgetManager::commit(const WidgetProxy& proxy)
{
	auto ref = widgmp.getEntry(proxy.Id, proxy.layer);
	Storage<WidgetProxy> &prxy = *ref;
	if(ref->isInitialized())
	{
		prxy.invalidate();
		prxy.beginSet();
	} else {
		prxy.beginSet();
		prxy->layer = proxy.layer;
		layers[proxy.layer % layers.size()].push_back(ref);
	}

	prxy->properties = proxy.properties;
	prxy->shader = proxy.shader;
	if(prxy->layer != proxy.layer) {
	   // Remove ref from prxy->layer
		for(auto widgIt = layers[prxy->layer % layers.size()].begin();
			widgIt != layers[prxy->layer % layers.size()].end();++widgIt)
			{
				if(*widgIt == ref) layers[prxy->layer % layers.size()].erase(widgIt);
				break;
			}
		// Add ref to proxy->layer
		prxy->layer = proxy.layer;
	   layers[proxy.layer % layers.size()].push_back(ref);
	}
	prxy.endSet();
	if(prxy->isVector)
	{
		Abstract::sFIO readah = PhysFS::FileHandle::openRead(proxy.loadPath);
		pushCommand(
		 [ref,proxy,readah](pGameSystem sys)
		{
			Storage<WidgetProxy> &prxy = *ref;
			prxy.invalidate();
			prxy.beginSet();
			prxy->vector = sys->getEngine()->createVectorWidget(readah);
			if(prxy->vector) {
			prxy->vector->setPos(proxy.properties.pos);
			prxy->vector->setSize(proxy.properties.size);
			prxy->vector->setRotation(proxy.properties.rotation);
			std::cout << "Successfully initialized Vector Widget!" << std::endl;
			}else std::cout << "Failed to initialize Vector Widget!" << std::endl;
			prxy.endSet();
		}
		);
	}

	return ref;
}
