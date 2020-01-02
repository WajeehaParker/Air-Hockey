#pragma once
#include "canva.h"

const float DEG2RAD = 3.14159 / 180.0;
std::vector<Point2> list;

canva cvs_s;

float l = 115, r = 435, t = 480, b = 40;

void drawEllipse(float xradius, float yradius, Point2 pos)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float degInRad = i * DEG2RAD;
		glVertex2f(cos(degInRad)*xradius + pos.getX(), sin(degInRad)*yradius + pos.getY());
	}
	glEnd();
}

void drawPolygon(int l, int r, int b, int t)
{
	glBegin(GL_POLYGON);
		glVertex2d(l, t);
		glVertex2d(r, t);
		glVertex2d(r, b);
		glVertex2d(l, b);
	glEnd();
}

void drawTriangleFan(Point2 a, Point2 b, Point2 c)
{
	glBegin(GL_POLYGON);
		glVertex2d(a.getX(), a.getY());
		glVertex2d(b.getX(), b.getY());
		glVertex2d(c.getX(), c.getY());
	glEnd();
}

void drawSolidCircle(int x, int y, int r)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < 60; i++)
		glVertex2d(cos(i * 2 * 180 / 60) * r + x, sin(i * 2 * 180 / 60) * r + y);
	glEnd();
}

void drawHollowCircle(int x, int y, int r)
{
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 60; i++)
		glVertex2d(cos(i * 2 * 180 / 60) * r + x, sin(i * 2 * 180 / 60) * r + y);
	glEnd();
}

void drawSemiCircle(int x, int y, int r, int s)
{
	glBegin(GL_LINE_STRIP);
	for (int i = s; i <= 90 + s; i++)
		glVertex2d(cos(i * 2 * 3.14159/180) * r + x, sin(i * 2 * 3.14159/180) * r + y);
	glEnd();
}

void drawLine(int x1, int y1, int x2, int y2)
{
	glBegin(GL_LINES);
		glVertex2d(x1, y1);
		glVertex2d(x2, y2);
	glEnd();
}

