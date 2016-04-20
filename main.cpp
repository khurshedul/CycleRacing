/*

  Final Project : A Cycle Racing
  

  Team Members :
  ---------------------------------

  1 . Barid, Khurshedul 		13-24026-2
  2 . Hossain, Md. Kief 		13-24867-2
  3 . Houque, Md. Ekramul 		13-24688-2
  4 . Iqbal , Mohammad Jafar 		12-21948-2



*/

#include<stdio.h>
#include <stdlib.h>
#include<limits.h>
#include<time.h>
#include<math.h>
#include<cstring>
#include<iostream>
#include<vector>

#include<GL/glut.h>

#define MAX_cycleS 3

void drawcycle();
void drawFootPath();
void drawDivider();
void drawSurroundings();
void stopGame();
void drawOthercycles(int);
void drawOther();
void setcycles();
void moveOthercycles();
int detectCollision();
void drawString(std::string);
void drawMainMenu();
void drawTime();
void drawEnd();
void stopGame();
void drawMessage();
void resumeGame();
void drawScore(int);
int score =0;
int foot_y = 200;
int div_y = 220;
int end_y = 160;


int a = 0;
int speed = 1;
int steerSpeed = 1;
int temp = 0;
int seconds = 0;
int distance = 178;


int game_state = 0;

void moveDivider();
void moveRoad();
void movecycle();
void periodicFunction(int);


int lane[MAX_cycleS];
int pos[MAX_cycleS];
int speeds[MAX_cycleS];
int speedsTemp[MAX_cycleS];

GLdouble width = 600, height = 400;

bool cycleMoveLeft = false, cycleMoveRight = false, cycleMoveFast = false, cycleStopped = false, gameStopped = false, horn = false;
bool highlightStart = false, highlightExit = false;
bool reachedEnd = false, gameCompleted = false;
//cycle variables
int cycle_x = 0;
int cycle_y = -100;



void maindisp()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	switch (game_state)
	{
	case 1: glClearColor(0.5, 0.5, 0.5, 0.0);
		drawFootPath();
		drawSurroundings();
		drawDivider();
		drawcycle();
		drawOther();
		drawTime();
		drawEnd();
		break;

	case 0: drawMainMenu();
		
		//drawDistanceBar();

		break;

	case 2: glClearColor(0.5, 0.5, 0.5, 0.0);
		drawFootPath();
		drawSurroundings();
		drawDivider();
		//if (gameCompleted)
		drawMessage();
		drawEnd();
		drawcycle();
		drawOther();
	
		drawTime();
		break;
	}

	glFlush();
	glutSwapBuffers();
}

void keyBoardFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: cycleMoveLeft = true; cycleMoveRight = false; break;
	case GLUT_KEY_RIGHT: cycleMoveRight = true; cycleMoveLeft = false; break;
	case GLUT_KEY_UP: cycleMoveFast = true; break;
	}
}

void keyboard_up_func(int k, int x, int y)
{
	switch (k)
	{
	case GLUT_KEY_LEFT: cycleMoveLeft = false;
		break;
	case GLUT_KEY_RIGHT:cycleMoveRight = false;
		break;

	case GLUT_KEY_UP: cycleMoveFast = false; break;
	case GLUT_KEY_DOWN: cycleStopped = false; break;
	}
}

void normalKeyBoardFunc(unsigned char key, int x, int y)
{
	if (game_state == 1)
	{
		switch (key)
		{
		//Horn
		case 'H':
		case 'h': horn = true; break;

		}
	}

	else if (game_state == 0)
	{
		if (key == 13)
		{
			setcycles();
			game_state = 1;
		}
	}
     else if (game_state == 2)
	{
		if (key == 13)
		{       gameStopped=false;
			//drawcycle();
                       // glTranslated(cycle_x, cycle_y, 0.0);
			setcycles();
			cycle_x=0, cycle_y=-100;
			//glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
			score=0;
			game_state = 1;
			seconds=0;
		}
	}
}

void mouse_func(int button, int state, int x, int y)
{
	switch (game_state)
	{
	case 0: if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (x >= 630 && x <= 810 && y >= 320 && y <= 405)
		{
			//gameStopped = false;
			setcycles();
			game_state = 1;
		}

		else if (x >= 630 && x <= 810 && y >= 490 && y <= 575)
			exit(0);
	}
			break;

	case 2: if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (x >= 630 && x <= 810 && y >= 320 && y <= 405)
		{
			gameStopped = false;
			gameCompleted = false;
			reachedEnd = false;
			seconds = 0;
			distance = 178;
			
		
			end_y = 160;
			setcycles();
			game_state = 1;
			cycle_x = 0;
		}

		else if (x >= 630 && x <= 810 && y >= 490 && y <= 575)
			exit(0);
	}
			break;



	}
}

