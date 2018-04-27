#ifndef GIFIO_HPP
#define GIFIO_HPP
#include <gif_lib.h>
#include "../abstract/FIO.hpp"
#include <vector>

class GifIO
{
private:
	const Abstract::sFIO fileIO;
	GifFileType* handle;
public:
	struct ImageCollection {
		std::vector<std::vector<uint32_t>> images;
		GifWord x,y;
	};
	GifIO(Abstract::sFIO nIO);
	~GifIO();

	static int GifInput(GifFileType* container, GifByteType* buffer, int size);

	GifWord getWidth(void) const;
	GifWord getHeight(void) const;
	int getImageCount(void) const;
	void resolveGif(ImageCollection& coll);
};

#endif // GIFIO_HPP
