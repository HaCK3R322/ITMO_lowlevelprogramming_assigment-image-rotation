#include "filters.h"
#include <inttypes.h>
#include <math.h>

void filter_sepia(struct Image* image) {
	struct RGB {
		uint8_t t;
	};

	size_t pixel_size = image->bitCount / 8;

	double discolorization = 0.7;
	for (size_t i = 0; i < image->width * image->height * pixel_size; i += pixel_size) {
		double input_red = (double)((uint8_t*)image->pixels)[i];
		double input_green = (double)((uint8_t*)image->pixels)[i + 1];
		double input_blue = (double)((uint8_t*)image->pixels)[i + 2];
		
		double output_red = (input_red * 0.393) + (input_green * 0.769) + (input_blue * 0.189);
		double output_green = (input_red * 0.349) + (input_green * 0.686) + (input_blue * 0.168);
		double output_blue = (input_red * 0.272) + (input_green * 0.534) + (input_blue * 0.131);

		output_red = output_red * discolorization + 10;
		output_green = output_green * discolorization + 10;
		output_blue = output_blue * discolorization + 10;

		((uint8_t*)image->pixels)[i] = (uint8_t)fmin((uint8_t)output_red, (uint8_t)255);
		((uint8_t*)image->pixels)[i + 1] = (uint8_t)fmin((uint8_t)output_green, (uint8_t)255);
		((uint8_t*)image->pixels)[i + 2] = (uint8_t)fmin((uint8_t)output_blue, (uint8_t)255);
	}
}
