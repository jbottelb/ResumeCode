// fractals.cpp
// Created by Josh Bottelberghe 12/9/19
// with the solution for number one because I understand it
// This program draws fractals

#include <iostream>
#include "gfx.h"
#include <cmath>
using namespace std;

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3);
void shrinkSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void spiralSquares(double cx, double cy, double theta, double l, double size);
void circularLace(int x, int y, int rad);
void snowflake(int xm, int ym, double theta, double length);
void tree(int x, int y, int l, int a);
void fern(int x, int y, int l, int a);
void spiralSpirals(int cx, int cy, double theta, double l);

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void drawRectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

int main()
{
	int width = 700, height = 700, mrgn = 20, sqrM = mrgn * 9;
	int c = 'n';


	gfx_open(width, height, "Fractals");

  	while (c != 'q') {
		c = gfx_wait();
    	gfx_clear();

		switch (c){
			case '1':
    			sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
				break;
			case '2':
				shrinkSquare(sqrM, sqrM, width-sqrM, sqrM, width - sqrM, height - sqrM, sqrM,  height - sqrM);
				break;
			case '3':
				spiralSquares(width/2, height/2, 5 * M_PI / 2, 300, 100);
				break;
			case '4':
				circularLace(width/2, height/2, 200);
				break;
			case '5':
				snowflake(width/2, height/2, 0, 240);
				break;
			case '6':
				tree(width/2, height - 10, width / 3, 0);
				break;
			case '7':
				fern(width/2, height - 10, width * 6 / 10, 0);
				break;
			case '8':
				spiralSpirals(width/2, height/2, 5*M_PI/2,400);	
				break;	
			default:
				
				break;
		}
	}
}

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
 	// Base case. 
 	if ( abs(x2-x1) < 5 ) return;

 	// Draw the triangle
 	drawTriangle( x1, y1, x2, y2, x3, y3 );

 	// Recursive calls
 	sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
 	sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
 	sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

void shrinkSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{

	int l = (abs(x1 - x2) / 4);	// the new length

	if (abs(x2-x1) < 2) {
		return;
	}

	drawRectangle(x1, y1, x2, y2, x3, y3, x4, y4);

	shrinkSquare(x1-l, y1 - l, x1 + l, y1 - l, x1 + l, y1 + l, x1 - l, y1 + l);
	shrinkSquare(x2-l, y2 - l, x2 + l, y2 - l, x2 + l, y2 + l, x2 - l, y2 + l);
	shrinkSquare(x3-l, y3 - l, x3 + l, y3 - l, x3 + l, y3 + l, x3 - l, y3 + l);
	shrinkSquare(x4-l, y4 - l, x4 + l, y4 - l, x4 + l, y4 + l, x4 - l, y4 + l);
}

void spiralSquares(double cx, double cy, double theta, double l, double s)
{
	if (s < .05) return;
	
	double x1 = cx + l * cos(theta);
	double y1 = cy + l * sin(theta);
	
	drawRectangle(x1, y1, x1 + s, y1, x1 + s, y1 - s, x1, y1 - s);

	l = l * 14 / 15;
	s = s * 14/15;
	theta = theta + M_PI / 5;


	spiralSquares(cx, cy, theta, l, s);
}

void circularLace(int x, int y, int rad)
{
	if (rad <= 1) return;

	gfx_circle(x, y, rad);

	// locations for new circles
	int newRad = (6 * rad)/16;
	int x1 = rad * cos(0);
	int y1 = rad * sin(0);
	int x2 = rad * cos(M_PI/3);
	int y2 = rad * sin(M_PI/3);
	int x3 = rad * cos(2 * M_PI/3);
	int y3 = rad * sin(2 * M_PI/3);
	int x4 = rad * cos(M_PI);
	int y4 = rad * sin(M_PI);
	int x5 = rad * cos(4 * M_PI/3);
	int y5 = rad * sin(4 * M_PI/3);
	int x6 = rad * cos(5 * M_PI/3);
	int y6 = rad * sin(5 * M_PI/3);

	circularLace(x + x1, y + y1, newRad);
	circularLace(x + x2, y + y2, newRad);
	circularLace(x + x3, y + y3, newRad);
	circularLace(x + x4, y + y4, newRad);
	circularLace(x + x5, y + y5, newRad);
	circularLace(x + x6, y + y6, newRad);

}

