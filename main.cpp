#include "definitions.h"

void reStart(void)
{
	// angle of rotation
	xpos = 10, ypos = 0, zpos = 10, xrot = 0, yrot = 180;
	yrotrad = (yrot / 180 * 3.141592654f);

	accCounter = 0;

	//monster coordinates
	xMons = 98.0f;
	yMons = 5.0f;		//key-keeper
	zMons = 2.0f;

	xMons2 = 28.0f;
	yMons2 = 0.0f;		//gatekeeper
	zMons2 = 98.0f;

	// camera rotation angle
	rot_cam = 22.5;

	//remaining time indicator
	remainingTime = RESO_W-20;

	jumpAcc = 1.0f;
	dummyVar = 10.0f;

	// our radius distance from our character
	cRadius = 10.0f;

	degree = 0.0f;
	fallDegree = 0.0f;

	keyFlag = false;
	exitFlag = false;
	boundFlag = false;
	coinColorFlag = false;
	fallFlag = false;
	jumpKeyFlag = false;
	wallFlag = false;
	monsterFlag = false;
	monster2Flag = false;
	monsterCollideFlag = false;
	monster2CollideFlag = false;
	timerStopperFlag = false;
	fallTrigger = false;
	jumpTrigger = false;
	surfaceFlag1 = false;
	surfaceFlag2 = false;
	atFirstFloor = false;
	fallingWallFlag = false;
	toggleShadow = true;

	turn1 = true;
	turn2 = false;
	turn3 = false;
	turn4 = false;

	east = false;
	west = false;
	south = false;
	north = false;

	colorJohnR = 1.0f;
	colorJohnG = 0.0f;
	colorJohnB = 0.0f;

	pos = 1;
	const int constant = 5;

	coinCount = 0;
	randomCoin();
}

void drawJohnAppleseed(void){

	glPushMatrix();

	glTranslated(xpos, ypos , zpos);

	if(!boundFlag)
	{
		glRotatef(xrot, -cos(yrotrad), 0, -sin(yrotrad));
		glRotatef(yrot, 0, -sin(yrotrad), 0);
	}

	if(boundFlag)
	{
		if (atFirstFloor)
			glTranslatef(0,-ypos,0);

		glRotatef(fallDegree*5, cos(yrotrad), 0.0, -sin(yrotrad));
	}
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glutWireSphere(1.02, 40, 40);
	glPopMatrix();

	glColor3f(colorJohnR, colorJohnG, colorJohnB);
	drawSphere(1.0,100.0,100.0);

	glPopMatrix();
}

void drawJohnAppleseedShadow(void){

	glPushMatrix();

	glTranslated(xpos, ypos + 0.2f , zpos);

	if(!boundFlag)
	{
		glRotatef(xrot, -cos(yrotrad), 0, -sin(yrotrad));
		glRotatef(yrot, 0, -sin(yrotrad), 0);
	}

	if(boundFlag)
	{
		if (atFirstFloor)
			glTranslatef(0,-ypos,0);

		glRotatef(fallDegree*5, cos(yrotrad), 0.0, -sin(yrotrad));
	}

	glColor4f(0.0,0.0,0.0,0.5f);
	drawSphere(1.0,100.0,100.0);

	glPopMatrix();
}

void drawMonster(void)
{
	glPushMatrix();

		glTranslatef(xMons, yMons , zMons);

		glPushMatrix();
		glColor3f(1.0f, 0.2f, 0.0f);
		glutWireSphere(1.02, 40, 40);
		glPopMatrix();

		glColor3f(0.63f, 0.12f, 0.94f);
		drawSphere(1.0,100.0,100.0);

	glPopMatrix();

	glPushMatrix();

		glTranslatef(xMons2, yMons2 , zMons2);

		glPushMatrix();
		glColor3f(1.0f, 0.2f, 0.0f);
		glutWireSphere(1.02, 40, 40);
		glPopMatrix();

		glColor3f(0.63f, 0.12f, 0.94f);
		drawSphere(1.0,100.0,100.0);

	glPopMatrix();
}

void drawKey(void){

	glPushMatrix();
	glTranslatef(87.5,5.0,20.0);
	glRotatef(degree, 1.0, 0.0, 0.0);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutSolidIcosahedron();
	glPopMatrix();
}

