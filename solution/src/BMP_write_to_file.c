#include "BMP_write_to_file.h"

void BMP_write_to_file(FILE* file, struct Image* image) {
	swap_1_and_3_bytes(image); //struct Image is RGB and BMP must be BRG

	size_t width = image->width;
	size_t height = image->height;
	size_t pixel_size_bytes = image->bitCount / 8;

	struct BMPHEADER32 header = { 0 };
	header.fileheader.bfType[0] = 'B';
	header.fileheader.bfType[1] = 'M';
	header.fileheader.bfReserved1 = 0;
	header.fileheader.bfReserved2 = 0;

	header.fileheader.bOffBits = sizeof(struct BMPFILEHEADER) + V3;

	size_t trash_bytes_addition = 0;
	if (width * pixel_size_bytes % 4 != 0) trash_bytes_addition = 4 - (width * pixel_size_bytes % 4);
	header.fileheader.bfSize = (width * pixel_size_bytes + trash_bytes_addition) * height + header.fileheader.bOffBits;

	header.infoheader.Size = V3;
	header.infoheader.Width = width;
	header.infoheader.Height = height;
	header.infoheader.Planes = 1;
	header.infoheader.BitCount = (uint16_t)image->bitCount;
	header.infoheader.Compression = 0;
	header.infoheader.SizeImage = width * height;
	header.infoheader.XPelsPerMeter = 0;
	header.infoheader.YPelsPerMeter = 0;

	header.infoheader.ClrUsed = 0;
	header.infoheader.ClrImportant = 0;

	enum BMPVersion version = V3;

	fwrite(&header, sizeof(struct BMPFILEHEADER) + version, 1, file);


	size_t trash_bytes_size = 0;
	size_t scan_width_bytes = width * pixel_size_bytes;
	if (scan_width_bytes % 4 != 0) trash_bytes_size = 4 - (scan_width_bytes % 4);

	for (size_t y = 0; y < height; y++) {
		fwrite(&(((uint8_t*)image->pixels)[(height - 1 - y) * (width * pixel_size_bytes)]),
			sizeof(uint8_t),
			scan_width_bytes, file);
		
		if (trash_bytes_size) {
			uint8_t* trash_bytes_array[4] = { 0,0,0,0 };
			fwrite(trash_bytes_array, sizeof(uint8_t), trash_bytes_size, file);
		}
	}

	swap_1_and_3_bytes(image);
}
