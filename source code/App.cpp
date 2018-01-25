#define _USE_MATH_DEFINES
#include "App.h"
#include <math.h>
#include <string.h>
#include <sstream>
using namespace std;

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h)
{
    mx = 0.0;
    my = 0.0;

	player = new ucm::Rectangle(-0.9f, -0.5f, 0.2f, 0.2f);
	c = new Circle(0.0f, 0.0f, 0.1f, 0.0f, 0.0f, 1.0f);
	ss[0] = new ucb::Heart(-0.9f, 0.9f, 0.1f, 0.1f);
	ss[1] = new ucb::Heart(-0.8f, 0.9f, 0.1f, 0.1f);
	ss[2] = new ucb::Heart(-0.7f, 0.9f, 0.1f, 0.1f);
	ss[3] = new ucb::Heart(-0.6f, 0.9f, 0.1f, 0.1f);
	e = new ucd::Enemy(0.0f, -0.5f, 0.2f, 0.2f);
	enemies.push_back(e);
	e = new ucd::Enemy(0.0f, 0.0f, 0.2f, 0.2f);
	enemies.push_back(e);

	marioFire = loadTexture("C:/Users/Jchen/Desktop/FinalProject/mariofire.bmp");
	mega = loadTexture("C:/Users/Jchen/Desktop/FinalProject/mega.bmp");
	laser = loadTexture("C:/Users/Jchen/Desktop/FinalProject/laser.bmp");
	laser2 = loadTexture("C:/Users/Jchen/Desktop/FinalProject/laser2.bmp");
    wall = loadTexture("C:/Users/Jchen/Desktop/FinalProject/mario.bmp");
	wall2 = loadTexture("C:/Users/Jchen/Desktop/FinalProject/wall.bmp");
	wall3 = loadTexture("C:/Users/Jchen/Desktop/FinalProject/wall2.bmp");
	background = new TexRect(-1, 1, 2, 2);
	mario = loadTexture("C:/Users/Jchen/Desktop/FinalProject/ma.bmp");
	marioright = loadTexture("C:/Users/Jchen/Desktop/FinalProject/marioright.bmp");
	marioleft = loadTexture("C:/Users/Jchen/Desktop/FinalProject/marioleft.bmp");
	mariostand = loadTexture("C:/Users/Jchen/Desktop/FinalProject/mariostand.bmp");
	heart = loadTexture("C:/Users/Jchen/Desktop/FinalProject/heart.bmp");

	move = true;
	right = true;
	theta = 0.0f;
	inc = 0.15f;
	shot = false;
	counter = 0;
	gameover = false;
	loop = true;
	jump = false;
	moveright = false;
	moveleft = false;
	eFire = false;
	backgroundSwitch = false;
	repeat = 0;
	speed = 0.01;
	showenemy = true;
	enemyleft = false;
	timebase = 0;
	life = 4;
}

GLuint App::loadTexture(const char *filename) 
{
    GLuint texture_id;
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    RgbImage theTexMap( filename );
    glGenTextures( 1, &texture_id );
    glBindTexture( GL_TEXTURE_2D, texture_id );
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(),GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
	return texture_id;
}

void DrawString(void *font, const char s[], float x, float y)
{
	unsigned int i;
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(x, y);
	for (i = 0; i<strlen(s); i++)
	{
		glutBitmapCharacter(font, s[i]);
	}
}

void App :: shoot()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		ucm::Rectangle * em = new ucm::Rectangle(enemies[i]->getX(), enemies[i]->getY(), 0.1f, 0.1f);
		enemyMissiles.push_back(em);
	}
}

