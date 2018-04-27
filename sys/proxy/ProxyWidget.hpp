#ifndef PROXYWIDGET_HPP
#define PROXYWIDGET_HPP
#include "ProxyShaderProgram.hpp"
#include "ProxyTexture.hpp"
#include "ProxyAnimatedTexture.hpp"
#include "../../abstract/RenderingEngine.hpp"

DEFINE_CLASS(WidgetProxy)
DEFINE_CLASS(WidgetManager)
typedef Reference<WidgetProxy> WidgetReference;

class WidgetProxy : public Proxy
{
private:
	Abstract::WidgetProperties properties;
	Abstract::sShaderProgram shader;
	unsigned int layer;
public:
	friend class WidgetManager;
	WidgetProxy();
	WidgetProxy(const WidgetProxy& cpy);
	WidgetProxy(const std::string& id, unsigned int nlayer);
	const Abstract::sShaderProgram getShader() const;
	void setShader(ShaderProgramReference shadr);
	const Abstract::sTexture getTexture() const;
	void setTexture(TextureReference text);
	void setTexture(AnimatedTextureReference text);
	const glm::vec2& getSize() const;
	void setSize(const glm::vec2& setto);
	const glm::vec2& getPos() const;
	void setPos(const glm::vec2& setto);
	const std::string& getId() const;
	void setRotation(float rotation);
	float getRotation();
	void defaultSize();
	void scale(const glm::vec2& scaler);
	void snapToWidth(float x);
	void snapToHeight(float y);
};

class WidgetManager : public ResourceManager
{
public:
	friend class WidgetProxy;
	typedef MapTrait<WidgetProxy,std::string> WidgetMap;
	typedef WidgetMap::HashIterator WidgetIterator;
	typedef std::vector<WidgetReference> Canvas;
	typedef Canvas::iterator CanvasIterator;
	typedef std::vector<Canvas> LayerVector;
	typedef LayerVector::iterator LayerIterator;
private:
	WidgetMap widgmp;
	LayerVector layers;
public:
	WidgetManager(unsigned int canvasNum);
	~WidgetManager();
	void draw(glm::mat4 &projection);
	WidgetReference query(const WidgetProxy& proxy);
	WidgetReference query(const std::string& key);
	WidgetReference commit(const WidgetProxy& proxy);
};

#endif // PROXYWIDGET_HPP