void mouse_hover(int x, int y)
{
	if (x >= 630 && x <= 810 && y >= 320 && y <= 405)
	{
		highlightStart = true;
		highlightExit = false;
	}

	else if (x >= 630 && x <= 810 && y >= 490 && y <= 575)
	{
		highlightStart = false;
		highlightExit = true;
	}

	else
	{
		highlightExit = false;
		highlightStart = false;
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize((int)width, (int)height);
	glutCreateWindow("Cycle racing !!!!!!!");
	//	glutFullScreen();

	gluOrtho2D(-240, 240.0, -160, 160.0);

	glutDisplayFunc(maindisp);
	glutTimerFunc(100, periodicFunction, 0);

	glutSpecialFunc(keyBoardFunc);
	glutSpecialUpFunc(keyboard_up_func);
	glutKeyboardFunc(normalKeyBoardFunc);
	glutMouseFunc(mouse_func);
	glutPassiveMotionFunc(mouse_hover);

	glutMainLoop();
	return 0;
}

//This function draws a cycle at (cycle_x, cycle_y)

void drawcycle(){
     glPushMatrix();
     glTranslated(cycle_x, cycle_y, 0.0);


	glRotatef(90,0,0,1);
	glScalef(2,2,4);

	glBegin(GL_TRIANGLES);
	glColor3f(0.34, 1.0, 1.0);
    glVertex3f(-7.533967,0.185733,0.0);
    glVertex3f(12.927628,-0.285263,0.0);
    glVertex3f(-7.533967,-0.285263,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(12.927628,-0.285263,0.0);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(-7.533967,-0.285263,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(5.796542,-4.708093,0.0);
    glVertex3f(5.419581,-4.708093,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.580334,-0.397233,0.0);
    glVertex3f(6.208558,-2.903887,0.0);
    glVertex3f(5.796542,-4.708093,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.336275,-2.201439,0.0);
    glVertex3f(6.600454,-2.903887,0.0);
    glVertex3f(6.208558,-2.903887,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.600454,-2.903887,0.0);
    glVertex3f(6.439872,-3.827642,0.0);
    glVertex3f(6.208558,-2.903887,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.59308,-3.827642,0.0);
    glVertex3f(6.712009,-4.094733,0.0);
    glVertex3f(6.439872,-3.827642,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.803168,-2.201439,0.0);
    glVertex3f(7.065145,-1.400044,0.0);
    glVertex3f(7.17499,-1.491234,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-7.533967,-0.285263,0.0);
    glVertex3f(-2.99355,-0.405407,0.0);
    glVertex3f(-4.999282,-0.389059,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.99355,-0.405407,0.0);
    glVertex3f(-4.275207,-0.92682,0.0);
    glVertex3f(-4.999282,-0.389059,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.99355,-0.405407,0.0);
    glVertex3f(-1.57044,-0.514514,0.0);
    glVertex3f(-2.023491,-0.514917,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.023491,-0.514917,0.0);
    glVertex3f(-3.36152,-1.104432,-0.0);
    glVertex3f(-3.472295,-0.864565,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(-0.095335,-0.53625,0.0);
    glVertex3f(-1.57044,-0.514514,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.095335,-0.53625,0.0);
    glVertex3f(-0.099977,-0.698496,-0.0);
    glVertex3f(-0.191713,-0.569639,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.191713,-0.569639,-0.0);
    glVertex3f(-2.294826,-1.036422,-0.0);
    glVertex3f(-2.27351,-0.879689,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.294826,-1.036422,-0.0);
    glVertex3f(-2.613698,-0.879689,-0.0);
    glVertex3f(-2.27351,-0.879689,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.062836,-0.537491,0.0);
    glVertex3f(1.693749,-0.592462,0.0);
    glVertex3f(1.300179,-0.601452,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(1.300179,-0.601452,0.0);
    glVertex3f(1.693749,-0.884052,0.0);
    glVertex3f(1.300179,-0.893042,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(1.300179,-0.893042,0.0);
    glVertex3f(0.878993,-0.766478,0.0);
    glVertex3f(1.300179,-0.601452,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.878993,-0.922409,0.0);
    glVertex3f(0.295815,-0.896073,-0.0);
    glVertex3f(0.878993,-0.766478,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.295815,-0.896073,-0.0);
    glVertex3f(-0.708549,-1.035805,-0.0);
    glVertex3f(-0.708549,-0.879874,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.708549,-1.035805,-0.0);
    glVertex3f(-0.464357,-1.093567,-0.0);
    glVertex3f(-0.596354,-1.091438,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.596354,-1.091438,-0.0);
    glVertex3f(-0.480556,-2.049332,-0.0);
    glVertex3f(-0.612552,-2.047203,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.480556,-2.049332,-0.0);
    glVertex3f(-0.176996,-1.407829,-0.0);
    glVertex3f(-0.184739,-1.864666,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.612552,-2.047203,-0.0);
    glVertex3f(-0.859743,-1.387821,-0.0);
    glVertex3f(-0.596354,-1.091438,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(12.927628,0.129748,0.0);
    glVertex3f(-7.533967,-0.341248,0.0);
    glVertex3f(-7.533967,0.129748,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,0.241718,0.0);
    glVertex3f(12.927628,0.129748,0.0);
    glVertex3f(-7.533967,0.129748,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,0.241718,0.0);
    glVertex3f(5.796542,4.552578,0.0);
    glVertex3f(6.580334,0.241718,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.208558,2.748373,0.0);
    glVertex3f(6.580334,0.241718,0.0);
    glVertex3f(5.796542,4.552578,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.600454,2.748373,0.0);
    glVertex3f(6.336275,2.045924,0.0);
    glVertex3f(6.208558,2.748373,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.439872,3.672128,0.0);
    glVertex3f(6.600454,2.748373,0.0);
    glVertex3f(6.208558,2.748373,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.712009,3.939219,0.0);
    glVertex3f(6.59308,3.672128,0.0);
    glVertex3f(6.439872,3.672128,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.803168,2.045924,0.0);
    glVertex3f(7.065145,1.244529,0.0);
    glVertex3f(6.336275,2.045924,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-7.533967,0.129748,0.0);
    glVertex3f(-2.99355,0.249893,0.0);
    glVertex3f(6.203372,0.241718,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-4.275207,0.771305,0.0);
    glVertex3f(-2.99355,0.249893,0.0);
    glVertex3f(-4.999282,0.233544,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.99355,0.249893,0.0);
    glVertex3f(-1.57044,0.359,0.0);
    glVertex3f(6.203372,0.241718,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.023491,0.359403,0.0);
    glVertex3f(-3.36152,0.948918,-0.0);
    glVertex3f(-1.57044,0.359,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.095335,0.380736,0.0);
    glVertex3f(6.203372,0.241718,0.0);
    glVertex3f(-1.57044,0.359,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.095335,0.380736,0.0);
    glVertex3f(-0.099977,0.542981,-0.0);
    glVertex3f(0.062836,0.381977,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.191713,0.414124,-0.0);
    glVertex3f(-2.294826,0.880908,-0.0);
    glVertex3f(-0.099977,0.542981,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.613698,0.724174,-0.0);
    glVertex3f(-2.294826,0.880908,-0.0);
    glVertex3f(-2.27351,0.724174,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.062836,0.381977,0.0);
    glVertex3f(1.693749,0.436948,0.0);
    glVertex3f(6.203372,0.241718,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(1.300179,0.445938,0.0);
    glVertex3f(1.693749,0.728537,0.0);
    glVertex3f(1.693749,0.436948,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.878993,0.610964,0.0);
    glVertex3f(1.300179,0.737527,0.0);
    glVertex3f(1.300179,0.445938,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.295815,0.740559,-0.0);
    glVertex3f(0.878993,0.766894,0.0);
    glVertex3f(0.878993,0.610964,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.295815,0.740559,-0.0);
    glVertex3f(-0.708549,0.88029,-0.0);
    glVertex3f(0.295815,0.89649,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.708549,0.88029,-0.0);
    glVertex3f(-0.464357,0.938053,-0.0);
    glVertex3f(0.295815,0.89649,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.596354,0.935924,-0.0);
    glVertex3f(-0.480556,1.893818,-0.0);
    glVertex3f(-0.464357,0.938053,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.480556,1.893818,-0.0);
    glVertex3f(-0.176996,1.252314,-0.0);
    glVertex3f(-0.464357,0.938053,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.859743,1.232307,-0.0);
    glVertex3f(-0.612552,1.891689,-0.0);
    glVertex3f(-0.596354,0.935924,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-7.533967,0.185733,0.0);
    glVertex3f(12.927628,0.185733,0.0);
    glVertex3f(12.927628,-0.285263,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(12.927628,-0.285263,0.0);
    glVertex3f(6.580334,-0.397233,0.0);
    glVertex3f(6.203372,-0.397233,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(6.580334,-0.397233,0.0);
    glVertex3f(5.796542,-4.708093,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.580334,-0.397233,0.0);
    glVertex3f(6.336275,-2.201439,0.0);
    glVertex3f(6.208558,-2.903887,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.336275,-2.201439,0.0);
    glVertex3f(6.803168,-2.201439,0.0);
    glVertex3f(6.600454,-2.903887,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.600454,-2.903887,0.0);
    glVertex3f(6.59308,-3.827642,0.0);
    glVertex3f(6.439872,-3.827642,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.59308,-3.827642,0.0);
    glVertex3f(6.768824,-3.952448,0.0);
    glVertex3f(6.712009,-4.094733,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.803168,-2.201439,0.0);
    glVertex3f(6.336275,-2.201439,0.0);
    glVertex3f(7.065145,-1.400044,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-7.533967,-0.285263,0.0);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(-2.99355,-0.405407,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.99355,-0.405407,0.0);
    glVertex3f(-3.717626,-0.931364,0.0);
    glVertex3f(-4.275207,-0.92682,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.99355,-0.405407,0.0);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(-1.57044,-0.514514,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.023491,-0.514917,0.0);
    glVertex3f(-1.57044,-0.514514,0.0);
    glVertex3f(-3.36152,-1.104432,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(0.062836,-0.537491,0.0);
    glVertex3f(-0.095335,-0.53625,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.095335,-0.53625,0.0);
    glVertex3f(0.062836,-0.537491,0.0);
    glVertex3f(-0.099977,-0.698496,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.191713,-0.569639,-0.0);
    glVertex3f(-0.099977,-0.698496,-0.0);
    glVertex3f(-2.294826,-1.036422,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.294826,-1.036422,-0.0);
    glVertex3f(-2.635014,-1.036422,-0.0);
    glVertex3f(-2.613698,-0.879689,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.062836,-0.537491,0.0);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(1.693749,-0.592462,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(1.300179,-0.601452,0.0);
    glVertex3f(1.693749,-0.592462,0.0);
    glVertex3f(1.693749,-0.884052,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(1.300179,-0.893042,0.0);
    glVertex3f(0.878993,-0.922409,0.0);
    glVertex3f(0.878993,-0.766478,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.878993,-0.922409,0.0);
    glVertex3f(0.295815,-1.052004,-0.0);
    glVertex3f(0.295815,-0.896073,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.295815,-0.896073,-0.0);
    glVertex3f(0.295815,-1.052004,-0.0);
    glVertex3f(-0.708549,-1.035805,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.708549,-1.035805,-0.0);
    glVertex3f(0.295815,-1.052004,-0.0);
    glVertex3f(-0.464357,-1.093567,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.596354,-1.091438,-0.0);
    glVertex3f(-0.464357,-1.093567,-0.0);
    glVertex3f(-0.480556,-2.049332,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.480556,-2.049332,-0.0);
    glVertex3f(-0.464357,-1.093567,-0.0);
    glVertex3f(-0.176996,-1.407829,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.612552,-2.047203,-0.0);
    glVertex3f(-0.867542,-1.848017,-0.0);
    glVertex3f(-0.859743,-1.387821,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(12.927628,0.129748,0.0);
    glVertex3f(12.927628,-0.341248,0.0);
    glVertex3f(-7.533967,-0.341248,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,0.241718,0.0);
    glVertex3f(6.580334,0.241718,0.0);
    glVertex3f(12.927628,0.129748,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,0.241718,0.0);
    glVertex3f(5.419581,4.552578,0.0);
    glVertex3f(5.796542,4.552578,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.208558,2.748373,0.0);
    glVertex3f(6.336275,2.045924,0.0);
    glVertex3f(6.580334,0.241718,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.600454,2.748373,0.0);
    glVertex3f(6.803168,2.045924,0.0);
    glVertex3f(6.336275,2.045924,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.439872,3.672128,0.0);
    glVertex3f(6.59308,3.672128,0.0);
    glVertex3f(6.600454,2.748373,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.712009,3.939219,0.0);
    glVertex3f(6.768824,3.796934,0.0);
    glVertex3f(6.59308,3.672128,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.803168,2.045924,0.0);
    glVertex3f(7.17499,1.33572,0.0);
    glVertex3f(7.065145,1.244529,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-7.533967,0.129748,0.0);
    glVertex3f(-4.999282,0.233544,0.0);
    glVertex3f(-2.99355,0.249893,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-4.275207,0.771305,0.0);
    glVertex3f(-3.717626,0.77585,0.0);
    glVertex3f(-2.99355,0.249893,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.99355,0.249893,0.0);
    glVertex3f(-2.023491,0.359403,0.0);
    glVertex3f(-1.57044,0.359,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.023491,0.359403,0.0);
    glVertex3f(-3.472295,0.709051,-0.0);
    glVertex3f(-3.36152,0.948918,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.095335,0.380736,0.0);
    glVertex3f(0.062836,0.381977,0.0);
    glVertex3f(6.203372,0.241718,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.095335,0.380736,0.0);
    glVertex3f(-0.191713,0.414124,-0.0);
    glVertex3f(-0.099977,0.542981,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.191713,0.414124,-0.0);
    glVertex3f(-2.27351,0.724174,-0.0);
    glVertex3f(-2.294826,0.880908,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.613698,0.724174,-0.0);
    glVertex3f(-2.635014,0.880908,-0.0);
    glVertex3f(-2.294826,0.880908,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.062836,0.381977,0.0);
    glVertex3f(1.300179,0.445938,0.0);
    glVertex3f(1.693749,0.436948,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(1.300179,0.445938,0.0);
    glVertex3f(1.300179,0.737527,0.0);
    glVertex3f(1.693749,0.728537,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.878993,0.610964,0.0);
    glVertex3f(0.878993,0.766894,0.0);
    glVertex3f(1.300179,0.737527,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.295815,0.740559,-0.0);
    glVertex3f(0.295815,0.89649,-0.0);
    glVertex3f(0.878993,0.766894,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.295815,0.740559,-0.0);
    glVertex3f(-0.708549,0.72436,-0.0);
    glVertex3f(-0.708549,0.88029,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.708549,0.88029,-0.0);
    glVertex3f(-0.596354,0.935924,-0.0);
    glVertex3f(-0.464357,0.938053,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.596354,0.935924,-0.0);
    glVertex3f(-0.612552,1.891689,-0.0);
    glVertex3f(-0.480556,1.893818,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.480556,1.893818,-0.0);
    glVertex3f(-0.184739,1.709152,-0.0);
    glVertex3f(-0.176996,1.252314,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.859743,1.232307,-0.0);
    glVertex3f(-0.867542,1.692503,-0.0);
    glVertex3f(-0.612552,1.891689,-0.0);
    glEnd();

	glPopMatrix();
}


void drawOthercycles(int i)
{
	glPushMatrix();

	glTranslated((lane[i] - 1) * 37, pos[i], 0.0);

	switch (speeds[i])
	{
	case 2: glColor3f(0.0, 1.0, 0.0); break;
	case 3: glColor3f(0.0, 0.0, 1.0); break;
	case 4:
	case 5:
	case 6:
	case 7: glColor3f(1.0, 0.0, 0.0); break;
	case 0: glColor3f(0.0, 0.0, 0.0); break;
	}
  

	glRotatef(90,0,0,1);
	glScalef(2,2,4);

	glBegin(GL_TRIANGLES);
    glVertex3f(-7.533967,0.185733,0.0);
    glVertex3f(12.927628,-0.285263,0.0);
    glVertex3f(-7.533967,-0.285263,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(12.927628,-0.285263,0.0);
    glVertex3f(6.203372,-0.397233,0.0);

    glVertex3f(-7.533967,-0.285263,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(5.796542,-4.708093,0.0);
    glVertex3f(5.419581,-4.708093,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.580334,-0.397233,0.0);
    glVertex3f(6.208558,-2.903887,0.0);
    glVertex3f(5.796542,-4.708093,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.336275,-2.201439,0.0);
    glVertex3f(6.600454,-2.903887,0.0);
    glVertex3f(6.208558,-2.903887,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.600454,-2.903887,0.0);
    glVertex3f(6.439872,-3.827642,0.0);
    glVertex3f(6.208558,-2.903887,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.59308,-3.827642,0.0);
    glVertex3f(6.712009,-4.094733,0.0);
    glVertex3f(6.439872,-3.827642,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.803168,-2.201439,0.0);
    glVertex3f(7.065145,-1.400044,0.0);
    glVertex3f(7.17499,-1.491234,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-7.533967,-0.285263,0.0);
    glVertex3f(-2.99355,-0.405407,0.0);
    glVertex3f(-4.999282,-0.389059,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.99355,-0.405407,0.0);
    glVertex3f(-4.275207,-0.92682,0.0);
    glVertex3f(-4.999282,-0.389059,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.99355,-0.405407,0.0);
    glVertex3f(-1.57044,-0.514514,0.0);
    glVertex3f(-2.023491,-0.514917,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.023491,-0.514917,0.0);
    glVertex3f(-3.36152,-1.104432,-0.0);
    glVertex3f(-3.472295,-0.864565,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(-0.095335,-0.53625,0.0);
    glVertex3f(-1.57044,-0.514514,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.095335,-0.53625,0.0);
    glVertex3f(-0.099977,-0.698496,-0.0);
    glVertex3f(-0.191713,-0.569639,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.191713,-0.569639,-0.0);
    glVertex3f(-2.294826,-1.036422,-0.0);
    glVertex3f(-2.27351,-0.879689,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.294826,-1.036422,-0.0);
    glVertex3f(-2.613698,-0.879689,-0.0);
    glVertex3f(-2.27351,-0.879689,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.062836,-0.537491,0.0);
    glVertex3f(1.693749,-0.592462,0.0);
    glVertex3f(1.300179,-0.601452,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(1.300179,-0.601452,0.0);
    glVertex3f(1.693749,-0.884052,0.0);
    glVertex3f(1.300179,-0.893042,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(1.300179,-0.893042,0.0);
    glVertex3f(0.878993,-0.766478,0.0);
    glVertex3f(1.300179,-0.601452,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.878993,-0.922409,0.0);
    glVertex3f(0.295815,-0.896073,-0.0);
    glVertex3f(0.878993,-0.766478,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.295815,-0.896073,-0.0);
    glVertex3f(-0.708549,-1.035805,-0.0);
    glVertex3f(-0.708549,-0.879874,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.708549,-1.035805,-0.0);
    glVertex3f(-0.464357,-1.093567,-0.0);
    glVertex3f(-0.596354,-1.091438,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.596354,-1.091438,-0.0);
    glVertex3f(-0.480556,-2.049332,-0.0);
    glVertex3f(-0.612552,-2.047203,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.480556,-2.049332,-0.0);
    glVertex3f(-0.176996,-1.407829,-0.0);
    glVertex3f(-0.184739,-1.864666,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.612552,-2.047203,-0.0);
    glVertex3f(-0.859743,-1.387821,-0.0);
    glVertex3f(-0.596354,-1.091438,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(12.927628,0.129748,0.0);
    glVertex3f(-7.533967,-0.341248,0.0);
    glVertex3f(-7.533967,0.129748,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,0.241718,0.0);
    glVertex3f(12.927628,0.129748,0.0);
    glVertex3f(-7.533967,0.129748,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,0.241718,0.0);
    glVertex3f(5.796542,4.552578,0.0);
    glVertex3f(6.580334,0.241718,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.208558,2.748373,0.0);
    glVertex3f(6.580334,0.241718,0.0);
    glVertex3f(5.796542,4.552578,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.600454,2.748373,0.0);
    glVertex3f(6.336275,2.045924,0.0);
    glVertex3f(6.208558,2.748373,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.439872,3.672128,0.0);
    glVertex3f(6.600454,2.748373,0.0);
    glVertex3f(6.208558,2.748373,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.712009,3.939219,0.0);
    glVertex3f(6.59308,3.672128,0.0);
    glVertex3f(6.439872,3.672128,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.803168,2.045924,0.0);
    glVertex3f(7.065145,1.244529,0.0);
    glVertex3f(6.336275,2.045924,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-7.533967,0.129748,0.0);
    glVertex3f(-2.99355,0.249893,0.0);
    glVertex3f(6.203372,0.241718,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-4.275207,0.771305,0.0);
    glVertex3f(-2.99355,0.249893,0.0);
    glVertex3f(-4.999282,0.233544,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.99355,0.249893,0.0);
    glVertex3f(-1.57044,0.359,0.0);
    glVertex3f(6.203372,0.241718,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.023491,0.359403,0.0);
    glVertex3f(-3.36152,0.948918,-0.0);
    glVertex3f(-1.57044,0.359,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.095335,0.380736,0.0);
    glVertex3f(6.203372,0.241718,0.0);
    glVertex3f(-1.57044,0.359,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.095335,0.380736,0.0);
    glVertex3f(-0.099977,0.542981,-0.0);
    glVertex3f(0.062836,0.381977,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.191713,0.414124,-0.0);
    glVertex3f(-2.294826,0.880908,-0.0);
    glVertex3f(-0.099977,0.542981,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.613698,0.724174,-0.0);
    glVertex3f(-2.294826,0.880908,-0.0);
    glVertex3f(-2.27351,0.724174,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.062836,0.381977,0.0);
    glVertex3f(1.693749,0.436948,0.0);
    glVertex3f(6.203372,0.241718,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(1.300179,0.445938,0.0);
    glVertex3f(1.693749,0.728537,0.0);
    glVertex3f(1.693749,0.436948,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.878993,0.610964,0.0);
    glVertex3f(1.300179,0.737527,0.0);
    glVertex3f(1.300179,0.445938,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.295815,0.740559,-0.0);
    glVertex3f(0.878993,0.766894,0.0);
    glVertex3f(0.878993,0.610964,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.295815,0.740559,-0.0);
    glVertex3f(-0.708549,0.88029,-0.0);
    glVertex3f(0.295815,0.89649,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.708549,0.88029,-0.0);
    glVertex3f(-0.464357,0.938053,-0.0);
    glVertex3f(0.295815,0.89649,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.596354,0.935924,-0.0);
    glVertex3f(-0.480556,1.893818,-0.0);
    glVertex3f(-0.464357,0.938053,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.480556,1.893818,-0.0);
    glVertex3f(-0.176996,1.252314,-0.0);
    glVertex3f(-0.464357,0.938053,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.859743,1.232307,-0.0);
    glVertex3f(-0.612552,1.891689,-0.0);
    glVertex3f(-0.596354,0.935924,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-7.533967,0.185733,0.0);
    glVertex3f(12.927628,0.185733,0.0);
    glVertex3f(12.927628,-0.285263,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(12.927628,-0.285263,0.0);
    glVertex3f(6.580334,-0.397233,0.0);
    glVertex3f(6.203372,-0.397233,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(6.580334,-0.397233,0.0);
    glVertex3f(5.796542,-4.708093,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.580334,-0.397233,0.0);
    glVertex3f(6.336275,-2.201439,0.0);
    glVertex3f(6.208558,-2.903887,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.336275,-2.201439,0.0);
    glVertex3f(6.803168,-2.201439,0.0);
    glVertex3f(6.600454,-2.903887,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.600454,-2.903887,0.0);
    glVertex3f(6.59308,-3.827642,0.0);
    glVertex3f(6.439872,-3.827642,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.59308,-3.827642,0.0);
    glVertex3f(6.768824,-3.952448,0.0);
    glVertex3f(6.712009,-4.094733,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.803168,-2.201439,0.0);
    glVertex3f(6.336275,-2.201439,0.0);
    glVertex3f(7.065145,-1.400044,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-7.533967,-0.285263,0.0);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(-2.99355,-0.405407,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.99355,-0.405407,0.0);
    glVertex3f(-3.717626,-0.931364,0.0);
    glVertex3f(-4.275207,-0.92682,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.99355,-0.405407,0.0);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(-1.57044,-0.514514,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.023491,-0.514917,0.0);
    glVertex3f(-1.57044,-0.514514,0.0);
    glVertex3f(-3.36152,-1.104432,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(0.062836,-0.537491,0.0);
    glVertex3f(-0.095335,-0.53625,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.095335,-0.53625,0.0);
    glVertex3f(0.062836,-0.537491,0.0);
    glVertex3f(-0.099977,-0.698496,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.191713,-0.569639,-0.0);
    glVertex3f(-0.099977,-0.698496,-0.0);
    glVertex3f(-2.294826,-1.036422,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.294826,-1.036422,-0.0);
    glVertex3f(-2.635014,-1.036422,-0.0);
    glVertex3f(-2.613698,-0.879689,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.062836,-0.537491,0.0);
    glVertex3f(6.203372,-0.397233,0.0);
    glVertex3f(1.693749,-0.592462,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(1.300179,-0.601452,0.0);
    glVertex3f(1.693749,-0.592462,0.0);
    glVertex3f(1.693749,-0.884052,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(1.300179,-0.893042,0.0);
    glVertex3f(0.878993,-0.922409,0.0);
    glVertex3f(0.878993,-0.766478,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.878993,-0.922409,0.0);
    glVertex3f(0.295815,-1.052004,-0.0);
    glVertex3f(0.295815,-0.896073,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.295815,-0.896073,-0.0);
    glVertex3f(0.295815,-1.052004,-0.0);
    glVertex3f(-0.708549,-1.035805,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.708549,-1.035805,-0.0);
    glVertex3f(0.295815,-1.052004,-0.0);
    glVertex3f(-0.464357,-1.093567,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.596354,-1.091438,-0.0);
    glVertex3f(-0.464357,-1.093567,-0.0);
    glVertex3f(-0.480556,-2.049332,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.480556,-2.049332,-0.0);
    glVertex3f(-0.464357,-1.093567,-0.0);
    glVertex3f(-0.176996,-1.407829,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.612552,-2.047203,-0.0);
    glVertex3f(-0.867542,-1.848017,-0.0);
    glVertex3f(-0.859743,-1.387821,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(12.927628,0.129748,0.0);
    glVertex3f(12.927628,-0.341248,0.0);
    glVertex3f(-7.533967,-0.341248,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,0.241718,0.0);
    glVertex3f(6.580334,0.241718,0.0);
    glVertex3f(12.927628,0.129748,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.203372,0.241718,0.0);
    glVertex3f(5.419581,4.552578,0.0);
    glVertex3f(5.796542,4.552578,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.208558,2.748373,0.0);
    glVertex3f(6.336275,2.045924,0.0);
    glVertex3f(6.580334,0.241718,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.600454,2.748373,0.0);
    glVertex3f(6.803168,2.045924,0.0);
    glVertex3f(6.336275,2.045924,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.439872,3.672128,0.0);
    glVertex3f(6.59308,3.672128,0.0);
    glVertex3f(6.600454,2.748373,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.712009,3.939219,0.0);
    glVertex3f(6.768824,3.796934,0.0);
    glVertex3f(6.59308,3.672128,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(6.803168,2.045924,0.0);
    glVertex3f(7.17499,1.33572,0.0);
    glVertex3f(7.065145,1.244529,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-7.533967,0.129748,0.0);
    glVertex3f(-4.999282,0.233544,0.0);
    glVertex3f(-2.99355,0.249893,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-4.275207,0.771305,0.0);
    glVertex3f(-3.717626,0.77585,0.0);
    glVertex3f(-2.99355,0.249893,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.99355,0.249893,0.0);
    glVertex3f(-2.023491,0.359403,0.0);
    glVertex3f(-1.57044,0.359,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.023491,0.359403,0.0);
    glVertex3f(-3.472295,0.709051,-0.0);
    glVertex3f(-3.36152,0.948918,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.095335,0.380736,0.0);
    glVertex3f(0.062836,0.381977,0.0);
    glVertex3f(6.203372,0.241718,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.095335,0.380736,0.0);
    glVertex3f(-0.191713,0.414124,-0.0);
    glVertex3f(-0.099977,0.542981,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.191713,0.414124,-0.0);
    glVertex3f(-2.27351,0.724174,-0.0);
    glVertex3f(-2.294826,0.880908,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.613698,0.724174,-0.0);
    glVertex3f(-2.635014,0.880908,-0.0);
    glVertex3f(-2.294826,0.880908,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.062836,0.381977,0.0);
    glVertex3f(1.300179,0.445938,0.0);
    glVertex3f(1.693749,0.436948,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(1.300179,0.445938,0.0);
    glVertex3f(1.300179,0.737527,0.0);
    glVertex3f(1.693749,0.728537,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.878993,0.610964,0.0);
    glVertex3f(0.878993,0.766894,0.0);
    glVertex3f(1.300179,0.737527,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.295815,0.740559,-0.0);
    glVertex3f(0.295815,0.89649,-0.0);
    glVertex3f(0.878993,0.766894,0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0.295815,0.740559,-0.0);
    glVertex3f(-0.708549,0.72436,-0.0);
    glVertex3f(-0.708549,0.88029,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.708549,0.88029,-0.0);
    glVertex3f(-0.596354,0.935924,-0.0);
    glVertex3f(-0.464357,0.938053,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.596354,0.935924,-0.0);
    glVertex3f(-0.612552,1.891689,-0.0);
    glVertex3f(-0.480556,1.893818,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.480556,1.893818,-0.0);
    glVertex3f(-0.184739,1.709152,-0.0);
    glVertex3f(-0.176996,1.252314,-0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.859743,1.232307,-0.0);
    glVertex3f(-0.867542,1.692503,-0.0);
    glVertex3f(-0.612552,1.891689,-0.0);
    glEnd();

	glPopMatrix();
	
        

}
void drawFootPath()
{
	int i, y;
	glPushMatrix();

	//Draw right side foot path
	glTranslated(60, 0, 0);
	y = foot_y + 20;

	for (i = 0; i < 20; i++)
	{
		if (a == 0)
		{
			if (i % 2 == 0)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(1.0, 1.0, 0.0);
		}

		else
		{
			if (i % 2 == 1)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(1.0, 1.0, 0.0);
		}


		y -= 20;
		glRectd(5, y, -5, y - 20);
	}
	glPopMatrix();

	//Draw left side foot path
	glPushMatrix();
	glTranslated(-60, 0, 0);

	y = foot_y + 20;
	for (i = 0; i < 20; i++)
	{

		if (a == 0)
		{
			if (i % 2 == 0)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(1.0, 1.0, 0.0);
		}

		else
		{
			if (i % 2 == 1)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(1.0, 1.0, 0.0);
		}

		y -= 20;
		glRectd(5, y, -5, y - 20);
	}
	glPopMatrix();

}

void drawDivider()
{
	int i;
	int y = div_y + 80;
	glColor3f(1.0, 1.0, 1.0);

	//Draw left divider

	for (i = 0; i < 8; i++)
	{
		y -= 80;
		glRectd(22, y, 18, y - 40);
		glRectd(-18, y, -22, y - 40);
	}

}

void drawSurroundings()
{
	glColor3f(0.0, 1.6, 1.0);
	glRectd(240, 160, 65, -160);
	glRectd(-240, 160, -65, -160);
}

void stopGame()
{
	speed = 0;
	steerSpeed = 0;
}

void resumeGame()
{
	speed = 2;
	steerSpeed = 1;
}

void drawOther()
{
	int i;
	for (i = 0; i < MAX_cycleS; i++)
	{
		drawOthercycles(i);
	}
}

void setcycles()
{
	int i;
	for (i = 0; i < MAX_cycleS; i++)
	{
		lane[i] = i;
		pos[i] = 110 + rand() % 100;
		speeds[i] = 1 + i + rand() % 4;
	}
}

void moveDivider()
{
	div_y -= speed;
	if (div_y < 120 && distance > 0)
	{
		div_y = 200;
		distance -= 1;
	

		if (distance < 5)
			reachedEnd = true;

	}
}

void movecycle()
{
	if (cycleMoveLeft)
		cycle_x -= steerSpeed;


	else if (cycleMoveRight)
		cycle_x += steerSpeed;

	if (cycle_x > 45 || cycle_x < -45)
	{
		
		game_state = 2;
		gameStopped = true;
		
	}
}

void moveRoad()
{
	foot_y -= speed;
	if (foot_y < 160)
	{
		foot_y = 180;
		if (a == 0)
			a = 1;
		else
			a = 0;
	}
}

void periodicFunction(int v)
{
	if (gameStopped){
		stopGame();
		drawMessage();		
}

	else
		resumeGame();

	if (speed != 0)
	{
		if (cycleMoveFast)
			speed = 6;

		else
			speed = 2;

	}


	moveRoad();
	moveDivider();
	movecycle();
	moveOthercycles();
	
	

	if (!detectCollision() && !gameStopped && game_state == 1)
		temp += 15;

	if (temp > 1000)
	{
		temp = 0;
		seconds++;
	}

	glutPostRedisplay();
	glutTimerFunc(10, periodicFunction, v);
}

void moveOthercycles()
{
	int i;
	for (i = 0; i < MAX_cycleS; i++)
	{
		pos[i] += -speed + speeds[i];

		if (pos[i] < -200 || pos[i] > 200)
		{
			pos[i] = 200 + rand() % 100;
			speeds[i] = 2 + rand() % 4;
		}
		//if((speeds[0] == speeds[1]) && (speeds[1] == speeds[2]))
		//  speeds[1]--;

	}

	if (horn)
	{
		speeds[(cycle_x + 60) / 40]++;
		if (speeds[(cycle_x + 60) / 40] > 7)
			speeds[(cycle_x + 60) / 40] = 7;
		horn = false;
	}
}

int detectCollision()
{
	if (game_state != 1)
		return 0;

	int i, limit;
	for (i = 0; i < MAX_cycleS; i++)
	{
		if (pos[i] < -70 && pos[i] > -130)
		{
			limit = (i - 1) * 40;
			if (cycle_x < limit + 22 && cycle_x > limit - 22)
			{
				speeds[i] = 0;
				gameStopped = true;
				game_state = 2;
				return 1;
			}
		}
	}


	return 0;

}

void draw_string(std::string str)
{
	for (unsigned int i = 0; i<str.length(); i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *(str.begin() + i));
	}
}
void drawMessage()
{

	//Draw start button
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawFootPath();
	drawSurroundings();
	drawDivider();
	drawcycle();

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslated(0, 30, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(30, 15);
	glVertex2f(30, -15);
	glVertex2f(-30, -15);
	glVertex2d(-30, 15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-20, 30, 0);
	glScalef(0.1, 0.1, 0.1);
	glColor3f(1.0, 1.0, 1.0);
	draw_string("Press enter to start again");

	glPopMatrix();





}

void drawMainMenu()
{

	//Draw start button
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawFootPath();
	drawSurroundings();
	drawDivider();
	drawcycle();

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslated(0, 30, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(30, 15);
	glVertex2f(30, -15);
	glVertex2f(-30, -15);
	glVertex2d(-30, 15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-20, 30, 0);
	glScalef(0.1, 0.1, 0.1);
	glColor3f(1.0, 1.0, 1.0);
	draw_string("START");

	glPopMatrix();





}

void drawTime()
{
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslated(-200, 90, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(50, 15);
	glVertex2f(50, -15);
	glVertex2f(-30, -15);
	glVertex2d(-30, 15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-220, 85, 0);
	glScalef(0.1, 0.1, 0.1);
	glColor3f(1.0, 1.0, 1.0);
	draw_string("Score: ");
	glPopMatrix();

	glPushMatrix();
	glTranslated(-180, 85, 0);
	glScalef(0.1, 0.1, 0.1);
	glColor3f(1.0, 0.0, 0.0);
	//glutStrokeCharacter(GLUT_STROKE_ROMAN, '4');
	drawScore(seconds);
	glPopMatrix();
}

void drawScore(int score)
{
	int temp = score;
	int str[20], i = 0;

	while (temp>0)
	{
		str[i++] = (temp % 10);
		temp /= 10;
	}
	i--;
	while (i >= 0)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i--] + '0');
	}
	if (score == 0) glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
}

void drawEnd()
{
	int i, j;
	for (i = 0; i < 5; i++)
	{
		if (i % 2 == 0)
			glColor3f(0.0, 0.0, 0.0);
		else
			glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();

		glTranslated(-55, end_y + 10 * i, 0);

		for (j = 0; j < 11; j++)
		{
			if (i % 2)
			{
				if (j % 2 == 0)
					glColor3f(0.0, 0.0, 0.0);
				else
					glColor3f(1.0, 1.0, 1.0);

			}

			else
			{
				if (j % 2)
					glColor3f(0.0, 0.0, 0.0);
				else
					glColor3f(1.0, 1.0, 1.0);
			}

			glRectd(10 * j, 0, 10 * (j + 1), 10);
		}

		glPopMatrix();
		//drawMessage();
	}
}


