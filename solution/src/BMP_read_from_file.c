#include "BMP_read_from_file.h"

void print_header_24(struct BMPHEADER32 bmp32) {
	printf("\nHEADER:\n");
	printf("bfType1:%c\n", bmp32.fileheader.bfType[0]);
	printf("bfType2:%c\n", bmp32.fileheader.bfType[1]);
	printf("bfSize:%d\n", bmp32.fileheader.bfSize);
	printf("bfReserved1:%d\n", bmp32.fileheader.bfReserved1);
	printf("bfReserved2:%d\n", bmp32.fileheader.bfReserved2);
	printf("bOffBits:%d\n", bmp32.fileheader.bOffBits);
	printf("Size:%d\n", bmp32.infoheader.Size);
	printf("Width:%d\n", bmp32.infoheader.Width);
	printf("Height:%d\n", bmp32.infoheader.Height);
	printf("Planes:%d\n", bmp32.infoheader.Planes);
	printf("BitCount:%d\n", bmp32.infoheader.BitCount);
	printf("Compression:%d\n", bmp32.infoheader.Compression);
	printf("SizeImage:%d\n", bmp32.infoheader.SizeImage);
	printf("XPelsPerMeter:%d\n", bmp32.infoheader.XPelsPerMeter);
	printf("YPelsPerMeter:%d\n", bmp32.infoheader.YPelsPerMeter);
	printf("ClrUsed:%d\n", bmp32.infoheader.ClrUsed);
	printf("ClrImportant:%d\n", bmp32.infoheader.ClrImportant);
}

void extract_rgb_only(struct Image* image) {
	if (image->bitCount == 24) {
		return;
	}
	else {
		struct pixel __attribute__((packed)) {
			uint8_t R;
			uint8_t G;
			uint8_t B;
		};
		
		struct pixel* RGB_pixels = malloc(image->width * image->height * sizeof(struct pixel));

		size_t current_pixel_size = image->bitCount / 8;

		for (size_t i = 0; i < image->width * image->height; i++) {
			RGB_pixels[i].R = ((uint8_t*)image->pixels)[i * current_pixel_size];
			RGB_pixels[i].G = ((uint8_t*)image->pixels)[i * current_pixel_size + 1];
			RGB_pixels[i].B = ((uint8_t*)image->pixels)[i * current_pixel_size + 2];
		}

		free(image->pixels);
		image->pixels = RGB_pixels;
		image->bitCount = 24;
	}
}

//TODO: ������� ��������� ������
enum BMPVersions BMP_read_file_header(FILE* file, struct BMPFILEHEADER* fileheader) {
	fread(fileheader, sizeof(struct BMPFILEHEADER), 1, file);

	uint32_t info_header_size = 0;
	enum BMPVersion BMP_version = NONE;
	fread(&info_header_size, sizeof(info_header_size), 1, file);
	fseek(file, 0, SEEK_SET);

	BMP_version = info_header_size;

	return BMP_version;
}

enum reading_status BMP_read_from_file(FILE* file, struct Image* image) {
	if (image == NULL || file == NULL) {
		return BMP_READING_NULLPTR_ERROR;
	}

	enum reading_status status = BMP_READING_ERROR;	

	struct BMPFILEHEADER fileheader = { 0 };
	enum BMPVersions version = BMP_read_file_header(file, &fileheader);
	if (version != V3) {
		printf("Sorry, but SIR works only with BMP V3 by now.\nYour version:%d\n", version);
		status = BMP_READING_UNKNOWN_VERSION_ERROR;
		return status;
	}

	struct BMPHEADER16 bmp16 = { 0 };
	struct BMPHEADER32 bmp32 = { 0 };

	size_t size_of_header = sizeof(struct BMPFILEHEADER) + version;
	switch (version)
	{
	case CORE:
		if (fread(&bmp16, sizeof(struct BMPHEADER16), 1, file) != 0) {
			status = BMP_READING_SUCCESS;
		}
		else {
			status = BMP_READING_HEADER_READING_ERROR;
		}
		break;
	case V3:
	case V4:
	case V5:
		if (fread(&bmp32, size_of_header, 1, file) != 0) {
			status = BMP_READING_SUCCESS;
		}
		else {
			return status = BMP_READING_HEADER_READING_ERROR;
		}
		break;
	default:
		status = BMP_READING_UNKNOWN_VERSION_ERROR;
		return status;
		break;
	}

	if (version == CORE) {
		image->width = bmp16.Width;
		image->height = bmp16.Height;
		image->bitCount = bmp16.BitCount;
	}
	else if(version != NONE) {
		image->width = bmp32.infoheader.Width;
		image->height = bmp32.infoheader.Height;
		image->bitCount = bmp32.infoheader.BitCount;
	}
	else {
		return BMP_READING_UNKNOWN_VERSION_ERROR;
	}

	//print_header_24(bmp32);
;
	if (version > CORE) {
		// allocate array of pixels without trash bytes
		size_t number_of_pixels = bmp32.infoheader.Width * bmp32.infoheader.Height;
		size_t pixel_size = image->bitCount / 8;
		uint8_t* pixels = malloc(pixel_size * number_of_pixels);

		// calculating number of trash bytes
		size_t trash_bytes_size = 0;
		if ((bmp32.infoheader.Width * pixel_size) % 4 != 0)
			trash_bytes_size = 4 - (bmp32.infoheader.Width * pixel_size) % 4;

		// allocate scan size
		size_t scan_size = bmp32.infoheader.Width * pixel_size;
		struct uint8_t* scan = malloc(scan_size);

		size_t reversed_y = bmp32.infoheader.Height - 1;
		for (size_t y = 0; y < bmp32.infoheader.Height; y++, reversed_y--) {

			fread(scan, pixel_size, bmp32.infoheader.Width, file);
			fseek(file, trash_bytes_size, SEEK_CUR);

			memcpy(&(pixels[reversed_y * scan_size]), scan, scan_size);
		}

		free(image->pixels);
		image->pixels = pixels;

		swap_1_and_3_bytes(image);	// BMP is BRG and struct Image must be RGB
		extract_rgb_only(image);	// even if BMP is V4 or V5 i will save it in V3 format

		status = BMP_READING_SUCCESS;
	}
	else {
		status = BMP_READING_UNKNOWN_VERSION_ERROR;
	}

	return status;
}
