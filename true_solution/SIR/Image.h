#pragma once

#include <inttypes.h>

//Image contains width, height and double array of RGB-pixels
//all readers read to RGB-24 bits format
//but if you need some other pixel sizes, you can write your own reader or modify mine, for that 
//image contains bit count - bpp

//all fuctions are working correspondly to bit count

struct Image {
	size_t width;
	size_t height;
	size_t bitCount;
	void* pixels;
};
