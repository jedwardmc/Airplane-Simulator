/** AIRPLANE IN THE NIGHT SKY : ASSIGNMENT
 **
 ** This shows an airplane flying over a height field
 ** terrain.
 **
 ** WRITTEN by Jasper Fitzgerald-Cherry
 ** DATE 06.11.2018
 ** STUDENT ID u3144749
 **
 **/

#include "Assignment.h"
#include "SOIL.h"
#include "FileOperations.h"

static void switchPerspective(int type) {
    
    /**
     ** Switchs the perspective from the following
     ** views: The nose of the plane, above the plane,
     ** the tail of the plane.
     **/
    
    switch(type) {
        case PERSP_NOSE:
            // Change the view to the nose of the plane
            rotY += 0.04f;
            rotAngle = -90;
            
            break;
        case PERSP_ABOVE:
            // Change the view to above the plane
           // gluLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ);
            break;
        case PERSP_TAIL:
            // Change the view to the tail of the plane
            //gluLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ);
            break;
    }
}

static void drawStars(int quantity) {
    /**
     ** Creates randomized collection of stars in the night sky.
     **/
  
    double pos[] = {-0.2, -0.5, 0.5, 0.2, 0.1};
    int j, k;
    long rand = random();
    
    glPointSize(9.0f);
    glBegin(GL_POINTS);
    for(j=0; j < quantity; j++){
        for(k=0; k < quantity; k++) {
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(pos[k] * rand, 0.5f, -0.5f);
      glVertex3f(pos[k] * rand, -0.5f, 0.5f);
            glVertex3f(pos[k+1] * rand, 0.5f, 0.5f);
            
            glVertex3f(pos[k+1] * rand, 0.5f, 0.5f);
        }
    }
        glEnd();

}


static void renderTerrain() {
    
    /***
     *** This creates terrain using height map fields loaded
     *** from local text files.
     ***
     ***/
    
    // for each file listed in height map directory
    // read height fields from the text file
    // if the extension does not match .txt
    // return an error
    // else
    // continue
    // end
    // end
    
    
    
    
    
    
    // render the terrain using the newly created height field arrays
    
    
    ter->render();
    
    
    
    
}

