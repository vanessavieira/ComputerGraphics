#include "main.h"

#include <fstream>
#include <SFML/Graphics.hpp>

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=-5.0f,z=6.0f, y=1.0f;


GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {0.0, 1.0, 1.0, 1.0};

float angle = 0.0f;

float glass_alpha = 0.5f;

float right_door_angle = 0.0f;
float left_door_angle = 0.0f;

GLuint texture_id[20];

void drawCube(GLdouble size, int *tex) {
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  for (i = 5; i >= 0; i--) {
    if(tex[i] >= 0) {
      glBindTexture(GL_TEXTURE_2D, texture_id[tex[i]]);
    }
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    if(i==1)
      glTexCoord2f(1.0f, 0.0f);
    else
      glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(&v[faces[i][0]][0]);
    if(i==1)
      glTexCoord2f(0.0f, 0.0f);
    else
      glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(&v[faces[i][1]][0]);
    if(i==1)
      glTexCoord2f(0.0f, 1.0f);
    else
      glTexCoord2f(1.0f, 1.0f);
    glVertex3fv(&v[faces[i][2]][0]);
    if(i==1)
      glTexCoord2f(1.0f, 1.0f);
    else
      glTexCoord2f(0.0f, 1.0f);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
    if(tex[i] >= 0) {
      glBindTexture(GL_TEXTURE_2D, 0);
    }
  }
}

void drawOfficeDesk(float x, float y, float z) {
    glColor3f(0.1f, 0.1f, 0.1f);
	
	int office_desk_texture[] = {9, 9, 9, 9, 9, 9};
    
    //base esquerda
    glPushMatrix();
    glTranslatef(x, 0.125f+y, z);
    glScalef(0.2, 0.1, 0.7);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();

	//lateral esquerda
	glPushMatrix();
    glTranslatef(x, 0.4f+y, z);
    glScalef(0.1, 0.5f, 0.4);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();
     
    //base direita
    glPushMatrix();
    glTranslatef(x+1, 0.125f+y, z);
    glScalef(0.2, 0.1, 0.7);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();    
    
    //lateral direita
	glPushMatrix();
    glTranslatef(x+1, 0.4f+y, z);
    glScalef(0.1, 0.5f, 0.4);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();
    
    //parte superior da mesa 
    glPushMatrix();
    glTranslatef(x+0.5, 0.7f+y, z);
    glScalef(1.5, 0.1, 1.0);
    drawCube(1.0f, office_desk_texture);
    glPopMatrix();
}

void drawProjector() {
	int projector_texture[] = {-1, -1, -1, 4, -1, -1};
	
//Projector 1
	glColor3f(1.0f, 1.0f, 1.0f);
	//suporte projetor
    glPushMatrix();
    glTranslatef(4.0f, 5.075f, -29.0);
    glScalef(0.05, 1.1, 0.05);
    glutSolidCube(1.0f);
    glPopMatrix();
    
	//projetor
    glPushMatrix();
    glTranslatef(4.0f, 4.4625f, -29.0f);
    glScalef(0.5, 0.125, 0.5);
    drawCube(1.0f, projector_texture);
    glPopMatrix();
    
//Projector 2
    glColor3f(1.0f, 1.0f, 1.0f);
    //suporte projetor
    glPushMatrix();
    glTranslatef(-4.0f, 5.075f, -29.0);
    glScalef(0.05, 1.1, 0.05);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    //projetor
    glPushMatrix();
    glTranslatef(-4.0f, 4.4625f, -29.0f);
    glScalef(0.5, 0.125, 0.5);
    drawCube(1.0f, projector_texture);
    glPopMatrix();
}

void drawPainting() {
    //bordas quadro
    int pulpit_texture[] = {-1, -1, -1, -1, 15, -1};
    glPushMatrix();
    //glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(-0.4f, 3.5f, -31.0f);
    glScalef(2.5, 3.0, 0.1);
    drawCube(1.0f, pulpit_texture);
   // glutSolidCube(1.0f);
    glPopMatrix();
}


void drawPulpit() {

    int pulpit_texture[] = {2, 2, 2, 2, 2, 2};
    
    //Base
    glColor3f(0.745,0.423,0.188);
    glPushMatrix();
    glTranslatef(-0.4f, 1.95f, -29.0);
    glScalef(1.0, 1.5, 0.8);
    drawCube(1.0f, pulpit_texture);
    glPopMatrix();
    
    //Tampa
    glColor3f(0.745,0.423,0.188);
    glPushMatrix();
    glTranslatef(-0.4f, 2.8f, -29.0);
    glScalef(1.5, 0.2, 0.8);
    drawCube(1.0f, pulpit_texture);
    glPopMatrix();

}

