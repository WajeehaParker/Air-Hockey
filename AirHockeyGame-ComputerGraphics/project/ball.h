#pragma once

class Ball
{
public:

	Ball();
	Ball(float, float, ray2);
	void setMovingPath(Point2, vector2);
	void drawBall(void);
	void moveBall(void);
	ray2 getMovingPath() { return movingPath; }
	Point2 getBase() { ray2 r = this->getMovingPath();  return r.base(); }
	vector2 getDir() { ray2 r = this->getMovingPath();  return r.direction(); }
	vector2 prevPosition;

private:
	float radius;
	float weight;
	ray2  movingPath;
	

};

Ball::Ball()
{
	radius = 0.5;
	weight = 20;
	movingPath.set(Point2(2, 0), vector2(-4, 0));
}

Ball::Ball(float r, float w, ray2 path)
{
	radius = r;
	weight = w;
	movingPath = path;
}

void Ball::setMovingPath(Point2 p, vector2 v)
{
	movingPath.set(p, v);
}

void Ball::drawBall()
{
	Point2 position = movingPath.base();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(position.getX(), position.getY(), 0);
	//glutSolidSphere(this->radius, 40, 40);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 60; i++)
		glVertex2d(cos(i * 2 * 180 / 60) * this->radius, sin(i * 2 * 180 / 60) * this->radius);
	glEnd();
	glPopMatrix();

	glColor3f(0.15, 0.0, 0.15);
	glLineWidth(1.0);
	float rad = this->radius - 3;
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 60; i++)
		glVertex2d(cos(i * 2 * 180 / 60) * rad + position.getX(), sin(i * 2 * 180 / 60) * rad + position.getY());
	glEnd();
	rad -= 3;
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 60; i++)
		glVertex2d(cos(i * 2 * 180 / 60) * rad + position.getX(), sin(i * 2 * 180 / 60) * rad + position.getY());
	glEnd();
	
}

float gettime()
{
	static __int64 i64Frequency = 0;
	static __int64 i64BeginCount = 0;
	if (i64Frequency == 0) {	// do this only for the first time
		QueryPerformanceFrequency((LARGE_INTEGER*)&i64Frequency);
		QueryPerformanceCounter((LARGE_INTEGER*)&i64BeginCount); //retrieve the number of
																 //ticks since system start (64bit int).

	}
	__int64 i64CurrentCount;
	QueryPerformanceCounter((LARGE_INTEGER*)&i64CurrentCount);
	return  (float)(i64CurrentCount - i64BeginCount) / i64Frequency;
}



void Ball::moveBall()
{
	static float prevtime = 0.0f;		// previous frame’s time
	float currtime = gettime();		// current frame’s time
	float elapsedtime = currtime - prevtime;	// elapsed time	
	prevPosition.setX(movingPath.base().getX());
	prevPosition.setY(movingPath.base().getY());

	if (getBase().getX() < 0 || getBase().getX() > 500 || getBase().getY() < 0 || getBase().getY() > 600)
	{
		movingPath.set(Point2(275, 50), vector2(10, 10));
	}
	else {
		Point2 newPosition = movingPath.base() + (elapsedtime*movingPath.direction());
		movingPath.setBase(newPosition);
	}

	prevtime = currtime;

}