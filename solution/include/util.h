#pragma once
#include <inttypes.h>

size_t getPos_byte(size_t x, size_t y, size_t width, size_t bitCount);
char* string_concatenate(char* str1, char* str2);
void swap_1_and_3_bytes(struct Image* image);