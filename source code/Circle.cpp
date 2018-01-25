#define _USE_MATH_DEFINES
#include <math.h>
#include "Circle.h"

void Circle::draw() 
{
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);

	for (float theta = 0.0; theta <= 2 * M_PI; theta += 0.00001) 
	{
		glVertex2f(radius * cos(theta) + x, radius * sin(theta) + y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(M_PI + 0.1, M_PI + 0.1);
	glEnd();
}

bool Circle::contains(float x, float y) 
{
	float d = sqrt(pow(x - this->x, 2) + pow(y - this->y, 2));
	return d < radius;
}
