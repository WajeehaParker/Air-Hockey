#include <iostream>
#include <fstream>
#include <string>
#include <glut.h>
#include "RGBApixMap.h"
#include "supportedClass.h"
#include "Mario.h"
#include "canva.h"
#include "game.h"
#include "draw.h"
#include<stdio.h>
#include<Windows.h>
#include<vector>
#include<math.h>
#include<ctype.h>
#include<iomanip>
#include "vector.h"
#include "ray.h"
#include "ball.h"
#include "Strier.h"
#include "screen1_2.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "glut32.lib")

using namespace std;

//canva cvs_ss;
int width = 500;
int height = 600;
Mario m(Point2(0, 0));
static int screen = 0;
int sound = 370;
int music = 370;

void Timer(int iUnused)
{
	glutPostRedisplay();//display call again
	glutTimerFunc(10, Timer, 0);// register timer again
}

void changeMouse()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	POINT mpos;
	ShowCursor(false);

	GetCursorPos(&mpos);

	glLoadIdentity();
	glTranslatef(mpos.x, mpos.y, 0);

	drawPolygon(0, 5, 0, 5);
}

void myDisplay(void)
{
	clearScreen();
	//cout <<endl<< screen;
	if (screen == 0)      //names
	{
		m.render(0);
		drawLogo();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            

		std::string heading;
		heading = "AIR HOCKEY";
		setColor(0, 0, 0);
		cvs_ss.drawText(heading.data(), heading.size(), 300, 520, 1);
		names();
		nextbutton();
		glColor3f(1, 1, 1);
		heading = "NEXT";
		cvs_ss.drawText(heading.data(), heading.size(), 530, 87, 3);
	}
	if (screen == 1)      //play & setting
	{
		m.render(0);
		/*m.setPosition(0, 500);
		m.render(1);*/
		/*drawPlay(400, 320);
		drawSettings(175, 250);*/
		glColor3f(1, 1, 1);
		drawAirHockey(470, 550);
		glColor3f(0.7, 0.1, 0.7);
		drawPlay(380, 320);
		drawSettings(195, 250);
	}
	if (screen == 2)      //game
	{
		glClearColor(0.25f, 0.0f, 0.25f, 0.0f);
		drawTable();
		hitPoint();
		Timer(10);
	}
	if (screen == 3)       //settings
	{
		glColor3f(1, 1, 1);
		m.render(0);
		drawSettings(450, 527);
		setColor(0, 0, 0);
		std::string setting;
		setting = "SOUND";
		cvs_ss.drawText(setting.data(), setting.size(), 200, 350, 1);
		setting = "MUSIC";
		cvs_ss.drawText(setting.data(), setting.size(), 200, 200, 1);
		glColor3f(0.7, 0.1, 0.7);
		drawPolygon(120, 380, 300, 310);       //sound
		drawPolygon(120, 380, 150, 160);       //music
		glColor3f(1, 1, 1);
		drawSolidCircle(sound, 305, 10);
		drawSolidCircle(music, 155, 10);
		nextbutton();
		glColor3f(1, 1, 1);
		string heading = "BACK";
		cvs_ss.drawText(heading.data(), heading.size(), 530, 87, 3);
	}

	glutSwapBuffers();
	
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (x >= 300 && x <= 400 && y >= 487 && y <= 522 && screen == 0)
		{
			screen = 1;
			glutPostRedisplay();	
		}
		if (x >= 150 && x <= 425 && y >= 200 && y <= 280 && screen == 1)
		{
			screen = 2;
			glutPostRedisplay();
		}
		if (x >= 100 && x <= 445 && y >= 350 && y <= 425 && screen == 1)
		{
			screen = 3;
			glutPostRedisplay();
		}
		/*if (screen == 2)
		{
			if (x > l && x<r && y>b && y < t)
				red.position.set(x, height - y);
			glutPostRedisplay();
		}*/
		if (x >= 50 && x <= 150 && y >= 55 && y <= 70 && screen == 2)
		{
			/*glColor3f(1, 1, 1);
			drawPolygon(x, x + 10, y, y + 10);*/
			screen = 1;
			glutPostRedisplay();
		}
		if (screen == 3 && x > 120 && x < 380)
		{
			if (y >= 290 && y <= 300)
				sound = x;
			if (y >= 440 && y <= 450)
				music = x;
			glutPostRedisplay();
		}
		if (x >= 300 && x <= 400 && y >= 487 && y <= 522 && screen == 3)
		{
			screen = 1;
			glutPostRedisplay();
		}
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
		if (blue.position.getX() + 1 != r-10)
		{
			x = blue.position.getX();
			x++;
			blue.position.set(x, blue.position.getY());
		}
		break;
		//case GLUT_KEY_LEFT:
	case 'a':
		if (blue.position.getX() - 1 != l+10)
		{
			x = blue.position.getX();
			x--;
			blue.position.set(x, blue.position.getY());
		}
		break;
		//case GLUT_KEY_UP:
	case 'w':
		if (blue.position.getY() + 1 != t-10)
		{
			y = blue.position.getY();
			y++;
			blue.position.set(blue.position.getX(), y);
		}
		break;
		//case GLUT_KEY_DOWN:
	case 'z':
		if (blue.position.getY() - 1 != b+10)
		{
			y = blue.position.getY();
			y--;
			blue.position.set(blue.position.getX(), y);
		}
		break;
	case 'k':
		if (red.position.getX() + 1 != r-10)
		{
			x = red.position.getX();
			x++;
			red.position.set(x, red.position.getY());
		}
		break;
		//case GLUT_KEY_LEFT:
	case 'j':
		if (red.position.getX() - 1 != l+10)
		{
			x = red.position.getX();
			x--;
			red.position.set(x, red.position.getY());
		}
		break;
		//case GLUT_KEY_UP:
	case 'i':
		if (red.position.getY() + 1 != t-10)
		{
			y = red.position.getY();
			y++;
			red.position.set(red.position.getX(), y);
		}
		break;
		//case GLUT_KEY_DOWN:
	case 'm':
		if (red.position.getY() - 1 != b+10)
		{
			y = red.position.getY();
			y--;
			red.position.set(red.position.getX(), y);
		}
		break;
	default:
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Air Hockey");

	setWindow(0, 500, 0, 600);
	
	myInit();
	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	//PlayBackgroundSound("backmusic.wav");

	glutMainLoop();
	return 0;
}