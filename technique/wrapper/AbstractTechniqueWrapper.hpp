#ifndef ABSTRACTTECHNIQUEWRAPPER_HPP
#define ABSTRACTTECHNIQUEWRAPPER_HPP
#include "../../abstract/Global.hpp"
namespace Abstract {

DEFINE_CLASS(TechniqueWrapper)
class TechniqueWrapper {
public:
	virtual ~TechniqueWrapper() = default;
	virtual void run() = 0;
};

}
#endif // ABSTRACTTECHNIQUEWRAPPER_HPP