void drawAirConditioning(float x, float z, char side) {
	//area de proje��o
	int air_texture[] = {3, -1, -1, -1, -1, -1};
	
	if(side == 'r') {
		air_texture[0] = 3;
	} else if(side == 'l') {
		air_texture[2] = 3;
	}
	
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(x, 3.25f, z);
    glScalef(0.25, 0.5, 1.5);
    drawCube(1.0f, air_texture);
    glPopMatrix();
}

void drawProjectionQuad() {
	int projection_texture[] = {5, -1, -1, -1, -1, -1, -1};
	
//Projector 1

    //bordas quadro
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(4.1f, 4.1f, -31.0f);
    glScalef(2.5, 2.0, 0.1);
    glutSolidCube(1.0f);
    glPopMatrix();

	//area de proje��o
	glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(4.1f, 4.0f, -30.5f);
    glScalef(2.0, 1.5, 0.1);
    drawCube(1.0f, projection_texture);
    glPopMatrix();

//Projector 2

    //bordas quadro
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(-4.1f, 4.1f, -31.0f);
    glScalef(2.5, 2.0, 0.1);
    glutSolidCube(1.0f);
    glPopMatrix();

    //area de proje��o
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-4.1f, 4.0f, -30.5f);
    glScalef(2.0, 1.5, 0.1);
    drawCube(1.0f, projection_texture);
    glPopMatrix();
}


void drawChair(float x, float z) {
    glColor3f(0.4f, 0.3f, 0.25f);
    
    int chair_texture[] = {2, 2, 2, 2, 2, 2};
    
    //base esquerda
    glPushMatrix();
    glTranslatef(x, 0.125f, z);
    glScalef(0.25, 0.25, 1.0);
    drawCube(1.0f, chair_texture);
    glPopMatrix();

	//lateral esquerda
	glPushMatrix();
    glTranslatef(x, 0.5f, z);
    glScalef(0.125, 0.5f, 0.8);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //suporte esquerdo do apoio traseiro
    glPushMatrix();
    glTranslatef(x, 0.875f, z+0.45);
    glScalef(0.1, 1.25f, 0.1);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //base direita
    glPushMatrix();
    glTranslatef(x+2, 0.125f, z);
    glScalef(0.25, 0.25, 1.0);
    drawCube(1.0f, chair_texture);
    glPopMatrix();    
    
    //lateral direita
	glPushMatrix();
    glTranslatef(x+2, 0.5f, z);
    glScalef(0.125, 0.5f, 0.8);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //assento 
    glPushMatrix();
    glTranslatef(x+1, 0.6f, z);
    glScalef(2.0, 0.1, 1.0);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //suporte direito do apoio traseiro
    glPushMatrix();
    glTranslatef(x+2, 0.875f, z+0.45);
    glScalef(0.1, 1.25f, 0.1);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
    
    //suporte das costas
    glPushMatrix();
    glTranslatef(x+1.0f, 1.125f, z+0.45);
    glScalef(2.25f, 0.75f, 0.1);
    drawCube(1.0f, chair_texture);
    glPopMatrix();
}

void drawTemple() {

int chair_texture[] = {2, 2, 2, 2, 2, 2};

//Pir�mide esquerda
float a = 0.4f;
float y = 8.05f;
float z = -2.1f;
float x = -3.38f;
glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.745,0.423,0.188); glVertex3f( 0.0f+x, a+y+0.4, 0.0f+z);   //V0(red)
    glColor3f(0.745,0.423,0.188); glVertex3f(-a+x,-a+y, a+z);   //V1(green)
    glColor3f(0.745,0.423,0.188); glVertex3f( a+x,-a+y, a+z);   //V2(blue)
    glColor3f(0.745,0.423,0.188); glVertex3f( a+x,-a+y,-a+z);   //V3(green)
    glColor3f(0.745,0.423,0.188); glVertex3f(-a+x,-a+y,-a+z);   //V4(blue)
    glColor3f(0.745,0.423,0.188); glVertex3f(-a+x,-a+y, a+z);   //V1(green)
glEnd();

//Pir�mide direita
a = 0.4f;
y = 8.05f;
z = -2.1f;
x = 2.35f;
glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.745,0.423,0.188); glVertex3f( 0.0f+x, a+y+0.4, 0.0f+z);   //V0(red)
    glColor3f(0.745,0.423,0.188); glVertex3f(-a+x,-a+y, a+z);   //V1(green)
    glColor3f(0.745,0.423,0.188); glVertex3f( a+x,-a+y, a+z);   //V2(blue)
    glColor3f(0.745,0.423,0.188); glVertex3f( a+x,-a+y,-a+z);   //V3(green)
    glColor3f(0.745,0.423,0.188); glVertex3f(-a+x,-a+y,-a+z);   //V4(blue)
    glColor3f(0.745,0.423,0.188); glVertex3f(-a+x,-a+y, a+z);   //V1(green)
glEnd();

//Desenha Cruz
    
