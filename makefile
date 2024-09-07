# Samuel Jordan
# CPSC 2311-002
# srjorda@clemson.edu

make: driver.c ppm.c ppm.h shape.c shape.h
	gcc driver.c ppm.c shape.c -lm

run: a.out input.txt
	./a.out input.txt output.ppm 

clean:
	rm -f a.out
	rm -f output.ppm
