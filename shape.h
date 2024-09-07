/*******************************
 *Samuel Jordan                *
 *CPSC 2311-002, F23           *
 *srjorda@clemson.edu          *
 ******************************/

#ifndef SHAPE_H
#define SHAPE_H

#include "ppm.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SQUARE(x) ((x)*(x))

// has an x and y coordinate
typedef struct {
	int x, y;
} point_t;

// has a center point, radius, and color
typedef struct {
	point_t center;
	int radius;
	pixel_t color;
} circle_t;

// has 3 points and a color
typedef struct {
	point_t a, b, c;
	pixel_t color;
} tri_t;

// has 4 points and a color
typedef struct {
	point_t a, b, c, d;
	pixel_t color;
} qua_t;

// shape struct, holds a string specifying type, and one of each shape
// the shape used is the one that correlates with the type
typedef struct shape {
	char type[4];
	circle_t circle;
	tri_t tri;
	qua_t qua;
} shape_t; 

/* @param: input FILE* to read info from   
 * @param: address of header_t to write header info to 
 * @param: address of circle_t to write circle info to
 * reads information from a FILE* to header_t and circle_t passed by reference
 */
void readInfo(FILE*, header_t*, int*);

/* @param: input FILE* to read shapes from
 * @param: shape_t array to read shape data to
 * @param: integer for number of shapes expected
 * reads the number of shapes specified from the input file to the array
 */
void readShapes(FILE*, shape_t*, int);

/* @param: circle_t to check against
 * @param: point_t to check
 * returns 1 if the point_t is inside the circle, 0 otherwise
 */
int isHitCir(circle_t, point_t);

/* @param: tri_t to check against
 * @param: point_t to check
 * returns 1 if the point_t is inside the triangle, 0 otherwise
 */
int isHitTri(tri_t, point_t);

/* @param: qua_t to check against
 * @param: point_t to check
 * returns 1 if the point_t is inside the quadrilateral, 0 otherwise
 */
int isHitQua(qua_t, point_t);

/* @param: out - FILE*
 * @param: arr - shape_t array holding all of the shapes
 * @param: count - number of shapes to write
 * @param: w - width of the image to create
 * @param: h - height of the image to create
 * writes pixel data to the output FILE* to generate all shapes in array
 * shapes are generated in the order they are in the array
 * background color is specified in the function itself
 */
void makeShapes(FILE* out, shape_t* arr, int count, int w, int h);

#endif
