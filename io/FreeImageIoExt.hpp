#ifndef FREEIMAGEIOEXT_HPP
#define FREEIMAGEIOEXT_HPP
#include <FreeImagePlus.h>
#include "../abstract/FIO.hpp"

DEFINE_CLASS(FlipImgExt)
class FlipImgExt : public fipImage
{
private:
	const Abstract::sFIO fhandle;
public:
	FlipImgExt(Abstract::sFIO reedaa);
};
extern FreeImageIO AbstractFreadImgio;

#endif // FREEIMAGEIOEXT_HPP