static void renderAirplane(GLfloat posX, GLfloat posY, GLfloat posZ) {
    
    /*** RESET THE IDENTITY MATRIX ***/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    /*** ENABLE DEPTH TESTING ***/
    glEnable(GL_DEPTH_TEST);
    
    /*** ENABLE TEXTURING FOR THE AIRPLANE ***/
    glEnable(GL_TEXTURE_2D);
    
    /*** LOAD AN IMAGE FROM THE LOCAL DIRECTORY ***/
    
    imagePtr = SOIL_load_image("/Users/jfc/Desktop/BoeingAssignment/final/Assignment/Assignment/stoneTexture.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
    
    /*** GENERATE THE TEXTURES FOR THE AIRPLANE ***/
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, imagePtr);

    /*** SET THE PARAMETERS FOR THE TEXTURING ***/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    

    /*** TRANSLATE THE AIRPLANE INTO VIEW ***/
   // glTranslatef( posX, 0, posZ );
    
     glRotatef(45, rotX, -rotY, rotZ);
    glTranslatef(posX, posY, posZ);
    
    /*** DRAW THE NOSE OF THE AIRCRAFT ***/
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    gluQuadricDrawStyle(nose, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, texId);
    gluQuadricTexture(nose, GL_TRUE);
    gluQuadricNormals(nose, GLU_SMOOTH);
    glRotatef(-90, 0, 2, 0);
    glTranslatef(noseX, noseY, noseZ);
    gluSphere(nose, noseDiameter, 24, 24);
    glPopMatrix();
    
    /*** DRAW THE BODY OF THE AIRCRAFT ***/

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glRotatef(-90, 0, 2, 0);
    gluQuadricDrawStyle(body, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, texId);
    gluQuadricTexture(body, GL_TRUE);
    gluQuadricNormals(body, GLU_SMOOTH);
    glTranslatef(bodyX, bodyY, bodyZ);
    gluCylinder(body, noseDiameter, noseDiameter, bodyLength, 10.0f, 10.0f);
    glPopMatrix();
    
    /*** DRAW THE WINGS OF THE AIRCRAFT ***/
    
    /**** WING ONE ****/
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, texId);
    glTexCoord2f(0, 1); glVertex3f(-wingDispX, wingDispY, wingDispZ); // P1;
    glTexCoord2f(0, 0); glVertex3f(-wingDispX+(wingStepX),    wingDispY, wingDispZ); // P2;
    glTexCoord2f(1, 0); glVertex3f(-wingDispX+(wingStepX*2),  wingDispY, wingDispZ*3); // P3;
    glTexCoord2f(1, 1); glVertex3f(-wingDispX+(wingStepX*3),  wingDispY, wingDispZ*5); // P4;
    glEnd();
    
    /**** WING TWO ****/
    glBegin(GL_QUADS);
    glColor3f(1.0f,1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexCoord2f(0, 1); glVertex3f(-wingDispX, wingDispY, -wingDispZ); // P1;
    glTexCoord2f(0, 0); glVertex3f(-wingDispX+(wingStepX), wingDispY, -wingDispZ); // P2;
    glTexCoord2f(1, 0); glVertex3f(-wingDispX+(wingStepX*2), wingDispY, -wingDispZ*3); // P3;
    glTexCoord2f(1, 1); glVertex3f(-wingDispX+(wingStepX*3), wingDispY, -wingDispZ*5); // P4;
    glEnd();
    
    /*** Lower region of wing one ***/
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0, 1); glVertex3f(-wingDispX, -wingDispY, wingDispZ); // translated to negative y axis
    glTexCoord2f(0, 0); glVertex3f(-wingDispX + wingStepX, -wingDispY, wingDispZ);
    glTexCoord2f(1, 0); glVertex3f(-wingDispX + (wingStepX*2), -wingDispY, wingDispZ);
    glTexCoord2f(1, 1); glVertex3f(-wingDispX + (wingStepX*3), -wingDispY, wingDispZ);
    glEnd();
    
    /*** Lower region of wing two ***/
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0, 1);
    glTexCoord2f(0, 0);
    glTexCoord2f(1, 0);
    glTexCoord2f(1, 1);
    glEnd();
    
    // write the code for the sign
    
    
    
    /*** DRAW THE TAIL FOR THE AIRCRAFT ***/
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, texId);
    glTexCoord2f(0, 1); glVertex3f(-0.5f, flapY, flapZ);
    glTexCoord2f(0, 0); glVertex3f(0.0f, flapY, flapZ);
    glTexCoord2f(1, 0); glVertex3f(-0.2f, flapY-flapY, flapZ);
    glTexCoord2f(1, 1); glVertex3f(-1.0f, flapY-flapY, flapZ);
    //glVertex3f(-1.5f, flapY, flapZ);
    glEnd();
    
    
    /*** DRAW THE BACK TAIL WINGS ***/
    
    /*** TAIL ONE ***/
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexCoord2f(0, 1); glVertex3f(-0.2f, 0.0f, -0.125f);
    glTexCoord2f(0, 0); glVertex3f(0.0f, 0.0f, -0.8f);
    glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.0f, -0.8f);
    glTexCoord2f(1, 1); glVertex3f(-0.8f, 0.0f, -0.125f);
    glEnd();
    
    /*** TAIL TWO ***/
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, texId);
    glTexCoord2f(0, 1); glVertex3f(-0.8f, 0.0f, 0.25f);
    glTexCoord2f(0, 0); glVertex3f(-0.2f, 0.0f, 0.125f);
    glTexCoord2f(1, 0); glVertex3f(0.0f, 0.0f, 0.8f);
    glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.0f, 0.8f);
    glEnd();
    
    
    /*** DRAW THE EXHAUST FOR THE AIRCRAFT ***/
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    
    gluQuadricDrawStyle(exhaust, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, texId);
    gluQuadricTexture(exhaust, GL_TRUE);
    gluQuadricNormals(exhaust, GLU_SMOOTH);
    
    
    glRotatef(-90, 0, 2, 0);
    gluCylinder(exhaust, exhaustDiameter, exhaustPipe, exhaustLength, 10.0f, 10.0f);
    glPopMatrix();
    
}

