#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "SOIL.h"

class Truck
{
public:
    float *normal;
    float normalArms[3] = {90, 30, 0};

    void buildTruck();
    void createCube();
    void createJetpack();
    void createChest();
    void getNormalArms();
    void transformation();
    float *vectorProduct(float point1, float point2, float point3, float point4, float point5, float point6, float point7, float point8, float point9);
    void mouseMove(int x, int y);
    void setlight();
    void setMaterial(int mode);
    void createHead();
    void createPelvis();
    void createLegs();
};