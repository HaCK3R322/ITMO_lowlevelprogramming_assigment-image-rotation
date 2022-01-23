#include "util.h"
#include <stdio.h>
#include <memory.h>
#include "Image.h"

size_t getPos_byte(size_t x, size_t y, size_t width, size_t bitCount) {
	return ((y * width) + x) * bitCount / 8;
}

char* string_concatenate(char* str1, char* str2) {
	char* buffer = (char*)malloc(1024);
	memset(buffer, 0, 1024);
	sprintf(buffer, "%s%s", str1, str2);
	return buffer;
}

void swap_1_and_3_bytes(struct Image* image) {
	uint8_t template_byte = 0;
	size_t pixel_size_bytes = image->bitCount / 8;
	for (size_t i = 0; i < image->width * image->height * pixel_size_bytes; i += pixel_size_bytes) {
		template_byte = ((uint8_t*)image->pixels)[i];
		((uint8_t*)image->pixels)[i] = ((uint8_t*)image->pixels)[i + 2];
		((uint8_t*)image->pixels)[i + 2] = template_byte;
	}
}
