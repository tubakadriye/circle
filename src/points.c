/*

 * points.c
 *
 *  Created on: Nov 23, 2020
 *      Author: tuba

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

int window;
int windowsizeX = 1400;
int windowsizeY = 900;

void Display ()
{
glPointSize(4.0);
glColor3f(1.0, 0.0, 0.0);
glBegin (GL_POINTS);
glVertex2d(300, 50);
//glVertex2d(2.0, -2.0);
//glVertex2d(0.0,2.0);
glEnd ( );
glFlush();
}

int main(int argc, char *argv[]) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowsizeX,windowsizeY);
	glutInitWindowPosition(450,50);
	window=glutCreateWindow("Draw a circle!");
	gluOrtho2D(0,windowsizeX,windowsizeY,0); //left,right,bottom,up
	glutDisplayFunc(Display); // everything will be inside this
	glutMainLoop();
	return 0;
}
*/
