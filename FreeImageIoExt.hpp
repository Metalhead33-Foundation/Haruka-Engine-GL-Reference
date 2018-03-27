#ifndef FREEIMAGEIOEXT_HPP
#define FREEIMAGEIOEXT_HPP
#include <FreeImagePlus.h>
#include "AbstractFread.hpp"
class FlipImgExt : public fipImage
{
public:
	FlipImgExt(sAbstractFread reedaa);
};

extern FreeImageIO AbstractFreadImgio;

#endif // FREEIMAGEIOEXT_HPP
