#pragma once
canva cvs_ss;

void drawLogo(void)
{
	glColor3f(255, 127, 0);

	for (float x = 50; x <= 120; x += 25)
	{
		glBegin(GL_TRIANGLES);
		glVertex2f(x, 520.0);
		glVertex2f(x + 10, 530.0);
		glVertex2f(x + 20, 520.0);
		glEnd();
	}
	for (float x = 62.5; x <= 107; x += 25)
	{
		glBegin(GL_TRIANGLES);
		glVertex2f(x, 535.0);
		glVertex2f(x + 10, 525.0);
		glVertex2f(x + 20, 535.0);
		glEnd();
	}
	glBegin(GL_TRIANGLES);
	glVertex2f(73.0, 540.0);
	glVertex2f(85.0, 555.0);
	glVertex2f(97.0, 540.0);
	glEnd();

	std::string logotext;
	logotext = "GAMEZ.ORG";
	setColor(0, 0, 0);
	cvs_ss.drawText(logotext.data(), logotext.size(), 80, 505, 2);
	//glutSwapBuffers();
}

void names(void)
{
	std::string heading;

	heading = "GROUP MEMBERS:";
	setColor(0, 0, 0);
	cvs_ss.drawText(heading.data(), heading.size(), 100, 400, 1);

	glBegin(GL_LINES);
	glVertex2f(62.0, 385.0);
	glVertex2f(350.0, 385.0);
	glEnd();

	heading = "-  WAJEEHA PARKER (B15101151)";
	cvs_ss.drawText(heading.data(), heading.size(), 100, 350, 3);

	heading = "-  BUSHRA IQBAL (B15101027)";
	cvs_ss.drawText(heading.data(), heading.size(), 100, 300, 3);

	heading = "-  ARUBA TAJWAR (B15101018)";
	cvs_ss.drawText(heading.data(), heading.size(), 100, 250, 3);

	heading = "-  SUBIKA IMAM ABIDI (B15101145)";
	cvs_ss.drawText(heading.data(), heading.size(), 100, 200, 3);

}

