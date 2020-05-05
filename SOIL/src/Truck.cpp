#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "Truck.h"

void Truck::buildTruck(){

    glPushMatrix();
        glTranslatef(0,2,0);
        //Top of the chest
        glPushMatrix();
            this->setMaterial(1);
            this->createChest();
            glutPostRedisplay();
        glPopMatrix();

        //Back (jetpack)
        glPushMatrix();
            this->setMaterial(2);
            this->createJetpack();
            glutPostRedisplay();
        glPopMatrix();

        glPushMatrix();
            this->setMaterial(5);
            this->createPelvis();
            glutPostRedisplay();
        glPopMatrix();

        glPushMatrix();
            this->createLegs();
            glutPostRedisplay();
        glPopMatrix();
    glPopMatrix();

}

float* Truck::vectorProduct(float point1, float point2, float point3, float point4, float point5, float point6, float point7, float point8, float point9) {
    float vector1[3];
    float vector2[3];
    float* normalVector = (float*) malloc(sizeof(float) * 3);

    vector1[0] = point4 - point1;
    vector1[1] = point5 - point2;
    vector1[2] = point6 - point3;

    vector2[0] = point7 - point1;
    vector2[1] = point8 - point2;
    vector2[2] = point9 - point3;

    *normalVector = vector1[1] * vector2[2] - vector1[2] * vector2[1];
    *(normalVector + 1) = vector1[2] * vector2[0] - vector1[0] * vector2[2];
    *(normalVector + 2) = vector1[0] * vector2[1] - vector1[1] * vector2[0];

    return normalVector;
}

void Truck::createCube() {
    glPushMatrix();
        glBegin(GL_QUADS);

        glNormal3f(0, 0, 1);
        //Front
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);

        glNormal3f(1, 0, 0);
        //Right
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);

        glNormal3f(0, 0, -1);
        //Back
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);

        glNormal3f(-1, 0, 0);
        //Left
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);

        glNormal3f(0, 1, 0);
        //Up
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);

        glNormal3f(0, -1, 0);
        //Down
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);

        glEnd();
    glPopMatrix();
}

void Truck::createChest()
{
 //Top of the chest
    glPushMatrix();
        glScalef(1,0.90,1);
        glTranslatef(0,-0.175,0);
        glPushMatrix();

            glBegin(GL_QUADS);

                glNormal3f(1, 0, 0);
                //Right
                glVertex3f(0.75f, 0.5f, 0.5f);
                glVertex3f(0.75f, -0.5f, 0.5f);
                glVertex3f(0.75f, -0.5f, -0.5f);
                glVertex3f(0.75f, 0.5f, -0.5f);

                //Back
                glNormal3f(0, 0, -1);
                glVertex3f(-0.75f, -0.5f, -0.5f);
                glVertex3f(0.75f, -0.5f, -0.5f);
                glVertex3f(0.75f, 0.5f, -0.5f);
                glVertex3f(-0.75f, 0.5f, -0.5f);

                //Left
                glNormal3f(-1, 0, 0);
                glVertex3f(-0.75f, 0.5f, 0.5f);
                glVertex3f(-0.75f, -0.5f, 0.5f);
                glVertex3f(-0.75f, -0.5f, -0.5f);
                glVertex3f(-0.75f, 0.5f, -0.5f);

                //Front left
                normal = vectorProduct(-0.75f, -0.5f, 0.5f, 0.0f, -0.5f, 0.7f,-0.75f, 0.5f, 0.5f);
                glNormal3f(normal[0], normal[1], normal[2]);
                glVertex3f(-0.75f, 0.5f, 0.5f);
                glVertex3f(-0.75f, -0.5f, 0.5f);
                glVertex3f(0.0f, -0.5f, 0.7f);
                glVertex3f(0.0f, 0.5f, 0.7f);

                //Front right
                normal = vectorProduct(0.0f, -0.5f, 0.7f,0.75f, -0.5f, 0.5f,0.0f, 0.5f, 0.7f);
                glNormal3f(normal[0], normal[1], normal[2]);
                glVertex3f(0.75f, 0.5f, 0.5f);
                glVertex3f(0.75f, -0.5f, 0.5f);
                glVertex3f(0.0f, -0.5f, 0.7f);
                glVertex3f(0.0f, 0.5f, 0.7f);

                //Top
                glNormal3f(0, 1, 0);
                glVertex3f(0.75f, 0.5f, 0.5f);
                glVertex3f(0.75f, 0.5f, -0.5f);
                glVertex3f(-0.75f, 0.5f, -0.5f);
                glVertex3f(-0.75f, 0.5f, 0.5f);

                //Bottom
                glNormal3f(0, -1, 0);
                glVertex3f(0.75f, -0.5f, 0.5f);
                glVertex3f(0.75f, -0.5f, -0.5f);
                glVertex3f(-0.75f, -0.5f, -0.5f);
                glVertex3f(-0.75f, -0.5f, 0.5f);

            glEnd();
        glPopMatrix();

        glPushMatrix();
            glBegin(GL_TRIANGLES);

                //Top triangle
                glNormal3f(0, 1, 0);
                glVertex3f(0.0f, 0.5f, 0.7f);
                glVertex3f(0.75f, 0.5f, 0.5f);
                glVertex3f(-0.75f, 0.5f, 0.5f);

                //Top triangle
                glNormal3f(0, -1, 0);
                glVertex3f(0.0f, -0.5f, 0.7f);
                glVertex3f(0.75f, -0.5f, 0.5f);
                glVertex3f(-0.75f, -0.5f, 0.5f);

            glEnd();
        glPopMatrix();
    glPopMatrix();
}

