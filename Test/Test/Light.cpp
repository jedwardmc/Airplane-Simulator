//
//  Light.cpp
//  Assignment
//
//  Influenced by Visual and Interactive Computing
//  tutorial materials. Credited to Rob Cox at
//  University of Canberra. 
//

#include "Light.h"

Light::Light() {
    init();
    
    mat = new MaterialClass();
    mat->setAmbient(0, 0, 0, 1);
    mat->setDiffuse(0, 0, 0, 1);
    mat->setSpecular(0, 0, 0, 1);
}

Light::~Light() {
    gluDeleteQuadric(quadric);
    delete mat;
}

void Light::setLightID(int id) {
    lightID = id;
}

void Light::init() {
    radius = 0.2f;
    setKind(normal);
    quadric = gluNewQuadric();
    setPosition(5, 5, 5, 0);
    setDiffuse(1, 1, 1, 1);
    setAmbient(0, 0, 0, 1);
    setSpecular(0, 0, 0, 1);
    setGlobalAmbient(0, 0, 0, 1);
    setSpotDir(-1, -1, -1);
    setSpotAngle(45);
    lightID = GL_LIGHT0;
}

void Light::setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    lpos[0] = x;
    lpos[1] = y;
    lpos[2] = z;
    lpos[3] = w;
}

void Light::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    ldif[0] = r;
    ldif[1] = g;
    ldif[2] = b;
    ldif[3] = a;
}

void Light::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    lamb[0] = r;
    lamb[1] = g;
    lamb[2] = b;
    lamb[3] = a;
}

void Light::setGlobalAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    lmodel_ambient[0] = r;
    lmodel_ambient[1] = g;
    lmodel_ambient[2] = b;
    lmodel_ambient[3] = a;
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}

void Light::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    lspe[0] = r;
    lspe[1] = g;
    lspe[2] = b;
    lspe[3] = a;
}

void Light::setRadius(GLfloat r) {
    radius = r;
}

void Light::setKind(Kind k) {
    kind = k;
}

int Light::render() {
    renderA(false);
    return true;
}

void Light::renderA(bool notColour) {
    if(!showAsSphere) return;
    
    glPushMatrix();
    
    mat->setEmissive(ldif[0], ldif[1], ldif[2], 1);
    
    if(notColour) mat->setEmissive(0.5, 0.5, 0.5, 1);
    mat->setMaterial();
    
    glutSolidSphere(radius, 11, 11);
    
    if (kind == spot) {
        glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(spotLightDir[0], spotLightDir[1], spotLightDir[2]);
        glEnd();
    }
    
    glPopMatrix();
    return;
    
}

void Light::addDark() {
    glDisable(lightID);
}

void Light::addLight() {
    glEnable(lightID);
    glLightfv(lightID, GL_POSITION, lpos);
    glLightfv(lightID,GL_AMBIENT,lamb);
    glLightfv(lightID,GL_DIFFUSE,ldif);
    glLightfv(lightID,GL_SPECULAR,lspe);
    if (kind==spot)
    {
        glLightfv(lightID, GL_SPOT_DIRECTION, spotLightDir);
        glLightf(lightID, GL_SPOT_CUTOFF,spotAngle);
    }
    else
    {
        glLightf(lightID, GL_SPOT_CUTOFF,180);
    }
    
}

void Light::setSpotDir(GLfloat x, GLfloat y, GLfloat z)
{
    spotLightDir[0]=x;
    spotLightDir[1]=y;
    spotLightDir[2]=z;
}

void Light::setSpotAngle(GLfloat a)
{
    spotAngle=a;
}

/*********************************************************************************************/

MaterialClass::MaterialClass()
{
    // white rubber aS DEFAULT
    setMaterialWhiteRubber();
}

void MaterialClass::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    dif[0]=r;
    dif[1]=g;
    dif[2]=b;
    dif[3]=a;
}

void MaterialClass::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    amb[0]=r;
    amb[1]=g;
    amb[2]=b;
    amb[3]=a;
}

void MaterialClass::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    spe[0]=r;
    spe[1]=g;
    spe[2]=b;
    spe[3]=a;
}

void MaterialClass::setEmissive(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    eme[0]=r;
    eme[1]=g;
    eme[2]=b;
    eme[3]=a;
}

void  MaterialClass::setMaterial()
{
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,dif);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spe);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,eme);
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
}

void MaterialClass::setShinyInt(int shinyZ)
{
    shiny = shinyZ;
}

void MaterialClass::setShinyFloat(GLfloat shinyZ)
{
    shiny = (int)shinyZ;
}

void MaterialClass::setMaterialJade()
{
    setAmbient(0.135f, 0.2225f, 0.1575f ,1);
    setDiffuse(0.54f, 0.89f, 0.63f ,1);
    setSpecular(0.316228f, 0.316228f, 0.316228f ,1);
    setEmissive(0,0,0,0);
    setShinyInt((int)(0.1*128.0));
}

void MaterialClass::setMaterialRedPlastic()
{
    setAmbient(0.0,0.0,0.0,1);
    setDiffuse(0.5f,0,0,1);
    setSpecular(0.7f,0.6f,0.6f,1);
    setEmissive(0,0,0,0);
    setShinyInt((int)(0.25*128.0));
}

void MaterialClass::setMaterialWhiteRubber()
{
    setAmbient(0.05f,0.05f,0.05f,1);
    setDiffuse(0.5f,0.5f,0.5f,1);
    setSpecular(0.7f,0.7f,0.7f,1);
    setEmissive(0,0,0,0);
    setShinyInt((int)(0.078125*128.0));
}

void MaterialClass::setMaterialBlackRubber()
{
    setAmbient(0.02f, 0.02f, 0.02f ,1);
    setDiffuse(0.01f, 0.01f, 0.01f ,1);
    setSpecular(0.4f, 0.4f, 0.4f ,1);
    setEmissive(0,0,0,0);
    setShinyInt((int)(0.078125*128.0));
}

//pearl    0.25    0.20725    0.20725    1    0.829    0.829    0.296648    0.296648    0.296648    0.088
// from http://devernay.free.fr/cours/opengl/materials.html
void MaterialClass::setMaterialPearl()
{
    setAmbient(0.25f, 0.207f, 0.207f ,1);
    setDiffuse(1.0f, 0.829f, 0.829f ,1);
    setSpecular(0.297f, 0.297f, 0.297f ,1);
    setEmissive(0,0,0,0);
    setShinyInt((int)(0.088*128.0));
}

void MaterialClass::setMaterialYellowSand()
{
    setAmbient(0.4f, 0.4f, 0.1575f ,1);
    setDiffuse(0.7f, 0.7f, 0.2f ,1);
    setSpecular(0.316228f, 0.316228f, 0.216228f ,1);
    setEmissive(0,0,0,0);
    setShinyInt((int)(0.1*128.0));
}

void MaterialClass::setMaterialGreenGrass()
{
    setAmbient(0.13f, 0.25f, 0.15f ,1);
    setDiffuse(0.24f, 0.89f, 0.33f ,1);
    setSpecular(0.116228f, 0.316228f, 0.116228f ,1);
    setEmissive(0,0,0,0);
    setShinyInt((int)(0.1*128.0));
}

