#ifndef TextEnemy_hpp
#define TextEnemy_hpp

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

class TextEnemy 
{
	float x;
	float y;
	float w;
	float h;

public:
	TextEnemy(float x = 0, float y = 1, float w = 0.5, float h = 0.5) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	void draw()
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(x, y - h);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(x, y);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(x + w, y);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(x + w, y - h);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
};

#endif 
