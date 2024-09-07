/*******************************
 *Samuel Jordan                *
 *CPSC 2311-002, F23           *
 *srjorda@clemson.edu          *
 ******************************/

#include "shape.h"
#include "ppm.h"

void writeHeader(FILE* out, header_t hdr)
{
	// writes header type, width, height, and maxVal in proper format
	fprintf(out, "%s\n%d %d\n%d\n", hdr.type, hdr.width, 
											  hdr.height, hdr.maxVal);   
}

void writePixel(FILE* out, pixel_t color)
{ 
	// writes pixel data to output file
	fprintf(out,"%c%c%c", color.r, color.g, color.b);    
}
