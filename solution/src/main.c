#include "main.h"

int main(int argc, char** argv) {
	if (argc != 3) {
		return 0;
	}

	FILE *input_file, *output_file;

	input_file = fopen(argv[argc - 2], "rb");
	output_file = fopen(argv[argc - 1], "wb+");

	if (input_file == NULL) {
		fclose(output_file);
		return 0;
	}

	struct Image image = { 0 };

	BMP_read_from_file(input_file, &image);
	rotate_90degrees_left(&image);
	BMP_write_to_file(output_file, &image);

	fclose(input_file);

	return 0;
}
