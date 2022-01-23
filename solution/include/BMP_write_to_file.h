#pragma once
#include <stdio.h>
#include <inttypes.h>
#include <memory.h>
#include "Image.h"
#include "BMP.h"
#include "util.h"

void BMP_write_to_file(FILE* file, struct Image* image);