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
   free(line);
   
	printf("Enter measurement from the plumb to the outer corner of RIGHT doubles & baseline (aka B) in millimeters: ");
   lineSize = getline(&line, &len, stdin);
	B= atof(line);
   free(line);

   // printf("A=%0.2f B=%0.2f\n", A, B);

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

   printf("camera location in mm: X=%0.1f Y=%0.1f\n", Xworld, Yworld);
   return 0;
}
