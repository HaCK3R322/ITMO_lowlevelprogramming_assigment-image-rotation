#include "SIR.h"
#include "util.h"

int main(int argc, char** argv) {
	FILE* input_file, * output_file;

	input_file = fopen(argv[argc - 2], "rb");

	if (input_file) {
		struct Image image;

		enum BMP_reading_status reading_status = BMP_read_from_file(input_file, &image);
		if (!reading_status) {
			fclose(input_file);
			return 0;
		}
		rotate_90degrees_left(&image);

		output_file = fopen(argv[argc - 1], "wb+");
		BMP_write_to_file(output_file, &image);

		if (image.pixels != NULL) free(image.pixels);
	}
	else {
		return 0;
	}

	fclose(output_file);
	fclose(input_file);
	return 0;
}

