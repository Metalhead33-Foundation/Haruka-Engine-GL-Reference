#ifndef RASTERD_DRAWABLE_HPP
#define RASTERD_DRAWABLE_HPP
#include "Drawable.hpp"
#include "Texture.hpp"
namespace Abstract {
DEFINE_CLASS(RasterDrawable)
class RasterDrawable : public Drawable
{
public:
	virtual ~RasterDrawable() = default;
	virtual const sTexture getTexture() const = 0;
	virtual void setTexture(sTexture ntexture) = 0;
};

}
#endif // RASTERD_DRAWABLE_HPP
