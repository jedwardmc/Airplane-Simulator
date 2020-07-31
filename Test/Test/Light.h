//
//  Light.h
//  Assignment
//
//  Created by Jasper Fitzgerald-Cherry on 06/11/2018.
//  Copyright © 2018 JFC. All rights reserved.
//

#ifndef Light_h
#define Light_h

#include <stdio.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class MaterialClass {
public:
    float dif[4];
    float amb[4];
    float spe[4];
    float eme[4];
    
    int shiny;
    
    void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setEmissive(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setShinyInt(int shinyZ);
    void setShinyFloat(GLfloat shinyZ);
    
    virtual void setMaterial();
    MaterialClass();
    
    void setMaterialJade();
    void setMaterialRedPlastic();
    void setMaterialWhiteRubber();
    void setMaterialBlackRubber();
    void setMaterialPearl();
    void setMaterialYellowSand();
    void setMaterialGreenGrass();
    
};

class Light {
public:
    enum Kind {normal, spot};
    
protected:
    GLUquadricObj *quadric;
    
    GLfloat lpos[4];
    GLfloat ldif[4];
    GLfloat lamb[4];
    GLfloat lspe[4];
    
    GLfloat lmodel_ambient[4];
    GLfloat spotLightDir[3];
    GLfloat spotAngle;
    
    bool showAsSphere;
    GLfloat radius;
    Kind kind;
    void init();
    int lightID;
    
    MaterialClass *mat;
    
public:
    
    void setRadius(GLfloat r);
    void setKind(Kind k);
    void setLightID(int id);
    void setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setGlobalAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setSpotDir(GLfloat x, GLfloat y, GLfloat z);
    void setSpotAngle(GLfloat a);
    
    void addLight();
    void addDark();
    
    void renderA(bool notColour);
    virtual int render();
    
    Light();
    ~Light(); 
    
};



#endif /* Light_h */