void App::draw() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	std::string st = to_string(KillCount);
	char const *pchar = st.c_str();
	DrawString(GLUT_BITMAP_HELVETICA_18, pchar, 0.3f, 0.85f);

	std::string strn = "Kill Count:";
	char const *strng = strn.c_str();
	DrawString(GLUT_BITMAP_HELVETICA_18, strng, 0.1f, 0.85f);

	//Background switch check.
	if (player->getX() >= 0.9f && (backgroundCheck == 0))
	{
		backgroundCheck = 1;
		enemyMissileSpeed += 0.01;
		player->setX(-0.9f);
		enemies.clear();
		e = new ucd::Enemy(0.0f, -0.5f, 0.2f, 0.2f);
		enemies.push_back(e);
		e = new ucd::Enemy(0.0f, 0.0f, 0.2f, 0.2f);
		enemies.push_back(e);
	}
	if (player->getX() >= 0.9f && (backgroundCheck == 1))
	{
		backgroundCheck = 2;
		enemyMissileSpeed += 0.01;
		player->setX(-0.9f);
		enemies.clear();
		e = new ucd::Enemy(0.0f, -0.5f, 0.2f, 0.2f);
		enemies.push_back(e);
		e = new ucd::Enemy(0.0f, 0.0f, 0.2f, 0.2f);
		enemies.push_back(e);
	}

	if (player->getX() >= 0.9f && (backgroundCheck == 2))
	{
		backgroundCheck = 0;
		enemyMissileSpeed += 0.01;
		player->setX(-0.9f);
		enemies.clear();
		e = new ucd::Enemy(0.0f, -0.5f, 0.2f, 0.2f);
		enemies.push_back(e);
		e = new ucd::Enemy(0.0f, -0.1f, 0.2f, 0.2f);
		enemies.push_back(e);
	}
	
	//Animation checks.
	if (jump == false)
		glBindTexture(GL_TEXTURE_2D, mariostand);
	if (jump == true)
		glBindTexture(GL_TEXTURE_2D, mario);
	if (moveright == true)
		glBindTexture(GL_TEXTURE_2D, marioright);
	if (moveleft == true)
		glBindTexture(GL_TEXTURE_2D, marioleft);
	if (fire == true)
		glBindTexture(GL_TEXTURE_2D, marioFire);
	player->draw();

	for (int i = 0; i < enemyMissiles.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, laser2);
		enemyMissiles[i]->draw();
	}

	for (int i = 0; i < playerMissiles.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, laser);
		playerMissiles[i]->draw();
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, mega);
		enemies[i]->draw();
	}

	//Health bars
	for (int k = 0; k < life; k++)
	{
		glBindTexture(GL_TEXTURE_2D, heart);
		ss[k]->draw();
	}


    glColor3d(1.0, 1.0, 1.0);
	char* strn1 = "Game Over";
	if (life == 0) 
	{
		DrawString(GLUT_BITMAP_HELVETICA_18, strn1, -0.15, 0.0f);
	}
	//Background switching.
	if (backgroundCheck == 2)
		glBindTexture(GL_TEXTURE_2D, wall2);
	if (backgroundCheck == 1)
		glBindTexture(GL_TEXTURE_2D, wall3);
	if (backgroundCheck == 0)
		glBindTexture(GL_TEXTURE_2D, wall);
	background->draw();
	c->draw();
	glDisable(GL_TEXTURE_2D);
	glFlush();
	glutSwapBuffers();
}

void App::mouseDown(float x, float y)
{
    mx = x;
    my = y;
    redraw();
}

void App::mouseDrag(float x, float y)
{
    mx = x;
    my = y;
    redraw();
}

void App::keyPress(unsigned char key)
{
	if (key == 27)
	{
		exit(0);
	}
	else if (key == 'f' || key == 'F')
	{
		missleX = player->getX() + 0.03f;
		missleY = player->getY();
		counter++;

		ucm::Rectangle* m = new ucm::Rectangle(missleX + 0.15f, missleY - 0.05f, 0.1f, 0.1f, 1.0f, 1.0f, 0.0f);

		playerMissiles.push_back(m);
	}
	else if (key == 'd' || key == 'D')
	{
		moveright = true;
	}
	else if (key == 'a' || key == 'A')
	{
		moveleft = true;
	}
	else if (key == 32)
	{
		jump = true;
	}
}


