#include "util.h"

size_t getPos_byte(size_t x, size_t y, size_t width, size_t bitCount) {
	return ((y * width) + x) * bitCount / 8;
}

size_t get_string_length(char* str) {
	size_t i = 0;
	while (str[i] != '\0') {
		i++;
	}
	return ++i; //null-terminator
}

void string_concatenate(char* str1, char* str2, char* buffer) {
	if(buffer == NULL)
		return;
	
	size_t str1_length = get_string_length(str1);
	size_t str2_length = get_string_length(str2);
	
	for (size_t i = 0; i < str1_length - 1; i++) {
		buffer[i] = str1[i];
	}
	for (size_t i = 0; i < get_string_length(str2); i++) {
		buffer[i + str1_length - 1] = str2[i];
	}
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

void extract_rgb_only(struct Image* image) {
	if (image->bitCount == 24) {
		return;
	}
	else {
#pragma pack(push, 1)
		struct pixel {
			uint8_t R;
			uint8_t G;
			uint8_t B;
		};
#pragma pack(pop, 1)
		struct pixel* RGB_pixels = malloc(image->width * image->height * sizeof(struct pixel));

		size_t current_pixel_size = image->bitCount / 8;

		if (RGB_pixels) {
			for (size_t i = 0; i < image->width * image->height; i++) {
				RGB_pixels[i].R = ((uint8_t*)image->pixels)[i * current_pixel_size];
				RGB_pixels[i].G = ((uint8_t*)image->pixels)[i * current_pixel_size + 1];
				RGB_pixels[i].B = ((uint8_t*)image->pixels)[i * current_pixel_size + 2];
			}
		}

		free(image->pixels);
		image->pixels = RGB_pixels;
		image->bitCount = 24;
	}
}

