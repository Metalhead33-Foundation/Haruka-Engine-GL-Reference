#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP
#include "Global.hpp"
#include "FIO.hpp"
#include "AbstractImageContainer.hpp"
namespace Abstract {

DEFINE_CLASS(ShaderProgram)
DEFINE_CLASS(Cubemap)
class Cubemap
{
public:
	friend class ShaderProgram;
	typedef ImageContainer TextureConstructor;
	typedef sImageContainer sTextureConstructor;
	virtual ~Cubemap() = default;
	virtual uint32_t getWidth() const = 0;
	virtual uint32_t getHeight() const = 0;
	virtual uint32_t getLinearSize() const = 0;
	virtual void bindCubemapSide() = 0;

	typedef sCubemap (*CubemapCreator)(Abstract::sFIO);
};

}
#endif // CUBEMAP_HPP
