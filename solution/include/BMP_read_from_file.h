#pragma once
#include "BMP.h"
#include "Image.h"
#include <inttypes.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"


enum BMP_reading_status {
	BMP_READING_SUCCESS = 0,
	BMP_READING_NULLPTR_ERROR,
	BMP_READING_HEADER_READING_ERROR,
	BMP_READING_UNKNOWN_VERSION_ERROR,
	BMP_READING_ERROR
};
static char* BMP_reading_status_msg[] = {
	[BMP_READING_SUCCESS] = "BMP readed successfully.",
	[BMP_READING_NULLPTR_ERROR] = "One of args is null ptr.",
	[BMP_READING_HEADER_READING_ERROR] = "Header do not corresspond verion.",
	[BMP_READING_UNKNOWN_VERSION_ERROR] = "Unknown version. SIR works only with [CORE, V3, V4, V5].",
	[BMP_READING_ERROR] = "Unknown reaeding error."
};

enum BMPVersion BMP_read_file_header(FILE* file, struct BMPFILEHEADER* fileheader);
enum BMP_reading_status BMP_read_from_file(FILE* file, struct Image* image);
