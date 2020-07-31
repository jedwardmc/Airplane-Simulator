#include "Terrain.h"

void Terrain::setUp(GLfloat xsizeZ, GLfloat zsizeZ, int xstepsZ, int zstepsZ) { 
    xsize = xsizeZ;
    zsize = zsizeZ;
    xsteps = xstepsZ;
    zsteps = zstepsZ;
}

void Terrain::setMaterialHeight(GLfloat height) { 
    if (height >= highHeight) {
        matHigh->setMaterial();
    } else {
        if (height > grassHeight) {
            matLand->setMaterial();
        } else {
            matBeach->setMaterial();
        }
    }
}

int Terrain::render() { 
    glPushMatrix();
    
    GLfloat xdelta = xsize/xsteps;
    GLfloat zdelta = zsize/zsteps;
    
    glNormal3f(0, 1, 0);
    
    for (int x=0; x < xsteps-1; x++) {
        for (int z=0; z < zsteps-1; z++) {
            glBegin(GL_TRIANGLES);
            setMaterialHeight(map[x][z]);
            glVertex3f(xdelta*x,map[x][z],zdelta*z);
            setMaterialHeight(map[x+1][z]);
            glVertex3f(xdelta*x+xdelta,map[x+1][z],zdelta*z);
            setMaterialHeight(map[x][z+1]);
            glVertex3f(xdelta*x,map[x][z+1],zdelta*z+zdelta);
            glEnd();
            
            glBegin(GL_TRIANGLES);
            setMaterialHeight(map[x+1][z+1]);
            glVertex3f(xdelta*x+xdelta,map[x+1][z+1],zdelta*z+zdelta);
            setMaterialHeight(map[x][z+1]);
            glVertex3f(xdelta*x,map[x][z+1],zdelta*z+zdelta);
            setMaterialHeight(map[x+1][z]);
            glVertex3f(xdelta*x+xdelta,map[x+1][z],zdelta*z);
            glEnd();
        }
    }
    glPopMatrix();
    return true;
}

int Terrain::renderLines() { 
    glPushMatrix();
    
    matLines->setMaterial();
    
    GLfloat xdelta=xsize/xsteps;
    GLfloat zdelta=zsize/zsteps;
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glBegin(GL_TRIANGLES);
    glNormal3f(0,1,0); // yes veronica all normals point up (students need to fix this)
    for (int x=0; x<xsteps-1; x++)
        for (int z=0; z<zsteps-1; z++)
        {
            glVertex3f(xdelta*x,0.01+map[x][z],zdelta*z);
            glVertex3f(xdelta*x+xdelta,0.01+map[x+1][z],zdelta*z);
            glVertex3f(xdelta*x,0.01+map[x][z+1],zdelta*z+zdelta);
            
            glVertex3f(xdelta*x+xdelta,0.01+map[x+1][z+1],zdelta*z+zdelta);
            glVertex3f(xdelta*x,0.01+map[x][z+1],zdelta*z+zdelta);
            glVertex3f(xdelta*x+xdelta,0.01+map[x+1][z],zdelta*z);
        }
    
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPopMatrix();
    
    return true;
}

Terrain::Terrain() { 
    mat = new MaterialClass();
    matLines = new MaterialClass();
    mat->setMaterialJade();
    matLines->setMaterialBlackRubber();
    
    matHigh  = new MaterialClass();
    matBeach = new MaterialClass();
    matLand  = new MaterialClass();
    
    matHigh->setMaterialPearl();
    matBeach->setMaterialYellowSand();
    matLand->setMaterialGreenGrass();
    
    mapWidth=48;
    mapHeight=48;
    
    GLfloat m0[]={0,0,0,0,0,0};
    GLfloat m1[]={0,0.2,0.3,0.1,0.2,0};
    GLfloat m2[]={0,1,1.5,3,2,0};
    GLfloat m3[]={0,1,2,1.5,2,0};
    GLfloat m4[]={0,1,0.4,0.2,0.2,0};
    GLfloat m5[]={0,0,0,0,0,0};
    for (int i=0; i<6; i++) map[0][i]=m0[i];
    for (int i=0; i<6; i++) map[1][i]=m1[i];
    for (int i=0; i<6; i++) map[2][i]=m2[i];
    for (int i=0; i<6; i++) map[3][i]=m3[i];
    for (int i=0; i<6; i++) map[4][i]=m4[i];
    for (int i=0; i<6; i++) map[5][i]=m5[i];
    
    
    setUp(mapWidth,mapHeight,mapWidth,mapHeight);
    
    highHeight=2.8;
    grassHeight=0.5;
}

Terrain::~Terrain() { 
    delete mat;
    delete matLines;
    delete matBeach;
    delete matHigh;
    delete matLand;
}
