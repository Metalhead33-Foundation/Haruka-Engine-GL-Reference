#ifndef VERTEXPROVIDER_HPP
#define VERTEXPROVIDER_HPP
#include "Global.hpp"
namespace Abstract {

DEFINE_CLASS(VertexProvider)
class VertexProvider {
public:
	virtual ~VertexProvider() = default;
	virtual void bind() = 0;
};

}
#endif // VERTEXPROVIDER_HPP
