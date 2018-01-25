#ifndef Enemy_hpp
#define Enemy_hpp
#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
namespace ucd
{
	class Enemy
	{
		float Xpos;
		float Ypos;
		float w, h;
		float r, g, b;

	public:
		bool emissle;
		bool enemyleft;

		Enemy(float xx = 0.0, float yy = 0.0, float ww = 0.2, float hh = 0.2, float rr = 0, float gg = 1, float bb = 0) :
			Xpos(xx), Ypos(yy), w(ww), h(hh), r(rr), g(gg), b(bb)
		{
			emissle = false;
			enemyleft = true;
		}

		void draw();
		void fire();
		bool contains(float xx, float yy);
		float getX() const { return Xpos; }
		float getY() const { return Ypos; }
		void setX(float x) { Xpos = x; }
		void setY(float y) { Ypos = y; }

		float getW() const { return w; }
		float getH() const { return h; }
		void setW(float ww) { w = ww; }
		void setH(float hh) { h = hh; }

		float getR() const { return r; }
		float getG() const { return g; }
		float getB() const { return b; }
		void setColor(float rr, float gg, float bb) { r = rr; g = gg; b = bb; }

	};
}
#endif