void snowflake (int xm, int ym, double theta, double length)
{
	if (length < 2) return;

	int x1,y1,x2,y2,x3,y3,x4,y4,x5,y5;
	x1 = xm - length*cos((60+theta) *M_PI/180);
	y1 = ym - length*sin((60+theta) *M_PI/180);
	x2 = xm - length*cos((132+theta) *M_PI/180);
	y2 = ym - length*sin((132+theta) *M_PI/180);
	x3 = xm - length*cos((204+theta) *M_PI/180);
	y3 = ym - length*sin((204+theta) *M_PI/180);
	x4 = xm - length*cos((276+theta) *M_PI/180);
	y4 = ym - length*sin((276+theta) *M_PI/180);
	x5 = xm - length*cos((348+theta) *M_PI/180);
	y5 = ym - length*sin((348+theta) *M_PI/180);

	gfx_line(xm, ym, x1, y1);
	gfx_line(xm, ym, x2, y2);
	gfx_line(xm, ym, x3, y3);
	gfx_line(xm, ym, x4, y4);
	gfx_line(xm, ym, x5, y5);

	snowflake(x1, y1, theta + 72, 2 * length / 5);
	snowflake(x2, y2, theta + 72, 2 * length / 5);
	snowflake(x3, y3, theta + 72, 2 * length / 5);
	snowflake(x4, y4, theta + 72, 2 * length / 5);
	snowflake(x5, y5, theta + 72, 2 * length / 5);

}

void tree (int x, int y, int l, int a)
{
	if (l < 1) return;

	gfx_line(x, y, x - l * sin(a * M_PI / 180), y - l * cos(a * M_PI / 180));

	tree(x - l * sin(a * M_PI / 180), y - l * cos(a * M_PI / 180), l * 2 / 3, a - 30);
	tree(x - l * sin(a * M_PI / 180), y - l * cos(a * M_PI / 180), l * 2 / 3, a + 30);

}

void fern (int x, int y, int l, int a)
{
	if (l < 4) return;

	gfx_line(x, y, x - l * sin(a * M_PI / 180), y - l * cos(a * M_PI / 180));

	fern(x - l * sin(a * M_PI / 180) / 4, y - l * cos(a * M_PI / 180) / 4, l / 3, a - 40);
	fern(x - l * sin(a * M_PI / 180) / 4, y - l * cos(a * M_PI / 180) / 4, l / 3, a + 40);
	fern(x - l * sin(a * M_PI / 180) / 2, y - l * cos(a * M_PI / 180) / 2, l / 3, a - 40);
	fern(x - l * sin(a * M_PI / 180) / 2, y - l * cos(a * M_PI / 180) / 2, l / 3, a + 40);
	fern(x - l * sin(a * M_PI / 180)*3 / 4, y - l * cos(a * M_PI / 180)*3 / 4, l / 3, a - 40);
	fern(x - l * sin(a * M_PI / 180)*3 / 4, y - l * cos(a * M_PI / 180)*3 / 4, l / 3, a + 40);
	fern(x - l * sin(a * M_PI / 180), y - l * cos(a * M_PI / 180), l / 3, a - 40);
	fern(x - l * sin(a * M_PI / 180), y - l * cos(a * M_PI / 180), l / 3, a + 40);

}

void spiralSpirals(int cx, int cy, double theta, double l)
{
	// find distance of l to the center as base
	if (l <= 1) {
		gfx_point(cx, cy);
		return;
	}
	
	// draw spirals in
	spiralSpirals(cx + l *( cos(theta)), cy + l * sin(theta), theta, l /5);
	
	// move to next spirals
	spiralSpirals(cx, cy, theta + M_PI / 9, l * 19/20);
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
 	gfx_line(x1,y1,x2,y2);
 	gfx_line(x2,y2,x3,y3);
 	gfx_line(x3,y3,x1,y1);
}

void drawRectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
 	gfx_line(x1,y1,x2,y2);
 	gfx_line(x2,y2,x3,y3);
 	gfx_line(x3,y3,x4,y4);
	gfx_line(x4,y4,x1,y1);
}

