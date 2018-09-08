#ifndef GIFIO_HPP
#define GIFIO_HPP
#include <gif_lib.h>
#include "../abstract/FIO.hpp"
#include "../abstract/AbstractImageContainer.hpp"
#include <vector>

class GifIO
{
private:
	const Abstract::sFIO fileIO;
	GifFileType* handle;
public:
	GifIO(Abstract::sFIO nIO);
	~GifIO();

	static int GifInput(GifFileType* container, GifByteType* buffer, int size);

	GifWord getWidth(void) const;
	GifWord getHeight(void) const;
	int getImageCount(void) const;
	void resolveGif(Abstract::AnimatedImageContainer& coll);
};

#endif // GIFIO_HPP
