#ifndef FREEIMAGEIOEXT_HPP
#define FREEIMAGEIOEXT_HPP
#include <FreeImagePlus.h>
#include "../abstract/AbstractFIO.hpp"

DEFINE_CLASS(FlipImgExt)
class FlipImgExt : public fipImage
{
private:
	const sAbstractFIO fhandle;
public:
	FlipImgExt(sAbstractFIO reedaa);
};
extern FreeImageIO AbstractFreadImgio;

#endif // FREEIMAGEIOEXT_HPP
