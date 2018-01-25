#ifndef App_hpp
#define App_hpp
#include "GlutApp.h"
#include "RgbImage.h"
#include "TexRect.hpp"
#include "visualc15\TextEnemy.hpp"
#include "visualc15\Rectangle.h"
#include "visualc15\Circle.h"
#include "visualc15\Enemy.h"
#include "visualc15\Heart.h"
#include<vector>
using namespace ucm;
class App: public GlutApp 
{
    // Maintain app state here
    float mx;
    float my;

	ucm::Rectangle* player;
	ucd::Enemy* e;
	ucd::Enemy* e1;
	ucd::Enemy* s[4];
	ucb::Heart* ss[4];
	ucd::Enemy *em;
	Circle* c;

	std::vector<ucm::Rectangle*> playerMissiles;
	std::vector<ucd::Enemy*> enemies;
	std::vector<ucm::Rectangle*> enemyMissiles;

	bool right;
	bool move;
	bool jump;
	bool moveright;
	bool moveleft;
	float theta;
	float inc;
	float missleX;
	float missleY;
	float enemyX;
	float enemyY;
	bool shot;
	int counter;
	int life;
	bool gameover;
	bool loop;
	bool eFire;
	bool backgroundSwitch;
	bool bgSwitch;
	int repeat;
	float speed;
	bool showenemy;
	bool enemyleft;
	int frame, time, timebase;
	bool W;
	int backgroundCheck = 0;
	int count = 0;
	int KillCount = 0;
	float enemyMissileSpeed = 0.02f;
	bool fire;
public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    // These are the events we want to handle
    void draw();
    void keyPress(unsigned char key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);
	void idle();
	void shoot();
	//void drawText(const char * text, int length, int x, int y);
	GLuint loadTexture(const char* filename);
    GLuint wall;
	GLuint wall2;
	GLuint wall3;
    TexRect* background;
	GLuint mario;
	GLuint marioright;
	GLuint mariostand;
	GLuint mega;
	GLuint mob;
	GLuint laser;
	GLuint laser2;
	GLuint marioleft;
	GLuint heart;
	GLuint marioFire;

	~App();
};

#endif