static void setProjection3D() {
    GLfloat aspect;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    aspect = (float) WindowWidth / (float) WindowHeight;
    gluPerspective(fov, aspect, near, far);
    glMatrixMode(GL_MODELVIEW);
    setCamera();
}

static void setProjection2D() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WindowWidth, 0, WindowHeight, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
}

static void setCamera() {
    glLoadIdentity();
    gluLookAt(camera[0], camera[1], camera[2],
              lookAtPoint[0], lookAtPoint[1], lookAtPoint[2],
              upVec[0], upVec[1], upVec[2]);
}

static void setParams() {
    
    /*** CAMERA PARAMETERS ***/
    
    camera[0] = 12.0;
    camera[1] = 12.0;
    camera[2] = 26.0;
    
    lookAtPoint[0] = 0;
    lookAtPoint[1] = 0;
    lookAtPoint[2] = 0;
    
    upVec[0] = 0;
    upVec[1] = 1;
    upVec[2] = 0;
    
    fov  = 60;
    near = 0.5;
    far  = 900;
    
    spinAngle = 0.0;
    
}

static void setUpLighting() {
    /*** Set up lighting for the scene ***/
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    
    light0->addLight();
}


static void display() {
    
    /** Set the 3D and camera parameters **/
    setProjection3D();
    setCamera();
    
    
    /** draw the stars in the night sky **/
    
    
    /*** VIEW PARAMETERS ***/
    glPushMatrix();
    if(showWireFrame) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    if(showDepth) {
        glEnable(GL_DEPTH_TEST);
        glDepthRange(near, far);
        glClearDepth(far);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
    
    if(showLighting) {
        glEnable(GL_LIGHTING);
        /*** Set up lighting for the airplane ***/
        setUpLighting();
    } else {
        glDisable(GL_LIGHTING);
    }
    
    if(showCulling) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        
        if(clockWise) glFrontFace(GL_CW);
        else glFrontFace(GL_CCW);
    } else {
        glDisable(GL_CULL_FACE);
    }
    

    
    /**
     ** Render the Boeing style aircraft - the function
     ** takes position values to move the airplane around
     **/

    renderAirplane(xpos, ypos, -4.0f);

    
    if(showGridAndAxes) {
        axes->render();
        glColor3f(1.0, 1.0, 1.0);
        grid->render();
    }
    
    
    
    
    glPopMatrix();
    
    glPushMatrix();
        drawStars(100);
    glPopMatrix();
    
    glPushMatrix();
        renderTerrain();
    glPopMatrix();
    /** Swap the buffers **/
    glutSwapBuffers();
    
}