void App::idle()
{
	if (loop)
	{
		time = glutGet(GLUT_ELAPSED_TIME);

		if (time - timebase < 20)
		{
			return;
		}

		timebase = time;

		if (e->getX() < 0.3f)
			enemyleft = false;

		if (e->getX() > 0.8f)
			enemyleft = true;

		if (enemyleft == true)
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i]->setX(enemies[i]->getX() - 0.01f);
			}
		}
		if (enemyleft == false)
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i]->setX(enemies[i]->getX() + 0.01f);
			}
		}
		//Background switch check.
		if (player->getX() >= 0.9f && (counter % 2 == 0))
		{
			backgroundSwitch = true;
			player->setX(-0.9f);
			e->Enemy::setX(0.9f);
			counter += 1;

		}
		if (player->getX() >= 0.9f && (counter % 2 == 1))
		{
			backgroundSwitch = false;
			player->setX(-0.9f);
			e->Enemy::setX(0.9f);
			counter += 1;
		}

		//mario movement
		if (moveleft == true)
		{
			float x = player->getX();
			if (x >= -0.97f)
				player->setX(x -= 0.05f);
			moveleft = false;
		}

		if (moveright == true)
		{
			float x = player->getX();
			player->setX(x += 0.05f);
			moveright = false;
		}

		if (jump == true && player->getY() <= -0.1)
		{
			float y = player->getY();
			player->setY(y += 0.04f);

			if (player->getY() >= -0.1)
				jump = false;
		}

		if (jump == false && player->getY() >= -0.47)
		{
			float y = player->getY();
			player->setY(y -= 0.04f);
		}

		repeat += 1;
		if (repeat % 40 == 0)
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				ucm::Rectangle * em = new ucm::Rectangle(enemies[i]->getX(), enemies[i]->getY(), 0.1f, 0.1f);
				enemyMissiles.push_back(em);
			}
		}

		int deleteThisMissile = -1;
		int deleteThisEnemy = -1;
		for (int i = 0; i < enemies.size(); i++)
		{
			for (int j = 0; j < playerMissiles.size(); j++)
			{
				if (enemies[i]->contains(playerMissiles[j]->getX(), playerMissiles[j]->getY()))
				{
					deleteThisEnemy = i;
					deleteThisMissile = j;
				}
			}
		}

		if (deleteThisMissile > -1 && deleteThisEnemy > -1)
		{
			enemies.erase(enemies.begin() + deleteThisEnemy);
			playerMissiles.erase(playerMissiles.begin() + deleteThisMissile);
			KillCount++;
		}

		for (int i = 0; i < playerMissiles.size(); i++)
		{
			playerMissiles[i]->setX(playerMissiles[i]->getX() + 0.03f);

			if (playerMissiles[i]->getX() > 0.9f)
				playerMissiles.erase(playerMissiles.begin() + i);
		}

		for (int i = 0; i < enemyMissiles.size(); i++)
		{
			if (player->contains(enemyMissiles[i]->getX(), enemyMissiles[i]->getY() - 0.01))
			{
				enemyMissiles.erase(enemyMissiles.begin() + i);
				life -= 1;
				if (life == 0) {
					gameover = true;
				}
				cout << "You have been HIT" << endl;
			}
		}

		for (int i = 0; i < enemyMissiles.size(); i++)
		{
			enemyMissiles[i]->setX(enemyMissiles[i]->getX() - enemyMissileSpeed);

			if (enemyMissiles[i]->getX() < -0.9f)
				enemyMissiles.erase(enemyMissiles.begin() + i);
		}

		// Update coordinates of enemy
		if (theta <= 2 * M_PI - inc)
			theta += inc;
		else
			theta = 0;

		c->setX(0.3f*cos(theta) + player->getX() + 0.5f * player->getW());
		c->setY(0.3f*sin(theta) + player->getY() - 0.5f * player->getH());

			                
		if (gameover == true)
		{
			cout << "You win!" << endl;
			if (counter == 1)
			{
				cout << counter << " shot was fired." << endl;
			}
			else
			{
				cout << counter << " shots were fired." << endl;
			}
			cout << "Press ESC to exit game." << endl;

			// Stop looping, otherwise final message will be displayed many times
			loop = false;
		}

		redraw();
	}
	}

	App::~App()
	{
		delete player;
		delete c;
		delete e;
	}
