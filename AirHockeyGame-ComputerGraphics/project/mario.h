#pragma once

class Mario
{
	public:
		RGBApixmap pix[2]; // make six empty pixmaps, one for each side of cube
		/*enum State	{	STANDING,	RUNNING1, RUNNING2,	RUNNING3,JUMPING,	DIE	}state ;
		enum ModeType{	STAY,RUN,	R,	JUMP,	DEAD} mode;*/
		float pos_X, pos_Y;

	Mario(Point2 pos)
	{
		pix[0].readBMPFile("bcg3.bmp");
		pix[1].readBMPFile("title.bmp");

		this->pos_X = 0.0;
		this->pos_Y = 0.0;
	};

	void setPosition(float x, float y)
	{
		this->pos_X = x;
		this->pos_Y = y;
	}
	void render(int i);
};

void Mario::render(int i)
{
	glRasterPos2i(this->pos_X,
		this->pos_Y);
	pix[i].mDraw();
}