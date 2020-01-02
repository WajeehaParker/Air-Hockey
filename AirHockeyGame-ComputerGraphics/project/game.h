#pragma once
#include<stdio.h>
#include<Windows.h>
#include<vector>
#include<glut.h>
#include<iostream>
#include<math.h>
#include<ctype.h>
#include<iomanip>
#include "vector.h"
#include "ray.h"
#include "ball.h"
#include "draw.h"
#include "Strier.h"
#include "sstream"
using namespace std;

//int width = 500, height = 600;

static boolean dist(Point2 A, Point2 B, Point2 C) {
	float AB = sqrt(powf(A.getX() - B.getX(), 2) + powf(A.getY() - B.getY(), 2));
	float AC = sqrt(powf(A.getX() - C.getX(), 2) + powf(A.getY() - C.getY(), 2));
	float CB = sqrt(powf(C.getX() - B.getX(), 2) + powf(C.getY() - B.getY(), 2));
	return(AB == (AC + CB));
}
static boolean inLine(Point2 A, Point2 B, Point2 C);

vector2 normalForm(Point2 p1, Point2 p2);
vector2 PointDiff(Point2 p1, Point2 p2);
float tHit(ray2 A, int side);

ray2 ray(Point2(275, 50), vector2(10, 10));        //vector gives speed
Ball ball(10, 20, ray);

struct Line {
	int lineNo;
	float TIn;
	float TOut;
};
struct Clipping
{
	Point2 enter,
		exit;
};

vector<Point2> innerborder = { {l, t}, {r, t}, {r, b}, {l, b} };
vector<Line> lineRecord;
std::vector<Clipping> clipping;
float TIn = 0;
float TOut = 1;

Striker red(Point2((r - l) / 2 + l, b + 20), 25, 1, 0, 0);
Striker blue(Point2((r - l) / 2 + l, t - 20), 25, 0, 0, 1);

void drawTable()
{
	backButton();
	score();
	glColor3f(0.15, 0.0, 0.15);
	//drawPolygon(l, r, t, b);
	drawPolygon(115, 435, 480, 40);
	drawBorder();
	drawInnerTable();

	red.drawStriker();
	blue.drawStriker();

	glColor3f(1, 1, 1);
	ball.drawBall();
	ball.moveBall();
}

void hitPoint()
{
	for (int i = 0; i < innerborder.size(); i++)
	{
		TIn = 0; TOut = 1;
		tHit(ball.getMovingPath(), i);
	}

	ray2 A = ball.getMovingPath();
	vector2 cBar = A.base() - ray.base();
	//p=a+ct
	Point2 enter(ray.base().getX() + cBar.deltaX()*TIn, ray.base().getY() + cBar.deltaY()*TIn);
	Point2 exit(ray.base().getX() + cBar.deltaX()*TOut, ray.base().getY() + cBar.deltaY()*TOut);
	//clipping.push_back({ enter, exit });

	if ((int)exit.getX() == l || (int)exit.getX() == r || (int)exit.getY() == b || (int)exit.getY() == t)
	{
		cout << "Enter: (" << (int)enter.getX() << ", " << (int)enter.getY() << ")\t";
		cout << "Exit: (" << (int)exit.getX() << ", " << (int)exit.getY() << ")\n";
		//cout << endl << "BALL: " << ball.getMovingPath().base().getX() << "," << ball.getMovingPath().base().getY();

		Point2 p1, p2;
		if ((int)exit.getX() == l)
		{
			p1 = Point2(l, b);
			p2 = Point2(l, t);
		}
		if ((int)exit.getX() == r)
		{
			p1 = Point2(r, t);
			p2 = Point2(r, b);
		}
		if ((int)exit.getX() == t)
		{
			p1 = Point2(l, t);
			p2 = Point2(r, t);
		}
		if ((int)exit.getX() == b)
		{
			p1 = Point2(r, b);
			p2 = Point2(l, b);
		}
		vector2 temp(-(p2.getX() - p1.getX()), (p2.getY() - p1.getY()));
		vector2 r = reflect(vector2((int)A.base().getX(), (int)A.base().getY()), temp);
		//vector2 r = reflect(ball.prevPosition, temp);
		//while(r.deltaX() > 10 && r.deltaY() > 10)
		//{
			/*r.setX(r.deltaX() - 10);
			r.setY(r.deltaY() - 10);*/
		//}
		ball.setMovingPath(exit, r);
	}
}

float tHit(ray2 A, int side)
{
	Point2 P1 = innerborder.at(side);
	Point2 P2 = innerborder.at((side + 1 == innerborder.size()) ? 0 : side + 1);
	vector2 nBar = normalForm(P1, P2);
	vector2 BdiffA = P1 - A.base();
	//vector2 cBar = Point2(A.direction().deltaX(), A.direction().deltaY()) - A.base();
	vector2 cBar = A.base() - ray.base();

	float numerator = nBar * BdiffA;
	float Denominator = nBar * cBar;
	float tHit = numerator / Denominator;

	if (Denominator > 0)
		TOut = min(TOut, tHit);
	else
		TIn = max(TIn, tHit);

	lineRecord.push_back(Line{ side,TIn,TOut });

	/*cout << "P1: (" << P1.getX() << "," << P1.getY() << ")  P2: (" << P2.getX() << "," << P2.getY() << ")"<< endl;
	cout << "Line: (" << ray.base().getX() << "," << ray.base().getY() << ") , ("<<A.base().getX()<<","<<A.base().getY()<<")"<<endl;
	cout << "B-A: (" << BdiffA.deltaX() << "," << BdiffA.deltaY() << ")" << endl;
	cout << "n: (" << nBar.deltaX() << "," << nBar.deltaY() << ")" << endl;
	cout << "c: (" << cBar.deltaX() << "," << cBar.deltaY() << ")" << endl;
	cout << "num: " << numerator << "  den: " << Denominator << endl;
	cout << "tHit: "<<tHit << endl;
	cout << "TIn: " << TIn << "  TOut: " << TOut << endl;*/

	return tHit;
}

vector2 normalForm(Point2 p1, Point2 p2)
{
	vector2 temp(-(p2.getY() - p1.getY()), p2.getX() - p1.getX());
	return temp;
}