/*******************************
 *Samuel Jordan                *
 *CPSC 2311-002, F23           *
 *srjorda@clemson.edu          *
 ******************************/

#include "shape.h"
#include "ppm.h"

int main(int argc, char* argv[])
{
	// input and output files specified on command line opened
	FILE* in = fopen(argv[1], "r");
	assert(in != NULL);		
	FILE* out = fopen(argv[2], "w");
	assert(out != NULL);

	// header and circle structs for later use
	header_t h;
	int shapeCount = 0;

	// info read from input, stored, and written to output
	readInfo(in, &h, &shapeCount);
	struct shape *arr = (struct shape*)malloc(sizeof(struct shape)*shapeCount);
	readShapes(in, arr, shapeCount);
	
	writeHeader(out, h);
	makeShapes(out, arr, shapeCount, h.width, h.height);

	// input and output files closed
	fclose(in);
	fclose(out);
	free(arr);

	return 0;
}
