/*



 ============================================================================
 Name        : circle.c
 Author      : circle
 Version     :
 Copyright   : Your copyright notice
 Description : A circle drawing program from entered 3 points in C, Ansi-style
 ============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

//max number of input points
#define N_max 3


//current number of input points
int N_points = 0;

int right_click=0;
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

double cX;
double cY;

double x01,y01,x02,y02, z01,z02,a,b, r ;

struct CIRCLE {
	double x;
	double y;
} ;

struct CIRCLE circle;

void drawcircle( double r,  double cX, double cY)
{
	glLineWidth(4);
	glColor3f(1, 0, 1);
	glBegin(GL_LINE_LOOP);
	int i;
	int precision = 100;
	double theta = 0;
	  //glBegin(GL_POLYGON);
	  for(i = 0; i < precision; i++){
	    theta = i * 2 * M_PI/precision;
	    glVertex2d(cX + r*cos(theta), cY + r*sin(theta));
	  }
	  glEnd();


	for (i = 0; i < 360; i++)
	{
		circle.x = cX+r*cos(i);
		circle.y = cY+r*sin(i);

		glVertex2d(circle.x , circle.y);

		circle.x = cX+r * cos(i + 0.1) ;
		circle.y = cY+r * sin(i + 0.1) ;

		glVertex2d(circle.x , circle.y);
		//glVertex3f(circle.x + k, circle.y - h, 0);

	}

	glEnd();
}


// function for writing text on (x,y) coordinate with helvetica font
void drawBitmapText (char *string, double x, double y)
{
	char *c;
	glRasterPos2i(x,y);


	for (c = string; *c != '\0' ; c++)
	{

			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

	}
}

//mouse function , it should be before display
//since we will call it in display
//args button: left/right mouse, state:clicked or not, x/y: coordinates
void mouse(int button, int state, int x, int y) //no change in arguments
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

void processSpecialKeys(int key, int x, int y) //for keyboard ctrl, alt, f1, f3
{
	if (key == GLUT_KEY_F1)
	{

		//to close the window
		glutDestroyWindow(window);
	}
}

//display function, it should be before main, everything will be seen in this function
void Display()
{
	if (start == 0)
	{
	int i;
	glClearColor(0.0, 0.0, 0.0, 1.0); //RGB AND ALPHA
	glClear(GL_COLOR_BUFFER_BIT);

	if (N_points < N_max)
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
	//use for tracking mouse pointer, optional
	//glVertex2d(mouseposX, mouseposY);
	// ### algorithm for circle, can be outside, and called here
	// 100 points connect points from the beginning to the end, the last n-1 to n

	glEnd(); //end glBegin()

	//these will be centers
	//double aX;
	//double aY;

	int center = 0;

	if (N_points == N_max )
	{
		if(right_click == 0)
		{
		drawBitmapText("Center of the circle",cX-60,cY+30);
		drawBitmapText("Right click to see the circle",50,50);
		drawBitmapText("passing through these points",50,70);
		}
		center = 1;

	}

	if (center == 1)
	{
		glPointSize(10.0);
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POINTS);
		glVertex2d(cX, cY);
		glEnd();
		center = 0;
	}


	double det;

	//these will be centers

	x01= X_pts_array[0] - X_pts_array[2];
	y01= Y_pts_array[0]- Y_pts_array[2];

	x02= X_pts_array[1] - X_pts_array[2];
	y02= Y_pts_array[1]- Y_pts_array[2];

	det = (y02 * x01) - (y01 * x02);

	z01 = -((x01*x01)+(y01*y01));
	z02 = -((x02*x02)+(y02*y02));

	a = (y02*z01-y01*z02)/(y02*x01-y01*x02);
	b = (z02*x01-z01*x02)/(y02*x01-y01*x02);

	cX = -(a/2);
	cY = -(b/2);

	r = sqrt(cX*cX+cY*cY);

	cX = cX + X_pts_array[2];
	cY = cY + Y_pts_array[2];


	if (right_click == 1 && det != 0) {

		drawcircle(r,cX,cY);
		drawBitmapText("Press F1 to close window!",50.0,50.0);
		drawBitmapText("Left click to draw a new circle",50,70);
		start=1;
	}
	}

	if (N_points == 1)
	{
		start = 0;
	}



	printf("\nx[0]:%lf\n",X_pts_array[0]);
	printf("\nx[0]:%lf\n",X_pts_array[1]);
	printf("\nx[2]:%lf\n",X_pts_array[2]);
	printf("\nx01:%lf\n",x01);
	printf("\ny01:%lf\n",y01);

	printf("\ncx:%lf\n",cX);
	printf("\ncy:%lf\n",cY);







    //use the following method for drawing 100 lines, N_points will be 100

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP); //draws lines
	//loop for lines
	for (i=0; i<N_points; i++)
	{
		aX = X_pts_array[i];
		aY = Y_pts_array[i];
		glVertex2d(aX,aY);
	}

	glEnd();


	//polygon and its edges for menus
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON); //connect lines
		glVertex2i(windowsizeX-300, windowsizeY-245); //(x,y) coordinates
		glVertex2i(windowsizeX-40, windowsizeY-245);
		glVertex2i(windowsizeX-40, windowsizeY-210);
		glVertex2i(windowsizeX-300, windowsizeY-210);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(5);
	glBegin(GL_LINES); //takes pairs of points and draws lines
		glVertex2i(windowsizeX-40, windowsizeY-245); //first line
		glVertex2i(windowsizeX-40, windowsizeY-210);

		glVertex2i(windowsizeX-300, windowsizeY-245); //second line
		glVertex2i(windowsizeX-300, windowsizeY-210);

		glVertex2i(windowsizeX-300, windowsizeY-245); //3rd line
		glVertex2i(windowsizeX-40, windowsizeY-245);

		glVertex2i(windowsizeX-40, windowsizeY-210);
		glVertex2i(windowsizeX-300, windowsizeY-210);
	glEnd();




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


*/
