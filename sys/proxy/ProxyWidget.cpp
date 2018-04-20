#include "ProxyWidget.hpp"
#include "../GameSystem.hpp"

WidgetProxy::WidgetProxy()
	: Id(""), layer(0), shader(nullptr)
{
	;
}
WidgetProxy::WidgetProxy(const std::string& id, int nlayer)
	: Id(id), layer(nlayer), shader(nullptr)
{
	;
}
const Abstract::sShaderProgram WidgetProxy::getShader() const
{
	return shader;
}
void WidgetProxy::setShader(ShaderProgramReference shadr)
{
	ReadReference<ShaderProgramProxy> shdr(shadr);
	shader = shdr->getProgram();
}
const Abstract::sTexture WidgetProxy::getTexture() const
{
	return properties.texture;
}
void WidgetProxy::setTexture(TextureReference text)
{
	ReadReference<TextureProxy> texture(text);
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
const glm::vec2 &WidgetProxy::getPos() const
{
	return properties.pos;
}
void WidgetProxy::setPos(const glm::vec2& setto)
{
	properties.pos = setto;
}
void WidgetManager::draw(glm::mat4& projection)
{
	for(auto canvasIt = layers.begin(); canvasIt != layers.end(); ++canvasIt)
	{
		for(auto widgIt = canvasIt->begin(); widgIt != canvasIt->end(); ++widgIt)
		{
			ReadReference<WidgetProxy> widget(*widgIt);
			SYS->getEngine()->renderWidget(widget->properties,projection,widget->shader);
		}
	}
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
	if(ref->isInitialized())
	{
		for(auto canvasIt = layers.begin(); canvasIt != layers.end(); ++canvasIt)
		{
			for(auto widgIt = canvasIt->begin(); widgIt != canvasIt->end(); ++widgIt)
			{
				ReadReference<WidgetProxy> widget(*widgIt);
				if(widget == ref)
				{
					canvasIt->erase(widgIt);
					break;
				}
			}
		}
		layers[proxy.layer % layers.size()].push_back(ref);
		return ref;
	}
	Storage<WidgetProxy> prxy = *ref;
	prxy.beginSet();
	prxy->setPos(proxy.getPos());
	prxy->setSize(proxy.getSize());
	prxy.endSet();
	layers[proxy.layer % layers.size()].push_back(ref);
	return ref;
}
