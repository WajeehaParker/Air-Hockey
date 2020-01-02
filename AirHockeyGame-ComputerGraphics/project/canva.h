#pragma once

class canva
{
	public:
		void drawText(const char *text, int length, int x, int y, int font);
		void setWindow(float left, float right, float bottom, float top);
		void myInit(void);
		void setBackgroundColor(float r, float g, float b);
		void setColor(int r, int g, int b);
		void clearScreen();
		void setwindowSizeandPosition(int w, int h, int p1, int p2);

	private:
	
};

void canva::drawText(const char *text, int length, int x, int y, int font)
{
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
	{
		if (font == 2)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, (int)text[i]);
		else if (font == 1)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
		else if (font == 3)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
		else if (font == 4)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void setWindow(float left, float right, float bottom, float top)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void setBackgroundColor(float r, float g, float b)
{
	glClearColor(r, g, b, 0.0f);
}

void setColor(int r, int g, int b)
{
	glColor3f(r, g, b);
}

void clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void myInit(void)
{
	setBackgroundColor(1.0f, 1.0f, 1.0f);
	setColor(1, 0, 0);
}

void setwindowSizeandPosition(int w, int h, int p1, int p2)
{
	glutInitWindowSize(w, h);
	glutInitWindowPosition(p1, p2);
	glutCreateWindow("Air Hockey");
}