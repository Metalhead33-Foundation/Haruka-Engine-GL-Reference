#ifndef FREEIMAGEIOEXT_HPP
#define FREEIMAGEIOEXT_HPP
#include <FreeImagePlus.h>
#include "../abstract/AbstractFread.hpp"

DEFINE_CLASS(FlipImgExt)
class FlipImgExt : public fipImage
{
private:
	const sAbstractFread fhandle;
public:
	FlipImgExt(sAbstractFread reedaa);
};
extern FreeImageIO AbstractFreadImgio;

#endif // FREEIMAGEIOEXT_HPP