//Desenha linha horizontal
    glPushMatrix();
    glTranslatef(-0.5f, 10.2f, -2.0f); 
    glScalef(1.5, 0.3, 0.3);  
    //glColor3f(0.745,0.423,0.188);
    drawCube(0.5f, chair_texture);
    glPopMatrix();
    
//Desenha linha vertical
    glPushMatrix();
    glTranslatef(-0.5f, 10.0f, -2.0f); 
    glScalef(0.3, 3.0, 0.3);  
    //glColor3f(0.745,0.423,0.188);
    drawCube(0.5f, chair_texture);
    glPopMatrix();

//Desenha parede frontal da direita da entrada
    glPushMatrix();
    glTranslatef(5.0f, 3.0f, -9.25f); 
    glScalef(10.0, 12.0, 1.0);  
    glColor3f(0.917,0.8431,0.7372);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 1� linha horizontal da parede frontal da direita da entrada
    glPushMatrix();
    glTranslatef(5.0f, 5.9f, -8.9f); 
    glScalef(10.0, 0.5, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 2� linha horizontal da parede frontal da direita da entrada
    glPushMatrix();
    glTranslatef(5.0f, 4.9f, -8.9f); 
    glScalef(10.0, 0.5, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 1� linha vertical da parede frontal da direita da entrada
    glPushMatrix();
    glTranslatef(2.9f, 3.0f, -8.9f); 
    glScalef(0.8, 12.0, 0.8);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 2� linha vertical da parede frontal da direita da entrada
    glPushMatrix();
    glTranslatef(7.3f, 3.0f, -8.9f);
    glScalef(0.8, 12.0, 0.8);  
    glRotatef(-90.0f, 0,0 , 1);
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha parede lateral direita da entrada    
    glPushMatrix();
    glTranslatef(2.5f, 3.75f, -5.5f);
    glScalef(0.5, 7.5, 7.0);  
    glColor3f(0.917,0.8431,0.7372);
    glutSolidCube(1.0);
    glPopMatrix();

//Desenha parede frontal da esquerda da entrada
    glPushMatrix();
    glTranslatef(-5.5f, 3.0f, -9.25f); 
    glScalef(8.0, 12.0, 1.0);  
    glColor3f(0.917,0.8431,0.7372);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 1� linha horizontal da parede frontal da esquerda da entrada
    glPushMatrix();
    glTranslatef(-5.5f, 5.9f, -8.9f); 
    glScalef(8.0, 0.5, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 2� linha horizontal da parede frontal da esquerda da entrada
    glPushMatrix();
    glTranslatef(-5.5f, 4.9f, -8.9f); 
    glScalef(8.0, 0.5, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 1� linha vertical da parede frontal da esquerda da entrada
    glPushMatrix();
    glTranslatef(-7.3f, 3.0f, -8.9f);
    glScalef(0.8, 12.0, 0.8);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 2� linha vertical da parede frontal da esquerda da entrada
    glPushMatrix();
    glTranslatef(-3.9f, 3.0f, -8.9f); 
    glScalef(0.8, 12.0, 0.8);  
    glRotatef(-90.0f, 0,0 , 1);
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha parede lateral esquerda da entrada  
    glPushMatrix();
    glTranslatef(-3.5f, 3.75f, -5.5f);
    glScalef(0.5, 7.5, 7.0);  
    glColor3f(0.917,0.8431,0.7372);
    glutSolidCube(1.0);
    glPopMatrix();
    
//Desenha parede da porta de entrada da igreja 1/4
    glPushMatrix();
    glTranslatef(-0.5f, 4.78f, -2.25f); 
    glScalef(12.9, 11.0, 1.0);  
    glColor3f(0.917,0.8431,0.7372);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha parede da porta de entrada da igreja 2/4
    glPushMatrix();
    glTranslatef(-3.0f, 0.9f, -2.25f); 
    glScalef(2.2, 4.55, 1.0);  
    glColor3f(0.917,0.8431,0.7372);
    //glColor3f(0.0,0.0,0.0);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha parede da porta de entrada da igreja 3/4
    glPushMatrix();
    glTranslatef(-0.5f,0.9f, -2.25f); 
    glScalef(1.8, 4.55, 1.0);  
    glColor3f(0.917,0.8431,0.7372);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha parede da porta de entrada da igreja 4/4
    glPushMatrix();
    glTranslatef(1.9f,0.9f, -2.25f); 
    glScalef(1.8,4.55, 1.0);  
    glColor3f(0.917,0.8431,0.7372);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha ponta da igreja
    glBegin(GL_TRIANGLES);  
    glColor3f(0.917,0.8431,0.7372);
    glVertex3f(-3.3f,7.5f,-1.7f);
    glVertex3f(2.3f,7.5f,-1.7f);
    glVertex3f(-0.5f,9.1f,-1.7f);
    glEnd();
    
//Desenha 1� linha horizontal da entrada da igreja
    glPushMatrix();
    glTranslatef(-0.5f, 7.1, -1.9); 
    glScalef(13.0, 0.3, 0.8);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 2� linha horizontal da entrada da igreja
    glPushMatrix();
    glTranslatef(-0.5f, 3.85f, -1.9); 
    glScalef(11.2, 0.3, 0.8);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 1� linha rotacionada da igreja (DIREITA)
    glPushMatrix();
    glTranslatef(0.91f, 2.8f, -1.9f);
    glRotatef(75.0f, 0, 0, 1); 
    glScalef(0.5, 5.9, 0.8);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 1� linha rotacionada da igreja (ESQUERDA)
    glPushMatrix();
    glTranslatef(-1.9f, 2.8f, -1.9f);
    glRotatef(-75.0, 0, 0, 1);
    glScalef(0.5, 5.9, 0.8);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 2� linha rotacionada da igreja (DIREITA)
    glPushMatrix();
    glTranslatef(0.91f, 3.3f, -1.9f);
    glRotatef(75.0f, 0, 0, 1); 
    glScalef(0.5, 5.9, 0.8);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 2� linha rotacionada da igreja (ESQUERDA)
    glPushMatrix();
    glTranslatef(-1.9f, 3.3f, -1.9f);
    glRotatef(-75.0, 0, 0, 1);
    glScalef(0.5, 5.9, 0.8);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 1� linha vertical da entrada da igreja
    glPushMatrix();
    glTranslatef(-3.52f, 3.75f, -1.9); 
    glScalef(1.0, 15.5, 0.8);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 2� linha vertical da entrada da igreja
    glPushMatrix();
    glTranslatef(2.52f, 3.75f, -1.9);
    glScalef(1.0, 15.5, 0.8);  
    glRotatef(-90.0f, 0,0 , 1);
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
	
//Parede lateral esquerda
	glPushMatrix();
    glColor3f(0.917,0.8431,0.7372);
    glTranslatef(7.25f, 2.75f, -20.5f);
    glScalef(0.5, 5.5, 23.0);
    glutSolidCube(1.0f);
    glPopMatrix();
    
//Parede lateral direita
	glPushMatrix();
    glColor3f(0.917,0.8431,0.7372);
    glTranslatef(-7.25f, 2.75f, -20.5f);
    glScalef(0.5, 5.5, 23.0);
    glutSolidCube(1.0f);
    glPopMatrix();

//parede do fundo do templo 
    glPushMatrix();
    glColor3f(0.9,0.9,0.9);
    glTranslatef(0.0f, 2.75f, -31.75f);
    glScalef(14.5, 5.5, 0.5); 
    glutSolidCube(1.0);
    glPopMatrix();

//teto do templo
    glPushMatrix();
    glColor3f(0.66f,0.66f,0.66f);
    glTranslatef(0.0f, 5.75f, -20.75f);
    glScalef(15.0, 0.5, 22.5);
    glutSolidCube(1.0);
    glPopMatrix();

//teto interno entrada do templo (DIREITA)
    glPushMatrix();
    glColor3f(0.745,0.423,0.188);
    glTranslatef(1.0f, 8.5f, -5.5f);
    glRotatef(60.15f, 0, 0, 1);
    glScalef(0.5, 3.8, 7.0);
    glutSolidCube(1.0);
    glPopMatrix();

//teto interno entrada do templo (ESQUERDA)
    glPushMatrix();
    glColor3f(0.745,0.423,0.188);
    glTranslatef(-2.0f, 8.5f, -5.5f);
    glRotatef(-60.0f, 0, 0, 1);
    glScalef(0.5, 3.8, 7.0);
    glutSolidCube(1.0);
    glPopMatrix();
    
//Desenha 1� linha do teto da igreja (DIREITA)
    glPushMatrix();
    glTranslatef(1.0f, 8.45f, -1.9f);
    glRotatef(59.15f, 0, 0, 1); 
    glScalef(0.8, 7.5, 0.8);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha 2� linha do teto da igreja (ESQUERDA)
    glPushMatrix();
    glTranslatef(-2.0f, 8.45f, -1.9f);
    glRotatef(-60.0f, 0, 0, 1);
    glScalef(0.8, 7.6, 0.8);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();

	int pulpito_texture[] = {9, 9, 9, 9, 9, 9};
    
//escadas frontais
    glPushMatrix();
    glColor3f(0.917,0.8431,0.7372);
    glTranslatef(0.0f, 1.0f, -30.0f);
    glScalef(14.9, 0.4, 3.5);
    drawCube(1.0, pulpito_texture);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.917,0.8431,0.7372);
    glTranslatef(0.0f, 0.60f, -29.5f);
    glScalef(14.9, 0.4, 4.5);
    drawCube(1.0, pulpito_texture);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.917,0.8431,0.7372);
    glTranslatef(0.0f, 0.20f, -29.0f);
    glScalef(14.9, 0.4, 5.5);
    drawCube(1.0, pulpito_texture);
    glPopMatrix();
}

void drawDoor() {
    
    int chair_texture[] = {2, 2, 2, 2, 2, 2};

    //Porta do lado esquerdo
    glPushMatrix();
    //glColor3f(0.11f,0.09f,0.043f);
    glTranslatef(-5.6f, 1.9f, -9.0f);
    glScalef(1.8, 3.8, 0.3f);
    drawCube(1.0f, chair_texture);
    glPopMatrix();            
    
    //Desenha janelinha 1
    glPushMatrix();
    glTranslatef(-6.0f, 3.2f, -8.9f);
    glScalef(0.9, 1.0, 0.3);  
    glColor4f(0.6f, 0.8f, 0.4f,0.5f);
    glutSolidCube(0.5);
    glPopMatrix();       
    
    //Desenha janelinha 2
    glPushMatrix();
    glTranslatef(-5.2f, 3.2f, -8.9f);
    glScalef(0.9, 1.0, 0.3);  
    glColor4f(0.6f, 0.8f, 0.4f,0.5f);
    glutSolidCube(0.5);
    glPopMatrix(); 
    
//Desenha borda esquerda da porta (ESQUERDA)
    glPushMatrix();
    glTranslatef(-6.5f, 1.9f, -8.8f);
    glScalef(0.3, 7.55, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();  
    
//Desenha borda direita da porta (ESQUERDA)
    glPushMatrix();
    glTranslatef(-4.7f, 1.9f, -8.8f);
    glScalef(0.3, 7.55, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix(); 
    
//Desenha primeira borda superior da porta (ESQUERDA)
    glPushMatrix();
    glTranslatef(-5.6f, 3.72f, -8.8f);
    glScalef(3.55, 0.3, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha segunda borda superior da porta (ESQUERDA)
    glPushMatrix();
    glTranslatef(-5.6f, 2.72f, -8.8f);
    glScalef(3.55, 0.3, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();

    //Porta do lado direito
    glPushMatrix();
    //glColor3f(0.11f,0.09f,0.043f);
    glTranslatef(5.1f, 1.9f, -9.0f);
    glScalef(2.2, 3.8, 0.3f);
    drawCube(1.0f, chair_texture);
    glPopMatrix();           
    
    //Desenha janelinha 1
    glPushMatrix();
    glTranslatef(4.5f, 3.2f, -8.8f);
    glScalef(0.7, 1.0, 0.3);  
    glColor4f(0.6f, 0.8f, 0.4f,0.5f);
    glutSolidCube(0.5);
    glPopMatrix();             
    
    //Desenha janelinha 2
    glPushMatrix();
    glTranslatef(5.1f, 3.2f, -8.8f);
    glScalef(0.7, 1.0, 0.3);  
    glColor4f(0.6f, 0.8f, 0.4f,0.5f);
    glutSolidCube(0.5);
    glPopMatrix();       
    
    //Desenha janelinha 3
    glPushMatrix();
    glTranslatef(5.7f, 3.2f, -8.8f);
    glScalef(0.7, 1.0, 0.3);  
    glColor4f(0.6f, 0.8f, 0.4f,0.5f);
    glutSolidCube(0.5);
    glPopMatrix();   
    
//Desenha borda esquerda da porta (DIREITA)
    glPushMatrix();
    glTranslatef(3.95f, 1.9f, -8.8f);
    glScalef(0.3, 7.55, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();  
    
//Desenha borda direita da porta (DIREITA)
    glPushMatrix();
    glTranslatef(6.2f, 1.9f, -8.8f);
    glScalef(0.3, 7.55, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix(); 
    
//Desenha primeira borda superior da porta (DIREITA)
    glPushMatrix();
    glTranslatef(5.0f, 3.72f, -8.8f);
    glScalef(4.5, 0.3, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha segunda borda superior da porta (DIREITA)
    glPushMatrix();
    glTranslatef(5.0f, 2.72f, -8.8f);
    glScalef(4.5, 0.3, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
    //porta direita principal
    glPushMatrix();
    //glColor3f(0.11f,0.09f,0.043f);
    glTranslatef(1.7f, 0.945f, -1.8f);
    glRotatef(right_door_angle, 0, 1, 0);
    glTranslatef(-1.0f, -0.01f, -0.2f);
    glScalef(1.5, 1.86, 0.3f);
    drawCube(1.0f, chair_texture);
    glPopMatrix();  
    
//Desenha borda superior da porta (DIREITA)
    glPushMatrix();
    glTranslatef(0.7f, 1.95f, -1.9f);
    glScalef(3.3, 0.3, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();     

    //porta esquerda principal
    glPushMatrix();
    //glColor3f(0.11f,0.09f,0.043f);
    glTranslatef(-0.95f, 0.93f, -2.1f);
    glRotatef(left_door_angle, 0, 1, 0);
    glTranslatef(-0.85f, 0.0f, -0.1f);
    glScalef(1.45, 1.9, 0.3f);
    drawCube(1.0f, chair_texture);
    glPopMatrix();     
    
//Desenha borda superior da porta (ESQUERDA)
    glPushMatrix();
    glTranslatef(-1.7f, 1.95f, -1.9f);
    glScalef(3.0, 0.3, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();     
    
//Desenha borda da porta 1 (ESQUERDA)
    glPushMatrix();
    glTranslatef(-2.52f, 0.9f, -1.9f);
    glScalef(0.3, 4.5, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha borda da porta 1 (DIREITA)
    glPushMatrix();
    glTranslatef(-1.0f, 0.9f, -1.9f);
    glScalef(0.3, 4.5, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha borda da porta 2 (ESQUERDA)
    glPushMatrix();
    glTranslatef(1.52f, 0.9f, -1.9f);
    glScalef(0.3, 4.5, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
//Desenha borda da porta 2 (DIREITA)
    glPushMatrix();
    glTranslatef(-0.1f, 0.9f, -1.9f);
    glScalef(0.3, 4.5, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();  
}

void drawWindows() {
    int chair_texture[] = {2, 2, 2, 2, 2, 2};

    //1� Janela principal
    glPushMatrix();
    //glColor3f(0.11f,0.09f,0.043f);
    glTranslatef(-2.2f, 5.1f, -2.0f);
    glScalef(1.2, 2.5, 0.3f);
    drawCube(1.0f, chair_texture);
    glPopMatrix();      
    
    //Desenha janelinha 1
    glPushMatrix();
    glTranslatef(-2.47f, 5.9f, -1.9f);
    glScalef(0.7, 0.6, 0.3);  
    glColor4f(0.6f, 0.8f, 0.4f,0.5f);
    glutSolidCube(0.5);
    glPopMatrix();       
    
    //Desenha janelinha 2
    glPushMatrix();
    glTranslatef(-1.95f, 5.9f, -1.9f);
    glScalef(0.7, 0.6, 0.3);  
    glColor4f(0.6f, 0.8f, 0.4f,0.5f);
    glutSolidCube(0.5);
    glPopMatrix();       

    //Desenha primeira borda superior da janela
    glPushMatrix();
    glTranslatef(-2.2f, 6.27f, -1.9f);
    glScalef(2.7, 0.3, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();       
    
    //Desenha segunda borda superior da janela
    glPushMatrix();
    glTranslatef(-2.2f, 5.57f, -1.9f);
    glScalef(2.7, 0.3, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();    
    
	//Desenha borda da janela 1 (ESQUERDA)
    glPushMatrix();
    glTranslatef(-2.85f, 5.1f, -1.9f);
    glScalef(0.3, 5.0, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();
    
	//Desenha borda da janela 1 (DIREITA)
    glPushMatrix();
    glTranslatef(-1.6f, 5.1f, -1.9f);
    glScalef(0.3, 5.0, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();

    //2� Janela principal
    glPushMatrix();
    //glColor3f(0.11f,0.09f,0.043f);
    glTranslatef(1.2f, 5.1, -2.0f);
    glScalef(1.2, 2.5, 0.3f);
    drawCube(1.0f, chair_texture);
    glPopMatrix();           
    
    //Desenha janelinha 1
    glPushMatrix();
    glTranslatef(-0.70f, 5.9f, -1.9f);
    glScalef(0.7, 0.6, 0.4);  
    glColor4f(0.6f, 0.8f, 0.4f,0.8f);
    glutSolidCube(0.5);
    glPopMatrix();       
    
    //Desenha janelinha 2
    glPushMatrix();
    glTranslatef(-0.15f, 5.9f, -1.9f);
    glScalef(0.7, 0.6, 0.4);  
    glColor4f(0.6f, 0.8f, 0.4f,0.8f);
    glutSolidCube(0.5);
    glPopMatrix(); 
    
    //Desenha primeira borda superior da janela
    glPushMatrix();
    glTranslatef(1.2f, 6.27f, -1.9f);
    glScalef(2.46, 0.3, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();       
    
    //Desenha segunda borda superior da janela
    glPushMatrix();
    glTranslatef(1.2f, 5.57f, -1.9f);
    glScalef(2.46, 0.3, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();  
    
	//Desenha borda da janela 2 (ESQUERDA)
    glPushMatrix();
    glTranslatef(-1.15f, 5.1f, -1.9f);
    glScalef(0.3, 5.0, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();  
    
	//Desenha borda da janela 2 (DIREITA)
    glPushMatrix();
    glTranslatef(0.15f, 5.1f, -1.9f);
    glScalef(0.3, 5.0, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();     

    //3� Janela principal
    glPushMatrix();
    //glColor3f(0.11f,0.09f,0.043f);
    glTranslatef(-0.5f, 5.1f, -2.0f);
    glScalef(1.2, 2.5, 0.3f);
    drawCube(1.0f, chair_texture);
    glPopMatrix();            
    
    //Desenha janelinha 1
    glPushMatrix();
    glTranslatef(1.57f, 5.9f, -1.8f);
    glScalef(0.7, 0.6, 0.3);  
    glColor4f(0.6f, 0.8f, 0.4f,0.5f);
    glutSolidCube(0.5);
    glPopMatrix();       
    
    //Desenha janelinha 2
    glPushMatrix();
    glTranslatef(1.05f, 5.9f, -1.8f);
    glScalef(0.7, 0.6, 0.3);  
    glColor4f(0.6f, 0.8f, 0.4f,0.5f);
    glutSolidCube(0.5);
    glPopMatrix();     
    
    //Desenha primeira borda superior da janela
    glPushMatrix();
    glTranslatef(-0.5f, 6.27f, -1.9f);
    glScalef(2.7, 0.3, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();       
    
    //Desenha segunda borda superior da janela
    glPushMatrix();
    glTranslatef(-0.5f, 5.57f, -1.9f);
    glScalef(2.7, 0.3, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();   
    
	//Desenha borda da janela 3 (ESQUERDA)
    glPushMatrix();
    glTranslatef(0.65f, 5.1f, -1.9f);
    glScalef(0.3, 5.0, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();  
    
	//Desenha borda da janela 3 (DIREITA)
    glPushMatrix();
    glTranslatef(1.9f, 5.1f, -1.9f);
    glScalef(0.3, 5.0, 0.6);  
    glColor3f(0.745,0.423,0.188);
    glutSolidCube(0.5);
    glPopMatrix();        
}

void drawFloor() {

  //piso-templo
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture_id[8]);	 
  glTranslatef(0.0f, 0.0f, -13.0f);
  glBegin(GL_QUADS);
  glColor3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0f, 1.0f); 
  glVertex3f(-7.5f, 0.0f, -19.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-7.5f, 0.0f, 7.5f);
  glTexCoord2f(1.0f, 0.0f); 
  glVertex3f( 7.5f, 0.0f, 7.5f);
  glTexCoord2f(1.0f, 1.0f); 
  glVertex3f( 7.5f, 0.0f, -19.0f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);	 
  glPopMatrix();
  
  //gramado lado esquerdo
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture_id[8]);
  glTranslatef(-5.0f, 0.0f, 6.25f);
  glBegin(GL_QUADS);
  glColor3f(0.0f, 0.3f, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-2.5f, 0.0f, -11.75f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-2.5f, 0.0f, 2.5f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f( 2.5f, 0.0f, 2.5f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f( 2.5f, 0.0f, -11.75f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
  
  //gramado lado direito
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture_id[8]);
  glTranslatef(3.25f, 0.0f, 4.5f);
  glBegin(GL_QUADS);
  glColor3f(0.0f, 0.3f, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-4.25f, 0.0f, -10.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-4.25f, 0.0f, 4.25f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f( 4.25f, 0.0f, 4.25f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f( 4.25f, 0.0f, -10.0f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
  
  //piso entrada
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture_id[8]);	 
  glTranslatef(-1.75f, 0.0f, 4.5f);
  glBegin(GL_QUADS);
  glColor3f(0.0f, 0.3f, 0.0f);
  glTexCoord2f(0.0f, 1.0f); 
  glVertex3f(-0.75f, 0.0f, -10.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-0.75f, 0.0f, 4.25f);
  glTexCoord2f(1.0f, 0.0f); 
  glVertex3f( 0.75f, 0.0f, 4.25f);
  glTexCoord2f(1.0f, 1.0f); 
  glVertex3f( 0.75f, 0.0f, -10.0f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);	 
  glPopMatrix();
}

void display()
{
  // Clear Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // To operate on model-view matrix
  glMatrixMode(GL_MODELVIEW);     
  // Reset transformations
  glLoadIdentity();
  // Set the camera
  gluLookAt(  x, y, z,
  x+lx, y, z+lz,
  0.0f, 1.0f, 0.0f);


  drawChair(3.0f, -16.0f);
  drawChair(3.0f, -18.0f);
  drawChair(3.0f, -20.0f);
  drawChair(3.0f, -22.0f);
  
  drawChair(-2.0f, -22.0f);
  drawChair(-2.0f, -20.0f);
  drawChair(-2.0f, -18.0f);
  drawChair(-2.0f, -16.0f);
  
  drawChair(-6.0f, -22.0f);
  drawChair(-6.0f, -20.0f);
  drawChair(-6.0f, -18.0f);
  drawChair(-6.0f, -16.0f);
  
  drawFloor();
  drawTemple();
  drawDoor();
  drawWindows();
  drawProjectionQuad();
  drawProjector();
  drawOfficeDesk(-5.5f, -0.1f, -10.0f);
  drawOfficeDesk(4.0f, -0.1f, -10.0f);
  drawAirConditioning(6.85, -22.0, 'r');
  drawAirConditioning(6.85, -18.0, 'r');
  drawAirConditioning(6.85, -14.0, 'r');  
  drawAirConditioning(-6.85, -28.0, 'l');
  drawAirConditioning(-6.85, -25.0, 'l');
  drawAirConditioning(-6.85, -22.0, 'l');
  drawPulpit();
  drawPainting();
  
  glFlush();
  glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y) {
    switch(key){
        case 'p':
        if(right_door_angle < 90.0f) right_door_angle=90.0f;
        glutPostRedisplay();
        break;
        
        case 'o':
        if(left_door_angle < 90.0f) left_door_angle=90.0f;
        glutPostRedisplay();
        break;

        case 'v':
        if(right_door_angle >= 90.0f) right_door_angle=0.0f;
        glutPostRedisplay();
        break;

        case 'c':
        if(left_door_angle >= 90.0f) left_door_angle=0.0f;
        glutPostRedisplay();
        break;
    }
}

void processSpecialKeys(int key, int xx, int yy)
{

float fraction = 0.5f;
float fraction_2 = 0.1f;

  switch (key)
  {
    case GLUT_KEY_LEFT :
    angle -= 0.05f;
    lx = sin(angle);
    lz = -cos(angle);
    break;
    case GLUT_KEY_RIGHT :
    angle += 0.05f;
    lx = sin(angle);
    lz = -cos(angle);
    break;
    case GLUT_KEY_UP :
    x += lx * fraction;
    z += lz * fraction;
    break;
    case GLUT_KEY_DOWN :
    x -= lx * fraction;
    z -= lz * fraction;
    break;
    case GLUT_KEY_PAGE_UP:
    y += y * fraction_2;
    break;
    case GLUT_KEY_PAGE_DOWN:
    y -= y * fraction_2;
    break;
  }
}

void loadTextureFromFile(char const *filename,int index) {
  int width, height, c;
  c = 3;
  std::ifstream file(filename);
  if(! file.good())
    throw "file not found";
  file.close();

sf::Image image;
image.loadFromFile(filename);

    printf("%d %d\n", width, height);

  glGenTextures(1, &texture_id[index]);
  glBindTexture(GL_TEXTURE_2D, texture_id[index]);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
  glBindTexture(GL_TEXTURE_2D, 0);
}

void initTextures(){
	loadTextureFromFile("texture/piso-escada.jpg", 0);
	loadTextureFromFile("texture/grass.jpg", 1);
	loadTextureFromFile("texture/tabaco.jpg", 2);
	loadTextureFromFile("texture/airc.jpg", 3);
	loadTextureFromFile("texture/projetor.jpg", 4);
	loadTextureFromFile("texture/slide_projetor.png", 5);
	loadTextureFromFile("texture/fachada-lt.png", 6);
	loadTextureFromFile("texture/piso-templo.jpg", 7);
	loadTextureFromFile("texture/piso-entrada.jpg", 8);
	loadTextureFromFile("texture/mesa.jpg", 9);
	loadTextureFromFile("texture/fachada-teto.png", 10);
	loadTextureFromFile("texture/inferior-cruz.png", 11);
	loadTextureFromFile("texture/superior-cruz.png", 12);
	loadTextureFromFile("texture/parede-pulpito.jpg", 13);
	loadTextureFromFile("texture/parede-lateral.jpg", 14);
    loadTextureFromFile("texture/jesus.jpg", 15);
	
}
	
void init() {
  glClearColor(0.7, 1.0, 1.0, 0.0);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  glEnable(GL_COLOR_MATERIAL);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
  glEnable(GL_TEXTURE_2D);
 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);

  initTextures();
}

void reshape(GLsizei width, GLsizei height)
{
  // Prevent a divide by zero, when window is too short
  // (you cant make a window of zero width).
  if (height == 0) {
      height = 1;
  }

  // Set the viewport to be the entire window
  glViewport(0, 0, width, height);

  float ratio = width * 1.0 / height;

  // Use the Projection Matrix
  glMatrixMode(GL_PROJECTION);

  // Reset Matrix
  glLoadIdentity();

  // Set the correct perspective.
  gluPerspective(45.0f, ratio, 0.1f, 100.0f);

  // Get Back to the Modelview
  glMatrixMode(GL_MODELVIEW);

}

int main(int argc,char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(10, 10);

  if(!glutCreateWindow("IGREJA FERNAO VELHO")) {
    fprintf(stderr,"Error opening a window.\n");
    exit(-1);
  }

  init();

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(display);
  glutSpecialFunc(processSpecialKeys);

  glutMainLoop();

  return 0;
}

