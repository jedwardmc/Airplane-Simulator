#include "Axes.h"



void Axes::drawLabeledAxesP(GLfloat len, GLfloat textSize) { 
    GLfloat lenP;
    lenP=len+textSize;
    drawAxesP(len);
    glBegin(GL_LINES);
    // Paint an "X" in red...
    glColor3f (1.0, 0.0, 0.0);
    glVertex3f(lenP, textSize, textSize);
    glVertex3f(lenP,-textSize,-textSize);
    
    glVertex3f(lenP, textSize,-textSize);
    glVertex3f(lenP,-textSize, textSize);
    
    // Paint a "Y" in green...
    glColor3f(0.0, 0.8f, 0.0);
    glVertex3f( textSize,lenP, textSize);
    glVertex3f(-textSize,lenP,-textSize);
    
    glVertex3f(textSize, lenP,-textSize);
    glVertex3f(0.0,  lenP, 0.0);
    
    // Paint a "Z", in blue...
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f( textSize, textSize, lenP);
    glVertex3f(-textSize,-textSize, lenP);
    
    glVertex3f( textSize, textSize, lenP);
    glVertex3f(-textSize, textSize, lenP);
    
    glVertex3f( textSize, -textSize, lenP);
    glVertex3f(-textSize, -textSize, lenP);
    glEnd();
}

void Axes::setLen(GLfloat len) {
    length = len;
}

void Axes::setTextSize(GLfloat t) { 
    tsize = t;
}

int Axes::render() { 
    glPushMatrix();
    drawLabeledAxesP(length, tsize);
    glPopMatrix();
    return true;
}

void Axes::drawAxesP(GLfloat len) { 
    glBegin(GL_LINES);
    //red x axis
    glColor3f(1, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(len, 0.0, 0.0);
    //green y axis
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, len, 0.0);
    //blue z axis
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, len);
    glEnd();
}

Axes::Axes() { 
    length=1;
    tsize=0.2f;
}
