
/*********************************************************/
/*        Projet Infographie : Optimus-Glut               */
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
float r = 8;//Rayon, Distance entre la camera et l'objet
float phi = 0;//Angle de rotation verticale de la camera
float alpha = 0;//Angle de rotation horizontale de la camera
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
float lz = 0.0;
float dabRightArm = 0;
float dabLeftArm = 0;
float normalArms[2] = {90, 30};
short myBool = 0;
float rotateRightLeg = 0;
float rotateLeftLeg = 0;
int rotateRightLegLimit = 0;
float rotateRightKnee = 0;
float rotateLeftKnee = 0;

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
void createJetpack();
void createChest();
void createHexagone();
void createRightArm();
void createLeftArm();
void dab();
void getNormalArms();
float* vectorProduct(float point1, float point2, float point3, float point4, float point5, float point6, float point7, float point8, float point9);
void mouseMove(int x, int y);
void setlight();
void setmaterial(int mode);
void createHead();
void walk();
void createPelvis();
void createLegs();

    /* Programme principal */
    int main(int argc, // argc: nombre d'arguments, argc vaut au moins 1
             char **argv)
{ // argv: tableau de chaines de caract�res, argv[0] contient le nom du programme lanc� (plus un �ventuel chemin)

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
	glutSetCursor(GLUT_CURSOR_NONE);

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
		      lx, ly, lz,      // point de mire
			  0.0, 1.0, 0.0);     // vecteur d'orientation cam�ra
    //glTranslatef(a,b,c);
    //glRotatef(5,1,0,0);
    //glRotatef(5,0,1,0);
    //glRotatef(5,0,0,1);


	/* A vous de jouer */


    //setlight();
    //setmaterial();

    //Top of the chest
    glPushMatrix();
        setmaterial(1);
        createChest();
        glutPostRedisplay();
    glPopMatrix();

    //Back (jetpack)
    glPushMatrix();
        setmaterial(2);
        createJetpack();
        glutPostRedisplay();
    glPopMatrix();

    glPushMatrix();
        setmaterial(3);
        createHexagone();
        glutPostRedisplay();
    glPopMatrix();

    //Right arm
    glPushMatrix();
        glScalef(1, 0.99, 1);
        createRightArm();
    glPopMatrix();

    glPushMatrix();
        glScalef(1, 0.99, 1);
        createLeftArm();
    glPopMatrix();

    glPushMatrix();
        setmaterial(2);
        createHead();
        glutPostRedisplay();
    glPopMatrix();

    glPushMatrix();
        setmaterial(3);
        createPelvis();
        glutPostRedisplay();
    glPopMatrix();

    glPushMatrix();
        createLegs();
        glutPostRedisplay();
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

