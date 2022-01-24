#pragma once
#include "Image.h"
#include <inttypes.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

size_t getPos_byte(size_t x, size_t y, size_t width, size_t bitCount);
void string_concatenate(char* str1, char* str2, char* buffer);
void swap_1_and_3_bytes(struct Image* image);
void extract_rgb_only(struct Image* image);
