#pragma once

class Striker{
public:	
	Striker(Point2 pos, int rad, int red, int green, int blue)
	{
		position = pos;
		radius = rad;
		r = red; g = green; b = blue;
	}

	Point2 position;
	int radius;
	int r, g, b;

	void drawStriker();

};

void Striker::drawStriker() {
	//Point2 position = movingPath.base();
	glColor3f(r, g, b);
	glPushMatrix();
	glTranslatef(position.getX(), position.getY(), 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 60; i++)
		glVertex2d(cos(i * 2 * 180 / 60) * 20, sin(i * 2 * 180 / 60) * 20);
	glEnd();
	glPopMatrix();

	glLineWidth(2.0);
	glColor3f(0.9, 0.5, 0.9);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 60; i++)
		glVertex2d(cos(i * 2 * 180 / 60) * (radius-5) + position.getX(), sin(i * 2 * 180 / 60) * (radius - 5) + position.getY());
	glEnd();

	glLineWidth(2.0);
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 60; i++)
		glVertex2d(cos(i * 2 * 180 / 60) * (radius - 10) + position.getX(), sin(i * 2 * 180 / 60) * (radius - 10) + position.getY());
	glEnd();

	glLineWidth(6.0);
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 60; i++)
		glVertex2d(cos(i * 2 * 180 / 60) * (radius - 18) + position.getX(), sin(i * 2 * 180 / 60) * (radius - 18) + position.getY());
	glEnd();
}