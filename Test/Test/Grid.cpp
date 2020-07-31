#include "Grid.h"



void Grid::setUp(GLfloat xsizeZ, GLfloat zsizeZ, int xstepsZ, int zstepsZ) { 
    xsize = xsizeZ;
    zsize = zsizeZ;
    xsteps = xstepsZ;
    zsteps = zstepsZ;
}

int Grid::render() { 
    glPushMatrix();
    
    GLfloat xdelta=xsize/xsteps;
    GLfloat zdelta=zsize/zsteps;
    glBegin(GL_QUADS);
    glNormal3f(0,1,0); // yes veronica all normals point up
    for (int x=0; x<xsteps; x++)
        for (int z=0; z<zsteps; z++)
        {
            glVertex3f(xdelta*x,0,zdelta*z+zdelta);
            glVertex3f(xdelta*x+xdelta,0,zdelta*z+zdelta);
            glVertex3f(xdelta*x+xdelta,0,zdelta*z);
            glVertex3f(xdelta*x,0,zdelta*z);
        }
    
    glEnd();
    glPopMatrix();
    return true;
}

int Grid::renderCW() { 
    glPushMatrix();
    
    GLfloat xdelta=xsize/xsteps;
    GLfloat zdelta=zsize/zsteps;
    glBegin(GL_QUADS);
    glNormal3f(0,1,0); // yes veronica all normals point up
    for (int x=0; x<xsteps; x++)
        for (int z=0; z<zsteps; z++)
        {
            glVertex3f(xdelta*x,0,zdelta*z);
            glVertex3f(xdelta*x+xdelta,0,zdelta*z);
            glVertex3f(xdelta*x+xdelta,0,zdelta*z+zdelta);
            glVertex3f(xdelta*x,0,zdelta*z+zdelta);
        }
    
    glEnd();
    glPopMatrix();
    return true;
}

int Grid::renderLines() { 
    glPushMatrix();
    
    GLfloat xdelta=xsize/xsteps;
    GLfloat zdelta=zsize/zsteps;
    
    glPolygonMode(GL_BACK, GL_LINE);
    glPolygonMode(GL_FRONT, GL_FILL);
    
    glBegin(GL_QUADS);
    glNormal3f(0,1,0); // yes veronica all normals point up
    for (int x=0; x<xsteps; x++)
        for (int z=0; z<zsteps; z++)
        {
            glVertex3f((GLfloat)xdelta*x,(GLfloat)0.01,(GLfloat)zdelta*z); // grid above and below surface
            glVertex3f((GLfloat)xdelta*x+xdelta,(GLfloat)0.01,(GLfloat)zdelta*z);
            glVertex3f((GLfloat)xdelta*x+xdelta,(GLfloat)0.01,(GLfloat)zdelta*z+zdelta);
            glVertex3f((GLfloat)xdelta*x,(GLfloat)0.01,(GLfloat)zdelta*z+zdelta);
            glVertex3f((GLfloat)xdelta*x,(GLfloat)-0.01,(GLfloat)zdelta*z);
            glVertex3f((GLfloat)xdelta*x+xdelta,(GLfloat)-0.01,(GLfloat)zdelta*z);
            glVertex3f((GLfloat)xdelta*x+xdelta,(GLfloat)-0.01,(GLfloat)zdelta*z+zdelta);
            glVertex3f((GLfloat)xdelta*x,(GLfloat)-0.01,(GLfloat)zdelta*z+zdelta);
        }
    
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPopMatrix();
    return true;
}

Grid::Grid() { 
    setUp(1,1,5,5);
}

Grid::~Grid() { 
}
