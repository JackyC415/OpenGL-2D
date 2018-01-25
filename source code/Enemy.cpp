#include "Enemy.h"
#include "App.h"
using namespace ucd;

void Enemy::draw()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(Xpos, Ypos);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(Xpos + w, Ypos);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(Xpos + w, Ypos - h);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(Xpos, Ypos - h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Enemy::fire()
{
	emissle = true;
}

bool Enemy::contains(float xx, float yy)
{
	if (xx < (Xpos + w) && xx > Xpos && yy > (Ypos -h) && yy < Ypos)
		return true;

	else
		return false;
}
