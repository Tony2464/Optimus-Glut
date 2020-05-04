#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "Robot.h"
#include "../fmod/fmod.h"

void Robot::buildOptimus(){

//Top of the chest
    glPushMatrix();
        glTranslatef(0, 3.7, 5);
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
            this->setMaterial(3);
            this->createHexagone();
            glutPostRedisplay();
        glPopMatrix();

        //Right arm
        glPushMatrix();
            glScalef(1, 0.99, 1);
            this->createRightArm();
        glPopMatrix();

        glPushMatrix();
            glScalef(1, 0.99, 1);
            this->createLeftArm();
        glPopMatrix();

        glPushMatrix();
            this->setMaterial(2);
            this->createHead();
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

void Robot::sound(){

FMOD_SYSTEM * sys;
  FMOD_SOUND * sound;
  FMOD_RESULT resultat;
  FMOD_CHANNEL * channel;

  FMOD_System_Create(&sys);
  FMOD_System_Init(sys, 1, FMOD_INIT_NORMAL, NULL);

  /* On ouvre la musique */
  resultat = FMOD_System_CreateSound(sys, "sounds/jesuisoptimus.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &sound);

    if (resultat != FMOD_OK)
  {
      printf("Impossible de lire le fichier mp3\n");
       //cout << "Impossible de lire le fichier mp3\n";
  }

  /* On joue la musique */
  FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound, 0, NULL);

  Sleep(4000);
  FMOD_Sound_Release(sound);
  FMOD_System_Close(sys);

}

float* Robot::vectorProduct(float point1, float point2, float point3, float point4, float point5, float point6, float point7, float point8, float point9) {
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

void Robot::createCube() {
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

void Robot::createHead(){

    //Head
    glPushMatrix();
        glBegin(GL_POLYGON);
        glNormal3f(0.0f, 1.0f, 0.0f);

        glVertex3f(0.0f, 0.95f, 0.4f);
        glVertex3f(0.3f, 0.95f, 0.3f);
        glVertex3f(0.3f, 0.95f, 0.0f);
        glVertex3f(0.15f, 0.95f, -0.3f);
        glVertex3f(-0.15f, 0.95f, -0.3f);
        glVertex3f(-0.3f, 0.95f, 0.0f);
        glVertex3f(-0.3f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        normal = vectorProduct(0.0f, 0.5f, 0.4f, 0.3f, 0.5f, 0.3f, 0.0f, 0.95f, 0.4f);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(0.0f, 0.95f, 0.4f);
        glVertex3f(0.0f, 0.5f, 0.4f);
        glVertex3f(0.3f, 0.5f, 0.3f);
        glVertex3f(0.3f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        normal = vectorProduct(-0.3f, 0.5f, 0.3f, 0.0f, 0.5f, 0.4f, -0.3f, 0.95f, 0.3f);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(0.0f, 0.95f, 0.4f);
        glVertex3f(0.0f, 0.5f, 0.4f);
        glVertex3f(-0.3f, 0.5f, 0.3f);
        glVertex3f(-0.3f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        glNormal3f(-1, 0, 0);

        glVertex3f(-0.3f, 0.95f, 0.0f);
        glVertex3f(-0.3f, 0.5f, 0.0f);
        glVertex3f(-0.3f, 0.5f, 0.3f);
        glVertex3f(-0.3f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        glNormal3f(1, 0, 0);

        glVertex3f(0.3f, 0.95f, 0.0f);
        glVertex3f(0.3f, 0.5f, 0.0f);
        glVertex3f(0.3f, 0.5f, 0.3f);
        glVertex3f(0.3f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        normal = vectorProduct(-0.15f, 0.5f, -0.3f, -0.3f, 0.5f, 0.0f, -0.15f, 0.95f, -0.3f);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(-0.15f, 0.5f, -0.3f);
        glVertex3f(-0.15f, 0.95f, -0.3f);
        glVertex3f(-0.3f, 0.95f, 0.0f);
        glVertex3f(-0.3f, 0.5f, 0.0f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        normal = vectorProduct(0.3f, 0.5f, 0.0f, 0.15f, 0.5f, -0.3f, 0.3f, 0.95f, 0.0f);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(0.15f, 0.5f, -0.3f);
        glVertex3f(0.15f, 0.95f, -0.3f);
        glVertex3f(0.3f, 0.95f, 0.0f);
        glVertex3f(0.3f, 0.5f, 0.0f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        glNormal3f(0.0f,0.0f,-1.0f);

        glVertex3f(0.15f, 0.5f, -0.3f);
        glVertex3f(0.15f, 0.95f, -0.3f);
        glVertex3f(-0.15f, 0.95f, -0.3f);
        glVertex3f(-0.15f, 0.5f, -0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        normal = vectorProduct(0.3f, 0.5f, 0.2f, 0.4f, 0.5f, 0.2f, 0.3f, 0.75f, 0.2f);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(0.3f, 0.5f, 0.2f);
        glVertex3f(0.4f, 0.5f, 0.2f);
        glVertex3f(0.4f, 0.75f, 0.2f);
        glVertex3f(0.3f, 0.75f, 0.2f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        normal = vectorProduct(0.4f, 0.5f, 0.1f, 0.3f, 0.5f, 0.1f, 0.4f, 0.75f, 0.1f);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(0.3f, 0.5f, 0.1f);
        glVertex3f(0.4f, 0.5f, 0.1f);
        glVertex3f(0.4f, 0.75f, 0.1f);
        glVertex3f(0.3f, 0.75f, 0.1f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        normal = vectorProduct(0.4f, 0.5f, 0.2f, 0.4f, 0.5f, 0.1f, 0.4f, 0.75f, 0.2f);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(0.4f, 0.5f, 0.1f);
        glVertex3f(0.4f, 0.5f, 0.2f);
        glVertex3f(0.4f, 0.75f, 0.2f);
        glVertex3f(0.4f, 0.75f, 0.1f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        normal = vectorProduct(-0.4f, 0.5f, 0.2f, -0.3f, 0.5f, 0.2f, -0.4f, 0.75f, 0.2f);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(-0.3f, 0.5f, 0.2f);
        glVertex3f(-0.4f, 0.5f, 0.2f);
        glVertex3f(-0.4f, 0.75f, 0.2f);
        glVertex3f(-0.3f, 0.75f, 0.2f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        normal = vectorProduct(-0.3f, 0.5f, 0.1f, -0.4f, 0.5f, 0.1f, -0.3f, 0.75f, 0.1f);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(-0.3f, 0.5f, 0.1f);
        glVertex3f(-0.4f, 0.5f, 0.1f);
        glVertex3f(-0.4f, 0.75f, 0.1f);
        glVertex3f(-0.3f, 0.75f, 0.1f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        normal = vectorProduct(-0.4f, 0.5f, 0.1f, -0.4f, 0.5f, 0.2f, -0.4f, 0.75f, 0.1f);
        glNormal3f(-normal[0], normal[1], -normal[2]);

        glVertex3f(-0.4f, 0.5f, 0.1f);
        glVertex3f(-0.4f, 0.5f, 0.2f);
        glVertex3f(-0.4f, 0.75f, 0.2f);
        glVertex3f(-0.4f, 0.75f, 0.1f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_TRIANGLES);
        normal = vectorProduct(-0.4f, 0.75f, 0.2f, -0.3f, 0.75f, 0.2f, -0.3f, 1.1f, 0.15f);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(-0.3f, 0.75f, 0.2f);
        glVertex3f(-0.4f, 0.75f, 0.2f);
        glVertex3f(-0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_TRIANGLES);
        normal = vectorProduct(-0.3f, 0.75f, 0.2f, -0.3f, 0.75f, 0.1f, -0.3f, 1.1f, 0.15f);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(-0.3f, 0.75f, 0.1f);
        glVertex3f(-0.3f, 0.75f, 0.2f);
        glVertex3f(-0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_TRIANGLES);
        normal = vectorProduct(-0.4f, 0.75f, 0.1f, -0.4f, 0.75f, 0.2f, -0.3f, 1.1f, 0.15f);
        glNormal3f(-normal[0], normal[1], normal[2]);

        glVertex3f(-0.4f, 0.75f, 0.1f);
        glVertex3f(-0.4f, 0.75f, 0.2f);
        glVertex3f(-0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_TRIANGLES);
        normal = vectorProduct(-0.3f, 0.75f, 0.1f, -0.4f, 0.75f, 0.1f, -0.3f, 1.1f, 0.15f);
        glNormal3f(-normal[0], normal[1], -normal[2]);

        glVertex3f(-0.3f, 0.75f, 0.1f);
        glVertex3f(-0.4f, 0.75f, 0.1f);
        glVertex3f(-0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    //
    glPushMatrix();
        glBegin(GL_TRIANGLES);
        normal = vectorProduct(0.3f, 0.75f, 0.2f, 0.4f, 0.75f, 0.2f, 0.3f, 1.1f, 0.15f);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(0.3f, 0.75f, 0.2f);
        glVertex3f(0.4f, 0.75f, 0.2f);
        glVertex3f(0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_TRIANGLES);
        normal = vectorProduct(0.3f, 0.75f, 0.1f, 0.3f, 0.75f, 0.2f, 0.3f, 1.1f, 0.15f);
        glNormal3f(-normal[0], normal[1], normal[2]);

        glVertex3f(0.3f, 0.75f, 0.1f);
        glVertex3f(0.3f, 0.75f, 0.2f);
        glVertex3f(0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_TRIANGLES);
        normal = vectorProduct(0.3f, 0.75f, 0.2f, 0.3f, 0.75f, 0.1f, 0.3f, 1.1f, 0.15f);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(0.4f, 0.75f, 0.1f);
        glVertex3f(0.4f, 0.75f, 0.2f);
        glVertex3f(0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_TRIANGLES);
        normal = vectorProduct(0.4f, 0.75f, 0.2f, 0.3f, 0.75f, 0.1f, 0.3f, 1.1f, 0.15f);
        glNormal3f(normal[0], normal[1], -normal[2]);

        glVertex3f(0.3f, 0.75f, 0.1f);
        glVertex3f(0.4f, 0.75f, 0.1f);
        glVertex3f(0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        glNormal3f(0.0f,0.0f,-1.0f);

        glVertex3f(-0.1f, 0.95f, -0.2f);
        glVertex3f(-0.05f, 1.0f, -0.2f);
        glVertex3f(0.05f, 1.0f, -0.2f);
        glVertex3f(0.1f, 0.95f, -0.2f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        glNormal3f(0.0f,0.0f,1.0f);

        glVertex3f(-0.1f, 0.95f, 0.3f);
        glVertex3f(-0.05f, 1.0f, 0.3f);
        glVertex3f(0.05f, 1.0f, 0.3f);
        glVertex3f(0.1f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        normal = vectorProduct(-0.1f, 0.95f, -0.2f, -0.1f, 0.95f, 0.3f, -0.05f, 1.0f, -0.2f);
        glNormal3f(-normal[0], normal[1], normal[2]);

        glVertex3f(-0.1f, 0.95f, -0.2f);
        glVertex3f(-0.05f, 1.0f, -0.2f);
        glVertex3f(-0.05f, 1.0f, 0.3f);
        glVertex3f(-0.1f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        normal = vectorProduct(0.1f, 0.95f, 0.3f, 0.1f, 0.95f, -0.2f, 0.05f, 1.0f, 0.3f);
        glNormal3f(normal[0], normal[1], normal[2]);

        glVertex3f(0.1f, 0.95f, -0.2f);
        glVertex3f(0.05f, 1.0f, -0.2f);
        glVertex3f(0.05f, 1.0f, 0.3f);
        glVertex3f(0.1f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        glNormal3f(0.0f,1.0f,0.0f);

        glVertex3f(-0.05f, 1.0f, -0.2f);
        glVertex3f(0.05f, 1.0f, -0.2f);
        glVertex3f(-0.05f, 1.0f, 0.3f);
        glVertex3f(0.05f, 1.0f, 0.3f);

    glEnd();
    glPopMatrix();

}

void Robot::createChest() {
    //Top of the chest
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
}

void Robot::createJetpack() {
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

void Robot::createHexagone() {
    //Hexagone

    glPushMatrix();
            //Top
        glBegin(GL_POLYGON);
            glNormal3f(0, 1, 0);
            glVertex3f(-0.5f, -0.5f, -0.4f);
            glVertex3f(0.5f, -0.5f, -0.4f);
            glVertex3f(0.7f, -0.5f, 0.0f);
            glVertex3f(0.5f, -0.5f, 0.5f);
            glVertex3f(-0.5f, -0.5f, 0.5f);
            glVertex3f(-0.7f, -0.5f, 0.0f);

        glEnd();
    glPopMatrix();

    glPushMatrix();
            //Bottom
        glBegin(GL_POLYGON);

            glNormal3f(0, -1, 0);
            glVertex3f(-0.5f, -0.9f, -0.4f);
            glVertex3f(0.5f, -0.9f, -0.4f);
            glVertex3f(0.7f, -0.9f, 0.0f);
            glVertex3f(0.5f, -0.9f, 0.5f);
            glVertex3f(-0.5f, -0.9f, 0.5f);
            glVertex3f(-0.7f, -0.9f, 0.0f);

        glEnd();
    glPopMatrix();

    glPushMatrix();
        glBegin(GL_QUADS);

            //Front
            normal = vectorProduct(-0.5f, -0.9f, 0.5f, 0.5f, -0.9f, 0.5f, -0.5f, -0.5f, 0.5f);
            glNormal3f(normal[0], normal[1], normal[2]);
            glVertex3f(-0.5f, -0.9f, 0.5f);
            glVertex3f(0.5f, -0.9f, 0.5f);
            glVertex3f(0.5f, -0.5f, 0.5f);
            glVertex3f(-0.5f, -0.5f, 0.5f);

            //Back
            normal = vectorProduct(-0.5f, -0.9f, -0.4f, 0.5f, -0.9f, -0.4f, -0.5f, -0.5f, -0.4f);
            glNormal3f(normal[0], normal[1], -normal[2]);
            glVertex3f(-0.5f, -0.9f, -0.4f);
            glVertex3f(0.5f, -0.9f, -0.4f);
            glVertex3f(0.5f, -0.5f, -0.4f);
            glVertex3f(-0.5f, -0.5f, -0.4f);

            //Front right
            normal = vectorProduct(0.5f, -0.9f, 0.5f, 0.7f, -0.9f, 0.0f, 0.5f, -0.5f, 0.5f);
            glNormal3f(normal[0], normal[1], normal[2]);
            glVertex3f(0.5f, -0.9f, 0.5f);
            glVertex3f(0.7f, -0.9f, 0.0f);
            glVertex3f(0.7f, -0.5f, 0.0f);
            glVertex3f(0.5f, -0.5f, 0.5f);

            //Back right
            normal = vectorProduct(0.5f, -0.9f, -0.4f, 0.7f, -0.9f, 0.0f, 0.5f, -0.5f, -0.4f);
            glNormal3f(-normal[0], normal[1], -normal[2]);
            glVertex3f(0.5f, -0.9f, -0.4f);
            glVertex3f(0.7f, -0.9f, 0.0f);
            glVertex3f(0.7f, -0.5f, 0.0f);
            glVertex3f(0.5f, -0.5f, -0.4f);

            //Back left
            normal = vectorProduct(-0.5f, -0.9f, -0.4f, -0.7f, -0.9f, 0.0f, -0.5f, -0.5f, -0.4f);
            glNormal3f(normal[0], normal[1], normal[2]);
            glVertex3f(-0.5f, -0.9f, -0.4f);
            glVertex3f(-0.7f, -0.9f, 0.0f);
            glVertex3f(-0.7f, -0.5f, 0.0f);
            glVertex3f(-0.5f, -0.5f, -0.4f);

            //Front left
            normal = vectorProduct(-0.5f, -0.9f, 0.5f, -0.7f, -0.9f, 0.0f, -0.5f, -0.5f, 0.5f);
            glNormal3f(normal[0], normal[1], normal[2]);
            glVertex3f(-0.5f, -0.9f, 0.5f);
            glVertex3f(-0.7f, -0.9f, 0.0f);
            glVertex3f(-0.7f, -0.5f, 0.0f);
            glVertex3f(-0.5f, -0.5f, 0.5f);

        glEnd();
    glPopMatrix();
}

void Robot::createRightArm() {

    //Right Shoulder
    glPushMatrix();
        setMaterial(3);
        glTranslatef(0.75, 0.25, 0);

        glPushMatrix();
            glScalef(0.3, 0.2, 0.2);
            createCube();
        glPopMatrix();

        glTranslatef(0.3, 0, 0);
        glutSolidSphere(radius, 255, 255);

    // Right Arm
        glRotatef(dabRightArm, 0, 0, 1);
        glRotatef(normalArms[0], 0, 0, -1);
        glRotatef(normalArms[2], 0, 1, 0);
        glPushMatrix();
            setMaterial(6);
            glTranslatef(0.375, 0, 0);
            glScalef(0.75, 0.5, 0.5);
            createCube();
        glPopMatrix();

    // Right Elbow
        glTranslatef(0.125, 0, 0);
        glPushMatrix();
            setMaterial(3);
            glTranslatef(0.75, 0, 0);
            glutSolidSphere(radius, 255, 255);
        glPopMatrix();

        glTranslatef(0.75, 0, 0);
        glRotatef(normalArms[1], 0, -1, 0);
        glTranslatef(-0.75, 0, 0);

    //Right Forearm
        glPushMatrix();
            setMaterial(6);
            glTranslatef(1.25, 0, 0);
            glScalef(0.75, 0.5, 0.5);
            createCube();
        glPopMatrix();

    //Right Sword
        setMaterial(8);
        glPushMatrix();
            glTranslatef(1.625, -0.05, 0);
            glPushMatrix();
                glBegin(GL_QUADS);
                    normal = vectorProduct(0, 0, -0.15, 1.5, 0, -0.15, 0, 0.1, 0);
                    glNormal3f(normal[0], normal[1], normal[2]);
                    glVertex3f(0, 0, -0.15);
                    glVertex3f(1.5, 0, -0.15);
                    glVertex3f(1.5, 0.1, 0);
                    glVertex3f(0, 0.1, 0);

                    normal = vectorProduct(0, -0.1, 0, 1.5, -0.1, 0, 0, 0, -0.15);
                    glNormal3f(normal[0], normal[1], normal[2]);
                    glVertex3f(0, 0, -0.15);
                    glVertex3f(1.5, 0, -0.15);
                    glVertex3f(1.5, -0.1, 0);
                    glVertex3f(0, -0.1, 0);

                    normal = vectorProduct(0, 0, 0.15, 1.5, 0, 0.15, 0, 0.1, 0);
                    glNormal3f(normal[0], normal[1], normal[2]);
                    glVertex3f(0, 0, 0.15);
                    glVertex3f(1.5, 0, 0.15);
                    glVertex3f(1.5, 0.1, 0);
                    glVertex3f(0, 0.1, 0);

                    normal = vectorProduct(0, -0.1, 0, 1.5, -0.1, 0, 0, 0, 0.15);
                    glNormal3f(normal[0], normal[1], normal[2]);
                    glVertex3f(0, 0, 0.15);
                    glVertex3f(1.5, 0, 0.15);
                    glVertex3f(1.5, -0.1, 0);
                    glVertex3f(0, -0.1, 0);
                glEnd();
            glPopMatrix();

        //Right Sword Tip
            glPushMatrix();
            glTranslatef(1.5, 0, 0);
                glBegin(GL_TRIANGLES);
                    normal = vectorProduct(0, 0, 0.15, 0.5, 0, 0, 0, 0.1, 0);
                    glNormal3f(normal[0], normal[1], normal[2]);
                    glVertex3f(0, 0, 0.15);
                    glVertex3f(0.5, 0, 0);
                    glVertex3f(0, 0.1, 0);

                    normal = vectorProduct(0, -0.1, 0, 0.5, 0, 0, 0, 0, 0.15);
                    glNormal3f(normal[0], normal[1], normal[2]);
                    glVertex3f(0, 0, 0.15);
                    glVertex3f(0.5, 0, 0);
                    glVertex3f(0, -0.1, 0);

                    normal = vectorProduct(0, 0, -0.15, 0, 0.1, 0, 0.5, 0, 0);
                    glNormal3f(normal[0], normal[1], normal[2]);
                    glVertex3f(0, 0, -0.15);
                    glVertex3f(0.5, 0, 0);
                    glVertex3f(0, 0.1, 0);

                    normal = vectorProduct(0, -0.1, 0, 0.5, 0, 0, 0, 0, -0.15);
                    glNormal3f(normal[0], normal[1], normal[2]);
                    glVertex3f(0, 0, -0.15);
                    glVertex3f(0.5, 0, 0);
                    glVertex3f(0, -0.1, 0);
                glEnd();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Robot::createLeftArm() {

    //Left Shoulder
    glPushMatrix();
        setMaterial(3);
        glTranslatef(-0.75, 0.25, 0);

        glPushMatrix();
            glScalef(0.3, 0.2, 0.2);
            createCube();
        glPopMatrix();

        glTranslatef(-0.3, 0, 0);
        glutSolidSphere(radius, 255, 255);
    glPopMatrix();


    //Left Arm
    glTranslatef(-0.3, 0, 0);
    setMaterial(6);
    glPushMatrix();
        glTranslatef(-0.75, 0.25, 0);
        glRotatef(dabLeftArm, 0, -1, 0);
        glRotatef(normalArms[0], 0, 0, -1);
        glRotatef(normalArms[2], 0, 1, 0);
        glPushMatrix();
            glTranslatef(0.375, 0, 0);
            glScalef(0.75, 0.5, 0.5);
            createCube();
        glPopMatrix();

        glTranslatef(0.75, 0, 0);
        glRotatef(normalArms[1], 0, -1, 0);
        glTranslatef(-0.75, 0, 0);

    //Left Elbow
        glTranslatef(0.125, 0, 0);
        glPushMatrix();
            setMaterial(3);
            glTranslatef(0.75, 0, 0);
            glutSolidSphere(radius, 255, 255);
        glPopMatrix();

    //Left Forearm
        glPushMatrix();
            setMaterial(6);
            glTranslatef(0.875, 0, 0);
            glRotatef(dabLeftArm, 0, 2.5, 1);
            glPushMatrix();
                glTranslatef(0.375, 0, 0);
                glScalef(0.75, 0.5, 0.5);
                createCube();
            glPopMatrix();

    //Left Sword
            glPushMatrix();
                setMaterial(8);
                glTranslatef(0.75, 0, 0);
                glBegin(GL_QUADS);

                    normal = vectorProduct(0, 0, -0.15, 1.5, 0, -0.15, 0, 0.1, 0);
                    glNormal3f(normal[0], normal[1], normal[2]);
                    glVertex3f(0, 0, -0.15);
                    glVertex3f(1.5, 0, -0.15);
                    glVertex3f(1.5, 0.1, 0);
                    glVertex3f(0, 0.1, 0);

                    normal = vectorProduct(0, -0.1, 0, 1.5, -0.1, 0, 0, 0, -0.15);
                    glNormal3f(normal[0], -normal[1], -normal[2]);
                    glVertex3f(0, 0, -0.15);
                    glVertex3f(1.5, 0, -0.15);
                    glVertex3f(1.5, -0.1, 0);
                    glVertex3f(0, -0.1, 0);

                    normal = vectorProduct(0, 0, 0.15, 1.5, 0, 0.15, 0, 0.1, 0);
                    glNormal3f(normal[0], normal[1], normal[2]);
                    glVertex3f(0, 0, 0.15);
                    glVertex3f(1.5, 0, 0.15);
                    glVertex3f(1.5, 0.1, 0);
                    glVertex3f(0, 0.1, 0);

                    normal = vectorProduct(0, -0.1, 0, 1.5, -0.1, 0, 0, 0, 0.15);
                    glNormal3f(normal[0], -normal[1], -normal[2]);
                    glVertex3f(0, 0, 0.15);
                    glVertex3f(1.5, 0, 0.15);
                    glVertex3f(1.5, -0.1, 0);
                    glVertex3f(0, -0.1, 0);
                glEnd();

        //Left Sword Tip
                glPushMatrix();
                    glTranslatef(1.5, 0, 0);
                    glBegin(GL_TRIANGLES);

                        normal = vectorProduct(0, 0, 0.15, 0.5, 0, 0, 0, 0.1, 0);
                        glNormal3f(normal[0], normal[1], normal[2]);
                        glVertex3f(0, 0, 0.15);
                        glVertex3f(0.5, 0, 0);
                        glVertex3f(0, 0.1, 0);

                        normal = vectorProduct(0, -0.1, 0, 0.5, 0, 0, 0, 0, 0.15);
                        glNormal3f(normal[0], normal[1], normal[2]);
                        glVertex3f(0, 0, 0.15);
                        glVertex3f(0.5, 0, 0);
                        glVertex3f(0, -0.1, 0);

                        normal = vectorProduct(0, 0, -0.15, 0, 0.1, 0, 0.5, 0, 0);
                        glNormal3f(normal[0], normal[1], normal[2]);
                        glVertex3f(0, 0, -0.15);
                        glVertex3f(0.5, 0, 0);
                        glVertex3f(0, 0.1, 0);

                        normal = vectorProduct(0, -0.1, 0, 0.5, 0, 0, 0, 0, -0.15);
                        glNormal3f(normal[0], normal[1], normal[2]);
                        glVertex3f(0, 0, -0.15);
                        glVertex3f(0.5, 0, 0);
                        glVertex3f(0, -0.1, 0);
                    glEnd();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Robot::dab() {
    if (dabLeftArm < 90) {
        dabLeftArm += 1.8;
        dabRightArm += 0.4;

        normalArms[0] -= 1.8;
        normalArms[1] -= 0.4;
    }

    if (normalArms[2] > 0) {
        normalArms[2] -= 1.8;
        normalArms[1] += 0.6;
    }
}

void Robot::getNormalArms() {
    if (normalArms[0] < 90) {
        dabLeftArm -= 1.8;
        dabRightArm -= 0.4;

        normalArms[0] += 1.8;
        normalArms[1] += 0.6;
    }

    if (normalArms[2] > 0) {
        normalArms[2] -= 1.8;
        normalArms[1] += 0.6;
    }

}

void Robot::transformation() {
    if (dabLeftArm > 0) dabLeftArm -= 1.8;
    if (dabRightArm > 0) dabRightArm -= 0.4;
    if (normalArms[1] > 0.0) normalArms[1] -= 0.6;
    if (normalArms[2] < 90.0) normalArms[2] += 1.8;
    if (rotateRightLeg < 90) rotateRightLeg += 1.8;
    if (rotateLeftLeg < 90) rotateLeftLeg += 1.8;
}

void Robot::walk(){

    //Avancer jambes
    if(rotateRightLegLimit == 0){
        //Rotation jambes
        rotateRightLeg -= 2;//Avance jambe g
        rotateLeftLeg += 2;//Recule jambe d

        //Rotation genoux
        if(rotateRightLeg <= -20 ){
            rotateRightKnee += 2;//Recule genou g
        }
        if(rotateLeftLeg <= -20 ){
            rotateLeftKnee -= 2;//Avance genou d
        }
    }

    if (rotateRightLeg <= -45 )
        rotateRightLegLimit = 1;

    //Reculer jambes
    if(rotateRightLegLimit == 1){
        //Rotation jambes
        rotateRightLeg += 2;//Recule jambe g
        rotateLeftLeg -= 2;//Avance jambe d

        //Rotation genoux
        if(rotateRightLeg >= 20){
            rotateRightKnee -= 2;//Avance genou d
        }
        if(rotateLeftLeg >= 20){
            rotateLeftKnee += 2;//Recule genou g
        }
    }

    if (rotateRightLeg >= 45 )
        rotateRightLegLimit =0;

    glutPostRedisplay();
}

void Robot::createPelvis(){
    glPushMatrix();
        glTranslatef(0, -1.08, 0.04);
        glScalef(1.2, 1.2, 1.2);

        //CENTER BLOCK
        glPushMatrix();
            glScalef(0.25, 0.3, 0.8);
            createCube();
        glPopMatrix();

        //RIGHT TRIANGLE
        glPushMatrix();
            //Front triangle
            glPushMatrix();
                glTranslatef(0.1, 0.15, -0.4);
                glBegin(GL_QUADS);
                glNormal3f(0,0,1);
                glVertex3f(0.0f, 0.0f, 0.8f);
                glVertex3f(0.0f, -0.3f, 0.8f);
                glVertex3f(0.45f, -0.1f, 0.8f);
                glVertex3f(0.45f, 0.0f, 0.8f);
                glEnd();
            glPopMatrix();

            //Back triangle
            glPushMatrix();
                glTranslatef(0.1, 0.15, -1.2);
                glBegin(GL_QUADS);
                glNormal3f(0, 0, -1);
                glVertex3f(0.0f, 0.0f, 0.8f);
                glVertex3f(0.0f, -0.3f, 0.8f);
                glVertex3f(0.45f, -0.1f, 0.8f);
                glVertex3f(0.45f, 0.0f, 0.8f);
                glEnd();
            glPopMatrix();

            //Bottom
            glPushMatrix();
                glTranslatef(0.1, 0.15, -0.4);
                glBegin(GL_QUADS);
                normal = vectorProduct(0.0f, -0.3f, 0.8f, 0.45f, -0.1f, 0.8f, 0.0f, -0.3f, -0.01f);
                glNormal3f(normal[0], -normal[1], normal[2]);
                glVertex3f(0.0f, -0.3f, 0.8f);
                glVertex3f(0.45f, -0.1f, 0.8f);
                glVertex3f(0.45f, -0.1f, -0.01f);
                glVertex3f(0.0f, -0.3f, -0.01f);
                glEnd();
            glPopMatrix();

            //Side right
            glPushMatrix();
                glTranslatef(0.1, 0.15, -0.4);
                glBegin(GL_QUADS);
                glNormal3f(1, 0, 0);
                glVertex3f(0.45f, -0.1f, 0.8f);
                glVertex3f(0.45f, -0.1f, -0.01f);
                glVertex3f(0.45f, 0.0f, -0.01f);
                glVertex3f(0.45f, 0.0f, 0.8f);
                glEnd();
            glPopMatrix();
        glPopMatrix();

        //LEFT TRIANGLE
        glPushMatrix();
            glRotated(180,0,1,0);
            //Front triangle
            glPushMatrix();
                glTranslatef(0.1, 0.15, -0.4);
                glBegin(GL_QUADS);
                glNormal3f(0,0,1);
                glVertex3f(0.0f, 0.0f, 0.8f);
                glVertex3f(0.0f, -0.3f, 0.8f);
                glVertex3f(0.45f, -0.1f, 0.8f);
                glVertex3f(0.45f, 0.0f, 0.8f);
                glEnd();
            glPopMatrix();

            //Back triangle
            glPushMatrix();
                glTranslatef(0.1, 0.15, -1.2);
                glBegin(GL_QUADS);
                glNormal3f(0, 0, -1);
                glVertex3f(0.0f, 0.0f, 0.8f);
                glVertex3f(0.0f, -0.3f, 0.8f);
                glVertex3f(0.45f, -0.1f, 0.8f);
                glVertex3f(0.45f, 0.0f, 0.8f);
                glEnd();
            glPopMatrix();

            //Bottom
            glPushMatrix();
                glTranslatef(0.1, 0.15, -0.4);
                glBegin(GL_QUADS);
                normal = vectorProduct(0.0f, -0.3f, 0.8f, 0.45f, -0.1f, 0.8f, 0.0f, -0.3f, -0.01f);
                glNormal3f(normal[0], -normal[1], normal[2]);
                glVertex3f(0.0f, -0.3f, 0.8f);
                glVertex3f(0.45f, -0.1f, 0.8f);
                glVertex3f(0.45f, -0.1f, -0.01f);
                glVertex3f(0.0f, -0.3f, -0.01f);
                glEnd();
            glPopMatrix();

            //Side right
            glPushMatrix();
                glTranslatef(0.1, 0.15, -0.4);
                glBegin(GL_QUADS);
                glNormal3f(1, 0, 0);
                glVertex3f(0.45f, -0.1f, 0.8f);
                glVertex3f(0.45f, -0.1f, -0.01f);
                glVertex3f(0.45f, 0.0f, -0.01f);
                glVertex3f(0.45f, 0.0f, 0.8f);
                glEnd();
            glPopMatrix();
        glPopMatrix();

        //Top
        glPushMatrix();
            glScalef(1.09, 1.0, 0.6);
            glTranslatef(-0.5, 0.149, -0.7);
            glRotated(90,1,0,0);
            glBegin(GL_QUADS);
            glNormal3f(0,1,0);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 1.4f, 0.0f);
            glVertex3f(0.0f, 1.4f, 0.0f);
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

void Robot::createLegs(){
    /**************right leg**************/
    glPushMatrix();
        glTranslatef(0.1, -0.1, 0);
            setMaterial(3);
            glTranslatef(0, -1.0, 0);
            glRotated(rotateRightLeg, 1, 0, 0);
            glTranslatef(0, 1.0, 0);
        //Thigh
        glPushMatrix();
            glTranslatef(0.3, -1.5, 0);
            glScalef(0.4, 1.10, 0.6);
            createCube();
        glPopMatrix();

        //Knee
        glPushMatrix();
            glTranslatef(0.3, -1.95, 0);
            glScaled(0.75,0.75,0.75);
            glutSolidSphere(radius, 255, 255);
        glPopMatrix();

        //Calf
        glPushMatrix();
            setMaterial(2);
            glTranslatef(0, -2.0, 0);
            glRotated(rotateRightKnee, 1, 0, 0);
            glTranslatef(0, 2.0, 0);

            glPushMatrix();
                glTranslatef(0.3, -2.7, 0);
                glScalef(0.6, 1.5, 0.8);
                createCube();
            glPopMatrix();

            //Foot
            glPushMatrix();
                    //Left triangle
                glPushMatrix();
                    glTranslatef(0.0, -3.45, 0.75);
                        glBegin(GL_QUADS);
                        glNormal3f(0, -1, 0);
                        glVertex3f(0.0f, 0.0f, -0.4f);
                        glVertex3f(0.0f, 0.0f, 0.2f);
                        glVertex3f(0.0f, 0.4f, 0.2f);
                        glVertex3f(0.0f, 0.70f, -0.4f);
                        glEnd();
                glPopMatrix();
                    //Right triangle
                glPushMatrix();
                    glTranslatef(0.6, -3.45, 0.75);
                        glBegin(GL_QUADS);
                        glNormal3f(0, 1, 0);
                        glVertex3f(0.0f, 0.0f, -0.4f);
                        glVertex3f(0.0f, 0.0f, 0.2f);
                        glVertex3f(0.0f, 0.4f, 0.2f);
                        glVertex3f(0.0f, 0.70f, -0.4f);
                        glEnd();
                glPopMatrix();

                //Front
                glPushMatrix();
                    glTranslatef(0.0, -3.45, 0.75);
                        glBegin(GL_QUADS);
                        glNormal3f(0,0,1);
                        glVertex3f(0.0f, 0.0f, 0.2f);
                        glVertex3f(0.6f, 0.0f, 0.2f);
                        glVertex3f(0.6f, 0.4f, 0.2f);
                        glVertex3f(0.0f, 0.4f, 0.2f);
                        glEnd();
                glPopMatrix();

                //Top
                glPushMatrix();
                    glTranslatef(0.0, -3.45, 0.75);
                        glBegin(GL_QUADS);
                        normal = vectorProduct(0.0f, 0.4f, 0.2f, 0.6f, 0.4f, 0.2f, 0.0f, 0.7f, -0.4f);
                        glNormal3f(normal[0], normal[1], normal[2]);
                        glVertex3f(0.0f, 0.7f, -0.4f);
                        glVertex3f(0.6f, 0.7f, -0.4f);
                        glVertex3f(0.6f, 0.4f, 0.2f);
                        glVertex3f(0.0f, 0.4f, 0.2f);
                        glEnd();
                glPopMatrix();

            glPopMatrix();

            //Wheel up
            glPushMatrix();
                glTranslated(0.6,-2.4,0);
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
                glTranslated(0.6,-3.1,0);
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
        glPopMatrix();
    glPopMatrix();

    /*********************left leg**************/
    glPushMatrix();
        glTranslatef(-0.7, -0.1, 0);
        setMaterial(3);
        glTranslatef(0, -1.0, 0);
            glRotated(rotateLeftLeg, 1, 0, 0);
            glTranslatef(0, 1.0, 0);
        //Thigh
        glPushMatrix();
            glTranslatef(0.3, -1.5, 0);
            glScalef(0.4, 1.10, 0.6);
            createCube();
        glPopMatrix();

        //Knee
        glPushMatrix();
            glTranslatef(0.3, -1.95, 0);
            glScaled(0.75,0.75,0.75);
            glutSolidSphere(radius, 255, 255);
        glPopMatrix();

        //Calf
        glPushMatrix();
            setMaterial(2);
            glTranslatef(0, -2.0, 0);
            glRotated(rotateLeftKnee, 1, 0, 0);
            glTranslatef(0, 2.0, 0);

            glPushMatrix();
                glTranslatef(0.3, -2.7, 0);
                glScalef(0.6, 1.5, 0.8);
                createCube();
            glPopMatrix();

            //Foot
            glPushMatrix();
                    //Left triangle
                glPushMatrix();
                    glTranslatef(0.0, -3.45, 0.75);
                        glBegin(GL_QUADS);
                        glNormal3f(0,-1,0);
                        glVertex3f(0.0f, 0.0f, -0.4f);
                        glVertex3f(0.0f, 0.0f, 0.2f);
                        glVertex3f(0.0f, 0.4f, 0.2f);
                        glVertex3f(0.0f, 0.70f, -0.4f);
                        glEnd();
                glPopMatrix();
                    //Right triangle
                glPushMatrix();
                    glTranslatef(0.6, -3.45, 0.75);
                        glBegin(GL_QUADS);
                        glNormal3f(0,1,0);
                        glVertex3f(0.0f, 0.0f, -0.4f);
                        glVertex3f(0.0f, 0.0f, 0.2f);
                        glVertex3f(0.0f, 0.4f, 0.2f);
                        glVertex3f(0.0f, 0.70f, -0.4f);
                        glEnd();
                glPopMatrix();

                //Front
                glPushMatrix();
                    glTranslatef(0.0, -3.45, 0.75);
                        glBegin(GL_QUADS);
                        glNormal3f(0,0,1);
                        glVertex3f(0.0f, 0.0f, 0.2f);
                        glVertex3f(0.6f, 0.0f, 0.2f);
                        glVertex3f(0.6f, 0.4f, 0.2f);
                        glVertex3f(0.0f, 0.4f, 0.2f);
                        glEnd();
                glPopMatrix();

                //Top
                glPushMatrix();
                    glTranslatef(0.0, -3.45, 0.75);
                        glBegin(GL_QUADS);
                        normal = vectorProduct(0.0f, 0.4f, 0.2f, 0.6f, 0.4f, 0.2f, 0.0f, 0.7f, -0.4f);
                        glNormal3f(normal[0], normal[1], normal[2]);
                        glVertex3f(0.0f, 0.7f, -0.4f);
                        glVertex3f(0.6f, 0.7f, -0.4f);
                        glVertex3f(0.6f, 0.4f, 0.2f);
                        glVertex3f(0.0f, 0.4f, 0.2f);
                        glEnd();
                glPopMatrix();

            glPopMatrix();


            glPushMatrix();
                glRotated(180,0,1,0);
                glTranslated(-0.6,0,0);
                //Wheel up
                glPushMatrix();
                    glTranslated(0.6,-2.4,0);
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
                    glTranslated(0.6,-3.1,0);
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

void Robot::setMaterial(int mode){
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
