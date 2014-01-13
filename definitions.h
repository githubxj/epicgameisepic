#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "imageloader.h"
#include "strutils.h"
#include <string>
#define M_PI 3.1415926535897f
#define RESO_W 1920
#define RESO_H 1080
#define screenRes "1920x1080:32@60"
// #define RESO_W 1366
// #define RESO_H 768
//#define screenRes "1366x768:32@60"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////
//SHADOW ICIN/////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

UINT TextureArray[2];

float floorShadow[4][4];	// matrix used to calculate our projected floor shadow
float firstLevelShadow[4][4]; //matrix used to calculate our projected first level shadow

float groundplane[]   = {0.0f, 1.0f, 0.0f, 1.0f}; // The normal of the floor
float firstLevelNormal[] = {0.0f, 4.0f, 0.0f, 1.0f};

float lightPosition[] = {20.0f, 50.0f,-20.0f, 1.0f};	// Holds our light position
float lightAmbient[]  = {0.5f, 0.5f, 0.5f, 0.2f};	// Ambient light
float lightDiffuse[]  = {10.0f, 10.0f, 10.0f, 1.0f};	// Diffuse light
float lightSpecular[] = {10.0f, 10.0f, 10.0f, 1.0f};	// Specular light

enum { X, Y, Z, W };

//////////////////////////////////////////////////////////////////////////////////////
//SHADOW ICIN/////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


struct tail
{
	GLfloat x;
	GLfloat z;
};


bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)

static GLfloat floorVertices[4][3] = {
	{ -1.0f , -1.0f, 101.0f }, //sag ust
	{ 101.0f, -1.0f, 101.0f }, //sol ust
	{ 101.0f, -1.0f,  -1.0f }, //sol alt
	{ -1.0f , -1.0f,  -1.0f }, //sag alt
};

static GLfloat firstLevelVertices [4][3] = {
	{ 60.0f , 4.0f, 80.0f }, //sag ust
	{ 101.0f, 4.0f, 80.0f }, //sol ust
	{ 101.0f, 4.0f,  -1.0f }, //sol alt
	{ 60.0f , 4.0f,  -1.0f }, //sag alt
};

static GLfloat secondLevelVertices [4][3] = {
	{ 80.0f , 9.0f, 60.0f }, //sag ust
	{ 101.0f, 9.0f, 60.0f }, //sol ust
	{ 101.0f, 9.0f,  -1.0f }, //sol alt
	{ 80.0f , 9.0f,  -1.0f }, //sag alt
};

static GLfloat firstLevelSide1Vertices [4][3] = {
	{ 60.0f , 4.0f, 80.0f }, //sag ust
	{ 60.0f, 4.0f, -1.0f }, //sol ust
	{ 60.0f, -1.0f,  -1.0f }, //sol alt
	{ 60.0f , -1.0f,  80.0f }, //sag alt
};

static GLfloat firstLevelSide2Vertices [4][3] = {
	{ 101.0f , 4.0f, 80.0f }, //sag ust
	{ 60.0f, 4.0f, 80.0f }, //sol ust
	{ 60.0f, -1.0f,  80.0f }, //sol alt
	{ 101.0f , -1.0f,  80.0f }, //sag alt
};

static GLfloat secondLevelSide1Vertices [4][3] = {
	{ 80.0f , 9.0f, 60.0f }, //sag ust
	{ 80.0f, 9.0f, -1.0f }, //sol ust
	{ 80.0f, 4.0f,  -1.0f }, //sol alt
	{ 80.0f , 4.0f,  60.0f }, //sag alt
};

static GLfloat secondLevelSide2Vertices [4][3] = {
	{ 101.0f , 9.0f, 60.0f }, //sag ust
	{ 80.0f, 9.0f, 60.0f }, //sol ust
	{ 80.0f, 4.0f,  60.0f }, //sol alt
	{ 101.0f , 4.0f,  60.0f }, //sag alt
};

// angle of rotation
GLfloat xpos = 10, ypos = 0, zpos = 10, xrot = 0, yrot = 180;
GLfloat xrotrad;
GLfloat yrotrad = (yrot / 180 * 3.141592654f);

GLfloat accCounter = 0;

