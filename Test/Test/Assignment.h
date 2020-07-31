#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <stdio.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "vec3.h"
#include "Light.h"
#include "Axes.h"
#include "Grid.h"
#include "Terrain.h"

/*** OBJECTS ***/

Light *light0;
MaterialClass *mat0;
Axes *axes;
Grid *grid;
Terrain *ter;

/*** CAMERA PARAMETERS ***/
static GLfloat camera[3];
static GLfloat lookAtPoint[3];
static GLfloat upVec[3];
static GLfloat spinAngle;
static GLfloat fov;
static GLfloat near;
static GLfloat far;

/*** BOOLEAN PARAMETERS ***/
bool showWireFrame      = false;
bool showDepth          = false;
bool showCulling        = false;
bool clockWise          = false;
bool showGridAndAxes    = false;
bool showLighting       = false; 

/*** IDLE PARAMETERS ***/
GLfloat angle    = 0;
GLfloat angleVar = 0;

/*** PERSPECTIVE CONSTANTS ***/
#define PERSP_NOSE   1
#define PERSP_ABOVE  2
#define PERSP_TAIL   3

/*** WINDOW RESIZING PARAMETERS ***/
static int WindowWidth, WindowHeight;

/*** POSITIONING VARIABLES ***/
static GLfloat xpos = 5.0;
static GLfloat ypos = 0.0;
static GLfloat zpos = 0.0;

/*** TIMER PARAMETERS ***/
#define framesPerSecond 25
#define timerMSecs ((int) 1000 / framesPerSecond)
bool timeForNextFrame = false;

/*** AIRPLANE QUADRICS ***/
GLUquadric *nose;
GLUquadric *body;
GLUquadric *exhaust;

/*** WING VARIABLES ***/
GLfloat wingDispX = 2.5f;
GLfloat wingDispY = 0.15625f;
GLfloat wingDispZ = 0.25f;

/*** AIRPLANE RESIZING VARIABLES ***/
GLfloat wingStepX = 0.5f;

/*** AIRPLANE SIZE VARIABLES ***/
GLfloat bodyLength      = 2.0f;
GLfloat noseDiameter    = 0.3125f;
GLfloat exhaustPipe     = 0.3f;
GLfloat exhaustLength   = 1.0f;
GLfloat exhaustDiameter = 0.0625f;

/*** TAIL VARIABLES ***/
GLfloat flapX = 0.0f; // change this later
GLfloat flapY = 0.75f;
GLfloat flapZ = 0.0f;


/*** AIRPLANE ROTATION VARIABLES ***/
GLfloat rotAngle = 90.0f;
GLfloat rotX     = 0.0f;
GLfloat rotY     = 2.0f;
GLfloat rotZ     = 0.0f;

/*** NOSE VARIABLES ***/
GLfloat noseZ = bodyLength + 1.0f;
GLfloat noseX = 0.0f;
GLfloat noseY = 0.0f;

/*** BODY VARIABLES ***/
GLfloat bodyX = 0.0f;
GLfloat bodyY = 0.0f;
GLfloat bodyZ = 1.0f;

/*** FUNCTION PROTOTYPES ***/
static void switchPerspective(int type);
static void renderAirplane(GLfloat posX, GLfloat posY, GLfloat posZ);
static void setProjection3D();
static void setCamera();
static void setParams();
static void display();
void mainKeyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void reshape(int width, int height);
void timer(int value);
void idleRoutine();
void init();

/*** TEXTURE VARIABLES FOR THE AIRPLANE ***/

GLuint texId;
unsigned char *imagePtr;
int width;
int height;

#endif /* ASSIGNMENT_H */