void drawExit(void){

	glPushMatrix();
	glTranslated(1.0,0.0,98.0);
	glRotatef(degree, 0.0, 1.0, 0.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutWireCube(3);
	glPopMatrix();
}

void drawMonsterShadow(void)
{
	glPushMatrix();

	glTranslatef(xMons, yMons , zMons);

	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
	drawSphere(1.0,100.0,100.0);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(xMons2, yMons2 , zMons2);

	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
	drawSphere(1.0,100.0,100.0);

	glPopMatrix();
}

void drawKeyShadow(void){

	glPushMatrix();
	glTranslatef(87.5,5.0,20.0);
	glRotatef(degree, 1.0, 0.0, 0.0);
	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
	glutSolidIcosahedron();
	glPopMatrix();
}

void drawExitShadow(void){

	glPushMatrix();
	glTranslated(1.0,0.0,98.0);
	glRotatef(degree, 0.0, 1.0, 0.0);
	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
	glutWireCube(3);
	glPopMatrix();
}

void randomCoin(void){

	for (int i = 0; i < 50; i++)
	{
		coinPosX[i] = rand() %50;
		coinPosZ[i] = rand() %50;

		// make sure coins do not get drawn near exit
		if(coinPosZ[i] >= 95 && coinPosX[i] <= 5)
			coinPosZ[i] -= 10;

		// make sure coins do not get drawn near key
		if(coinPosZ[i] >= 95 && coinPosX[i] >= 95)
			coinPosZ[i] -= 10;
	}
}

void drawCoin (void)
{
	degree +=1;

	if(degree>360)
		degree = 0;

	int dummyIndex;

	for(int i = 0; i < 10; i++)
	{
		coinY[i] = 0.0f;

		if (coinPosX[i]*2 <= 101.0f && coinPosX[i]*2 >= 60.0f && coinPosZ[i]*2 <=80.0f && coinPosZ[i] >= -1.0f)
			coinY[i] = 4.5f;

		dummyX = coinPosX[i];
		dummyZ = coinPosZ[i];
		dummyY = coinY[i];
		dummyIndex = i;

		//collision detection with coins
		if ((xpos <= (dummyX*2)+1.5 && xpos >= (dummyX*2)-1.5) && (zpos <= (dummyZ*2)+1.5 && zpos >= (dummyZ*2)-1.5))
		{
			if ((ypos < dummyY +0.5f && ypos > dummyY - 0.5f) && (!jumpTrigger && !fallFlag))
			{
				if (!jumpCheckFlag)
				{
					cout << "COIN COLLISION" << endl;
					coinPosX[dummyIndex] = -99999.0;
					coinPosZ[dummyIndex] = -99999.0;
					coinCount++;
				}
			}
		}

		glPushMatrix();
		glTranslated(coinPosX[i]*2, coinY[i], coinPosZ[i]*2);
		glRotatef(degree, 0.0, 1.0, 0.0);
		glColor3f(1.0,0.8,0.0);
		drawCylinder(100, 0, 0.5 , 0.1);
		glPopMatrix();
	}
}

void drawCoinShadow (void)
{
	degree +=1;

	if(degree>360)
		degree = 0;

	int dummyIndex;

	for(int i = 0; i < 10; i++)
	{
		dummyX = coinPosX[i];
		dummyZ = coinPosZ[i];
		dummyIndex = i;

		//collision detection with coins
		if ((xpos <= (dummyX*2)+1.5 && xpos >= (dummyX*2)-1.5) && (zpos <= (dummyZ*2)+1.5 && zpos >= (dummyZ*2)-1.5))
		{
			cout << "COIN COLLISION" << endl;
			coinPosX[dummyIndex] = -99999.0;
			coinPosZ[dummyIndex] = -99999.0;
			coinCount++;
		}

		if (coinPosX[i]*2 <= 101.0f && coinPosX[i]*2 >= 60.0f && coinPosZ[i]*2 <=80.0f && coinPosZ[i] >= -1.0f)
			coinY[i] = 4.5f;

		glPushMatrix();
		glTranslated(coinPosX[i]*2, coinY[i], coinPosZ[i]*2);
		glRotatef(degree, 0.0, 1.0, 0.0);
		glColor4f(0.0,0.0,0.0,0.5f);
		drawCylinder(100, 0, 0.5 , 0.1);
		glPopMatrix();

		coinY[i] = 0.0f;
	}
}

//ozark.hendrix.edu/~burch/cs/490/sched/feb8/
void drawSphere(double r, int lats, int longs)
{
	glBindTexture(GL_TEXTURE_2D, TextureArray[1]);

	int i, j;
	for(i = 0; i <= lats; i++) {
		double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
		double z0  = sin(lat0);
		double zr0 =  cos(lat0);

		double lat1 = M_PI * (-0.5 + (double) i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for(j = 0; j <= longs; j++) {
			double lng = 2 * M_PI * (double) (j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(x * zr0, y * zr0, z0);

			glNormal3f(x * zr1, y * zr1, z1);
			glTexCoord2f(1.0f,1.0f);
			glVertex3f(x * zr1, y * zr1, z1);
		}
		glEnd();
	}
}

//cboard.cprogramming.com/game-programming/133658-opengl-draw-cylinder-yourself.html
void drawCylinder(int n, int arg, float mult, float v)
{

	//Function drw_polygon:
	//Arguments:
	//n - number of sides
	//arg - starting angle (not so important at all)
	//mult - multiplying sides to increase their length
	//v - cylinder height

	if(arg<0) arg = 0;


	// Cylinder 
	glBegin(GL_POLYGON);
	//glColor4f(1.0,8 0.0, 1.0);
	for(int i = arg; i <= (360 + arg); i += (360 / n)) {
		float a = i * M_PI / 180; // degrees to radians
		glVertex3f(mult * cos(a), mult * sin(a), 0.0);
	}
	glEnd();

	// Cylinder Top
	glBegin(GL_POLYGON);
	//glColor4f(0.0, 0.8, 1.0, 1.0);
	for(int i = arg; i <= (360 + arg); i += (360 / n)) {
		float a = i * M_PI / 180; // degrees to radians
		glVertex3f(mult * cos(a), mult * sin(a), v);
	}
	glEnd();

	// Cylinder "Cover"
	glBegin(GL_QUAD_STRIP);
	//glColor4f(1.0, 1.0, 0.0, 1.0);
	for(int i = arg; i < 480; i += (360 / n)) {
		float a = i * M_PI / 180; // degrees to radians
		glVertex3f(mult * cos(a), mult * sin(a), 0.0);
		glVertex3f(mult * cos(a), mult * sin(a), v);
	}
	glEnd();



}

// This matrix function  will project our shadow
void shadowmatrix(float shadowMat[4][4], float groundplane[4], float lightpos[4])
{

	// Find the dot product between the light position vector and the ground plane normal
	float dot = groundplane[X] * lightpos[X] + groundplane[Y] * lightpos[Y] + groundplane[Z] * lightpos[Z] + groundplane[W] * lightpos[W];

	shadowMat[0][0] = dot - lightpos[X] * groundplane[X];
	shadowMat[1][0] = 0.f - lightpos[X] * groundplane[Y];
	shadowMat[2][0] = 0.f - lightpos[X] * groundplane[Z];
	shadowMat[3][0] = 0.f - lightpos[X] * groundplane[W];

	shadowMat[X][1] = 0.f - lightpos[Y] * groundplane[X];
	shadowMat[1][1] = dot - lightpos[Y] * groundplane[Y];
	shadowMat[2][1] = 0.f - lightpos[Y] * groundplane[Z];
	shadowMat[3][1] = 0.f - lightpos[Y] * groundplane[W];

	shadowMat[X][2] = 0.f - lightpos[Z] * groundplane[X];
	shadowMat[1][2] = 0.f - lightpos[Z] * groundplane[Y];
	shadowMat[2][2] = dot - lightpos[Z] * groundplane[Z];
	shadowMat[3][2] = 0.f - lightpos[Z] * groundplane[W];

	shadowMat[X][3] = 0.f - lightpos[W] * groundplane[X];
	shadowMat[1][3] = 0.f - lightpos[W] * groundplane[Y];
	shadowMat[2][3] = 0.f - lightpos[W] * groundplane[Z];
	shadowMat[3][3] = dot - lightpos[W] * groundplane[W];

}

void calculatePlaneNormal(GLfloat (*plane)[3])
{
	float ax, ay, az, bx, by, bz;
	float nx, ny, nz;
	float l;

	float p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z;

	p1x = plane[0][0];
	p1y = plane[0][1];
	p1z = plane[0][2];

	p2x = plane[1][0];
	p2y = plane[1][1];
	p2z = plane[1][2];

	p3x = plane[2][0];
	p3y = plane[2][1];
	p3z = plane[2][2];

	ax = p2x - p1x;
	ay = p2y - p1y;
	az = p2z - p1z;

	bx = p3x - p1x;
	by = p3y - p1y;
	bz = p3z - p1z;

	nx = (ay * bz) - (az * by);
	ny = (az * bx) - (ax * bz);
	nz = (ax * by) - (ay * bx);

	// Normalize (divide by root of dot product)
	l = sqrt(nx * nx + ny * ny + nz * nz);
	nx /= l;
	ny /= l;
	nz /= l;

	planeNormal[3] = nx;
	planeNormal[1] = ny;
	planeNormal[2] = nz;
}

void drawPlanes(void)
{
	if (toggleShadow)
		drawFloor();

	drawFirstLevel();
	drawFirstLevelSide1();
	drawFirstLevelSide2();

}

void drawPlanesShadow(void)
{
	drawFirstLevelShadow();
	drawFirstLevelSide1Shadow();
	drawFirstLevelSide2Shadow();
}

GLuint loadTexture(Image *image) {

	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture

	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
		//as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void printtext(int x, int y, string c_string, string d_string)
{
	char buffer [33];
	char buffer2 [256];
	string ccc = itoa(coinCount, buffer, 10);
	string ddd = itoa(totalScore, buffer2, 10);
	
	ccc = c_string+ccc+" / 10";
	ddd = d_string+ddd+ " / 22900";
	//(x,y) is from the bottom left of the window
	glMatrixMode(GL_PROJECTION);

	glDisable(GL_LIGHTING);

	glPushMatrix();
	glLoadIdentity();
	glColor3f(0, 1.0f, 0);
	glOrtho(0, RESO_W, 0, RESO_H, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glScalef(4.0f, 4.0f, 4.0f);
	glLoadIdentity();

	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2i(x,y);
	for (int i=0; i<ccc.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ccc[i]);
	}
	for (int i=0; i<ddd.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ddd[i]);
	}

	glPopAttrib();


	//red timer dot
	glPushMatrix(); 
	glColor3f (1.0f, 0.0f, 0.0f);
	glTranslatef(remainingTime, 20.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f( 2.0f, 10.0f, 0.0f );
	glVertex3f( 2.0f, 30.0f, 0.0f );
	glVertex3f( 22.0f, 30.0f, 0.0f );
	glVertex3f( 22.0f, 10.0f, 0.0f ); 
	glEnd();
	glPopMatrix();

	//transparent time bar
	glPushMatrix();  
	glColor4f (0.0, 0.0, 0.0, 0.5);
	glBegin(GL_QUADS);
	glVertex3f( 0.0f, 30.0f, 0.0f );
	glVertex3f( 0.0f, 50.0f, 0.0f );
	glVertex3f( RESO_W, 50.0f, 0.0f );
	glVertex3f( RESO_W, 30.0f, 0.0f ); 
	glEnd(); 
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

void printEndGame(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, endGameTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glMatrixMode(GL_PROJECTION);

	glDisable(GL_LIGHTING);

	glPushMatrix();

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	glLoadIdentity();
	glOrtho(0, RESO_W, 0, RESO_H, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	glColor3f(1.0f,0,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0,0,0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(RESO_W,0,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(RESO_W,RESO_H,0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0,RESO_H,0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void printWinGame(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, endGameWinTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glMatrixMode(GL_PROJECTION);

	glDisable(GL_LIGHTING);

	glPushMatrix();

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	glLoadIdentity();
	glOrtho(0, RESO_W, 0, RESO_H, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	glColor3f(1.0f,0,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0,0,0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(RESO_W,0,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(RESO_W,RESO_H,0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0,RESO_H,0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void calculateFacingSide(void)
{
	//faces west
	if (yrot > 0 && yrot <= 90)
	{
		west = true;
		east = false;
		north= false;
		south = false;
		JohnTail.z = zpos;
		JohnTail.x = xpos -1.0f;
	}

	//faces north
	if (yrot > 90 && yrot <= 180)
	{
		west = false;
		east = false;
		north= true;
		south = false;
		JohnTail.x = xpos;
		JohnTail.z = zpos - 1.0f;
	}

	//faces east
	if (yrot > 180 && yrot <= 270)
	{
		west = false;
		east = true;
		north= false;
		south = false;
		JohnTail.z = zpos;
		JohnTail.x = xpos + 1.0f;
	}

	//faces south
	if (yrot > 270 && (yrot == 360 || yrot == 0))
	{
		west = false;
		east = false;
		north= false;
		south = true;
		JohnTail.x = xpos;
		JohnTail.z = zpos + 1.0f;
	}
}

void collisionCheck(void)
{

	//if john takes all the coins (bonus), change the color to YELLOW
	if (coinCount == 10)
	{
		colorJohnR = 1.0f;
		colorJohnG = 1.0f;
		colorJohnB = 0.0f;
		coinColorFlag = true;
	}

	if(!jumpTrigger && !fallTrigger)
	{
		//collision detection with Key
		if((xpos >= 85.5 && xpos <= 89.5) && (zpos >= 18.0 && zpos <= 22.0))
		{
			keyFlag = true;

			//if john takes all the coins, change the color to BLUE
			if(!coinColorFlag)
			{
				colorJohnR = 0.0f;
				colorJohnG = 0.0f;
				colorJohnB = 1.0f;
			}
		}

		//if john reaches the exit with the key (finishes the game)
		if ((xpos >= 0 && xpos <= 4.0) && (zpos >= 96.0 && zpos <= 100.0) && keyFlag)
		{
			exitFlag = true;
			timerStopperFlag = true;
		}
	}

	//if john takes key with all the coins, change the color to GREEN
	if (keyFlag && coinColorFlag)
	{
		colorJohnR = 0.0f;
		colorJohnG = 1.0f;
		colorJohnB = 0.0f;
	}

	//if john reaches the exit with the key (finishes the game)
	if ((xpos >= 0 && xpos <= 4.0) && (zpos >= 96.0 && zpos <= 100.0) && keyFlag)
	{
		exitFlag = true;
		timerStopperFlag = true;
	}
	//if john goes out of 'bounds'
	if (((xpos <= -0.5 || xpos >= 101.0) || (zpos <= -0.5 || zpos >= 101.0)) && !exitFlag)
		boundFlag = true;


	////////////////////////////////////////////////////////////////////////////////////// WALL COLLISION ///////////////////////////////////////////////////////////////////////////

	//if john collides with a wall (following 4 if-checks)

	//1st floor wall, long side
	if (xpos > 57.0f && xpos < 59.0f && zpos < 80.0f)
	{
		if ((GLint)yrot%360 < 180 && (GLint)yrot%360 > 0 && ypos < 5.0f)
			wallFlag = true;
		else
			wallFlag = false;
	}

	//1st floor wall, short side
	if (xpos > 60.0f && zpos < 83.0f && zpos > 81.0f)
	{
		if (ypos < 5.0f && (((GLint)yrot%360 > 270 && (GLint)yrot%360 <= 360) || ((GLint)yrot%360 < 90 && (GLint)yrot%360 >= 0) || ((GLint)yrot%360 > -90 && (GLint)yrot%360 <= 0)))
			wallFlag = true;
		else
			wallFlag = false;
	}

	////////////////////////////////////////////////////////////////////////////////////// WALL COLLISION ///////////////////////////////////////////////////////////////////////////



	//if ((xpos > 60.0f && xpos < 80.0f && zpos < 80.0f) || (zpos < 80.0f && zpos > 60.0f && xpos > 60.0f))
	if (xpos > 60.0f && zpos < 80.0f)
	{
		surfaceFlag1 = true;
		atFirstFloor = true;
	}
	else
		surfaceFlag1 = false;




	if (xpos > 80.0f && zpos < 60.0f)
		monsterFlag = true;
	else monsterFlag = false;

	if ( (xpos > 10.0f && xpos < 28.0f) && (zpos < 100.0f && zpos > 40.0f) )
		monster2Flag = true;
	else monster2Flag = false;

	//key-keeper collide
	if (xMons < xpos + 2.0f && xMons > xpos - 2.0f && zMons < zpos + 2.0f && zMons > zpos - 2.0f)
	{
		monsterCollideFlag = true;
		timerStopperFlag = true;
	}

	//gatekeeper collide
	if (xMons2 < xpos + 2.0f && xMons2 > xpos - 2.0f && zMons2 < zpos + 2.0f && zMons2 > zpos - 2.0f)
	{
		monster2CollideFlag = true;
		timerStopperFlag = true;
	}
}

void Timer(int value) 
{

	if(turnLeftFlag || turnRightFlag)
	{
		if (yrot == 360 || yrot == -360)
			yrot = 0;
		if (yrot < 0)
			yrot = 360 + yrot;

		if(turnLeftFlag)
			yrot -= 7.5;
		else if(turnRightFlag)
			yrot += 7.5;

		turnLeftFlag  = false;
		turnRightFlag = false;

		yrotrad = (yrot / 180 * 3.141592654f);

		cout << "yrot: " << yrot << "facing side: "<< north << east << south << west << endl;
	}

	if(goForward)
	{
		if (xrotrad == 6000)
			xrotrad = 0;

		xrotrad = (xrot / 180 * 3.141592654f);
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos += float(sin(yrotrad));
		zpos -= float(cos(yrotrad));

		xrot += 15;

		goForward = false;
	}

	if (!monsterFlag)
	{
		if (xMons > 80.0f && turn1)
		{
			xMons = xMons - 0.1f;
			if (xMons > 80.0f && xMons < 82.0f) {turn1 = false; turn2 = true;}
		}

		if (zMons < 60.0f && turn2)
		{
			zMons = zMons + 0.1f;
			if (zMons < 60.0f && zMons > 58.0f) {turn2 = false; turn3 = true;}
		}

		if (xMons < 100.0f && turn3)
		{
			xMons = xMons + 0.1f;
			if (xMons < 100.0f && xMons > 98.0f) {turn3 = false; turn4 = true;}
		}

		if (zMons > 0 && turn4)
		{
			zMons = zMons - 0.1f;
			if (zMons > 0 && zMons < 2.0f) {turn4 = false; turn1 = true;}
		}
	}

	if(!monster2Flag)
	{
		if (xMons2 > 10.0f && turn1)
		{
			xMons2 = xMons2 - 0.1f;
			if (xMons2 > 10.0f && xMons2 < 12.0f) {turn1 = false; turn2 = true;}
		}

		if (zMons2 < 98.0f && turn4)
		{
			zMons2 = zMons2 + 0.1f;
			if (zMons2 < 98.0f && zMons2 > 96.0f) {turn4 = false; turn1 = true;}
		}

		if (xMons2 < 30.0f && turn3)
		{
			xMons2 = xMons2 + 0.1f;
			if (xMons2 < 30.0f && xMons2 > 28.0f) {turn3 = false; turn4 = true;}
		}

		if (zMons2 > 38 && turn2)
		{
			zMons2 = zMons2 - 0.1f;
			if (zMons2 > 38 && zMons2 < 40.0f) {turn2 = false; turn3 = true;}
		}
	}

	if (monsterFlag)
	{
		if (xpos < xMons)
		{
			if (xMons != JohnTail.x)
			{
				xMons = xMons - 1.05f;
			}
		}

		if (xpos >= xMons)
		{
			if (xMons != JohnTail.x)
			{
				xMons = xMons + 1.05f;
			}
		}

		if (zpos < zMons)
		{
			if (zMons != JohnTail.z)
			{
				zMons = zMons - 1.05f;
			}
		}

		if (zpos >= zMons)
		{
			if (zMons != JohnTail.z)
			{
				zMons = zMons + 1.05f;
			}
		}
	}

	if(monster2Flag)
	{
		if(xpos < xMons2)
		{
			if (xMons2 != JohnTail.x)
			{
				xMons2 = xMons2 - 1.05f;
			}
		}

		if (xpos >= xMons2)
		{
			if (xMons2 != JohnTail.x)
			{
				xMons2 = xMons2 + 1.05f;
			}
		}

		if (zpos < zMons2)
		{
			if (zMons2 != JohnTail.z)
			{
				zMons2 = zMons2 - 1.05f;
			}
		}

		if (zpos >= zMons2)
		{
			if (zMons2 != JohnTail.z)
			{
				zMons2 = zMons2 + 1.05f;
			}
		}
	}


	if (jumpTrigger && !fallTrigger)
	{
		jumpCheckFlag = true;
		ypos = (velocity - dummyVar);

		if (!atFirstFloor)
		{
			if (dummyVar > 3.0f)
			{
				dummyVar -= 0.5;

				if (dummyVar == 3.0f)
				{
					fallTrigger = true;
					jumpTrigger = false;
				}
			}
		}

		else if (atFirstFloor && jumpCheckFlag)
		{
			if (dummyVar > -2.0f)
			{
				dummyVar -=0.5f;

				if (dummyVar == -2.0f)
				{
					fallTrigger = true;
					jumpTrigger = false;
				}
			}
		}

	}


	if (fallTrigger)
	{
		if (!surfaceFlag1)
		{
			ypos = (velocity - dummyVar);
			dummyVar += jumpAcc;

			if (ypos >= 0 && ypos < 0.5f)
			{
				jumpCheckFlag = false;
				fallTrigger = false;
			}
		}

		if (surfaceFlag1)
		{
			ypos = (velocity - dummyVar);
			dummyVar += jumpAcc;

			if (ypos >= 5 && ypos < 5.5f)
			{
				jumpCheckFlag = false;
				fallTrigger = false;
			}
		}
	}

	if (atFirstFloor && (xpos <=60.0f || zpos >= 80.0f))
	{
		jumpTrigger = false;
		ypos = (velocity - dummyVar);
		dummyVar += jumpAcc;

		if (ypos >= 0 && ypos < 0.5f)
		{
			atFirstFloor = false;
		}
	}


	if (!timerStopperFlag)
		remainingTime -= 0.5f;
	if (remainingTime == 0.0f) timerStopperFlag = true;

	if(keyFlag) totalScore = (coinCount*1000) + (remainingTime*5) + 5000;
	else totalScore = (coinCount*1000) + (remainingTime*5);

	glutPostRedisplay();
	glutTimerFunc(1, Timer, 0);
}

void init(void){

	for(int i = 0; i < 256; i++)
	{
		keyStates[i] = false;
	}

	glShadeModel(GL_SMOOTH);
	glClearColor(0.7f, 0.6f, 0.65f, 0);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	 glPointSize(5);
	glEnable(GL_POINT_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);

	glutSetCursor(GLUT_CURSOR_NONE);

	randomCoin();

	Image* image = loadBMP("dirt.bmp");
	_textureId = loadTexture(image);
	delete image;

	Image* imageWall = loadBMP("stone.bmp");
	wallTexture = loadTexture(imageWall);
	delete imageWall;

	Image* imageGlass = loadBMP("stone.bmp");
	glassTex = loadTexture(imageGlass);
	delete imageGlass;

	Image* imageEndGame = loadBMP("message.bmp");
	endGameTexture = loadTexture(imageEndGame);
	delete imageEndGame;

	Image* imageEndGameWin = loadBMP("messagewin.bmp");
	endGameWinTexture = loadTexture(imageEndGameWin);
	delete imageEndGame;

}

void display(void)
{	
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

	calculateFacingSide();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	keyOperations();
	collisionCheck();

	//if not out of bound and did not finish the game, draw
	if(!exitFlag && !boundFlag && !monsterCollideFlag && !timerStopperFlag)
	{

		glLoadIdentity();

		gluLookAt(xpos-10*float(sin(yrotrad)), 4+ypos, zpos+10*float(cos(yrotrad)),
			xpos, ypos, zpos,
			0,1,0);

		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);

		glEnable(GL_STENCIL_TEST);

		glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
		glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE);


		
		if (!surfaceFlag1)
		{		
			glBindTexture(GL_TEXTURE_2D, _textureId);
			glBegin(GL_QUADS);
			glNormal3f(0,1.0f,0);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(floorVertices[0]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(floorVertices[1]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(floorVertices[2]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(floorVertices[3]);
			glEnd();
		}

		if (surfaceFlag1)
		{
			glBindTexture(GL_TEXTURE_2D, _textureId);
			glBegin(GL_QUADS);
			glNormal3f(0,1.0f,0);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(firstLevelVertices[0]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(firstLevelVertices[1]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(firstLevelVertices[2]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(firstLevelVertices[3]);
			glEnd();
		}
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);

		glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
		glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);

			glBindTexture(GL_TEXTURE_2D, _textureId);
			glBegin(GL_QUADS);
			glNormal3f(0,1.0f,0);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(floorVertices[0]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(floorVertices[1]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(floorVertices[2]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(floorVertices[3]);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, _textureId);
			glBegin(GL_QUADS);
			glNormal3f(0,1.0f,0);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(firstLevelVertices[0]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(firstLevelVertices[1]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(firstLevelVertices[2]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(firstLevelVertices[3]);
			glEnd();
		glPushMatrix();

		drawPlanes();

		glColor4f(0.0, 0.0, 0.0, 0.5f);

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glStencilOp(GL_KEEP,GL_KEEP,GL_INCR);


		
		if (!surfaceFlag1)
		{
			shadowmatrix(floorShadow, groundplane, lightPosition);
			glMultMatrixf((float *)floorShadow);
		}
		
		if (surfaceFlag1)
		{
			shadowmatrix(firstLevelShadow, groundplane, lightPosition);
			glMultMatrixf((float *)firstLevelShadow);
		}

		drawJohnAppleseedShadow();
		drawMonsterShadow();
		drawExitShadow();
		drawCoinShadow();

		if(!keyFlag)
			drawKeyShadow();

		drawPlanesShadow();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);

		glPopMatrix();

		glPushMatrix();
		glDisable(GL_STENCIL_TEST);

		drawJohnAppleseed();
		drawMonster();
		drawExit();
		drawCoin();

		if(!keyFlag)
			drawKey();

		//drawPlanes();
		//drawFirstLevel();
		drawFirstLevelSide1();
		drawFirstLevelSide2();

		glPopMatrix();

	}

	//if out of bounds, draw only a falling john
	if(boundFlag)
	{

		glLoadIdentity();

		gluLookAt(xpos-10*float(sin(yrotrad)), 4, zpos+10*float(cos(yrotrad)),
			xpos, 0, zpos,
			0,1,0);

		if(!fallFlag)
		{
			if (fallDegree < 90)
			{
				fallDegree +=1;
			}
			else if (fallDegree >= 90)
			{
				timerStopperFlag = true;
				glLoadIdentity();
				printEndGame();
			}

			//draw John Appleseed
			drawJohnAppleseed();

			//rotate camera & john
			glRotatef(yrot, 0.0, 1.0, 0.0);
			glTranslated(-xpos, 0.0f, -zpos);
			glColor3f(1.0f, 1.0f, 1.0f);
		}
	}

	if (monsterCollideFlag || monster2CollideFlag)
	{
		glLoadIdentity();
		printEndGame();
	}

	if (exitFlag)
	{
		glLoadIdentity();
		printWinGame();
	}

	glPushMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	char string[64];
	//sprintf(string, "Coin Count: ");
	
	char string2[256];
	//sprintf(string2, "\t\t\t\tTOTAL SCORE: ");
	
	//printtext(10,10,string, string2);

	if (remainingTime == 0.0f && timerStopperFlag)
	{
		glLoadIdentity();
		printEndGame();
	}

	sprintf(string, "Coin Count: ");
	sprintf(string2, "                                                                          TOTAL SCORE: ");
	printtext(10,10,string, string2);

	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h){

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}

void keyOperations (void) {

	if (!wallFlag){

		if (keyStates['w']){

			goForward = true;

			cout << "x: " << xpos <<" || z: " << zpos << " || y: " << ypos << " || dummyVar: " << dummyVar << endl << endl;
		}
	}

	if (keyStates['d']){

		turnRightFlag = true;

		cout << "yrot: " << yrot << ", yrotrad: " << yrotrad << endl << endl;
	}

	if (keyStates['a']){

		turnLeftFlag = true;

		cout << "yrot: " << yrot << ", yrotrad: " << yrotrad << endl << endl;
	}

	if (keyStates[' '])
		jumpTrigger = true;

	if (keyStates['q']){
		if (rot_cam <= 60)
			rot_cam += 1;
	}

	if (keyStates['z']){
		if (rot_cam >= 10 )
			rot_cam -= 1;
	}

	if (keyStates['r'])
		reStart();

	if (keyStates['g'])
		toggleShadow = true;

	if (keyStates['h'])
		toggleShadow = false;

	if (keyStates['1'])
	{
		glutLeaveGameMode();
		exit(0);
	}
}

void keyPressed (unsigned char key, int x, int y) {
	keyStates[key] = true; // Set the state of the current key to pressed
}

void keyUp (unsigned char key, int x, int y) {
	keyStates[key] = false; // Set the state of the current key to not pressed
}

void main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
 	glutGameModeString(screenRes);
 	glutEnterGameMode();
	//glutInitWindowSize(800,800);
	//glutInitWindowPosition(0,0);
	//glutCreateWindow("window");
	init();

	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	Timer(0);

	glutMainLoop();

}