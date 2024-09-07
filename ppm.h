/*******************************
 *Samuel Jordan                *
 *CPSC 2311-002, F23           *
 *srjorda@clemson.edu          *
 ******************************/

#ifndef PPM_H
#define PPM_H

#include "shape.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct {
	char type[3];
	int width, height, maxVal;
} header_t;

typedef struct {
	unsigned char r, g, b;
} pixel_t;

/* @param: out - FILE* to write header data to
 * @param: hdr - header_t holding data to write to output file
 * writes information from given header_t to output file
 */
void writeHeader(FILE* out, header_t hdr);

/* @param: out - FILE* to write pixel data to
 * @param: color - single pixel to write to output file
 * writes the data of a single given pixel to the output file
 */
void writePixel(FILE* out,  pixel_t color);

#endif
