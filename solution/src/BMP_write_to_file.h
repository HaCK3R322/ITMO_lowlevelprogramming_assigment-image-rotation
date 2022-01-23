#pragma once
#include "BMP.h"
#include "Image.h"
#include <inttypes.h>
#include <memory.h>
#include <stdio.h>
#include "util.h"

void BMP_write_to_file(FILE* file, struct Image* image);
