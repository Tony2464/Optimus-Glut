
/*********************************************************/
/*        Projet Infgraphie : Optimus-Glut               */
/*********************************************************/
/*													     */
/* Groupe : Nicolas Fouchard, Steven Ye, Anthony Fargette*/
/*													     */
/*********************************************************/
/*													     */
/*                                                       */
/*													     */
/*********************************************************/



#include<windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "fmod/fmod.h"

float angle = 0.0;
float angleL2 = 0.0;
float cameraAngle = 10.0;
int way = 0;
float r = 3;//Rayon, Distance entre la camera et l'objet
float phi = 0;//Angle de rotation veritcale de la camera
float alpha = 0;//Amgle de rotation horizontale de la camera
float xCam = 0, yCam = 0, zCam = 0;//Coordonnees de la camera
float rotateValue = 0.25;
float zoomValue = 0.25;
float limitZoom = 2;
float limitRotate = 0.005;
float tab[9];
float *normal;
float radius = 0.25;
float lx = 0.0;
float ly = 0.0;

/* prototypes de fonctions */
void initRendering();                           // Initialisation du rendu
void display();                             // mod�lisation
void reshape(int w,int h);                      // visualisation
void update(int value);                         // mise � jour: appelle Timer pour l'animation de la sc�ne
void rotateRight();
void rotateLeft();
void rotateUp();
void rotateDown();
void zoom();
void dezoom();
void sound();
void keyboard(unsigned char key, int x, int y); // fonction clavier
void SpecialInput(int key, int x, int y);
void createCube();
float* vectorProduct(float point1, float point2, float point3, float point4, float point5, float point6, float point7, float point8, float point9);
void mouseMove(int x, int y);


/* Programme principal */
int main(int argc,       // argc: nombre d'arguments, argc vaut au moins 1
		  char **argv){  // argv: tableau de chaines de caract�res, argv[0] contient le nom du programme lanc� (plus un �ventuel chemin)


	/* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);                       // Initialisation
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // mode d'affichage RGB, et test prafondeur
    glutInitWindowSize(500, 500);                // dimension fen�tre
	glutInitWindowPosition (100, 100);           // position coin haut gauche
	glutCreateWindow("Robot");  // nom

	/* Initialisation d'OpenGL */
	initRendering();

	/* Enregistrement des fonctions de rappel
     => initialisation des fonctions callback appel�es par glut */
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialInput);

	glutPassiveMotionFunc(mouseMove);

	/* rq: le callback de fonction (fonction de rappel) est une fonction qui est pass�e en argument � une
	autre fonction. Ici, le main fait usage des deux fonctions de rappel (qui fonctionnent en m�me temps)
	alors qu'il ne les conna�t pas par avance.*/


	/* Entr�e dans la boucle principale de glut, traitement des �v�nements */
    glutMainLoop();         // lancement de la boucle de r�ception des �v�nements
    return 0;               // pour finir
}


/* Initialisation d'OpenGL pour le rendu de la sc�ne */
void initRendering() {

    /* Active le z-buffer */
    glEnable(GL_DEPTH_TEST);

	/* Activation des couleurs */
	glEnable(GL_COLOR_MATERIAL);

	/* d�finit la couleur d'effacement et la couleur de fond */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  d�finit la taille d'un pixel*/
	glPointSize(2.0);

}

