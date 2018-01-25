#include "Rectangle.h"
#include "App.h"

using namespace ucm;


void Rectangle::draw() 
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 1.0);
	glVertex2f(x, y);

	glTexCoord2f(1.0, 1.0);
	glVertex2f(x + w, y);

	glTexCoord2f(1.0, 0.0);
	glVertex2f(x + w, y - h);

	glTexCoord2f(0.0, 0.0);
	glVertex2f(x, y - h);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Rectangle::fire() 
{
	missle = true;
}

bool Rectangle::contains(float xx, float yy)
{
	if (xx < (x + w) && xx > x && yy >(y - h) && yy < y)
		return true;

	else
		return false;
}