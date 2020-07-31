#ifndef Axes_h
#define Axes_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Axes {
protected:
    void drawLabeledAxesP(GLfloat len, GLfloat textSize);
    
public:
    GLfloat length;
    GLfloat tsize;
    
    void setLen(GLfloat len);
    void setTextSize(GLfloat t);
    
    virtual int render();
    void drawAxesP(GLfloat len);
    Axes();
};


#endif /* Axes_h */
