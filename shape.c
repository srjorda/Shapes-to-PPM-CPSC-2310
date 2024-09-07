/*******************************
 *Samuel Jordan                *
 *CPSC 2311-002, F23           *
 *srjorda@clemson.edu          *
 ******************************/

#include "shape.h"
#include "ppm.h"

int isHitCir(circle_t c, point_t p)
{
   // if the distance between a point and the center of the circle
	// is less than the circle's radius, return 1 (true)
	if(sqrt(SQUARE(p.x-c.center.x) + SQUARE(p.y-c.center.y)) < c.radius) {
		return 1;
	}
	// if the point is outside of or on the radius, return false)
	return 0;
}

int isHitTri(tri_t t, point_t p) 
{	
	// 3 scalars
	double a = (double) ((t.b.y-t.c.y)*(p.x - t.c.x) + 
				  			 	(t.c.x-t.b.x)*(p.y - t.c.y)) / 
		 		  			  ((t.b.y-t.c.y)*(t.a.x-t.c.x) + 
								(t.c.x-t.b.x)*(t.a.y-t.c.y));
	double b = (double) ((t.c.y-t.a.y)*(p.x - t.c.x) + 
								(t.a.x-t.c.x)*(p.y - t.c.y)) / 
				  			  ((t.b.y-t.c.y)*(t.a.x-t.c.x) + 
								(t.c.x-t.b.x)*(t.a.y-t.c.y));
	double c = 1 - a - b;
	// a point likes within the triangle if all of this is true
	if(a >= 0 && a <= 1) {
		if(b >= 0 && b <= 1) {
			if(c >= 0 && c <= 1) {
				return 1;
			}
		}
	}
	// if any of these are false it does not
	return 0;
} 

int isHitQua(qua_t q, point_t p)
{
	// three triangles created to guarantee complete coverage
	tri_t t1 = {q.a, q.b, q.c, q.color};
	tri_t t2 = {q.a, q.b, q.d, q.color};
	tri_t t3 = {q.a, q.c, q.d, q.color};
	
	// if p is within any of these triangles, then it hit the quadrilateral
	if(isHitTri(t1, p) || isHitTri(t2, p) || isHitTri(t3, p)) {
		return 1;
	}
	// if it isn't, then it doesn't
	return 0;
}

void readInfo(FILE* in, header_t* hdr, int* count)
{
	// reads type, width, height, and maxVal to header
	fscanf(in, "%s %d %d %d\n%d\n", (*hdr).type, 
										 	  &(*hdr).width, 
										 	  &(*hdr).height, 
										 	  &(*hdr).maxVal,
										 	  count);
}

void readShapes(FILE* in, shape_t* arr, int count) 
{
	for(int i = 0; i < count; i++) {
		fscanf(in, "%s\n", arr[i].type);
		
		if(strcmp(arr[i].type, "Cir") == 0) {
			// reads center and radius to circle
			fscanf(in, "%d %d %d\n", &(arr[i].circle.center.x), 
										 	 &(arr[i].circle.center.y),
										 	 &(arr[i].circle.radius));
			// reads color to circle
			fscanf(in, "%hhu %hhu %hhu", &(arr[i].circle.color.r), 
										  	  	  &(arr[i].circle.color.g), 
										     	  &(arr[i].circle.color.b));
		}
		if(strcmp(arr[i].type, "Tri") == 0) {
			// reads 3 points to triangle
			fscanf(in, "%d %d\n%d %d\n%d %d\n", &(arr[i].tri.a.x), 
										 	 				&(arr[i].tri.a.y),
										 	 				&(arr[i].tri.b.x),
															&(arr[i].tri.b.y),
															&(arr[i].tri.c.x),
															&(arr[i].tri.c.y));
			// reads color
			fscanf(in, "%hhu %hhu %hhu", &(arr[i].tri.color.r), 
										  	  	  &(arr[i].tri.color.g), 
										     	  &(arr[i].tri.color.b));	
		}
		if(strcmp(arr[i].type, "Qua") == 0) {
			// reads 4 points to quadrilateral
			fscanf(in, "%d %d\n%d %d\n%d %d\n%d %d\n", &(arr[i].qua.a.x), 
										 	 						 &(arr[i].qua.a.y),
										 	 						 &(arr[i].qua.b.x),
																	 &(arr[i].qua.b.y),
																	 &(arr[i].qua.c.x),
																	 &(arr[i].qua.c.y),
																	 &(arr[i].qua.d.x),
																	 &(arr[i].qua.d.y));
			// reads color
			fscanf(in, "%hhu %hhu %hhu", &(arr[i].qua.color.r), 
										  	  	  &(arr[i].qua.color.g), 
										     	  &(arr[i].qua.color.b));	
		}
	}
}

void makeShapes(FILE* out, shape_t* arr, int count, int w, int h)
{
	// point to be edited and passed for each loop
	point_t pt;
	// background color to be used by default
	pixel_t bg = { 20, 180, 160 };
	// pixel to actually write to the file
	pixel_t wr = bg;
	// starting at the top left, moving across 
	// with the center of the image as origin
	// for each pixel...
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			for(int k = 0; k < count; k++) {
				// temp pixel coordinates set to current coordinates
				pt.x = j;
				pt.y = i;
				// uses proper function based on the shape
				// if the point is inside the shape, use shape color
				if(strcmp(arr[k].type, "Cir") == 0) {
					if(isHitCir(arr[k].circle, pt) == 1)
						wr = arr[k].circle.color;
				} 
				else if(strcmp(arr[k].type, "Tri") == 0) {
					if(isHitTri(arr[k].tri, pt) == 1)
						wr = arr[k].tri.color;
				}
				else if(strcmp(arr[k].type, "Qua") == 0) {
					if(isHitQua(arr[k].qua, pt) == 1)
						wr = arr[k].qua.color;	
				}
			}
			// after going through all shapes, write the last shape's color
			writePixel(out, wr);
			// reset starting color for next pixel
			wr = bg;
		}
	}
}