void mainKeyboard(unsigned char key, int x, int y) {
    switch(key) {
        case ',':
            /** Moves the airplane forward **/
            xpos-=0.4f;
            zpos-=0.4f;
            break;
        case '.':
            /** Returns the plane to initial position **/
            xpos += 0.4f;
            zpos += 0.4f;
            break;
        case 'l':
            /** Tilts the airplane to the left **/
            
            rotX -= 0.04f;
            rotY -= 0.04f;
            rotZ -= 0.04f;
            
            printf("rotX: %0.2f, rotY: %0.2f, rotZ: %0.2f, rotAngle: %0.2f\n", rotX, rotY, rotZ, rotAngle);
            break;
        case 'r':
            /** Tilts the airplane to the right **/
            rotX += 0.04f;
            rotY += 0.04f;
            rotZ += 0.04f;
            rotAngle = 90;
            printf("rotX: %0.2f, rotY: %0.2f, rotZ: %0.2f, rotAngle: %0.2f\n", rotX, rotY, rotZ, rotAngle);

            break;
        case 'w':
            /** Shows the wireframe **/
            showWireFrame = !showWireFrame;
            break;
        case 'v':
            /** Enables/disables depth buffering **/
            showDepth = !showDepth;
            break;
        case 'j':
            showLighting = !showLighting;
            break;
            
        case 'c':
            /*** Enables/disables culling ***/
            showCulling = !showCulling;
            break;
        case 'm':
            /** Zooms out the view **/
            break;
        case 'p':
            /** Zooms in the view **/
            break;
        case 'u':
            /*** Airplane ascends upward ***/
            break;
        case 'd':
            /*** Airplane descends downward ***/
            break;
        case 'b':
            /*** Swivels airplane to the left ***/
            break;
        case 'n':
            /*** Swivels airplane to right ***/
            break;
            
        case '1':
            /** Perspective to the nose **/
            switchPerspective(PERSP_NOSE);
            break;
        case '2':
            /** Above the nose **/
            switchPerspective(PERSP_ABOVE);
            break;
        case '3':
            /** The tail of the plane **/
            switchPerspective(PERSP_TAIL);
            break;
        case 'k':
            showGridAndAxes = !showGridAndAxes;
            break;
            
    }
}


void specialKeyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            camera[2] = camera[2] - 2;
            break;
            
        case GLUT_KEY_DOWN:
            camera[2] = camera[2] + 2;
            break;
            
        case GLUT_KEY_PAGE_UP:
            camera[1] = camera[1] + 2;
            break;
        case GLUT_KEY_PAGE_DOWN:
            camera[1] = camera[1] - 2;
            break;
            
        case GLUT_KEY_LEFT:
            camera[0] = camera[0] + 2;
            break;
        case GLUT_KEY_RIGHT:
            camera[0] = camera[0] - 2;
            break;
    }
}

void reshape(int width, int height) {
    WindowWidth  = width;
    WindowHeight = height;
    
    glViewport(0, 0, WindowWidth, WindowHeight);
}

void timer (int value){
    timeForNextFrame = true;
    glutTimerFunc(timerMSecs, timer, 0);
}

void idleRoutine() {
    if (timeForNextFrame) {
        spinAngle += 0.4f;
        
        if(spinAngle > 360.0) {
            spinAngle -= 360.0;
            glutPostRedisplay();
            timeForNextFrame = false;
            
            if (angleVar < angle) {
                angleVar += 1;
                
                if(angleVar > angle) angleVar = angle;
            }
            
            if(angleVar > angle) {
                angleVar -= 1;
                
                if(angleVar < angle) angleVar = angle;
            }
        }
    }
}


void init() {
    
    /** Set the view parameters **/
    setParams();
    
    /** Declare all airplane quadrics **/
    nose    = gluNewQuadric();
    body    = gluNewQuadric();
    exhaust = gluNewQuadric();
    
    /*** Declare lighting for the scene ***/
    light0  = new Light();
    
    /*** Create the axes ***/
    axes = new Axes();
    grid = new Grid();
    ter  = new Terrain();
    
    /*** Set up the grid ***/
     grid->setUp(20, 20, 10, 10);
    
    /** Declare all necessary objects
     lighting    = new Light();
     airplane    = new Airplane();
     terrain     = new Terrain();
     strip       = new Strip();
     sky         = new Skybox();
     
     And initialize them
     airplane->init();
     terrain->init();
     strip->init();
     sky->init();
     
     Enable texturing and lighting
     glEnable(GL_TEXTURE_2D);
     **/
    
    
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 75);
    glutCreateWindow("Assignment : Airplane In Night Sky");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(mainKeyboard);
    glutSpecialFunc(specialKeyboard);
    glutIdleFunc(idleRoutine);
    glutTimerFunc(timerMSecs, timer, 0);
    
    glutMainLoop();
    
    return 0;
    
}
