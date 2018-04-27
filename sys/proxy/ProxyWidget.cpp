#include "ProxyWidget.hpp"
#include "../GameSystem.hpp"

WidgetProxy::WidgetProxy()
	: Proxy(""), shader(nullptr), layer(0)
{
	;
}
WidgetProxy::WidgetProxy(const WidgetProxy& cpy)
	: Proxy(cpy.Id), properties(cpy.properties), shader(cpy.shader), layer(cpy.layer)
{
	;
}
WidgetProxy::WidgetProxy(const std::string& id, unsigned int nlayer)
	: Proxy(id), shader(nullptr), layer(nlayer)
{
	;
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
			SYS->getEngine()->renderWidget(widget->properties,projection,widget->shader);
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
	std::cout << "[WIDGETS] Widget \"" << prxy->Id << "\" initialized." << std::endl;

	return ref;
}
