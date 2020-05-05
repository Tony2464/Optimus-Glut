#include "Map.h"
#include "Block.h"
#include "Robot.h"

#define GL_CLAMP_TO_EDGE 0x812F
#define SKY_DISTANCE 200.0f

Map::Map()
{
}

void Map::LoadTextures()
{
    // Skybox
    Skybox[0] = SOIL_load_OGL_texture("img/posx.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    Skybox[1] = SOIL_load_OGL_texture("img/negz.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    Skybox[2] = SOIL_load_OGL_texture("img/posy.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    Skybox[3] = SOIL_load_OGL_texture("img/posz.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    Skybox[4] = SOIL_load_OGL_texture("img/negx.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    Skybox[5] = SOIL_load_OGL_texture("img/negy.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

    // Textures utilisables
    ListeTextures[11] = SOIL_load_OGL_texture("img/negy2.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

void Map::DrawGround()
{
    Block *b = new Block(0.0f, 0.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, ListeTextures[11]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-8.0f, 0.0f, -200.0f);
    glTexCoord2f(0.0f, 200.0f);
    glVertex3f(-8.0f, 0.0f, 200.0f);
    glTexCoord2f(8.0f, 200.0f);
    glVertex3f(8.0f, 0.0f, 200.0f);
    glTexCoord2f(8.0f, 0.0f);
    glVertex3f(8.0f, 0.0f, -200.0f);
    glEnd();
    glTranslatef(0.0f, 1.0f, 0.0f);
    b->Draw();
}

void Map::DrawSkybox(Camera *cam)
{

    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    float LightPos[4]={0,1.5,0,0};
    glLightfv(GL_LIGHT0,GL_POSITION,LightPos);
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,40);	//d�finit la taille de la tache sp�culaire
    glEnable(GL_LIGHT0);

    //glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    // Face
    glBindTexture(GL_TEXTURE_2D, Skybox[1]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 0);
    glVertex3f(-SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 1);
    glVertex3f(-SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(0, 1);
    glVertex3f(SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glEnd();

    // Render the left quad
    glBindTexture(GL_TEXTURE_2D, Skybox[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 0);
    glVertex3f(SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 1);
    glVertex3f(SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(0, 1);
    glVertex3f(SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glEnd();

    // Render the back quad
    glBindTexture(GL_TEXTURE_2D, Skybox[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 0);
    glVertex3f(SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 1);
    glVertex3f(SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(0, 1);
    glVertex3f(-SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);

    glEnd();

    // Render the right quad
    glBindTexture(GL_TEXTURE_2D, Skybox[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 0);
    glVertex3f(-SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 1);
    glVertex3f(-SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(0, 1);
    glVertex3f(-SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glEnd();

    // Render the top quad
    glBindTexture(GL_TEXTURE_2D, Skybox[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(-SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(0, 0);
    glVertex3f(-SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 0);
    glVertex3f(SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 1);
    glVertex3f(SKY_DISTANCE + cam->posx, SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glEnd();

    // Render the bottom quad

    glBindTexture(GL_TEXTURE_2D, Skybox[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(-SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glTexCoord2f(0, 0);
    glVertex3f(-SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 0);
    glVertex3f(SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, -SKY_DISTANCE + cam->posz);
    glTexCoord2f(1, 1);
    glVertex3f(SKY_DISTANCE + cam->posx, -SKY_DISTANCE + cam->posy, SKY_DISTANCE + cam->posz);
    glEnd();
}


void Map::setLight(){
    //here you set the lights and parameters, example with one light
    float LightAmbient[] = { 0.75f, 0.75f, 0.75f, 1.0f };
    float LightEmission[] = { 1.0f, 1.0f, 0.8f, 1.0f };
    float LightDiffuse[] = { 1.0f, 1.0f, 0.8f, 1.0f };
    float LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float LightDirection[]={-0.5f, -0.5f, -0.5f};

    float lightPos1[] = {3, 3, 3, 1};
    float lightColor1[] = {1, 1, 1};

    float lightPos2[] = {2, 3, 3, 1};
    float lightColor2[] = {1, 1, 1};

    float lightPos3[] = {-2, 3, 3, 1};
    float lightColor3[] = {1, 1, 1};

    float lightPos4[] = {0, 2, 5, 1};
    float lightColor4[] = {1, 1, 1};

    float lightPos5[] = {0, 0, -5, 1};
    float lightColor5[] = {1, 1, 1};

    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
    glEnable(GL_LIGHT2);

    glLightfv(GL_LIGHT3, GL_DIFFUSE, lightColor3);
    glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);
    glEnable(GL_LIGHT3);

    glLightfv(GL_LIGHT4, GL_DIFFUSE, lightColor4);
    glLightfv(GL_LIGHT4, GL_POSITION, lightPos4);
    glEnable(GL_LIGHT4);

    glLightfv(GL_LIGHT5, GL_DIFFUSE, lightColor5);
    glLightfv(GL_LIGHT5, GL_POSITION, lightPos5);
    glEnable(GL_LIGHT5);

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, LightDirection);
    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
}