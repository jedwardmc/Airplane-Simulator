#ifndef Terrain_h
#define Terrain_h

#include <stdio.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Light.h"
#include "FileOperations.h"

class Terrain {
protected:
    GLfloat xsize;
    GLfloat zsize;
    int xsteps;
    int zsteps;
    
    GLfloat map[MAX_WIDTH][MAX_DEPTH];
    int mapInt[MAX_WIDTH][MAX_DEPTH];
    
public:
    
    int mapWidth, mapHeight;
    MaterialClass *mat;
    MaterialClass *matLines;
    MaterialClass *matHigh;
    MaterialClass *matBeach;
    MaterialClass *matLand;
    
    GLfloat highHeight;
    GLfloat grassHeight;
    
    void setUp(GLfloat xsizeZ, GLfloat zsizeZ, int xstepsZ, int zstepsZ);
    void setMaterialHeight(GLfloat height);
    
    virtual int render();
    virtual int renderLines();
    Terrain();
    ~Terrain();
};


#endif /* Terrain_h */