void setlight(){
    //here you set the lights and parameters, example with one light
    float LightAmbient[] = { 0.1f, 0.1f, 0.05f, 1.0f };
    float LightEmission[] = { 1.0f, 1.0f, 0.8f, 1.0f };
    float LightDiffuse[] = { 1.0f, 1.0f, 0.8f, 1.0f };
    float LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float LightDirection[]={-0.5f, -0.5f, -0.5f};

    float lightPos[] = {2, 2, 2, 1};
    float lightColor[] = {1, 0, 0};

    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, LightDirection);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void setmaterial(int mode){
    //here you set materials, you must declare each one of the colors global or locally like this:
    float MatAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    float MatDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float MatSpecular[] = { 0.1f, 0.1f, 0.0f, 0.1f };
    float MatShininess = 60;
    float color[] = {1.0f,0.0f,0.0f,1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);


    switch(mode){

    case 1 :
         glColor3f(0.6f,0.0f,0.0f);
         break;

    case 2 :
         glColor3f(0.0f,0.0f,0.7f);
         break;

    case 3 :
         glColor3f(0.5f,0.5f,0.5f);
         break;

    case 4 :
         glColor3f(0.1f, 0.1f, 0.1f);
         break;

    case 5 :
        glColor3f(0.2f, 0.2f, 0.2f);
        break;

    case 6 :
        glColor3f(0.2f, 0.2f, 0.2f);
        break;

    case 7 :
        glColor3f(0.2f, 0.2f, 0.2f);
        break;

    case 8 :
        glColor3f(0.2f, 0.2f, 0.2f);
        break;
    }

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

            case 'b':
                if (dabLeftArm < 90)
                    dab();
            break;

            case 'n':
                if (normalArms[0] < 90)
                    getNormalArms();
            break;

            case 'a':   /* marcher */
			    walk();
                glutPostRedisplay();
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

void createHead(){

    //Head
    glPushMatrix();
        glBegin(GL_POLYGON);
        glNormal3f(0.0f,1.0f,0.0f);

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
        normal = vectorProduct(0.0f, 0.5f, 0.4f, -0.3f, 0.5f, 0.3f, 0.0f, 0.95f, 0.4f);
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
        glNormal3f(-normal[0], normal[1], -normal[2]);

        glVertex3f(-0.15f, 0.5f, -0.3f);
        glVertex3f(-0.15f, 0.95f, -0.3f);
        glVertex3f(-0.3f, 0.95f, 0.0f);
        glVertex3f(-0.3f, 0.5f, 0.0f);

    glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
        normal = vectorProduct(0.3f, 0.5f, 0.0f, 0.15f, 0.5f, -0.3f, 0.3f, 0.95f, 0.0f);
        glNormal3f(normal[0], normal[1], -normal[2]);

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
        glNormal3f(normal[0], normal[1], -normal[2]);

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
        glNormal3f(normal[0], normal[1], -normal[2]);

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

void mouseMove(int x, int y) {
    if (x > 250) {
        if (xCam >= 1.5 && lz > -1.5) {
            lz -= 0.01;
        }
        if (xCam < 1.5 && lz < 1.5) {
            lz += 0.01;
        }
        if (zCam >= 1.5 && lx < 1.5) {
            lx += 0.01;
        }
        if (zCam <= 1.5 && lx > -1.5) {
            lx -= 0.01;
        }
    }

    if (x < 250) {
        if (xCam >= 1.5 && lz < 1) {
            lz += 0.01;
        }
        if (xCam < 1.5 && lz > -1) {
            lz -= 0.01;
        }
        if (zCam >= 1.5 && lx > -1) {
            lx -= 0.01;
        }
        if (zCam <= 1.5 && lx < 1) {
            lx += 0.01;
        }
    }

    if (y > 250 && ly > -0.7) {
        ly -= 0.01;
    }

    if (y < 250 && ly < 0.7) {
        ly += 0.01;
    }

    glutWarpPointer(250, 250);
    glutPostRedisplay();
}

void createChest() {
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
}

void createJetpack() {
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
}

void createHexagone() {
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

void createRightArm() {

    //Right Shoulder
    glPushMatrix();
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
        glPushMatrix();
            glTranslatef(0.375, 0, 0);
            glScalef(0.75, 0.5, 0.5);
            createCube();
        glPopMatrix();

    // Right Elbow
        glTranslatef(0.125, 0, 0);
        glPushMatrix();
            glTranslatef(0.75, 0, 0);
            glutSolidSphere(radius, 255, 255);
        glPopMatrix();

        glTranslatef(0.75, 0, 0);
        glRotatef(normalArms[1], 0, -1, 0);
        glTranslatef(-0.75, 0, 0);

    //Right Forearm
        glPushMatrix();
            glTranslatef(1.25, 0, 0);
            glScalef(0.75, 0.5, 0.5);
            createCube();
        glPopMatrix();

    //Right Sword
        glPushMatrix();
            glTranslatef(1.625, -0.05, 0);
            glPushMatrix();
                glBegin(GL_QUADS);
                    glVertex3f(0, 0, -0.15);
                    glVertex3f(1.5, 0, -0.15);
                    glVertex3f(1.5, 0.1, 0);
                    glVertex3f(0, 0.1, 0);

                    glVertex3f(0, 0, -0.15);
                    glVertex3f(1.5, 0, -0.15);
                    glVertex3f(1.5, -0.1, 0);
                    glVertex3f(0, -0.1, 0);

                    glVertex3f(0, 0, 0.15);
                    glVertex3f(1.5, 0, 0.15);
                    glVertex3f(1.5, 0.1, 0);
                    glVertex3f(0, 0.1, 0);

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
                    glVertex3f(0, 0, 0.15);
                    glVertex3f(0.5, 0, 0);
                    glVertex3f(0, 0.1, 0);

                    glVertex3f(0, 0, 0.15);
                    glVertex3f(0.5, 0, 0);
                    glVertex3f(0, -0.1, 0);

                    glVertex3f(0, 0, -0.15);
                    glVertex3f(0.5, 0, 0);
                    glVertex3f(0, 0.1, 0);

                    glVertex3f(0, 0, -0.15);
                    glVertex3f(0.5, 0, 0);
                    glVertex3f(0, -0.1, 0);
                glEnd();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void createLeftArm() {

    //Left Shoulder
    glPushMatrix();
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
    glPushMatrix();
        glTranslatef(-0.75, 0.25, 0);
        glRotatef(dabLeftArm, 0, -1, 0);
        glRotatef(normalArms[0], 0, 0, -1);
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
            glTranslatef(0.75, 0, 0);
            glutSolidSphere(radius, 255, 255);
        glPopMatrix();

    //Left Forearm
        glPushMatrix();
            glTranslatef(0.875, 0, 0);
            glRotatef(dabLeftArm, 0, 2.5, 1);
            glPushMatrix();
                glTranslatef(0.375, 0, 0);
                glScalef(0.75, 0.5, 0.5);
                createCube();
            glPopMatrix();

    //Left Sword
            glPushMatrix();
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

void dab() {
    dabLeftArm += 1.8;
    dabRightArm += 0.4;

    normalArms[0] -= 1.8;
    normalArms[1] -= 0.4;
}

void getNormalArms() {
    dabLeftArm -= 1.8;
    dabRightArm -= 0.4;

    normalArms[0] += 1.8;
    normalArms[1] += 0.6;
}

void walk(){

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

void createPelvis(){
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
            glScalef(1.09,1.0,0.6);
            glTranslatef(-0.5, 0.07, -0.7);
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

void createLegs(){
    /**************right leg**************/
    glPushMatrix();
        glTranslatef(0.1, -0.1, 0);

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
                        normal = vectorProduct(0.0f, 0.70f, -0.4f, 0.6f, 0.70f, -0.4f, 0.0f, 0.4f, 0.2f);
                        glNormal3f(normal[0], normal[1], normal[2]);
                        glVertex3f(0.0f, 0.70f, -0.4f);
                        glVertex3f(0.6f, 0.70f, -0.4f);
                        glVertex3f(0.6f, 0.4f, 0.2f);
                        glVertex3f(0.0f, 0.4f, 0.2f);
                        glEnd();
                glPopMatrix();

            glPopMatrix();

            //Wheel up
            glPushMatrix();
                glTranslated(0.6,-2.4,0);
                glRotated(90,0,1,0);
                setmaterial(4);
                GLUquadricObj *quadratic;
                quadratic = gluNewQuadric();
                gluCylinder(quadratic, 0.3f, 0.3f, 0.3, 80, 80);

                //Draw Circle
                setmaterial(5);
                glBegin(GL_POLYGON);
                    for(double i = 0; i < 2 * M_PI; i += M_PI / 6) //<-- Change this Value
                        glVertex3f(cos(i) * 0.31, sin(i) * 0.31, 0.3);
                glEnd();
            glPopMatrix();

            //Wheel bottom
            glPushMatrix();
                glTranslated(0.6,-3.1,0);
                glRotated(90,0,1,0);
                setmaterial(4);
                GLUquadricObj *quadratic2;
                quadratic2 = gluNewQuadric();
                gluCylinder(quadratic2, 0.3f, 0.3f, 0.3, 80, 80);

                //Draw Circle
                setmaterial(5);
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
                        normal = vectorProduct(0.0f, 0.70f, -0.4f, 0.6f, 0.70f, -0.4f, 0.0f, 0.4f, 0.2f);
                        glNormal3f(normal[0], normal[1], normal[2]);
                        glVertex3f(0.0f, 0.70f, -0.4f);
                        glVertex3f(0.6f, 0.70f, -0.4f);
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
                    setmaterial(4);
                    GLUquadricObj *quadratic3;
                    quadratic3 = gluNewQuadric();
                    gluCylinder(quadratic3, 0.3f, 0.3f, 0.3, 80, 80);

                    //Draw Circle
                    setmaterial(5);
                    glBegin(GL_POLYGON);
                        for(double i = 0; i < 2 * M_PI; i += M_PI / 6) //<-- Change this Value
                            glVertex3f(cos(i) * 0.31, sin(i) * 0.31, 0.3);
                    glEnd();
                glPopMatrix();

                //Wheel bottom
                glPushMatrix();
                    glTranslated(0.6,-3.1,0);
                    glRotated(90,0,1,0);
                    setmaterial(4);
                    GLUquadricObj *quadratic4;
                    quadratic4 = gluNewQuadric();
                    gluCylinder(quadratic4, 0.3f, 0.3f, 0.3, 80, 80);

                    //Draw Circle
                    setmaterial(5);
                    glBegin(GL_POLYGON);
                        for(double i = 0; i < 2 * M_PI; i += M_PI / 6) //<-- Change this Value
                            glVertex3f(cos(i) * 0.31, sin(i) * 0.31, 0.3);
                    glEnd();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

}

