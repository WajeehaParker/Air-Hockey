#include<stdio.h>
#include<Windows.h>
#include<vector>
#include<glut.h>
#include<iostream>
#include<math.h>
#include<ctype.h>
#include<iomanip>
#include "helpingClasses.h"
#include "vector.h"
#include "ray.h"
#include "ball.h"
#include "draw.h"
#include "Strier.h"

using namespace std;

int width = 500, height = 600;

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
	glColor3f(0.15, 0.0, 0.15);
	drawPolygon(l, r, t, b);
	drawBorder();
	drawInnerTable();
	
	red.drawStriker();
	blue.drawStriker();

	glColor3f(1, 1, 1);
	ball.drawBall();
	ball.moveBall();
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (x > l && x<r && y>b && y < t)
			red.position.set(x, height-y);
	}
}

void myKeyboard(unsigned char theKey, int mousex, int mousey)
{
	GLint x = mousex;
	GLint y = height - mousey;
	switch (theKey)
	{
	//case GLUT_KEY_RIGHT:
	case 's':
		if (blue.position.getX() + 1 != r)
		{
			x = blue.position.getX();
			x++;
			blue.position.set( x, blue.position.getY());
		}
		break;
	//case GLUT_KEY_LEFT:
	case 'a':
		if (blue.position.getX() - 1 != l)
		{
			x = blue.position.getX();
			x--;
			blue.position.set(x, blue.position.getY());
		}
		break;
	//case GLUT_KEY_UP:
	case 'w':
		if (blue.position.getY() + 1 != t)
		{
			y = blue.position.getY();
			y++;
			blue.position.set(blue.position.getX(), y);
		}
		break;
	//case GLUT_KEY_DOWN:
	case 'z':
		if (blue.position.getY() -1 != b)
		{
			y = blue.position.getY();
			y--;
			blue.position.set(blue.position.getX(), y);
		}
		break;
	default:
		break;
	}
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
	Point2 enter(ray.base().getX() + cBar.deltaX()*TIn, ray.base().getY() + cBar.deltaY()*TIn);
	Point2 exit(ray.base().getX() + cBar.deltaX()*TOut, ray.base().getY() + cBar.deltaY()*TOut);
	//clipping.push_back({ enter, exit });

	if ((int)exit.getX() == l || (int)exit.getX() == r || (int)exit.getY() == b || (int)exit.getY() == t)
	{
		cout << "Enter: (" << (int)enter.getX() << ", " << (int)enter.getY() << ")\t";
		cout << "Exit: (" << (int)exit.getX() << ", " << (int)exit.getY() << ")\n";


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
		vector2 temp(-(p2.getY() - p1.getY()), (p2.getX() - p1.getX()));
		vector2 r = reflect(vector2(A.base().getX(), A.base().getY()), temp);
		ball.setMovingPath(exit, r);
	}
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.25f, 0.0f, 0.25f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 550, 0, 600);

	drawTable();
	hitPoint();

	glFlush();
	glutSwapBuffers();
}

void Timer(int iUnused)
{
	glutPostRedisplay();//display call again
	glutTimerFunc(100, Timer, 0);// register timer again
}

//  {l, t}, { r, t }, { r, b }, { l, b };
//  { l = 115, r = 435, t = 480, b = 40 };


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

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("First Window");

	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKeyboard);

	Timer(0);
	glutMainLoop();
	return 0;
}