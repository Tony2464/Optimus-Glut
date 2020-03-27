#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "SOIL.h"

class Robot
{
public:
    float *normal;
    float radius = 0.25;
    float dabRightArm = 0;
    float dabLeftArm = 0;
    float normalArms[3] = {90, 30, 0};
    short myBool = 0;
    float rotateRightLeg = 0;
    float rotateLeftLeg = 0;
    int rotateRightLegLimit = 0;
    float rotateRightKnee = 0;
    float rotateLeftKnee = 0;

    void buildOptimus();
    void createCube();
    void createJetpack();
    void createChest();
    void createHexagone();
    void createRightArm();
    void createLeftArm();
    void dab();
    void getNormalArms();
    void transformation();
    float *vectorProduct(float point1, float point2, float point3, float point4, float point5, float point6, float point7, float point8, float point9);
    void mouseMove(int x, int y);
    void setlight();
    void setMaterial(int mode);
    void createHead();
    void walk();
    void createPelvis();
    void createLegs();
    void sound();
};