void Truck::createJetpack(){
     //Right
    glPushMatrix();

        //Bottom
        glBegin(GL_QUADS);
        glNormal3f(0, -1, 0);
        glVertex3f(0.3f, -0.5f, -0.5f);
        glVertex3f(0.3f, -0.5f, -0.7f);
        glVertex3f(0.5f, -0.5f, -0.7f);
        glVertex3f(0.5f, -0.5f, -0.5f);

        //Top
        glNormal3f(0, 1, 0);
        glVertex3f(0.3f, 0.5f, -0.5f);
        glVertex3f(0.3f, 0.5f, -0.7f);
        glVertex3f(0.5f, 0.5f, -0.7f);
        glVertex3f(0.5f, 0.5f, -0.5f);

        //Back
        glNormal3f(0, 0, -1);
        glVertex3f(0.3f, -0.5f, -0.7f);
        glVertex3f(0.5f, -0.5f, -0.7f);
        glVertex3f(0.5f, 0.5f, -0.7f);
        glVertex3f(0.3f, 0.5f, -0.7f);

        //Right
        glNormal3f(1, 0, 0);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.7f);
        glVertex3f(0.5f, 0.5f, -0.7f);
        glVertex3f(0.5f, 0.5f, -0.5f);

        //Left
        glNormal3f(-1, 0, 0);
        glVertex3f(0.3f, -0.5f, -0.5f);
        glVertex3f(0.3f, -0.5f, -0.7f);
        glVertex3f(0.3f, 0.5f, -0.7f);
        glVertex3f(0.3f, 0.5f, -0.5f);

        glEnd();
    glPopMatrix();

        //Left
    glPushMatrix();

        //Bottom
        glBegin(GL_QUADS);
            glNormal3f(0, -1, 0);
            glVertex3f(-0.3f, -0.5f, -0.5f);
            glVertex3f(-0.3f, -0.5f, -0.7f);
            glVertex3f(-0.5f, -0.5f, -0.7f);
            glVertex3f(-0.5f, -0.5f, -0.5f);

            //Top
            glNormal3f(0, 1, 0);
            glVertex3f(-0.3f, 0.5f, -0.5f);
            glVertex3f(-0.3f, 0.5f, -0.7f);
            glVertex3f(-0.5f, 0.5f, -0.7f);
            glVertex3f(-0.5f, 0.5f, -0.5f);

            //Back
            glNormal3f(0, 0, -1);
            glVertex3f(-0.3f, -0.5f, -0.7f);
            glVertex3f(-0.5f, -0.5f, -0.7f);
            glVertex3f(-0.5f, 0.5f, -0.7f);
            glVertex3f(-0.3f, 0.5f, -0.7f);

            //Right
            glNormal3f(1, 0, 0);
            glVertex3f(-0.5f, -0.5f, -0.5f);
            glVertex3f(-0.5f, -0.5f, -0.7f);
            glVertex3f(-0.5f, 0.5f, -0.7f);
            glVertex3f(-0.5f, 0.5f, -0.5f);

            //Left
            glNormal3f(-1, 0, 0);
            glVertex3f(-0.3f, -0.5f, -0.5f);
            glVertex3f(-0.3f, -0.5f, -0.7f);
            glVertex3f(-0.3f, 0.5f, -0.7f);
            glVertex3f(-0.3f, 0.5f, -0.5f);

        glEnd();
    glPopMatrix();
}