tail JohnTail;

//GLfloat johnTail = zpos - 1.0f;

//monster coordinates
GLfloat xMons = 98.0f;
GLfloat yMons = 5.0f;		//key-keeper
GLfloat zMons = 2.0f;

GLfloat xMons2 = 28.0f;
GLfloat yMons2 = 0.0f;		//gatekeeper
GLfloat zMons2 = 98.0f;

// camera rotation angle
GLfloat rot_cam = 22.5;

// our radius distance from our character
GLfloat cRadius = 10.0f;

GLfloat lightColor0[] = {1.0f, 1.0f, 1.0f};
GLfloat lightColor1[] = {1.0f, 1.0f, 1.0f};
// the position of the light
static GLfloat position[] = {25.0f,15.0f,25.0f,1.0f};
//static GLfloat position2[]= {40.0f,20.0f,40.0f,40.0f};

//static GLfloat floorShadow[4][4];
static GLfloat normalVertices[] = {0, 0, 0, 1};
static GLfloat planeNormal[3];
static GLfloat johnPosition[4];

float coinY[50];

GLfloat positionx[50];
GLfloat positionz[50];
GLfloat coinPosX[50];
GLfloat coinPosZ[50];

GLfloat degree = 0.0;
GLfloat fallDegree = 0.0;

GLfloat velocity = 10.0;
GLfloat gravity = -1.0;
GLfloat dummyVar = 10.0f;
GLfloat jumpAcc = 1.0f;
GLfloat remainingTime = RESO_W-20;

bool keyFlag = false;
bool exitFlag = false;
bool boundFlag = false;
bool coinColorFlag = false;
bool fallFlag = false;
bool jumpKeyFlag = false;
bool jumpTrigger = false;
bool fallTrigger = false;
bool shadowFlag = false;
bool turnLeftFlag = false;
bool turnRightFlag =false;
bool goForward = false;
bool wallFlag = false;
bool monsterFlag = false;
bool monster2Flag = false;
bool monsterCollideFlag = false;
bool monster2CollideFlag = false;
bool timerStopperFlag = true;
bool surfaceFlag1 = false;
bool surfaceFlag2 = false;
bool atFirstFloor = false;
bool atSecondFloor = false;
bool fallingWallFlag = false;
bool accelerationFlag = false;
bool jumpCheckFlag = false;
bool landedOnFirstFloor = false;
bool toggleShadow = true;


bool turn1 = true;
bool turn2 = false;
bool turn3 = false;
bool turn4 = false;

bool east = false;
bool west = false;
bool north = false;
bool south = false;

GLfloat colorJohnR = 1.0f;
GLfloat colorJohnG = 0.0f;
GLfloat colorJohnB = 0.0f;

GLuint _textureId;
GLuint textureBall;
GLuint glassTex;
GLuint wallTexture;
GLuint endGameTexture;
GLuint endGameWinTexture;

GLfloat dummyX, dummyZ, dummyY;


int coinCount = 0;
int pos = 1;
const int constant = 5;
int totalScore = 0;

/**************PROTOTYPES START**************/
void reStart(void);
void drawJohnAppleseed(void);
void drawKey(void);
void drawExit(void);
void randomCoin(void);
void drawCoin (void);
void drawSphere(double r, int lats, int longs);
void drawCylinder(int n, int arg, float mult, float v);
void shadowmatrix(float shadowMat[4][4], float groundplane[4], float lightpos[4]);
void calculatePlaneNormal(GLfloat (*plane)[3]);
void drawFloor(void);
void drawFirstLevel(void);
void drawFirstLevelSide1(void);
void drawFirstLevelSide2(void);
void drawPlanes(void);
GLuint loadTexture(Image *image);
void printtext(int x, int y, string c_string);
void printEndGame(void);
void printWinGame(void);
void collisionCheck(void);
void Timer(int value);
void init(void);
void display(void);
void reshape(int w, int h);
void keyOperations();
void keyPressed (unsigned char key, int x, int y);
void keyUp (unsigned char key, int x, int y);

/**************PROTOTYPES FINISH**************/


