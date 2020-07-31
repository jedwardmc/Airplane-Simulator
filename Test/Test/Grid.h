#ifndef Grid_h
#define Grid_h

#include <stdio.h>
#include <string.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Grid {
protected:
    GLfloat xsize;
    GLfloat zsize;
    int xsteps;
    int zsteps;
    
public:
    void setUp(GLfloat xsizeZ, GLfloat zsizeZ, int xstepsZ, int zstepsZ);
    int render();
    int renderCW();
    int renderLines();
    Grid();
    ~Grid();
    
};



#endif /* Grid_h */
