#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP
#include "Global.hpp"
#include "FIO.hpp"
namespace Abstract {

DEFINE_CLASS(ShaderProgram)
DEFINE_CLASS(Cubemap)
class Cubemap
{
public:
	friend class ShaderProgram;
public:
	virtual ~Cubemap() = default;
	virtual uint32_t getWidth() = 0;
	virtual uint32_t getHeight() = 0;
	virtual uint32_t getLinearSize() = 0;
	virtual void bindCubemapSide() = 0;

	typedef sCubemap (*CubemapCreator)(Abstract::sFIO);
};

}
#endif // CUBEMAP_HPP
