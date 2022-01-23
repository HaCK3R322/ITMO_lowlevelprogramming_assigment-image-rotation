#include "rotation.h"


bool rotate_90degrees_left(struct Image* image) {
	if (image->bitCount < 8) return false;

	size_t width = image->width;
	size_t height = image->height;
	size_t pixel_size_bytes = image->bitCount / 8;

	uint8_t* new_data = malloc(width * height * pixel_size_bytes);

	size_t old_width = image->width;
	size_t old_height = image->height;
	size_t new_width = image->height;
	size_t new_height = image->width;

	size_t old_x = old_width - 1;
	size_t old_y = 0;

	for (size_t new_y = 0; new_y < new_height; new_y++) {
		for (size_t new_x = 0; new_x < new_width; new_x++) {
			size_t calculated_pos_new = (new_y * new_width + new_x) * pixel_size_bytes;
			size_t calculated_pos_old = (old_y * old_width + old_x) * pixel_size_bytes;
			memcpy(&(new_data[calculated_pos_new]),
				&(((uint8_t*)image->pixels)[calculated_pos_old]),
				pixel_size_bytes
			);
			old_y++;
		}
		//printf("\n");
		old_y = 0;
		old_x --;
	}

	image->width = height;
	image->height = width;

	free(image->pixels);
	image->pixels = new_data;

	return true;
}