void drawBorder()
{
	//border heighlight
	glColor3f(0.5, 0.0, 0.5);
	drawPolygon(l-21, l, b, t);     //left
	drawPolygon(l, r, t, t+21);       //top
	drawPolygon(r, r+21, b, t);   //right
	drawPolygon(l, r, b-21, b); //bottom

	//for border
	glColor3f(0.15, 0.0, 0.15);
	drawPolygon(l-20, l, b, t);     //left
	drawPolygon(l, r, t, t+20);       //top
	drawPolygon(r, r+20, b, t);   //right
	drawPolygon(l, r, b-20, b); //bottom
	
	//for corners
	drawTriangleFan(Point2(l, t), Point2(l, t+20), Point2(l-20, t));
	drawTriangleFan(Point2(r, t), Point2(r+20, t), Point2(r, t+20));
	drawTriangleFan(Point2(r, b), Point2(r+20, b), Point2(r, b-20));
	drawTriangleFan(Point2(l, b), Point2(l-20, b), Point2(l, b-20));

	//decorating border
	glColor3f(0.05, 0.0, 0.05);
	for(int i=b+10; i<130; i++)            //left
		drawSolidCircle(l-10, i, 10);
	for (int i = 150; i <245 ; i++)
		drawSolidCircle(l - 10, i, 10);
	for (int i = 275; i < 370; i++)
		drawSolidCircle(l - 10, i, 10);
	for (int i = 390; i < t-10; i++)
		drawSolidCircle(l - 10, i, 10);
	list.push_back(Point2(l - 10, 235));
	list.push_back(Point2(l - 10, 285));

	for (int i = b+10; i < 130; i++)            //right
		drawSolidCircle(r+10, i, 10);
	for (int i = 150; i < 245; i++)
		drawSolidCircle(r + 10, i, 10);
	for (int i = 275; i < 370; i++)
		drawSolidCircle(r + 10, i, 10);
	for (int i = 390; i < t-10; i++)
		drawSolidCircle(r + 10, i, 10);
	list.push_back(Point2(r + 10, 235));
	list.push_back(Point2(r + 10, 285));

	for(int i = l + 10; i < 200; i++)           //bottom
		drawSolidCircle(i, b-10, 10);
	for (int i = 355; i < r-10; i++)
		drawSolidCircle(i, b - 10, 10);


	for (int i = l + 10; i < 200; i++)          //top
		drawSolidCircle(i, t + 10, 10);
	for (int i = 355; i < r-10; i++)
		drawSolidCircle(i, t + 10, 10);

	//Goals  210   340
	glLineWidth(2.0);
	drawLine(215, t + 20, 340, t + 20);
	drawLine(215, b-20, 340, b-20 + 20);

	glColor3f(0.7, 0.0, 0.7);
	glLineWidth(2.0);
	for (int i = 215; i < 340; i += 6)
	{
		drawLine(i, b, i, b - 20);
		drawLine(i, t, i, t + 20);
	}

	//border circles
	list.push_back(Point2(l - 5, t+10));
	list.push_back(Point2(195, t + 10));
	list.push_back(Point2(r + 5, t + 10));
	list.push_back(Point2(360, t + 10));
	list.push_back(Point2(l - 5, b - 10));
	list.push_back(Point2(195, b - 10));
	list.push_back(Point2(r + 5, b - 10));
	list.push_back(Point2(360, b - 10));

	for (int i = 0; i < list.size(); i++)
	{
		glColor3f(0.7, 0.0, 0.7);
		drawSolidCircle(list.at(i).getX(), list.at(i).getY(), 8);
		glLineWidth(1.0);
		glColor3f(0.5, 0.5, 0.5);
		drawHollowCircle(list.at(i).getX(), list.at(i).getY(), 8);
		glColor3f(0.05, 0.0, 0.05);
		drawSolidCircle(list.at(i).getX(), list.at(i).getY(), 5);
	}
}

void drawInnerTable()
{
	glLineWidth(4.0);
	glColor3f(0.7, 0.0, 0.7);
	drawSemiCircle((r - l) / 2 + l, b, 65, 0);
	drawSemiCircle((r - l) / 2 + l, t, 65, 90);
	drawLine(l, (t - b) / 2 + b, r, (t - b) / 2 + b);
	drawHollowCircle((r - l) / 2 + l, (t - b) / 2 + b, 65);

	glColor3f(1, 1, 1);
	glLineWidth(1.0);
	drawSemiCircle((r - l) / 2 + l, b, 65, 0);
	drawSemiCircle((r - l) / 2 + l, t, 65, 90);
	drawLine(l, (t - b) / 2 + b, r, (t - b) / 2 + b);
	drawHollowCircle((r - l) / 2 + l, (t - b) / 2 + b, 65);
}

void backButton()
{
	setColor(0.05, 0.0, 0.05);
	drawPolygon(50, 150, 530, 565);
	glColor3f(0.7, 0.0, 0.7);
	drawLine(50, 565, 150, 565);
	drawLine(50, 530, 150, 530);
	drawLine(50, 530, 50, 565);
	drawLine(150, 530, 150, 565);
	glColor3f(1, 1, 1);
	std::string heading;
	heading = "BACK";
	cvs_s.drawText(heading.data(), heading.size(), 100, 540, 1);
}

int scores = 0;
void score()
{
	glColor3f(1, 1, 1);
	std::string heading;
	heading = "SCORE: ";
	cvs_s.drawText(heading.data(), heading.size(), 450, 540, 1);

	/*std::string out_string;
	std::stringstream ss;
	ss << scores;
	out_string = ss.str();
	cvs_s.drawText(out_string.data(), out_string.size(), 450, 540, 1);*/

}