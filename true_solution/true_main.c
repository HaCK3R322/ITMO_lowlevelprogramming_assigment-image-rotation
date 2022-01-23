#include <stdio.h>
#include "SIR.H"
#include "util.h"

void print_help() {
	printf("To start program, enter args in the next fromat:\n");
	printf("image_1_path image_2_path ... image_N_path -action\n\n");
	printf("ACTIONS:\n");
	printf("	-rotate_left: rotates image 90 degrees left.\n\n");
	printf("Ivan Androsov ITMO P3210 19/01/2022 \n");
}

static const size_t NUMBER_OF_ACTIONS = 3;
enum action {
	ROTATE = 1,
	FILTER_SEPIA
};
static char* actions_names[] = {
	[NONE] = "NONE",
	[ROTATE] = "-rotate",
	[FILTER_SEPIA] = "-filter_sepia"
};
enum actions get_action_by_name(const char* action_str) {
	for (size_t i = 0; i < NUMBER_OF_ACTIONS; i++) {
		if (strcmp(actions_names[i], action_str) == 0) {
			return i;
		}
	}
	return NONE;
}

int main(int argc, char** argv) {
	if (argc < 3) {
		print_help();
		return 0;
	}

	for (size_t i = 1; i < argc - 1; i++) {
		char* input_file_path = argv[i];
		FILE* input_file = fopen(input_file_path, "rb");

		if (input_file == NULL) {
			printf("File %s not found. Moving to next.\n", argv[i]);
		}
		else {
			struct Image image = { 0 };

			printf("Reading image from %s: ", argv[i]);
			enum BMP_reading_status reading_status = BMP_read_from_file(input_file, &image);
			printf("%s\n", BMP_reading_status_msg[reading_status]);

			if (reading_status == BMP_READING_SUCCESS) {
				
				enum action action = get_action_by_name(argv[argc - 1]);
				switch (action) {
				case ROTATE:
					rotate_90degrees_left(&image);
					printf("Image rotated.\n");
					break;
				case FILTER_SEPIA:
					filter_sepia(&image);
					printf("A sepia filter has been added to the image.\n");
					break;
				default:
					printf("Action %s not found.\n", argv[argc - 1]);
				}
				
				char* output_file_name = string_concatenate("output_", input_file_path);
				printf("Saving image to %s... ", output_file_name);
				FILE* output_file = fopen(output_file_name, "wb+");
				BMP_write_to_file(output_file, &image);
				fclose(output_file);
				printf("Image saved.\n");
			}
		}

		if (input_file != NULL) fclose(input_file);
		
		printf("\n");
	}

	return 0;
}
