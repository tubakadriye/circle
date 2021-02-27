/*



 ============================================================================
 Name        : circle.c
 Author      : Tuba
 Version     :
 Copyright   : Your copyright notice
 Description : A circle drawing program from entered 3 points in C
 ============================================================================

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

//max number of input points
#define N_max 3


//current number of input points
int N_points = 0;

//control of right click
int right_click=0;
//control of start over
int start = 0;

//coordinate arrays for input points
double X_pts_array[N_max];
double Y_pts_array[N_max];

// for window and its size
int window;
int windowsizeX = 1400;
int windowsizeY = 900;

//for mouse position
double mouseposX = 0.0;
double mouseposY = 0.0;

//center coordinates of the circle
double cX;
double cY;

//variables for calculating the center
//r is radius
double x01,y01,x02,y02, z01,z02,a,b,r ;

struct CIRCLE {
	double x;
	double y;
} ;

struct CIRCLE circle;

//function for drawing circle with given center(cX,cY) and radius(r)
void drawcircle( double r,  double cX, double cY)
{
	glLineWidth(4);
	glColor3f(1, 0, 1);
	glBegin(GL_LINE_LOOP);
	int i;
	int precision = 100;
	double theta = 0;
	  for(i = 0; i < precision; i++){
	    theta = i * 2 * M_PI/precision;
	    glVertex2d(cX + r*cos(theta), cY + r*sin(theta));
	  }
	  glEnd();
}


// function for writing text on (x,y) coordinate
void drawBitmapText (char *string, double x, double y)
{
	char *c;
	glRasterPos2i(x,y);

	for (c = string; *c != '\0' ; c++)
	{

			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

	}
}

//mouse function for left and right clicks

void mouse(int button, int state, int x, int y)
{
	mouseposX = x; //the position of mouse
	mouseposY = y;

	//if left clicked , draw a point
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		right_click=0;

		if (N_points >= N_max) //if current number of points is greater than 3, make it 0
		{
			N_points = 0;

		}

		X_pts_array[N_points] = mouseposX;
		Y_pts_array[N_points] = mouseposY;
		N_points++;

	}


	//if right clicked make the variable right_click 1.
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if(right_click==0)
		{
		right_click = 1;
		}

	}
}

//mouse movement function
void mouse_move(int x, int y)
{
	mouseposX = x;
	mouseposY = y;
	glutPostRedisplay();
}

void processSpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{

		//to close the window
		glutDestroyWindow(window);
	}
}

//display function, it should be before main,
//everything will be seen in this function
void Display()
{
	//for a new start
	if (start == 0)
	{
	int i;
	glClearColor(0.0, 0.0, 0.0, 1.0); //RGB AND ALPHA
	glClear(GL_COLOR_BUFFER_BIT);

	if (N_points < N_max) //if clicked points are less than 3
	{
	glColor3f(1,0,1); //RGB
	drawBitmapText("Draw 3 points by left clicking the mouse!",50.0,50.0);
	}

	glPointSize(10.0);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS); //to start drawing points
	//loop for marking the clicks and mouse pointer
	for (i=0; i<N_points; i++)
	{
		glVertex2d(X_pts_array[i],Y_pts_array[i]); //to draw points
	}

	glEnd();

	//control of center point,first no center
	int center = 0;

	if (N_points == N_max )
	{
		if(right_click == 0) //if no center write the following
		{
		drawBitmapText("Center of the circle",cX-60,cY+30);
		drawBitmapText("Right click to see the circle",50,50);
		drawBitmapText("passing through these points",50,70);
		}
		center = 1;
	}

	//if center=1 than draw the center
	if (center == 1)
	{
		glPointSize(10.0);
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POINTS);
		glVertex2d(cX, cY);
		glEnd();
		center = 0; //change the center to zero
	}

	//denominator of a and b variables
	double d;

	// 3 points are shown by translating one of the points to (0,0) and
	// calculating the the positions of the other two accordingly
	x01= X_pts_array[0] - X_pts_array[2];
	y01= Y_pts_array[0]- Y_pts_array[2];

	x02= X_pts_array[1] - X_pts_array[2];
	y02= Y_pts_array[1]- Y_pts_array[2];

	d = (y02 * x01) - (y01 * x02);

	z01 = -((x01*x01)+(y01*y01));
	z02 = -((x02*x02)+(y02*y02));

	a = (y02*z01-y01*z02)/(y02*x01-y01*x02);
	b = (z02*x01-z01*x02)/(y02*x01-y01*x02);

	//center of the circle with translated coordinates
	cX = -(a/2);
	cY = -(b/2);

	//radius of the circle
	r = sqrt(cX*cX+cY*cY);

	//center of the original circle
	cX = cX + X_pts_array[2];
	cY = cY + Y_pts_array[2];

	//when right clicked and the denominator is not equal to zero,
	//draw the circle and ask for a new start
	if (right_click == 1 && d!= 0) {

		drawcircle(r,cX,cY);
		drawBitmapText("Press F1 to exit!",50.0,50.0);
		drawBitmapText("Left click to draw a new circle",50,70);
		start=1;
	}
	}

	if (N_points == 1)
	{
		start = 0;
	}

	glFlush(); //for drawing, without this nothing will be seen
}

int main(int argc, char *argv[]) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowsizeX,windowsizeY);
	glutInitWindowPosition(450,50);
	window=glutCreateWindow("Draw a circle!");
	gluOrtho2D(0,windowsizeX,windowsizeY,0); //left,right,bottom,up
	glutMouseFunc(mouse);
	glutDisplayFunc(Display); // everything will be inside this
	glutPassiveMotionFunc(mouse_move); // for mouse to follow the point on the screen
	glutSpecialFunc(processSpecialKeys);
	glutMainLoop();
	return 0;
}