//www.opengl.org/resources/code/samples/mjktips/TexShadowReflectLight.html
void drawFloor(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glColor3f(1.0f, 1.0f, 1.0f);

	//	calculatePlaneNormal();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(floorVertices[0]);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0, 16.0);
	glVertex3fv(floorVertices[1]);

	glNormal3f(0, 1, 0);
	glTexCoord2f(16.0, 16.0);
	glVertex3fv(floorVertices[2]);

	glNormal3f(0, 1, 0);
	glTexCoord2f(16.0, 0.0);
	glVertex3fv(floorVertices[3]);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawFirstLevel(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, glassTex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);

	//	calculatePlaneNormal();
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(firstLevelVertices[0]);
	
	glNormal3f(0,1,0);
	glTexCoord2f(0.0, 16.0);
	glVertex3fv(firstLevelVertices[1]);
	
	glNormal3f(0,1,0);
	glTexCoord2f(16.0, 16.0);
	glVertex3fv(firstLevelVertices[2]);
	
	glNormal3f(0,1,0);
	glTexCoord2f(16.0, 0.0);
	glVertex3fv(firstLevelVertices[3]);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawFirstLevelSide1(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wallTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);

	//	calculatePlaneNormal();
	glBegin(GL_QUADS);
	//glNormal3f(normalVertices[0], normalVertices[1], normalVertices[2]);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(firstLevelSide1Vertices[0]);
	glTexCoord2f(0.0, 12.8);
	glVertex3fv(firstLevelSide1Vertices[1]);
	glTexCoord2f(3.2, 12.8);
	glVertex3fv(firstLevelSide1Vertices[2]);
	glTexCoord2f(3.2, 0.0);
	glVertex3fv(firstLevelSide1Vertices[3]);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawFirstLevelSide2(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wallTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);

	//	calculatePlaneNormal();
	glBegin(GL_QUADS);
	//glNormal3f(normalVertices[0], normalVertices[1], normalVertices[2]);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(firstLevelSide2Vertices[0]);
	glTexCoord2f(0.0, 12.8);
	glVertex3fv(firstLevelSide2Vertices[1]);
	glTexCoord2f(3.2, 12.8);
	glVertex3fv(firstLevelSide2Vertices[2]);
	glTexCoord2f(3.2, 0.0);
	glVertex3fv(firstLevelSide2Vertices[3]);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


void drawFirstLevelShadow(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor4f(0.0f,0.0f,0.0f,0.5f);

	//	calculatePlaneNormal();
	glBegin(GL_QUADS);
	//glNormal3f(normalVertices[0], normalVertices[1], normalVertices[2]);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(firstLevelVertices[0]);
	glTexCoord2f(0.0, 16.0);
	glVertex3fv(firstLevelVertices[1]);
	glTexCoord2f(16.0, 16.0);
	glVertex3fv(firstLevelVertices[2]);
	glTexCoord2f(16.0, 0.0);
	glVertex3fv(firstLevelVertices[3]);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawFirstLevelSide1Shadow(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wallTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor4f(0.0f,0.0f,0.0f,0.5f);

	//	calculatePlaneNormal();
	glBegin(GL_QUADS);
	//glNormal3f(normalVertices[0], normalVertices[1], normalVertices[2]);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(firstLevelSide1Vertices[0]);
	glTexCoord2f(0.0, 12.8);
	glVertex3fv(firstLevelSide1Vertices[1]);
	glTexCoord2f(3.2, 12.8);
	glVertex3fv(firstLevelSide1Vertices[2]);
	glTexCoord2f(3.2, 0.0);
	glVertex3fv(firstLevelSide1Vertices[3]);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawFirstLevelSide2Shadow(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wallTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor4f(0.0f,0.0f,0.0f,0.5f);

	//	calculatePlaneNormal();
	glBegin(GL_QUADS);
	//glNormal3f(normalVertices[0], normalVertices[1], normalVertices[2]);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(firstLevelSide2Vertices[0]);
	glTexCoord2f(0.0, 12.8);
	glVertex3fv(firstLevelSide2Vertices[1]);
	glTexCoord2f(3.2, 12.8);
	glVertex3fv(firstLevelSide2Vertices[2]);
	glTexCoord2f(3.2, 0.0);
	glVertex3fv(firstLevelSide2Vertices[3]);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}