/* Bezier Curve
 *@author YU LI
 * CS 116A
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> 

float window_width = 800.0;		//  variables representing the window size
float window_height = 600.0;	
int pointsCounter = 0;		// Counter for the points
bool threeDModeFlag = false;


// Point class for points with x and y
class Point {
	public: float x, y;
	void setxy(float x1, float y1) 
	{ x = x1; y = y1; }
	const Point & operator=(const Point &rPoint) 
	{
		x = rPoint.x;
		y = rPoint.y;
		return *this;
	}
};

Point points[16]; //allowed to create up to 16 points 

void init()
{
	glClearColor(0.0,0.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,window_width,0.0,window_height);
}

//Draw the point out when the user clicks on the screen
void drawPoint(int x, int y) 
{
	glPointSize(10.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}


void drawLine(Point point1, Point point2) 
{
	glLineWidth(1.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
		glVertex2f(point1.x, point1.y);
		glVertex2f(point2.x, point2.y);
	glEnd();
	glFlush();
}

//Draw the Beaier Curve with 3 control points
Point drawBezier3(Point A, Point B, Point C, double t)
{
	Point p;
	p.x = (1 - t) * (1-t) * A.x + 2 * t * (1 -t) * B.x + t * t * C.x;
	p.y = pow((1 - t), 2) * A.y + 2 * t * (1 -t) * B.y + pow(t, 2) * C.y;
	return p;
}

//Draw the Beaier Curve with 4 control points
Point drawBezier4(Point A, Point B, Point C, Point D, double t) 
{
	Point p;
	p.x = pow((1 - t), 3) * A.x + 3 * t * (1 -t) * (1-t) * B.x +3 * t * t * (1 -t) * C.x + pow(t, 3) * D.x;
	p.y = pow((1 - t), 3) * A.y + 3 * t * (1 -t) * (1-t) * B.y +3 * t * t * (1 -t) * C.y + pow(t, 3) * D.y;
	return p;
}

//Draw the Beaier Curve with 5 control points
Point drawBezier5(Point A, Point B, Point C, Point D, Point E, double t) 
{
	Point p;
	p.x = 1 * pow(t, 0) * pow((1 - t), 4) * A.x + 4 * pow(t, 1) * pow((1 - t), 3) * B.x + 6 * pow(t, 2) * pow((1 - t), 2) * C.x
		+ 4 * pow(t, 3) * pow((1 - t), 1) * D.x + 1 * pow(t, 4) * pow((1 - t), 0) * E.x;
	p.y = 1 * pow(t, 0) * pow((1 - t), 4) * A.y + 4 * pow(t, 1) * pow((1 - t), 3) * B.y + 6 * pow(t, 2) * pow((1 - t), 2) * C.y
		+ 4 * pow(t, 3) * pow((1 - t), 1) * D.y + 1 * pow(t, 4) * pow((1 - t), 0) * E.y;
	return p;
}

//Draw the Beaier Curve with 6 control points
Point drawBezier6(Point A, Point B, Point C, Point D, Point E, Point F, double t) 
{
	Point p;
	p.x = 1 * pow(t, 0) * pow((1 - t), 5) * A.x + 5 * pow(t, 1) * pow((1 - t), 4) * B.x + 10 * pow(t, 2) * pow((1 - t), 3) * C.x
		+ 10 * pow(t, 3) * pow((1 - t), 2) * D.x + 5 * pow(t, 4) * pow((1 - t), 1) * E.x  + 1 * pow(t, 5) * pow((1 - t), 0) * F.x;
	p.y = 1 * pow(t, 0) * pow((1 - t), 5) * A.y + 5 * pow(t, 1) * pow((1 - t), 4) * B.y + 10 * pow(t, 2) * pow((1 - t), 3) * C.y
		+ 10 * pow(t, 3) * pow((1 - t), 2) * D.y + 5 * pow(t, 4) * pow((1 - t), 1) * E.y  + 1 * pow(t, 5) * pow((1 - t), 0) * F.y;
	return p;
}

//Draw the Beaier Curve with 7 control points
Point drawBezier7(Point A, Point B, Point C, Point D, Point E, Point F,Point G, double t) 
{
	Point p;
	p.x = 1 * pow(t, 0) * pow((1 - t), 6) * A.x + 6 * pow(t, 1) * pow((1 - t), 5) * B.x + 15 * pow(t, 2) * pow((1 - t), 4) * C.x
		+ 20 * pow(t, 3) * pow((1 - t), 3) * D.x + 15 * pow(t, 4) * pow((1 - t), 2) * E.x  + 6 * pow(t, 5) * pow((1 - t), 1) * F.x
		+ 1 * pow(t, 6) * pow((1 - t), 0) * G.x;
	p.y = 1 * pow(t, 0) * pow((1 - t), 6) * A.y + 6 * pow(t, 1) * pow((1 - t), 5) * B.y + 15 * pow(t, 2) * pow((1 - t), 4) * C.y
		+ 20 * pow(t, 3) * pow((1 - t), 3) * D.y + 15 * pow(t, 4) * pow((1 - t), 2) * E.y  + 6 * pow(t, 5) * pow((1 - t), 1) * F.y
		+ 1 * pow(t, 6) * pow((1 - t), 0) * G.y;
	return p;
}

//Draw the Beaier Curve with 8 control points
Point drawBezier8(Point A, Point B, Point C, Point D, Point E, Point F,Point G,Point H, double t) 
{
	Point p;
	p.x = 1 * pow(t, 0) * pow((1 - t), 7) * A.x + 7 * pow(t, 1) * pow((1 - t), 6) * B.x + 21 * pow(t, 2) * pow((1 - t), 5) * C.x
		+ 35 * pow(t, 3) * pow((1 - t), 4) * D.x + 35 * pow(t, 4) * pow((1 - t), 3) * E.x  + 21 * pow(t, 5) * pow((1 - t), 2) * F.x
		+ 7 * pow(t, 6) * pow((1 - t), 1) * G.x + 1 * pow(t, 7) * pow((1 - t), 0) * H.x;
	p.y = 1 * pow(t, 0) * pow((1 - t), 7) * A.y + 7 * pow(t, 1) * pow((1 - t), 6) * B.y + 21 * pow(t, 2) * pow((1 - t), 5) * C.y
		+ 35 * pow(t, 3) * pow((1 - t), 4) * D.y + 35 * pow(t, 4) * pow((1 - t), 3) * E.y  + 21 * pow(t, 5) * pow((1 - t), 2) * F.y
		+ 7 * pow(t, 6) * pow((1 - t), 1) * G.y + 1 * pow(t, 7) * pow((1 - t), 0) * H.y;
	return p;
}

//Draw the Beaier Curve with 9 control points
Point drawBezier9(Point A, Point B, Point C, Point D, Point E, Point F,Point G,Point H,Point I, double t) 
{
	Point p;
	p.x = 1 * pow(t, 0) * pow((1 - t), 8) * A.x + 8 * pow(t, 1) * pow((1 - t), 7) * B.x + 28 * pow(t, 2) * pow((1 - t), 6) * C.x
		+ 56 * pow(t, 3) * pow((1 - t), 5) * D.x + 70 * pow(t, 4) * pow((1 - t), 4) * E.x  + 56 * pow(t, 5) * pow((1 - t), 3) * F.x
		+ 28 * pow(t, 6) * pow((1 - t), 2) * G.x + 8 * pow(t, 7) * pow((1 - t), 1) * H.x + 1 * pow(t, 8) * pow((1 - t), 0) * I.x;
	p.y = 1 * pow(t, 0) * pow((1 - t), 8) * A.y + 8 * pow(t, 1) * pow((1 - t), 7) * B.y + 28 * pow(t, 2) * pow((1 - t), 6) * C.y
		+ 56 * pow(t, 3) * pow((1 - t), 5) * D.y + 70 * pow(t, 4) * pow((1 - t), 4) * E.y  + 56 * pow(t, 5) * pow((1 - t), 3) * F.y
		+ 28 * pow(t, 6) * pow((1 - t), 2) * G.y + 8 * pow(t, 7) * pow((1 - t), 1) * H.y + 1 * pow(t, 8) * pow((1 - t), 0) * I.y;
	return p;
}

//Draw the Beaier Curve with 10 control points
Point drawBezier10(Point A, Point B, Point C, Point D, Point E, Point F,Point G,Point H,Point I,Point J, double t) 
{
	Point p;
	p.x = 1 * pow(t, 0) * pow((1 - t), 9) * A.x + 9 * pow(t, 1) * pow((1 - t), 8) * B.x + 36 * pow(t, 2) * pow((1 - t), 7) * C.x
		+ 84 * pow(t, 3) * pow((1 - t), 6) * D.x + 126 * pow(t, 4) * pow((1 - t), 5) * E.x  + 126 * pow(t, 5) * pow((1 - t), 4) * F.x
		+ 84 * pow(t, 6) * pow((1 - t), 3) * G.x + 36 * pow(t, 7) * pow((1 - t), 2) * H.x + 9 * pow(t, 8) * pow((1 - t), 1) * I.x
		+ 1 * pow(t, 9) * pow((1 - t), 0) * J.x;
	p.y = 1 * pow(t, 0) * pow((1 - t), 9) * A.y + 9 * pow(t, 1) * pow((1 - t), 8) * B.y + 36 * pow(t, 2) * pow((1 - t), 7) * C.y
		+ 84 * pow(t, 3) * pow((1 - t), 6) * D.y + 126 * pow(t, 4) * pow((1 - t), 5) * E.y  + 126 * pow(t, 5) * pow((1 - t), 4) * F.y
		+ 84 * pow(t, 6) * pow((1 - t), 3) * G.y + 36 * pow(t, 7) * pow((1 - t), 2) * H.y + 9 * pow(t, 8) * pow((1 - t), 1) * I.y
		+ 1 * pow(t, 9) * pow((1 - t), 0) * J.y;
	return p;
}

//Draw the Beaier Curve with 11 control points
Point drawBezier11(Point A, Point B, Point C, Point D, Point E, Point F,Point G,Point H,Point I,Point J,Point K, double t) 
{
	Point p;
	p.x = 1 * pow(t, 0) * pow((1 - t), 10) * A.x + 10 * pow(t, 1) * pow((1 - t), 9) * B.x + 45 * pow(t, 2) * pow((1 - t), 8) * C.x
		+ 120 * pow(t, 3) * pow((1 - t), 7) * D.x + 210 * pow(t, 4) * pow((1 - t), 6) * E.x  + 252 * pow(t, 5) * pow((1 - t), 5) * F.x
		+ 210 * pow(t, 6) * pow((1 - t), 4) * G.x + 120 * pow(t, 7) * pow((1 - t), 3) * H.x + 45 * pow(t, 8) * pow((1 - t), 2) * I.x
		+ 10 * pow(t, 9) * pow((1 - t), 1) * J.x + 1 * pow(t, 10) * pow((1 - t), 0) * K.x;
	p.y = 1 * pow(t, 0) * pow((1 - t), 10) * A.y + 10 * pow(t, 1) * pow((1 - t), 9) * B.y + 45 * pow(t, 2) * pow((1 - t), 8) * C.y
		+ 120 * pow(t, 3) * pow((1 - t), 7) * D.y + 210 * pow(t, 4) * pow((1 - t), 6) * E.y  + 252 * pow(t, 5) * pow((1 - t), 5) * F.y
		+ 210 * pow(t, 6) * pow((1 - t), 4) * G.y + 120 * pow(t, 7) * pow((1 - t), 3) * H.y + 45 * pow(t, 8) * pow((1 - t), 2) * I.y
		+ 10 * pow(t, 9) * pow((1 - t), 1) * J.y + 1 * pow(t, 10) * pow((1 - t), 0) * K.y;
	return p;
}

//Draw the Beaier Curve with 12 control points
Point drawBezier12(Point A, Point B, Point C, Point D, Point E, Point F,Point G,Point H,Point I,Point J,Point K, Point L, double t) 
{
	Point p;
	p.x = 1 * pow(t, 0) * pow((1 - t), 11) * A.x + 11 * pow(t, 1) * pow((1 - t), 10) * B.x + 55 * pow(t, 2) * pow((1 - t), 9) * C.x
		+ 165 * pow(t, 3) * pow((1 - t), 8) * D.x + 330 * pow(t, 4) * pow((1 - t), 7) * E.x  + 462 * pow(t, 5) * pow((1 - t), 6) * F.x
		+ 462 * pow(t, 6) * pow((1 - t), 5) * G.x + 330 * pow(t, 7) * pow((1 - t), 4) * H.x + 165 * pow(t, 8) * pow((1 - t), 3) * I.x
		+ 55 * pow(t, 9) * pow((1 - t), 2) * J.x + 11 * pow(t, 10) * pow((1 - t), 1) * K.x + 1 * pow(t, 11) * pow((1 - t), 0) * L.x;
	p.y = 1 * pow(t, 0) * pow((1 - t), 11) * A.y + 11 * pow(t, 1) * pow((1 - t), 10) * B.y + 55 * pow(t, 2) * pow((1 - t), 9) * C.y
		+ 165 * pow(t, 3) * pow((1 - t), 8) * D.y + 330 * pow(t, 4) * pow((1 - t), 7) * E.y  + 462 * pow(t, 5) * pow((1 - t), 6) * F.y
		+ 462 * pow(t, 6) * pow((1 - t), 5) * G.y + 330 * pow(t, 7) * pow((1 - t), 4) * H.y + 165 * pow(t, 8) * pow((1 - t), 3) * I.y
		+ 55 * pow(t, 9) * pow((1 - t), 2) * J.y + 11 * pow(t, 10) * pow((1 - t), 1) * K.y + 1 * pow(t, 11) * pow((1 - t), 0) * L.y;
	return p;
}

//Draw the Beaier Curve with 13 control points
Point drawBezier13(Point A, Point B, Point C, Point D, Point E, Point F,Point G,Point H,Point I,Point J,Point K, Point L, Point M, double t) 
{
	Point p;
	p.x = 1 * pow(t, 0) * pow((1 - t), 12) * A.x + 12 * pow(t, 1) * pow((1 - t), 12) * B.x + 66 * pow(t, 2) * pow((1 - t), 10) * C.x
		+ 220 * pow(t, 3) * pow((1 - t), 9) * D.x + 495 * pow(t, 4) * pow((1 - t), 8) * E.x  + 792 * pow(t, 5) * pow((1 - t), 7) * F.x
		+ 924 * pow(t, 6) * pow((1 - t), 6) * G.x + 792 * pow(t, 7) * pow((1 - t), 5) * H.x + 495 * pow(t, 8) * pow((1 - t), 4) * I.x
		+ 220 * pow(t, 9) * pow((1 - t), 3) * J.x + 66 * pow(t, 10) * pow((1 - t), 2) * K.x + 12 * pow(t, 11) * pow((1 - t), 1) * L.x
		+ 1 * pow(t, 12) * pow((1 - t), 0) * M.x;
	p.y = 1 * pow(t, 0) * pow((1 - t), 12) * A.y + 12 * pow(t, 1) * pow((1 - t), 12) * B.y + 66 * pow(t, 2) * pow((1 - t), 10) * C.y
		+ 220 * pow(t, 3) * pow((1 - t), 9) * D.y + 495 * pow(t, 4) * pow((1 - t), 8) * E.y  + 792 * pow(t, 5) * pow((1 - t), 7) * F.y
		+ 924 * pow(t, 6) * pow((1 - t), 6) * G.y + 792 * pow(t, 7) * pow((1 - t), 5) * H.y + 495 * pow(t, 8) * pow((1 - t), 4) * I.y
		+ 220 * pow(t, 9) * pow((1 - t), 3) * J.y + 66 * pow(t, 10) * pow((1 - t), 2) * K.y + 12 * pow(t, 11) * pow((1 - t), 1) * L.y
		+ 1 * pow(t, 12) * pow((1 - t), 0) * M.y;
	return p;
}

//Draw the Beaier Curve with 14 control points
Point drawBezier14(Point A, Point B, Point C, Point D, Point E, Point F,Point G,Point H,Point I,Point J,Point K, Point L, Point M,Point N, double t) 
{
	Point p;
	p.x = 1 * pow(t, 0) * pow((1 - t), 13) * A.x + 13 * pow(t, 1) * pow((1 - t), 13) * B.x + 78 * pow(t, 2) * pow((1 - t), 11) * C.x
		+ 286 * pow(t, 3) * pow((1 - t), 10) * D.x + 715 * pow(t, 4) * pow((1 - t), 9) * E.x  + 1287 * pow(t, 5) * pow((1 - t), 8) * F.x
		+ 1716 * pow(t, 6) * pow((1 - t), 7) * G.x + 1716 * pow(t, 7) * pow((1 - t), 6) * H.x + 1287 * pow(t, 8) * pow((1 - t), 5) * I.x
		+ 715 * pow(t, 9) * pow((1 - t), 4) * J.x + 286 * pow(t, 10) * pow((1 - t), 3) * K.x + 78 * pow(t, 11) * pow((1 - t), 2) * L.x
		+ 13 * pow(t, 12) * pow((1 - t), 1) * M.x + 1 * pow(t, 13) * pow((1 - t), 0) * N.x;
	p.y = 1 * pow(t, 0) * pow((1 - t), 13) * A.y + 13 * pow(t, 1) * pow((1 - t), 13) * B.y + 78 * pow(t, 2) * pow((1 - t), 11) * C.y
		+ 286 * pow(t, 3) * pow((1 - t), 10) * D.y + 715 * pow(t, 4) * pow((1 - t), 9) * E.y  + 1287 * pow(t, 5) * pow((1 - t), 8) * F.y
		+ 1716 * pow(t, 6) * pow((1 - t), 7) * G.y + 1716 * pow(t, 7) * pow((1 - t), 6) * H.y + 1287 * pow(t, 8) * pow((1 - t), 5) * I.y
		+ 715 * pow(t, 9) * pow((1 - t), 4) * J.y + 286 * pow(t, 10) * pow((1 - t), 3) * K.y + 78 * pow(t, 11) * pow((1 - t), 2) * L.y
		+ 13 * pow(t, 12) * pow((1 - t), 1) * M.y + 1 * pow(t, 13) * pow((1 - t), 0) * N.y;
	return p;
}

//Draw the Beaier Curve with 15 control points
Point drawBezier15(Point A, Point B, Point C, Point D, Point E, Point F,Point G,Point H,Point I,Point J,Point K, Point L, 
						Point M,Point N, Point O, double t) 
{
	Point p;
	p.x = 1 * pow(t, 0) * pow((1 - t), 14) * A.x + 14 * pow(t, 1) * pow((1 - t), 14) * B.x + 91 * pow(t, 2) * pow((1 - t), 12) * C.x
		+ 364 * pow(t, 3) * pow((1 - t), 11) * D.x + 1001 * pow(t, 4) * pow((1 - t), 10) * E.x  + 2002 * pow(t, 5) * pow((1 - t), 9) * F.x
		+ 3003 * pow(t, 6) * pow((1 - t), 8) * G.x + 3432 * pow(t, 7) * pow((1 - t), 7) * H.x + 3003 * pow(t, 8) * pow((1 - t), 6) * I.x
		+ 2002 * pow(t, 9) * pow((1 - t), 5) * J.x + 1001 * pow(t, 10) * pow((1 - t), 4) * K.x + 364 * pow(t, 11) * pow((1 - t), 3) * L.x
		+ 91 * pow(t, 12) * pow((1 - t), 2) * M.x + 14 * pow(t, 13) * pow((1 - t), 1) * N.x + 1 * pow(t, 14) * pow((1 - t), 0) * O.x;
	p.y = 1 * pow(t, 0) * pow((1 - t), 14) * A.y + 14 * pow(t, 1) * pow((1 - t), 14) * B.y + 91 * pow(t, 2) * pow((1 - t), 12) * C.y
		+ 364 * pow(t, 3) * pow((1 - t), 11) * D.y + 1001 * pow(t, 4) * pow((1 - t), 10) * E.y  + 2002 * pow(t, 5) * pow((1 - t), 9) * F.y
		+ 3003 * pow(t, 6) * pow((1 - t), 8) * G.y + 3432 * pow(t, 7) * pow((1 - t), 7) * H.y + 3003 * pow(t, 8) * pow((1 - t), 6) * I.y
		+ 2002 * pow(t, 9) * pow((1 - t), 5) * J.y + 1001 * pow(t, 10) * pow((1 - t), 4) * K.y + 364 * pow(t, 11) * pow((1 - t), 3) * L.y
		+ 91 * pow(t, 12) * pow((1 - t), 2) * M.y + 14 * pow(t, 13) * pow((1 - t), 1) * N.y + 1 * pow(t, 14) * pow((1 - t), 0) * O.y;
	
	return p;
}

//Draw the Beaier Curve with 16 control points
Point drawBezier16(Point A, Point B, Point C, Point D,Point E, Point F, Point G, Point H, Point I, Point J, Point K,
						Point L,Point M, Point N, Point O, Point P, double t) 
{
	Point p;
	p.x = 1 * pow(t, 0) * pow((1 - t), 15) * A.x + 15 * pow(t, 1) * pow((1 - t), 14) * B.x + 105 * pow(t, 2) * pow((1 - t), 13) * C.x
		+ 455 * pow(t, 3) * pow((1 - t), 12) * D.x + 1365 * pow(t, 4) * pow((1 - t), 11) * E.x + 3003 * pow(t, 5) * pow((1 - t), 10) * F.x
		+ 5005 * pow(t, 6) * pow((1 - t), 9) * G.x + 6435 * pow(t, 7) * pow((1 - t), 8) * H.x + 6435 * pow(t, 8) * pow((1 - t), 7) * I.x
		+ 5005 * pow(t, 9) * pow((1 - t), 6) * J.x + 3003 * pow(t, 10) * pow((1 - t), 5) * K.x + 1365 * pow(t, 11) * pow((1 - t), 4) * L.x 
		+ 455 * pow(t, 12) * pow((1 - t), 3) * M.x + 105 * pow(t, 13) * pow((1 - t), 2) * N.x + 15 * pow(t, 14) * pow((1 - t), 1) * O.x
		+ 1 * pow(t, 15) * pow((1 - t), 0) * P.x;
	p.y = 1 * pow(t, 0) * pow((1 - t), 15) * A.y + 15 * pow(t, 1) * pow((1 - t), 14) * B.y + 105 * pow(t, 2) * pow((1 - t), 13) * C.y
		+ 455 * pow(t, 3) * pow((1 - t), 12) * D.y + 1365 * pow(t, 4) * pow((1 - t), 11) * E.y + 3003 * pow(t, 5) * pow((1 - t), 10) * F.y
		+ 5005 * pow(t, 6) * pow((1 - t), 9) * G.y + 6435 * pow(t, 7) * pow((1 - t), 8) * H.y + 6435 * pow(t, 8) * pow((1 - t), 7) * I.y
		+ 5005 * pow(t, 9) * pow((1 - t), 6) * J.y + 3003 * pow(t, 10) * pow((1 - t), 5) * K.y + 1365 * pow(t, 11) * pow((1 - t), 4) * L.y 
		+ 455 * pow(t, 12) * pow((1 - t), 3) * M.y + 105 * pow(t, 13) * pow((1 - t), 2) * N.y + 15 * pow(t, 14) * pow((1 - t), 1) * O.y
		+ 1 * pow(t, 15) * pow((1 - t), 0) * P.y;
	return p;
}


//3D mode function
void draw3DDisplayPanel(void)
{
  GLfloat light_ambient[4] = { 0.2, 0.2, 0.2, 1.0 }; // r, g, b, a
  GLfloat light_diffuse[4] = { 0.8, 0.3, 0.1, 1.0 }; // r, g, b, a
  GLfloat light_specular[4] = { 0.8, 0.3, 0.1, 1.0 }; // r, g, b, a
  GLfloat light_position[4] = { -1.0, 0.0, 0.0 , 0.0 }; // x, y, z, w

  float ad_col[4] = { 1.0, 0, 0.5, 1.0 }; // r, g, b, a
  float ad_col2[4] = { 1.0, 0, 1.0, 1.0 }; // r, g, b, a
  float spec_col[4] = { 1.0, 1.0, 1.0, 1.0 }; // r, g, b, a

  glClearColor(0.0,0.0,0.0,0.0); 
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,(float)(window_width) /(float)window_height,1.0,500.0);
                          // theta, aspect, dnear, dfar
  glViewport(0,0,window_width,window_height); // startx, starty, xsize, ysize 
  glScissor(0,0,window_width - 100,window_height); 
 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();	

  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ad_col);
  glMaterialfv(GL_FRONT, GL_SPECULAR, spec_col);

	// viewer is at (-10,10,-10) looking towards the center of the terrain
	gluLookAt(-20,20,-20,128,0,128,0,1,0);

	// draw the terrain
	// a 256x256 square with lower left corner (0,0,0)
	// up direction is y
	glBegin(GL_QUADS);
	glNormal3f(0.0,1.0,0.0);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(600,0.0,0.0);
	glVertex3f(600,0.0,600);
	glVertex3f(0.0,0.0,600);
	glEnd();
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ad_col2);

	glPushMatrix();
	
	glNormal3f(0.0,1.0,0.0);
	
	
}


//myGlutMouse Function
void myGlutMouse(int button, int state, int x, int y) 
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		points[pointsCounter].setxy((float)x,(float)(window_height - y));	//y coordinate is backward
		pointsCounter++;		//points[0] = pointerCounter 1 ;points[1] = pointerCounter 2; and so far and so on
		
		//if pointsCounter equals to 1
		if(pointsCounter == 1)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}
		}
		
		//if pointsCounter equals to 2
		if(pointsCounter == 2)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}
		}

		//if pointsCounter equals to 3
		if(pointsCounter == 3)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}

			Point oldPoint = points[0];

			for(double t = 0.0;t <= 1; t += 0.005) 
			{
				Point nextPoint = drawBezier3(points[0], points[1], points[2], t);
				drawLine(oldPoint, nextPoint);
				oldPoint = nextPoint;
			}
		}

		//if pointsCounter equals to 4
		if(pointsCounter == 4) 
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}

			Point oldPoint = points[0];

			for(double t = 0.0;t <= 1; t += 0.005) 
			{
				Point nextPoint = drawBezier4(points[0], points[1], points[2],points[3], t);
				drawLine(oldPoint, nextPoint);
				oldPoint = nextPoint;
			}		
		}

		//if pointsCounter equals to 5
		if(pointsCounter == 5) 
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}

			Point oldPoint = points[0];

			for(double t = 0.0;t <= 1; t += 0.005) 
			{
				Point nextPoint = drawBezier5(points[0], points[1], points[2],points[3],points[4], t);
				drawLine(oldPoint, nextPoint);
				oldPoint = nextPoint;
			}
		}

		//if pointsCounter equals to 6
		if(pointsCounter == 6) 
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}

			Point oldPoint = points[0];

			for(double t = 0.0;t <= 1; t += 0.005) 
			{
				Point nextPoint = drawBezier6(points[0], points[1], points[2],points[3],points[4],points[5], t);
				drawLine(oldPoint, nextPoint);
				oldPoint = nextPoint;
			}		
		}

		//if pointsCounter equals to 7
		if(pointsCounter == 7) 
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}

			Point oldPoint = points[0];

			for(double t = 0.0;t <= 1; t += 0.005) 
			{
				Point nextPoint = drawBezier7(points[0], points[1], points[2],points[3],points[4],points[5],points[6], t);
				drawLine(oldPoint, nextPoint);
				oldPoint = nextPoint;
			}		
		}

		//if pointsCounter equals to 8
		if(pointsCounter == 8) 
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}

			Point oldPoint = points[0];

			for(double t = 0.0;t <= 1; t += 0.005) 
			{
				Point nextPoint = drawBezier8(points[0], points[1], points[2],points[3],points[4],points[5],points[6],points[7], t);
				drawLine(oldPoint, nextPoint);
				oldPoint = nextPoint;
			}		
		}

		//if pointsCounter equals to 9
		if(pointsCounter == 9) 
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}

			Point oldPoint = points[0];

			for(double t = 0.0;t <= 1; t += 0.005) 
			{
				Point nextPoint = drawBezier9(points[0], points[1], points[2],points[3],points[4],points[5],points[6],points[7],points[8], t);
				drawLine(oldPoint, nextPoint);
				oldPoint = nextPoint;
			}		
		}

		//if pointsCounter equals to 10
		if(pointsCounter == 10) 
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}

			Point oldPoint = points[0];

			for(double t = 0.0;t <= 1; t += 0.005) 
			{
				Point nextPoint = drawBezier10(points[0], points[1], points[2],points[3],points[4],points[5],points[6],points[7],points[8],points[9],t);
				drawLine(oldPoint, nextPoint);
				oldPoint = nextPoint;
			}		
		}

		//if pointsCounter equals to 11
		if(pointsCounter == 11) 
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}

			Point oldPoint = points[0];

			for(double t = 0.0;t <= 1; t += 0.005) 
			{
				Point nextPoint = drawBezier11(points[0], points[1], points[2],points[3],points[4],points[5],points[6],points[7],points[8],points[9],points[10],t);
				drawLine(oldPoint, nextPoint);
				oldPoint = nextPoint;
			}		
		}

		//if pointsCounter equals to 12
		if(pointsCounter == 12) 
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}

			Point oldPoint = points[0];

			for(double t = 0.0;t <= 1; t += 0.005) 
			{
				Point nextPoint = drawBezier12(points[0], points[1], points[2],points[3],points[4],points[5],points[6],points[7],points[8],points[9],points[10],
									points[11],t);
				drawLine(oldPoint, nextPoint);
				oldPoint = nextPoint;
			}		
		}

		//if pointsCounter equals to 13
		if(pointsCounter == 13) 
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}

			Point oldPoint = points[0];

			for(double t = 0.0;t <= 1; t += 0.005) 
			{
				Point nextPoint = drawBezier13(points[0], points[1], points[2],points[3],points[4],points[5],points[6],points[7],points[8],points[9],points[10],
									points[11],points[12],t);
				drawLine(oldPoint, nextPoint);
				oldPoint = nextPoint;
			}		
		}

		//if pointsCounter equals to 14
		if(pointsCounter == 14) 
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}

			Point oldPoint = points[0];

			for(double t = 0.0;t <= 1; t += 0.005) 
			{
				Point nextPoint = drawBezier14(points[0], points[1], points[2],points[3],points[4],points[5],points[6],points[7],points[8],points[9],points[10],
									points[11],points[12],points[13],t);
				drawLine(oldPoint, nextPoint);
				oldPoint = nextPoint;
			}		
		}

		//if pointsCounter equals to 15
		if(pointsCounter == 15) 
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}

			Point oldPoint = points[0];

			for(double t = 0.0;t <= 1; t += 0.005) 
			{
				Point nextPoint = drawBezier15(points[0], points[1], points[2],points[3],points[4],points[5],points[6],points[7],points[8],points[9],points[10],
									points[11],points[12],points[13],points[14],t);
				drawLine(oldPoint, nextPoint);
				oldPoint = nextPoint;
			}		
		}

		//if pointsCounter equals to 16
		if(pointsCounter == 16) 
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear color and depth buffers
			for ( int i = 0; i < pointsCounter; i++)
			{
				drawPoint(points[i].x, points[i].y);	//draw the points
				
			}
			for ( int i = 0; i < pointsCounter -1; i++)
			{
				drawLine(points[i], points[i+1]);		//draw the lines
			}

			Point oldPoint = points[0];

			for(double t = 0.0;t <= 1; t += 0.005) 
			{
				Point nextPoint = drawBezier16(points[0], points[1], points[2],points[3], points[4], points[5], points[6], points[7], points[8],
											points[9], points[10], points[11], points[12], points[13], points[14], points[15],t);
				drawLine(oldPoint, nextPoint);
				oldPoint = nextPoint;
			}	
			pointsCounter = 0;	//reset the pointsCounter to 0
		}
	}


	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)	// move points by right-clicking on them and moving the
	{													//mouse while holding the right button down.
			for ( int k = 0; k <= pointsCounter ; k++)
				{
					if(points[k].x < x + 10 && points[k].x > x - 10 && points[k].y < (window_height - y + 10) && points[k].y > (window_height - y - 10))
						{
							printf ("PoinsCounter: %d  selected\n", k);
							
						}
				}		
	}

	if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)	// move points by right-clicking on them and moving the
	{													//mouse while holding the right button down.
			for ( int k = 0; k <= pointsCounter ; k++)
				{
					if(points[k].x < x + 10 && points[k].x > x - 10 && points[k].y < (window_height - y + 10) && points[k].y > (window_height - y - 10))
						{
							printf ("PoinsCounter: %d  selected\n", k);
							points[k+1].setxy((float)x,(float)(window_height - y));
						}
				}		
	}
}


/********************* myGlutMotionMouse() **********/

void myGlutMotionMouse(int x, int y)
{
	printf ("Mouse Drag Position: %d, %d.\n", x, y);
}


/********************* myGlutKeyboard() **********/

void myGlutKeyboard(unsigned char Key, int x1, int y1)
{
  switch(Key)
  {	
	case 'm':
		if (threeDModeFlag == false)
		{
			draw3DDisplayPanel();
			glutSwapBuffers();
			threeDModeFlag = true; 
		}
		else
		{	
			threeDModeFlag = false;
		}
		break;
	case 27: 
	case 'q':
		exit(0);
		break;
  };
}


void myGlutDisplay() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc, char *argv[]) 
{
	glutInit(&argc, argv);				// Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);		//Set display mode.
	glutInitWindowPosition( 50, 30 );				//Set top-left display-window position.	
	glutInitWindowSize(window_width, window_height);	//Set display-window width and height;
	glutCreateWindow("Bezier Curve");				//Create display window with the a given caption for the title bar.
	glutMouseFunc(myGlutMouse);
	glutMotionFunc(myGlutMotionMouse); 
	glutDisplayFunc(myGlutDisplay);
	
	glutKeyboardFunc( myGlutKeyboard );

	init();
	glutMainLoop();

	return 0;
} 