void Truck::createPelvis(){
    //Top of the chest
    glPushMatrix();
        glTranslatef(0,-1,0);
        glPushMatrix();
            glScalef(1.5, 0.8, 1.40);
            createCube();
        glPopMatrix();
        
        //Front wheels
        //Right wheel
        glPushMatrix();
            glTranslated(0.5,-0.20,0.2);
            glRotated(90,0,1,0);
            setMaterial(4);
            GLUquadricObj *quadratic6;
            quadratic6 = gluNewQuadric();
            gluCylinder(quadratic6, 0.3f, 0.3f, 0.3, 80, 80);

            //Draw Circle
            setMaterial(5);
            glBegin(GL_POLYGON);
                for(double i = 0; i < 2 * M_PI; i += M_PI / 6) //<-- Change this Value
                    glVertex3f(cos(i) * 0.31, sin(i) * 0.31, 0.3);
            glEnd();
        glPopMatrix();

        //Left wheel
        glPushMatrix();
            glRotated(180,0,1,0);
            glTranslated(0.5,-0.20,-0.20);
            glRotated(90,0,1,0);
            setMaterial(4);
            GLUquadricObj *quadratic7;
            quadratic7 = gluNewQuadric();
            gluCylinder(quadratic7, 0.3f, 0.3f, 0.3, 80, 80);

            //Draw Circle
            setMaterial(5);
            glBegin(GL_POLYGON);
                for(double i = 0; i < 2 * M_PI; i += M_PI / 6) //<-- Change this Value
                    glVertex3f(cos(i) * 0.31, sin(i) * 0.31, 0.3);
            glEnd();
        glPopMatrix();
    glPopMatrix();

}

