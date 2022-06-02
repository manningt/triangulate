#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
   char *line;
   size_t len;
   ssize_t lineSize __attribute__((unused));
	float A, B;

   printf("Enter measurement from the plumb to the outer corner of LEFT doubles & baseline (aka A) in millimeters: ");
   lineSize = getline(&line, &len, stdin);
	A= atof(line);
   
	printf("Enter measurement from the plumb to the outer corner of RIGHT doubles & baseline (aka B) in millimeters: ");
   lineSize = getline(&line, &len, stdin);
	B= atof(line);

   printf("With A=%0.1f B=%0.1f as inputs...\n", A, B);

	#define FEET_TO_MM 304.8
	#define DOUBLES_COURT_WIDTH_MM (72 * FEET_TO_MM)
	#define SINGLES_TO_DOUBLES_WIDTH_MM (4.5 * FEET_TO_MM)
	#define DOUBLES_COURT_HALF_WIDTH_SQUARED_MM (DOUBLES_COURT_WIDTH_MM/2 * DOUBLES_COURT_WIDTH_MM/2)
	#define HALF_COURT_LENGTH_MM (39 * FEET_TO_MM)
	float x1, y1, Xworld, Yworld;

	x1 = (DOUBLES_COURT_HALF_WIDTH_SQUARED_MM + A*A - B*B)/DOUBLES_COURT_WIDTH_MM;
	y1 = sqrt(A*A - x1*x1);
	Xworld = x1 - SINGLES_TO_DOUBLES_WIDTH_MM;
	Yworld = y1 + HALF_COURT_LENGTH_MM;

   printf("... the camera location in mm: X=%0.1f Y=%0.1f\n", Xworld, Yworld);
   return 0;
}
/*
test conversion from A and B measurements to world X and Y
Let A represent the distance in feet from the left doubles corner to the plumb bob mark
Let B represent the distance in feet from the right doubles corner to the plumb bob mark
Solve for the world X and Y of the plumb bob relative to the center of the court and left singles sideline (origin)

The distance between the 2 corners is 36 feet. I'll do all the calculations in feet then convert to mm at the end
Let "a" represent the point at the left doubles corner
Let "b" represent the point at the right doubles corner
Let "c" represent the point at the plumb bob, directly below the camera focal point
Let "d" represent the projection of point "c" on the near baseline

The equations all use pythogrean's theorem, the hypothenuse of a right triangle squared is equal to the sum of each leg squared
So the distance between ab is 36 feet
the distance between ac is B (which the user will measure in feet)
The distance between ad is x1 (along the baseline until it lines up with point c) We'll solve for x1
the distance between db = 36- x1
the distance between dc = y1 ( distance from the baseline to point c) We'll also solve for y1
the distance between bc = B (which the user will measure in feet)

Use the P theorem: A*A = x1*x1 + y1*y1 (eq. 1)
and B*B = (36-x)*(36-x) + y1*y1 (eq. 2)
So moving x1*x1 to the other side in eq. 1 yields y1*y1 = A*A - x1*x1 which gives us y1*y1 in terms of x1 (call this eq. 3)
Substituting from y1*y1 in eq. 2 yields B*B = (36-x1)*(36-x1) + A*A - x1*x1
Expanding out, we get B*B = 1296 - 72*x1 + x1*x1 + A*A - x1*x1
the -x1*x1 and + x1*x1 cancel out, so we get B*B = 1296 - 72*x1 + A*A
Moving the x1 part to the left and the B*B part to the right, we get 72*x1 = 1296 + A*A - B*B
Dividing both sides by 72 yields x1 = (1296 + A*A - B*B)/72 so we have solved for x1
Now substituting x1 back into eq. 3 we solve for  y1*y1 = A*A - x1*x1
Or y1 = sqrt(A*A - x1*x1)

I'll throw some values in for A and B and see if it all works out
Once we have x1 we have to subtract 4.5 feet from x1 to get the true Xworld relative to the singles sideline because the doubles sideline
is 4.5 feet to the left of the singles sideline.
And once we have y1 we have to add 39 feet to y1 to get the true Yworld relative to the center of the court because the near baseline
is 39 feet from the center of the court (origin)

A= 20.0;	// These values should yield x1 of 18-4.5=13.5 feet and a y1=8.7 feet
B= 20.0;
*/