/* Cr�ation de la sc�ne */
void display(){

	/* Efface les tampons de couleur et de profondeur de l'image avec la couleur de fond.
	rq: buffer: m�moire tampon, c'est donc une surface en memoire utilis�e pour stocker une image*/
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/* la mat de visualisation-mod�lisation est modifiable par d�faut */
	glMatrixMode(GL_MODELVIEW);

	/* on charge l'identit� dans la matrice de mod�lisation-visualisation*/
	glLoadIdentity();


	/* Permet de cr�er un point de vue. D�finit une matrice de mod�lisation-visualisation et la multiplie
	� droite de lma matrice active, ici l'identit�*/
	xCam = r * cos(phi) * sin(alpha);
	yCam = r * sin(phi);
	zCam = r * cos(phi) * cos(alpha);
	gluLookAt(xCam, yCam, zCam,      // position cam�ra
		      lx, ly, 0.0,      // point de mire
			  0.0, 1.0, 0.0);     // vecteur d'orientation cam�ra
    //glTranslatef(a,b,c);
    //glRotatef(5,1,0,0);
    //glRotatef(5,0,1,0);
    //glRotatef(5,0,0,1);


	/* A vous de jouer */



    //Top of the chest
    glPushMatrix();

    glBegin(GL_QUADS);

    glNormal3f(1, 0, 0);
    //Right
    glColor3f(0.6f, 0.0, 0.0f);
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
    glVertex3f(-0.75f, 0.5f, 0.5f);
    glVertex3f(-0.75f, -0.5f, 0.5f);
    glVertex3f(0.0f, -0.5f, 0.7f);
    glVertex3f(0.0f, 0.5f, 0.7f);

    //Front right
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

    //Back (jetpack)
    glPushMatrix();

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
    glNormal3f(0, -1, 0);
    glVertex3f(0.3f, 0.5f, -0.5f);
    glVertex3f(0.3f, 0.5f, -0.7f);
    glVertex3f(0.5f, 0.5f, -0.7f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    //Back
    normal = vectorProduct(0.3, -0.5, -0.7, 0.5, -0.5, -0.7, 0.3, 0.5, -0.7);
    glNormal3f(normal[0], normal[1], normal[2]);
    glVertex3f(0.3f, -0.5f, -0.7f);
    glVertex3f(0.5f, -0.5f, -0.7f);
    glVertex3f(0.5f, 0.5f, -0.7f);
    glVertex3f(0.3f, 0.5f, -0.7f);

    //Right
    normal = vectorProduct(0.5, -0.5, -0.5, 0.5, -0.5, -0.7, 0.5, 0.5, -0.5);
    glNormal3f(normal[0], normal[1], normal[2]);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.7f);
    glVertex3f(0.5f, 0.5f, -0.7f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    //Right
    normal = vectorProduct(0.3, -0.5f, -0.5f, 0.3f, -0.5f, -0.7f, 0.3f, 0.5f, -0.5f);
    glNormal3f(normal[0], normal[1], normal[2]);
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

    glPopMatrix();

    //Hexagone
    glPushMatrix();

    glColor3f(0.4f,0.4f,0.4f);

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

    glEnd();
    glPopMatrix();

    //Right arm
    glPushMatrix();
        glPushMatrix();
            glTranslatef(1.125, 0.25, 0);
            glScalef(0.75, 0.5, 0.5);
            createCube();
        glPopMatrix();

        glPushMatrix();
            glColor3f(1, 1, 1);
            glTranslatef(1.5, 0.25, 0);
            glutSolidSphere(radius, 255, 255);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(1.875, 0.25, 0);
            glScalef(0.75, 0.5, 0.5);
            createCube();
        glPopMatrix();
    glPopMatrix();

    //Head
    glPushMatrix();
        glBegin(GL_POLYGON);
        glColor3f(0.2f, 0.2f, 0.8f);

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

        glVertex3f(0.0f, 0.95f, 0.4f);
        glVertex3f(0.0f, 0.5f, 0.4f);
        glVertex3f(0.3f, 0.5f, 0.3f);
        glVertex3f(0.3f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(0.0f, 0.95f, 0.4f);
        glVertex3f(0.0f, 0.5f, 0.4f);
        glVertex3f(-0.3f, 0.5f, 0.3f);
        glVertex3f(-0.3f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(-0.3f, 0.95f, 0.0f);
        glVertex3f(-0.3f, 0.5f, 0.0f);
        glVertex3f(-0.3f, 0.5f, 0.3f);
        glVertex3f(-0.3f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(0.3f, 0.95f, 0.0f);
        glVertex3f(0.3f, 0.5f, 0.0f);
        glVertex3f(0.3f, 0.5f, 0.3f);
        glVertex3f(0.3f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(-0.15f, 0.5f, -0.3f);
        glVertex3f(-0.15f, 0.95f, -0.3f);
        glVertex3f(-0.3f, 0.95f, 0.0f);
        glVertex3f(-0.3f, 0.5f, 0.0f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(0.15f, 0.5f, -0.3f);
        glVertex3f(0.15f, 0.95f, -0.3f);
        glVertex3f(0.3f, 0.95f, 0.0f);
        glVertex3f(0.3f, 0.5f, 0.0f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(0.15f, 0.5f, -0.3f);
        glVertex3f(0.15f, 0.95f, -0.3f);
        glVertex3f(-0.15f, 0.95f, -0.3f);
        glVertex3f(-0.15f, 0.5f, -0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(0.3f, 0.5f, 0.2f);
        glVertex3f(0.4f, 0.5f, 0.2f);
        glVertex3f(0.4f, 0.75f, 0.2f);
        glVertex3f(0.3f, 0.75f, 0.2f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(0.3f, 0.5f, 0.1f);
        glVertex3f(0.4f, 0.5f, 0.1f);
        glVertex3f(0.4f, 0.75f, 0.1f);
        glVertex3f(0.3f, 0.75f, 0.1f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(0.4f, 0.5f, 0.1f);
        glVertex3f(0.4f, 0.5f, 0.2f);
        glVertex3f(0.4f, 0.75f, 0.2f);
        glVertex3f(0.4f, 0.75f, 0.1f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(-0.3f, 0.5f, 0.2f);
        glVertex3f(-0.4f, 0.5f, 0.2f);
        glVertex3f(-0.4f, 0.75f, 0.2f);
        glVertex3f(-0.3f, 0.75f, 0.2f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(-0.3f, 0.5f, 0.1f);
        glVertex3f(-0.4f, 0.5f, 0.1f);
        glVertex3f(-0.4f, 0.75f, 0.1f);
        glVertex3f(-0.3f, 0.75f, 0.1f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(-0.4f, 0.5f, 0.1f);
        glVertex3f(-0.4f, 0.5f, 0.2f);
        glVertex3f(-0.4f, 0.75f, 0.2f);
        glVertex3f(-0.4f, 0.75f, 0.1f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_TRIANGLES);

        glVertex3f(-0.3f, 0.75f, 0.2f);
        glVertex3f(-0.4f, 0.75f, 0.2f);
        glVertex3f(-0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_TRIANGLES);

        glVertex3f(-0.3f, 0.75f, 0.1f);
        glVertex3f(-0.3f, 0.75f, 0.2f);
        glVertex3f(-0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_TRIANGLES);

        glVertex3f(-0.4f, 0.75f, 0.1f);
        glVertex3f(-0.4f, 0.75f, 0.2f);
        glVertex3f(-0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_TRIANGLES);

        glVertex3f(-0.4f, 0.75f, 0.1f);
        glVertex3f(-0.4f, 0.75f, 0.1f);
        glVertex3f(-0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    //
    glPushMatrix();
        glBegin(GL_TRIANGLES);

        glVertex3f(0.3f, 0.75f, 0.2f);
        glVertex3f(0.4f, 0.75f, 0.2f);
        glVertex3f(0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_TRIANGLES);

        glVertex3f(0.3f, 0.75f, 0.1f);
        glVertex3f(0.3f, 0.75f, 0.2f);
        glVertex3f(0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_TRIANGLES);

        glVertex3f(0.4f, 0.75f, 0.1f);
        glVertex3f(0.4f, 0.75f, 0.2f);
        glVertex3f(0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_TRIANGLES);

        glVertex3f(0.4f, 0.75f, 0.1f);
        glVertex3f(0.4f, 0.75f, 0.1f);
        glVertex3f(0.3f, 1.1f, 0.15f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(-0.1f, 0.95f, -0.2f);
        glVertex3f(-0.05f, 1.0f, -0.2f);
        glVertex3f(0.05f, 1.0f, -0.2f);
        glVertex3f(0.1f, 0.95f, -0.2f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(-0.1f, 0.95f, 0.3f);
        glVertex3f(-0.05f, 1.0f, 0.3f);
        glVertex3f(0.05f, 1.0f, 0.3f);
        glVertex3f(0.1f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(-0.1f, 0.95f, -0.2f);
        glVertex3f(-0.05f, 1.0f, -0.2f);
        glVertex3f(-0.05f, 1.0f, 0.3f);
        glVertex3f(-0.1f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(0.1f, 0.95f, -0.2f);
        glVertex3f(0.05f, 1.0f, -0.2f);
        glVertex3f(0.05f, 1.0f, 0.3f);
        glVertex3f(0.1f, 0.95f, 0.3f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);

        glVertex3f(-0.05f, 1.0f, -0.2f);
        glVertex3f(0.05f, 1.0f, -0.2f);
        glVertex3f(-0.05f, 1.0f, 0.3f);
        glVertex3f(0.05f, 1.0f, 0.3f);

    glEnd();
    glPopMatrix();



	/* On swap (�change) les buffers, c�d, on fait passer l'image calcul�e et dessin�e
	dans le back buffer au buffer qui va l'afficher: le front buffer (en g�n�ral), c'est le bouble buffering
	Cela �vite une image anim�e sacad�e, si elle �tait directement trac�e dans le front buffer*/
	glutSwapBuffers();

	/* On force l'affichage */
	glFlush(); // nettoie les fen�tres pr�c�dentes
}



/*  Mise en forme de la sc�ne pour l'affichage */
void reshape(int w,  // w: largeur fen�tre
			 int h)  // h: hauteur fen�tre
{
	/* Viewport: cadrage. Sp�cifie la r�gion (position et taille en px) que l'image observ�e de la sc�ne occupe
	� l'�cran => r�duction et agrandissement de l'image possible*/
	glViewport(0, 0,(GLsizei) w, (GLsizei) h);

	/* Sp�cifie que la matrice de projection va �tre modifi�e  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();             // matrice courante: l'identit�
	//glOrtho(-2.0, 2.0, -2.0, 2.0, 1.5, 20.0);
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

	/* Perspective avec point de fuite */
	gluPerspective(60.0,                       // angle d'ouverture vertical cam�ra
				   (GLfloat) w / (GLfloat) h,  // ratio largeur-hauteur
				   1.0,						   // plan proche z=1
				   200.0);                     // plan �loign� z=200


}

void update(int value){



}

/* Fonction de gestion du clavier */
void keyboard(unsigned char key, int x, int y) {

		switch (key) {

			case 'z':   /* rotation */
			    zoom();
                glutPostRedisplay();
            break;

            case 'd':   /* rotation */
			    dezoom();
                glutPostRedisplay();
            break;

            case 'j':   /* son */
			    sound();
            break;

			case 'q':   /* Quitter le programme */
				exit(0);
            break;
		}
}

/* Fonction de gestion du clavier pour les fleches */
void SpecialInput(int key, int x, int y) {
    switch(key) {
    case GLUT_KEY_UP:
        rotateUp();
        glutPostRedisplay();
    break;

    case GLUT_KEY_DOWN:
        rotateDown();
        glutPostRedisplay();
    break;

    case GLUT_KEY_LEFT:
        rotateLeft();
        glutPostRedisplay();
    break;

    case GLUT_KEY_RIGHT:
        rotateRight();
        glutPostRedisplay();
    break;
    }
}


/*Fonctions de rotation et de zoom de la camera*/
void rotateRight() {
    alpha += rotateValue;
}

void rotateLeft() {
    alpha -= rotateValue;
}

void rotateUp() {
    phi += rotateValue;
        if(phi > M_PI/2 - limitRotate)
            phi = M_PI/2 - 0.005;
}

void rotateDown() {
    phi -= rotateValue;
        if(phi < - M_PI/2 + limitRotate)
                phi = - M_PI/2 + 0.005;
}

void zoom() {
    r -= zoomValue;
        if(r < limitZoom)
            r = limitZoom;
}

void dezoom() {
    r += zoomValue;
}

void sound(){

  FMOD_SYSTEM * sys;
  FMOD_SOUND * sound;
  FMOD_RESULT resultat;
  FMOD_CHANNEL * channel;

  FMOD_System_Create(&sys);
  FMOD_System_Init(sys, 1, FMOD_INIT_NORMAL, NULL);

  /* On ouvre la musique */
  resultat = FMOD_System_CreateSound(sys, "../../sounds/jesuisoptimus.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &sound);

    if (resultat != FMOD_OK)
  {
      fprintf(stderr, "Impossible de lire le fichier mp3\n");
  }

  /* On joue la musique */
  FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound, 0, NULL);

  Sleep(4000);
  FMOD_Sound_Release(sound);
  FMOD_System_Close(sys);

}

float* vectorProduct(float point1, float point2, float point3, float point4, float point5, float point6, float point7, float point8, float point9) {
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

void createCube() {
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

void mouseMove(int x, int y) {
    if (x > 250) {
        lx += 0.1;
    }

    if (x < 250) {
        lx -= 0.1;
    }

    if (y > 250) {
        ly -= 0.1;
    }

    if (y < 250) {
        ly += 0.1;
    }

    glutWarpPointer(250, 250);
    glutPostRedisplay();
}