void Truck::createLegs(){
    /**************"LEGS"**************/
    glPushMatrix();
        // glTranslatef(0.1, -0.1, 0);
        setMaterial(3);
        glTranslatef(0, -1.0, 0);
        glRotated(90, 1,0,0);
        
        glTranslatef(0, 0.25, 0);
        //Thigh
        glPushMatrix();
            glTranslatef(0, -1.5, 0);
            glScalef(1.5, 1.10, 0.6);
            createCube();
        glPopMatrix();

        //Calf
        glPushMatrix();
            setMaterial(2);
            glTranslatef(0, -2.1, 0);
            glTranslatef(0, 2.0, 0);

            glPushMatrix();
                glTranslatef(0, -2.7, 0);
                glScalef(1.5, 1.5, 0.8);
                createCube();
            glPopMatrix();


            //RIGHT WHEELS
            //Wheel up
            glPushMatrix();
                glTranslated(0.5,-2.4,0.2);
                glRotated(90,0,1,0);
                setMaterial(4);
                GLUquadricObj *quadratic;
                quadratic = gluNewQuadric();
                gluCylinder(quadratic, 0.3f, 0.3f, 0.3, 80, 80);

                //Draw Circle
                setMaterial(5);
                glBegin(GL_POLYGON);
                    for(double i = 0; i < 2 * M_PI; i += M_PI / 6) //<-- Change this Value
                        glVertex3f(cos(i) * 0.31, sin(i) * 0.31, 0.3);
                glEnd();
            glPopMatrix();

            //Wheel bottom
            glPushMatrix();
                glTranslated(0.5,-3.1,0.2);
                glRotated(90,0,1,0);
                setMaterial(4);
                GLUquadricObj *quadratic2;
                quadratic2 = gluNewQuadric();
                gluCylinder(quadratic2, 0.3f, 0.3f, 0.3, 80, 80);

                //Draw Circle
                setMaterial(5);
                glBegin(GL_POLYGON);
                    for(double i = 0; i < 2 * M_PI; i += M_PI / 6) //<-- Change this Value
                        glVertex3f(cos(i) * 0.31, sin(i) * 0.31, 0.3);
                glEnd();
            glPopMatrix();

            //LEFT WHEELS
            glPushMatrix();
                glRotated(180,0,1,0);
                glTranslated(0, 0, -0.40);

                glPushMatrix();
                    glTranslated(0.5,-2.4,0.2);
                    glRotated(90,0,1,0);
                    setMaterial(4);
                    GLUquadricObj *quadratic3;
                    quadratic3 = gluNewQuadric();
                    gluCylinder(quadratic3, 0.3f, 0.3f, 0.3, 80, 80);

                    //Draw Circle
                    setMaterial(5);
                    glBegin(GL_POLYGON);
                        for(double i = 0; i < 2 * M_PI; i += M_PI / 6) //<-- Change this Value
                            glVertex3f(cos(i) * 0.31, sin(i) * 0.31, 0.3);
                    glEnd();
                glPopMatrix();

                //Wheel bottom
                glPushMatrix();
                    glTranslated(0.5,-3.1,0.2);
                    glRotated(90,0,1,0);
                    setMaterial(4);
                    GLUquadricObj *quadratic4;
                    quadratic4 = gluNewQuadric();
                    gluCylinder(quadratic4, 0.3f, 0.3f, 0.3, 80, 80);

                    //Draw Circle
                    setMaterial(5);
                    glBegin(GL_POLYGON);
                        for(double i = 0; i < 2 * M_PI; i += M_PI / 6) //<-- Change this Value
                            glVertex3f(cos(i) * 0.31, sin(i) * 0.31, 0.3);
                    glEnd();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Truck::setMaterial(int mode){
    //here you set materials, you must declare each one of the colors global or locally like this:
    float MatAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    float MatDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float MatSpecular[] = { 0.1f, 0.1f, 0.0f, 0.1f };
    float MatShininess = 10;
    float color[] = {1.0f,0.0f,0.0f,1.0f};
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
//    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
//    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);


    switch(mode){

    case 1 :
         glColor3f(0.6f,0.0f,0.0f);
         break;

    case 2 :
         glColor3f(0.0f,0.0f,0.7f);
         break;

    case 3 :
         glColor3f(0.7f, 0.7f, 0.7f);
         break;

    case 4 :
         glColor3f(0.1f, 0.1f, 0.1f);
         break;

    case 5 :
        glColor3f(0.2f, 0.2f, 0.2f);
        break;

    case 6 :
        glColor3f(0.6f, 0.0f, 0.0f);
        break;

    case 7 :
        glColor3f(0.2f, 0.2f, 0.2f);
        break;

    case 8 :
        glColor3f(0.7f, 0.7f, 0.7f);
        break;
    }

}