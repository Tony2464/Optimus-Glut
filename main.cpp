
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
float coord[9];
float* normal = (float*) malloc(sizeof(float) * 3);

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
void keyboard(unsigned char key, int x, int y); // fonction clavier
void SpecialInput(int key, int x, int y);
float* vectorProduct(float tab[9]);


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
		      0.0, 0.0, 0.0,      // point de mire
			  0.0, 1.0, 0.0);     // vecteur d'orientation cam�ra
    //glTranslatef(a,b,c);
    //glRotatef(5,1,0,0);
    //glRotatef(5,0,1,0);
    //glRotatef(5,0,0,1);


	/* A vous de jouer */




    glPushMatrix();

        glBegin(GL_QUADS);

            coord[0] = -0.5;
            coord[1] = -0.5;
            coord[2] = 0.5;
            coord[3] = 0.5;
            coord[4] = -0.5;
            coord[5] = 0.5;
            coord[6] = -0.5;
            coord[7] = 0.5;
            coord[8] = 0.5;
            normal = vectorProduct(coord);
            printf("%.1f\n", normal[0]);
            printf("%.1f\n", normal[1]);
            printf("%.1f\n", normal[2]);
            glNormal3f(normal[0], normal[1], normal[2]);
            //Front
            glColor3f(1, 0, 0);
            glVertex3f(-0.5f, -0.5f, 0.5f);
            glVertex3f(0.5f, -0.5f, 0.5f);
            glVertex3f(0.5f, 0.5f, 0.5f);
            glVertex3f(-0.5f, 0.5f, 0.5f);

            glNormal3f(1, 0, 0);
            //Right
            glColor3f(0, 1, 0);
            glVertex3f(0.5f, 0.5f, 0.5f);
            glVertex3f(0.5f, -0.5f, 0.5f);
            glVertex3f(0.5f, -0.5f, -0.5f);
            glVertex3f(0.5f, 0.5f, -0.5f);

            glNormal3f(0, 0, -1);
            //Back
            glColor3f(0, 0, 1);
            glVertex3f(-0.5f, 0.5f, -0.5f);
            glVertex3f(-0.5f, -0.5f, -0.5f);
            glVertex3f(0.5f, -0.5f, -0.5f);
            glVertex3f(0.5f, 0.5f, -0.5f);

            glNormal3f(-1, 0, 0);
            //Left
            glColor3f(1, 0, 1);
            glVertex3f(-0.5f, 0.5f, 0.5f);
            glVertex3f(-0.5f, -0.5f, 0.5f);
            glVertex3f(-0.5f, -0.5f, -0.5f);
            glVertex3f(-0.5f, 0.5f, -0.5f);

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

			case 'q':   /* Quitter le programme */
				exit(0);
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

float* vectorProduct(float tab[9]) {
    float vector1[3];
    float vector2[3];
    float* normalVector = (float*) malloc(sizeof(float) * 3);

    vector1[0] = tab[3] - tab[0];
    vector1[1] = tab[4] - tab[1];
    vector1[2] = tab[5] - tab[2];

    vector2[0] = tab[6] - tab[0];
    vector2[1] = tab[7] - tab[1];
    vector2[2] = tab[8] - tab[2];

    *normalVector = vector1[1] * vector2[2] - vector1[2] * vector2[1];
    *(normalVector + 1) = vector1[2] * vector2[0] - vector1[0] * vector2[2];
    *(normalVector + 2) = vector1[0] * vector2[1] - vector1[1] * vector2[0];

    return normalVector;
}