void nextbutton(void)
{
	setColor(0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(300.0, 78.0);
	glVertex2f(400.0, 78.0);
	glVertex2f(400.0, 113.0);
	glVertex2f(300.0, 113.0);
	glEnd();
}

void drawPlay(int top, int bot)
{
	//P
	drawPolygon(140, 160, top, bot);
	drawPolygon(160, 185, top-15, top);
	//drawPolygon(160, 185, bot+45, bot+30);
	drawPolygon(160, 205, bot + 35, bot + 20);
	drawPolygon(185, 205, bot+30, top);
	//L
	drawPolygon(210, 230, top, bot);
	drawPolygon(210, 265, bot+20, bot);
	//A
	glBegin(GL_POLYGON);
	glVertex2d(270, bot);
	glVertex2d(290, bot);
	glVertex2d(312, top);
	glVertex2d(292, top);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2d(315, bot);
	glVertex2d(335, bot);
	glVertex2d(312, top);
	glVertex2d(292, top);
	glEnd();
	drawPolygon(290, 315, bot + 20, bot+30);
	//Y
	glBegin(GL_POLYGON);
	glVertex2d(372, bot + 40);
	glVertex2d(352, bot + 40);
	glVertex2d(330, top);
	glVertex2d(350, top);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2d(372, bot + 40);
	glVertex2d(352, bot+40);
	glVertex2d(375, top);
	glVertex2d(395, top);
	glEnd();
	drawPolygon(352, 372, bot, bot+40);
}

void drawSettings(int bot, int top)
{
	//S
	drawPolygon(100, 150, top-15, top);
	drawPolygon(100, 150, bot+30, top-30);
	drawPolygon(100, 150, bot, bot+15);
	drawPolygon(100, 115, top-30, top-15);
	drawPolygon(135, 150, bot+15, bot+30);
	//E
	drawPolygon(155, 170, bot, top);
	drawPolygon(155, 205, top - 15, top);
	drawPolygon(155, 205, bot, bot+15);
	drawPolygon(155, 190, bot + 30, top - 30);
	//T
	drawPolygon(210, 260, top - 15, top);
	drawPolygon(227, 243, bot, top);
	//T
	drawPolygon(265, 315, top - 15, top);
	drawPolygon(282, 298, bot, top);
	//I
	drawPolygon(320, 335, bot, top);
	//N
	drawPolygon(340, 355, bot, top);
	drawPolygon(375, 390, bot, top);
	glBegin(GL_POLYGON);
	glVertex2d(340, top);
	glVertex2d(355, top);
	glVertex2d(390, bot);
	glVertex2d(375, bot);
	glEnd();
	//G
	drawPolygon(395, 410, bot, top);
	drawPolygon(395, 445, top - 15, top);
	/*drawPolygon(395, 420, bot, bot + 15);
	drawPolygon(420, 445, bot + 30, top - 30);
	drawPolygon(420, 430, bot, bot + 30);
	drawPolygon(435, 445, bot, bot + 30);*/
	drawPolygon(395, 445, bot, bot + 15);
	drawPolygon(430, 445, bot, bot + 30);
	drawPolygon(420, 445, bot + 30, top - 30);
}

void drawAirHockey(int bot, int top)
{
	//A
	glBegin(GL_POLYGON);
	glVertex2d(30, bot);
	glVertex2d(45, bot);
	glVertex2d(62, top);
	glVertex2d(47, top);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2d(65, bot);
	glVertex2d(80, bot);
	glVertex2d(62, top);
	glVertex2d(47, top);
	glEnd();
	drawPolygon(40, 60, bot + 25, top - 45);
	//I
	drawPolygon(85, 100, bot, top);
	//R
	drawPolygon(105, 120, bot, top);
	drawPolygon(140, 155, bot + 40, top);
	drawPolygon(105, 155, top - 15, top);
	drawPolygon(105, 155, bot + 45, bot + 30);
	glBegin(GL_POLYGON);
	glVertex2d(105, bot + 40);
	glVertex2d(120, bot + 40);
	glVertex2d(155, bot);
	glVertex2d(140, bot);
	glEnd();
	//H
	drawPolygon(175, 190, bot, top);
	drawPolygon(210, 225, bot, top);
	drawPolygon(175, 225, bot + 32, top - 32);
	//O
	drawPolygon(230, 245, bot, top);
	drawPolygon(260, 275, bot, top);
	drawPolygon(230, 275, top - 15, top);
	drawPolygon(230, 275, bot, bot + 15);
	//C
	drawPolygon(280, 295, bot, top);
	drawPolygon(280, 320, top - 15, top);
	drawPolygon(280, 320, bot, bot + 15);
	//K
	drawPolygon(325, 340, bot, top);
	glBegin(GL_POLYGON);
	glVertex2d(340, bot + 40);
	glVertex2d(355, bot + 40);
	glVertex2d(375, top);
	glVertex2d(360, top);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2d(340, bot + 40);
	glVertex2d(355, bot + 40);
	glVertex2d(375, bot);
	glVertex2d(360, bot);
	glEnd();
	//E
	drawPolygon(380, 395, bot, top);
	drawPolygon(380, 425, top - 15, top);
	drawPolygon(380, 425, bot, bot + 15);
	drawPolygon(380, 410, bot + 32, top - 32);
	//Y
	glBegin(GL_POLYGON);
	glVertex2d(430, top);
	glVertex2d(445, top);
	glVertex2d(462, bot + 40);
	glVertex2d(447, bot + 40);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2d(480, top);
	glVertex2d(465, top);
	glVertex2d(447, bot + 40);
	glVertex2d(462, bot + 40);
	glEnd();
	drawPolygon(447, 462, bot, bot + 40);

}