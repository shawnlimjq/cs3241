#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

/* Include header files depending on platform */
#ifdef _WIN32
	#include "glut.h"
	#define M_PI 3.14159
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>
#endif

using namespace std;

bool isTwilight = false;
float animation = 0.0;
float control = 0.02;

int bellRotate = 0;
int rotation = 4;

// You may add more functions here if you like
// ========================================================================

void drawHalfSphere(int scaley, int scalex, GLfloat r) {
    int i, j;
    GLfloat v[scalex*scaley][3];
    
    for (i=0; i<scalex; ++i) {
        for (j=0; j<scaley; ++j) {
            v[i*scaley+j][0]=r*cos(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
            v[i*scaley+j][1]=r*sin(i*M_PI/(2*scalex));
            v[i*scaley+j][2]=r*sin(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
        }
    }
    
    glBegin(GL_QUADS);
    for (i=0; i<scalex-1; ++i) {
        for (j=0; j<scaley; ++j) {
            glVertex3fv(v[i*scaley+j]);
            glVertex3fv(v[i*scaley+(j+1)%scaley]);
            glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
            glVertex3fv(v[(i+1)*scaley+j]);
        }
    }
    glEnd();
}

void drawSphere(double r)
{
    int i,j;
    int n = 20;
    for(i=0;i<n;i++) {
        for(j=0;j<2*n;j++) {
            glBegin(GL_QUADS);

            glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
            glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
            glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
            glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
            glEnd();
        }
    }
}

bool cmpf(float A, float B, float epsilon = 0.005f)
{
    return (fabs(A - B) < epsilon);
}


void animate(int value) {
    if(isTwilight) {
        if(cmpf(animation, 0.1f)) {
            control = -control;
        } else if(cmpf(animation, -0.1f)){
           control = -control;
        }
        animation += control;
        
        if(bellRotate == 20) {
            rotation = -rotation;
        } else if(bellRotate == -20){
            rotation = -rotation;
        }
        bellRotate += rotation;
        
        glutPostRedisplay();
        }
    glutTimerFunc(500, animate, 0);
}

// ========================================================================

void drawMyHouse(GLuint texSet[])
{
	//plot dimension
	//x: -5:5
	//y: >= 0
	//z: -5:5

	// Your main drawing code goes here
	// =========================================

	// floor plane (you may remove this)
	glBegin(GL_POLYGON);
		glColor3f(0.18, 0.31, 0.18);
		glVertex3f(-5, -0.02, -5);
		glVertex3f( 5, -0.02, -5);
		glVertex3f( 5, -0.02,  5);
		glVertex3f(-5, -0.02,  5);
	glEnd();
    
    glPushMatrix();
    glTranslatef(0, 6, 0);
    glScalef(10, 14, 10);  // x=8 left and right, y=12 up, z=8 front and back
    glColor3f(1.0, 1.0, 1.0);
    glutWireCube(1);
    glPopMatrix();
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);
    
    // Floor
    glPushMatrix();
        glColor3f(0.85,0.70,0.59);
        glEnable(GL_TEXTURE_2D);
        glBindTexture( GL_TEXTURE_2D, texSet[24] );
        glBegin(GL_POLYGON);
            glTexCoord2d(0,0); glVertex3d(-4,0,-5);
            glTexCoord2d(4,0); glVertex3d(4,0,-5);
            glTexCoord2d(4,4); glVertex3d(4,0,5);
            glTexCoord2d(0,4); glVertex3d(-4,0,5);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    // Bottom settlement
    glColor3f(0.85,0.70,0.59);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texSet[41] );
    
    // Front Left
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);	glVertex3d(-5,3,2);
    glTexCoord2d(8,0);	glVertex3d(-2,3,2);
    glTexCoord2d(8,8);	glVertex3d(-2,0,2);
    glTexCoord2d(0,8);	glVertex3d(-5,0,2);
    glEnd();
    
    // Front Right
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);	glVertex3d(5,3,2);
    glTexCoord2d(8,0);	glVertex3d(2,3,2);
    glTexCoord2d(8,8);	glVertex3d(2,0,2);
    glTexCoord2d(0,8);	glVertex3d(5,0,2);
    glEnd();
    
    // Right
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);	glVertex3d(5,3,2);
    glTexCoord2d(8,0);	glVertex3d(5,3,-2);
    glTexCoord2d(8,8);	glVertex3d(5,0,-2);
    glTexCoord2d(0,8);	glVertex3d(5,0,2);
    glEnd();
    
    // Back
    glPushMatrix();
    glRotatef(180,0,1,0);
    glBegin(GL_POLYGON);
				glTexCoord2d(0,0);	glVertex3d(-5,3,2);
				glTexCoord2d(8,0);	glVertex3d(5,3,2);
				glTexCoord2d(8,8);	glVertex3d(5,0,2);
				glTexCoord2d(0,8);	glVertex3d(-5,0,2);
    glEnd();
    
    // Left
    glBegin(GL_POLYGON);
				glTexCoord2d(0,0);	glVertex3d(5,3,2);
				glTexCoord2d(8,0);	glVertex3d(5,3,-2);
				glTexCoord2d(8,8);	glVertex3d(5,0,-2);
				glTexCoord2d(0,8);	glVertex3d(5,0,2);
    glEnd();
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    // Bottom Roof
    glColor3ub(133,60,8);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texSet[18] );
    //glTranslatef(0,0,-1);
    
    // Top
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);	glVertex3d(-5,4,-1.5);
    glTexCoord2d(3,0);	glVertex3d(5,4,-1.5);
    glTexCoord2d(3,3);	glVertex3d(5,4,1.5);
    glTexCoord2d(0,3);	glVertex3d(-5,4,1.5);
    glEnd();
    
    // Front
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);	glVertex3d(-5,4,1.5);
    glTexCoord2d(2,0);	glVertex3d(5,4,1.5);
    glTexCoord2d(2,2);	glVertex3d(5,3,2);
    glTexCoord2d(0,2);	glVertex3d(-5,3,2);
    glEnd();
    
    // Right
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);	glVertex3d(5,3,-2);
    glTexCoord2d(2,0);	glVertex3d(5,4,-1.5);
    glTexCoord2d(2,2);	glVertex3d(5,4,1.5);
    glTexCoord2d(0,2);	glVertex3d(5,3,2);
    glEnd();
    
    // Back
    glPushMatrix();
    glRotatef(180,0,1,0);
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);	glVertex3d(-5,4,1.5);
    glTexCoord2d(2,0);	glVertex3d(5,4,1.5);
    glTexCoord2d(2,2);	glVertex3d(5,3,2);
    glTexCoord2d(0,2);	glVertex3d(-5,3,2);
    glEnd();
    
    // Left
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);	glVertex3d(5,3,-2);
    glTexCoord2d(2,0);	glVertex3d(5,4,-1.5);
    glTexCoord2d(2,2);	glVertex3d(5,4,1.5);
    glTexCoord2d(0,2);	glVertex3d(5,3,2);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    // Door
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texSet[27] );
    glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
    glTexCoord2d(-0.8,0); glVertex3d(-2,3,2);
    glTexCoord2d(1,0); glVertex3d(2,3,2);
    glTexCoord2d(1,1); glVertex3d(2,0,2);
    glTexCoord2d(-0.8,1); glVertex3d(-2,0,2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    // Clock Tower
    glColor3f(0.96,0.90,0.80);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texSet[41] );
    
    glPushMatrix();
    for(int j = 0; j < 360; j+= 90) {
        
        glRotatef(j, 0, 1, 0);
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-1.0,10,1.0);
        glTexCoord2d(8,0);	glVertex3d(1.0,10,1.0);
        glTexCoord2d(8,8);	glVertex3d(1.0,4,1.0);
        glTexCoord2d(0,8);	glVertex3d(-1.0,4,1.0);
        glEnd();
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    // Clock Tower Adjacent
    glPushMatrix();
    for(int j = 0; j < 360; j+= 180) {
        glRotatef(j, 0, 1, 0);
        
        // Main
        glColor3f(0.92,0.78,0.62);
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture( GL_TEXTURE_2D, texSet[26] );
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-1.6,9.5,0.75);
        glTexCoord2d(4,0);	glVertex3d(-1.6,9.5,-0.75);
        glTexCoord2d(4,4);	glVertex3d(-1.0,9.5,-0.75);
        glTexCoord2d(0,4);	glVertex3d(-1.0,9.5,0.75);
        glEnd();
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-1.6,9.5,0.75);
        glTexCoord2d(4,0);	glVertex3d(-1.0,9.5,0.75);
        glTexCoord2d(4,4);	glVertex3d(-1.0,4,0.75);
        glTexCoord2d(0,4);	glVertex3d(-1.6,4,0.75);
        glEnd();
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-1.6,9.5,0.75);
        glTexCoord2d(4,0);	glVertex3d(-1.6,9.5,-0.75);
        glTexCoord2d(4,4);	glVertex3d(-1.6,4,-0.75);
        glTexCoord2d(0,4);	glVertex3d(-1.6,4,0.75);
        glEnd();
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-1.0,9.5,-0.75);
        glTexCoord2d(4,0);	glVertex3d(-1.6,9.5,-0.75);
        glTexCoord2d(4,4);	glVertex3d(-1.6,4,-0.75);
        glTexCoord2d(0,4);	glVertex3d(-1.0,4,-0.75);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        
        // Secondary
        glEnable(GL_TEXTURE_2D);
        glBindTexture( GL_TEXTURE_2D, texSet[41] );
        glBegin(GL_POLYGON);
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-1.5,10,0.25);
        glTexCoord2d(8,0);	glVertex3d(-1.3,10,0.25);
        glTexCoord2d(8,8);	glVertex3d(-1.3,9.5,0.25);
        glTexCoord2d(0,8);	glVertex3d(-1.5,9.5,0.25);
        glEnd();
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-1.5,10,0.25);
        glTexCoord2d(8,0);	glVertex3d(-1.5,10,-0.25);
        glTexCoord2d(8,8);	glVertex3d(-1.5,9.5,-0.25);
        glTexCoord2d(0,8);	glVertex3d(-1.5,9.5,0.25);
        glEnd();
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-1.3,10,-0.25);
        glTexCoord2d(8,0);	glVertex3d(-1.5,10,-0.25);
        glTexCoord2d(8,8);	glVertex3d(-1.5,9.5,-0.25);
        glTexCoord2d(0,8);	glVertex3d(-1.3,9.5,-0.25);
        glEnd();
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-1.3,10,0.25);
        glTexCoord2d(8,0);	glVertex3d(-1.3,10,-0.25);
        glTexCoord2d(8,8);	glVertex3d(-1.3,9.5,-0.25);
        glTexCoord2d(0,8);	glVertex3d(-1.3,9.5,0.25);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    
        // Roof
        glColor3ub(133,60,8);
        glEnable(GL_TEXTURE_2D);
        glBindTexture( GL_TEXTURE_2D, texSet[18] );
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-1.5,10,0.25);
        glTexCoord2d(8,0);	glVertex3d(-1.4,10.5,0);
        glTexCoord2d(8,8);	glVertex3d(-1.3,10,0.25);
        glEnd();
        
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-1.3,10,0.25);
        glTexCoord2d(8,0);	glVertex3d(-1.4,10.5,0);
        glTexCoord2d(8,8);	glVertex3d(-1.3,10,-0.25);
        glEnd();
        
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-1.5,10,-0.25);
        glTexCoord2d(8,0);	glVertex3d(-1.4,10.5,0);
        glTexCoord2d(8,8);	glVertex3d(-1.3,10,-0.25);
        glEnd();
        
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-1.5,10,-0.25);
        glTexCoord2d(8,0);	glVertex3d(-1.4,10.5,0);
        glTexCoord2d(8,8);	glVertex3d(-1.5,10,0.25);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
    
    // Twin Towers
    glPushMatrix();
    glColor3f(0.92,0.78,0.62);
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texSet[41] );
    for(int j = 0; j < 360; j+= 180) {
        
        glRotatef(j, 0, 1, 0);
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-3,6,0.5);
        glTexCoord2d(8,0);	glVertex3d(-2,6,0.5);
        glTexCoord2d(8,8);	glVertex3d(-2,4,0.5);
        glTexCoord2d(0,8);	glVertex3d(-3,4,0.5);
        glEnd();
        
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-3,6,-0.5);
        glTexCoord2d(8,0);	glVertex3d(-2,6,-0.5);
        glTexCoord2d(8,8);	glVertex3d(-2,4,-0.5);
        glTexCoord2d(0,8);	glVertex3d(-3,4,-0.5);
        glEnd();
        
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-2,6,0.5);
        glTexCoord2d(8,0);	glVertex3d(-2,6,-0.5);
        glTexCoord2d(8,8);	glVertex3d(-2,4,-0.5);
        glTexCoord2d(0,8);	glVertex3d(-2,4,0.5);
        glEnd();
        
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-3,6,-0.5);
        glTexCoord2d(8,0);	glVertex3d(-3,6,0.5);
        glTexCoord2d(8,8);	glVertex3d(-3,4,0.5);
        glTexCoord2d(0,8);	glVertex3d(-3,4,-0.5);
        glEnd();
        
    }
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    // Twin Tower Roof
    glColor3ub(133,60,8);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texSet[18] );
    glPushMatrix();
    for(int j = 0; j < 360; j+= 180) {
        
        glRotatef(j, 0, 1, 0);
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-2.5,7.5,0);
        glTexCoord2d(8,0);	glVertex3d(-1.9,6,0.6);
        glTexCoord2d(8,8);	glVertex3d(-3.1,6,0.6);
        glEnd();
        
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-2.5,7.5,0);
        glTexCoord2d(8,0);	glVertex3d(-1.9,6,-0.6);
        glTexCoord2d(8,8);	glVertex3d(-1.9,6,0.6);
        glEnd();
        
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-2.5,7.5,0);
        glTexCoord2d(8,0);	glVertex3d(-3.1,6,-0.6);
        glTexCoord2d(8,8);	glVertex3d(-1.9,6,-0.6);
        glEnd();
        
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-2.5,7.5,0);
        glTexCoord2d(8,0);	glVertex3d(-3.1,6,-0.6);
        glTexCoord2d(8,8);	glVertex3d(-3.1,6,0.6);
        glEnd();
        
    }
    glPopMatrix();
    
    // Clock Box
    glColor3f(0.96,0.90,0.80);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texSet[40] );
    glBegin(GL_POLYGON);
    glTexCoord2d(0.1,1);	glVertex3d(-1.0,9.5,1.01);
    glTexCoord2d(1.05,1);	glVertex3d(1.0,9.5,1.01);
    glTexCoord2d(1.05,0);	glVertex3d(1.0,7.5,1.01);
    glTexCoord2d(0.1,0);	glVertex3d(-1.0,7.5,1.01);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texSet[41] );
    for(int j = 0; j < 360; j+= 180) {
        glPushMatrix();
        glRotatef(j, 0, 1, 0);
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-2.25,8.5,0.99);
        glTexCoord2d(4,0);	glVertex3d(0,10.5,0.99);
        glTexCoord2d(4,4);	glVertex3d(2.25,8.5,0.99);
        glTexCoord2d(0,4);	glVertex3d(0,6.5,0.99);
        glEnd();
        glPopMatrix();
    }
    for(int j = 0; j < 360; j+= 180) {
        glPushMatrix();
        glRotatef(j, 0, 1, 0);
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-2.25,8.5,-0.99);
        glTexCoord2d(3,0);	glVertex3d(0,10.5,-0.99);
        glTexCoord2d(3,3);	glVertex3d(0,10.5,0.99);
        glTexCoord2d(0,3);	glVertex3d(-2.25,8.5,0.99);
        glEnd();
        glPopMatrix();
    }
    for(int j = 0; j < 360; j+= 180) {
        glPushMatrix();
        glRotatef(j, 0, 1, 0);
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-2.25,8.5,-0.99);
        glTexCoord2d(3,0);	glVertex3d(0,6.5,-0.99);
        glTexCoord2d(3,3);	glVertex3d(0,6.5,0.99);
        glTexCoord2d(0,3);	glVertex3d(-2.25,8.5,0.99);
        glEnd();
        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
    
    // Black Arches
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texSet[1] );
    for(int j = 0; j < 360; j+= 90) {
        
        // Wall
        glRotatef(j, 0, 1, 0);
        glColor3ub(255,255,255);
        for(float i = 0; i <1.5; i+=0.125) {
            glBegin(GL_POLYGON);
            glTexCoord2d(0,0);	glVertex3d(-0.625+i,10.5,1.0);
            glTexCoord2d(8,0);	glVertex3d(-0.5+i,10.5,1.0);
            glTexCoord2d(8,8);	glVertex3d(-0.5+i,10,1.0);
            glTexCoord2d(0,8);	glVertex3d(-0.625+i,10,1.0);
            glEnd();
        }
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-1.0,10.5,1.0);
        glTexCoord2d(1,0);	glVertex3d(-0.75,10.5,1.0);
        glTexCoord2d(1,1);	glVertex3d(-0.75,10,1.0);
        glTexCoord2d(0,1);	glVertex3d(-1.0,10,1.0);
        glEnd();
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(0.75,10.5,1.0);
        glTexCoord2d(1,0);	glVertex3d(1.0,10.5,1.0);
        glTexCoord2d(1,1);	glVertex3d(1.0,10,1.0);
        glTexCoord2d(0,1);	glVertex3d(0.75,10,1.0);
        glEnd();
        
        // Black
        for(float i = 0; i <1.5; i+=0.25) {
            glBegin(GL_POLYGON);
            glColor3ub(0, 0, 0);
            glVertex3d(-0.75+i,10.5,1.01);
            glVertex3d(-0.625+i,10.5,1.01);
            glVertex3d(-0.625+i,10,1.01);
            glVertex3d(-0.75+i,10,1.01);
            glEnd();
        }

    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    // Top Roof
    glPushMatrix();
    glColor3ub(133,60,8);
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texSet[18] );
    
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);	glVertex3d(-0.75,12.5,-0.75);
    glTexCoord2d(3,0);	glVertex3d(0.75,12.5,-0.75);
    glTexCoord2d(3,3);	glVertex3d(0.75,12.5,0.75);
    glTexCoord2d(0,3);	glVertex3d(-0.75,12.5,0.75);
    glEnd();
    
    glPushMatrix();
    for(int j = 0; j < 360; j+= 90) {
        glRotatef(j, 0, 1, 0);
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);	glVertex3d(-0.75,12.5,0.75);
        glTexCoord2d(3,0);	glVertex3d(0.75,12.5,0.75);
        glTexCoord2d(3,3);	glVertex3d(1.2,10.2,1.2);
        glTexCoord2d(0,3);	glVertex3d(-1.2,10.2,1.2);
        glEnd();
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    
    // front roof semicircle
    glPushMatrix();
    glColor3ub(255,255,255);
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texSet[42] );
    glBegin(GL_POLYGON);
    for (float i=0; i <= M_PI*6/5; i += M_PI/5){
        glTexCoord2d(cos(i)/2.25+0.57, sin(i)/5.7+0.81);	glVertex3d(cos(i)*2, sin(i)+3, 4);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texSet[18] );
    glBegin(GL_QUADS); // round roof
    for (float i=0; i <= (M_PI*6/5)-(M_PI/5); i += M_PI/5){
        glColor3ub(133,60,8);
        glTexCoord2d(0,0);	glVertex3d(cos(i)*2, sin(i)+3, 1.5);
        glTexCoord2d(1,0);	glVertex3d(cos(i+M_PI/5)*2, sin(i+M_PI/5)+3, 1.5);
        glTexCoord2d(1,1);	glVertex3d(cos(i+M_PI/5)*2, sin(i+M_PI/5)+3, 4);
        glTexCoord2d(0,0);	glVertex3d(cos(i)*2, sin(i)+3, 4);
    }
    glEnd();
    
    // Porch Poles
    glPushMatrix();
    for(float i = -1.8; i < 3.6; i+=3.6) {
        glPushMatrix();
        glTranslatef(i, 1.5, 3.8);
        glRotatef(90, 1, 0, 0);
        for (int a = 0; a <= 45; a++) {
            glBegin(GL_POLYGON);
            
            int i = 2 * a;
            float h = 3.0;
            float r = 0.1;
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);
            glEnd();
        }
        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
    
    // Double Brick Pillars
    glColor3ub(255,100,100);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texSet[3] );
    
    for(double i = 0; i <= 3.5; i+=3.5) {
        glTranslatef(i, 0, 0);
        // Front
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);      glVertex3d(-2,3,2.5);
        glTexCoord2d(0.7,0);	glVertex3d(-1.5,3,2.5);
        glTexCoord2d(0.7,0.7);	glVertex3d(-1.5,1,2.5);
        glTexCoord2d(0,0.7);	glVertex3d(-2,1,2.5);
        glEnd();
        
        // Right
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);      glVertex3d(-1.5,3,2.5);
        glTexCoord2d(0.7,0);	glVertex3d(-1.5,3,1.5);
        glTexCoord2d(0.7,0.7);	glVertex3d(-1.5,1,1.5);
        glTexCoord2d(0,0.7);	glVertex3d(-1.5,1,2.5);
        glEnd();
        
        // Back
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);      glVertex3d(-2,3,1.5);
        glTexCoord2d(0.7,0);	glVertex3d(-1.5,3,1.5);
        glTexCoord2d(0.7,0.7);	glVertex3d(-1.5,1,1.5);
        glTexCoord2d(0,0.7);	glVertex3d(-2,1,1.5);
        glEnd();
        
        // Left
        glBegin(GL_POLYGON);
        glTexCoord2d(0,0);      glVertex3d(-2,3,1.5);
        glTexCoord2d(0.7,0);	glVertex3d(-2,3,2.5);
        glTexCoord2d(0.7,0.7);	glVertex3d(-2,1,2.5);
        glTexCoord2d(0,0.7);	glVertex3d(-2,1,1.5);
        glEnd();
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    // Podium
    glColor3f(0.77,0.77,0.77);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texSet[25] );
    
    for(float i = 0; i < 1; i+=0.25) {
        glPushMatrix();
        glScalef(1, 1-i, 1+(i/4));
    // Top
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);	glVertex3d(-2,1,1);
    glTexCoord2d(3,0);	glVertex3d(2,1,1);
    glTexCoord2d(3,3);	glVertex3d(2,1,4);
    glTexCoord2d(0,3);	glVertex3d(-2,1,4);
    glEnd();
    
    // Front
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);	glVertex3d(-2,1,4);
    glTexCoord2d(3,0);	glVertex3d(2,1,4);
    glTexCoord2d(3,3);	glVertex3d(2,0,4);
    glTexCoord2d(0,3);	glVertex3d(-2,0,4);
    glEnd();
    
    // Right
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);	glVertex3d(2,1,4);
    glTexCoord2d(3,0);	glVertex3d(2,1,1);
    glTexCoord2d(3,3);	glVertex3d(2,0,1);
    glTexCoord2d(0,3);	glVertex3d(2,0,4);
    glEnd();
    
    // Back
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);	glVertex3d(-2,1,1);
    glTexCoord2d(3,0);	glVertex3d(2,1,1);
    glTexCoord2d(3,3);	glVertex3d(2,0,1);
    glTexCoord2d(0,3);	glVertex3d(-2,0,1);
    glEnd();
    
    // Left
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);	glVertex3d(-2,1,1);
    glTexCoord2d(3,0);	glVertex3d(-2,1,4);
    glTexCoord2d(3,3);	glVertex3d(-2,0,4);
    glTexCoord2d(0,3);	glVertex3d(-2,0,1);
    glEnd();
        glPopMatrix();
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    // Bells
    glPushMatrix();
    for(int j = 0; j <= 180; j+=180) {
        glColor3f(0.65,0.49,0.24);
        glEnable(GL_TEXTURE_2D);
        glBindTexture( GL_TEXTURE_2D, texSet[34] );
        glRotatef(j, 0, 1, 0);
        glPushMatrix();
        glTranslatef(-0.8, 11.5, 0);
        glRotatef(90, 0, 1, 0);
        for (int a = 0; a <= 45; a++) {
            glBegin(GL_POLYGON);
            
            int i = 2 * a;
            float h = 1.0;
            float r = 0.15;
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);
            glEnd();
        }
    
        glTranslatef(0, 0.12, -0.54);
        glRotatef(45, 1, 0, 0);
        for (int a = 0; a <= 45; a++) {
            glBegin(GL_POLYGON);
            
            int i = 2 * a;
            float h = 0.5;
            float r = 0.15;
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);
            glEnd();
        }
    
        glTranslatef(0, 0.3, -0.5);
        glRotatef(45, 1, 0, 0);
        for (int a = 0; a <= 45; a++) {
            glBegin(GL_POLYGON);
            
            int i = 2 * a;
            float h = 1;
            float r = 0.15;
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);
            glEnd();
        }
    
        glTranslatef(0, -0.12, -0.54);
        glRotatef(-45, 1, 0, 0);
        for (int a = 0; a <= 45; a++) {
            glBegin(GL_POLYGON);
            
            int i = 2 * a;
            float h = 0.5;
            float r = 0.15;
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);
            glEnd();
        }
    
        glTranslatef(0, -0.21, -0.375);
        glRotatef(-45, 1, 0, 0);
        for (int a = 0; a <= 45; a++) {
            glBegin(GL_POLYGON);
            
            int i = 2 * a;
            float h = 0.8;
            float r = 0.15;
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);
            glEnd();
        }
        
        glRotatef(-90, 1, 0, 0);
        glTranslatef(0, 0.1, 0);
        for (int i = 0; i <= 45; i++) {
            glBegin(GL_POLYGON);
            float h = 0.6;
            float r = 0.3;
            glVertex3f(0, 0, h);
            glVertex3d(r*sin(M_PI/180), r*cos(M_PI/180), 0);
            glVertex3d(r*sin(M_PI/180 * i+10), r*cos(M_PI/180 * i+10), 0);
            glEnd();
        }
        glTranslatef(0, 0, -0.3);
        for (int a = 0; a <= 45; a++) {
            glBegin(GL_POLYGON);
            int i = 2 * a;
            float h = 0.9;
            float r = 0.15;
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);
            glEnd();
        }
         glTranslatef(0, -0.1, 0.3);

        glRotatef(90, 1, 0, 0);
        glTranslatef(0, -0.12, -0.54);
        glRotatef(-45, 1, 0, 0);
        for (int a = 0; a <= 45; a++) {
            glBegin(GL_POLYGON);
            int i = 2 * a;
            float h = 0.5;
            float r = 0.15;
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);
            glEnd();
        }
        
        glRotatef(-45, 1, 0, 0);
        glTranslatef(0, 0.3, -0.1);
        for (int a = 0; a <= 45; a++) {
            glBegin(GL_POLYGON);
            int i = 2 * a;
            float h = 0.6;
            float r = 0.1;
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);
            glEnd();
        }
        glTranslatef(0, 0, 0.3);
        for(int i = 0; i < 360; i+=1) {
            glBegin(GL_POLYGON);
            float h = 0.3;
            float r = 0.1;
            glVertex3f(0, 0, h);
            glVertex3d(r*sin(M_PI/180), r*cos(M_PI/180), 0);
            glVertex3d(r*sin(M_PI/180 * i+10), r*cos(M_PI/180 * i+10), 0);
            glEnd();
        }
        glTranslatef(0, 0, -0.2);
        glTranslatef(0, -0.3, 0.1);
        glRotatef(45, 1, 0, 0);
        
        glTranslatef(0, 0, -0.1);
        glRotatef(135, 1, 0, 0);
        for(int i = 0; i < 360; i+=1) {
            glBegin(GL_POLYGON);
            float h = 0.5;
            float r = 0.2;
            glVertex3f(0, 0, h);
            glVertex3d(r*sin(M_PI/180), r*cos(M_PI/180), 0);
            glVertex3d(r*sin(M_PI/180 * i+10), r*cos(M_PI/180 * i+10), 0);
            glEnd();
        }
        
        glRotatef(90, 1, 0, 0);
        glTranslatef(0, 0, 0.3);
        for(int i = 0; i < 360; i+=1) {
            glBegin(GL_POLYGON);
            float h = 0.3;
            float r = 0.15;
            glVertex3f(0, 0, h);
            glVertex3d(r*sin(M_PI/180), r*cos(M_PI/180), 0);
            glVertex3d(r*sin(M_PI/180 * i+10), r*cos(M_PI/180 * i+10), 0);
            glEnd();
        }
        glDisable(GL_TEXTURE_2D);
        
        glPushMatrix();
        glRotatef(-180, 1, 0, 0);
        glTranslatef(0, -1.3, 0.8);
        glScalef(1, 2.2, 1);
        glColor3f(0.55, 0.47, 0.14);
        glRotatef(bellRotate, 0, 0, 1);
        drawHalfSphere(24, 24, 0.45);
        glPopMatrix();
        
        glRotatef(-180, 1, 0, 0);
        glTranslatef(0, -0.7, 0.05);
        glScalef(1, 1.3, 0.7);
        drawHalfSphere(24, 24, 0.3);
        glPopMatrix();
    }
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
// clouds
    glPushMatrix();
    glTranslatef(0, 12+animation, 3);
    if(isTwilight) {
        glColor4d(1, 0.85, 0, 0.8);
    } else {
        glColor4d(1, 1, 1, 0.8);
    }
    glScalef(1.2, 0.5, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.4, 11.7+animation, 3);
    glScalef(1.5, 0.7, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.4, 11.7+animation, 3);
    glScalef(1.5, 0.5, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 11.85+animation, 3);
    if(isTwilight) {
        glColor4d(1, 0.7, 0, 0.8);
    } else {
        glColor4d(1, 1, 1, 0.8);
    }
    glScalef(1.8, 0.5, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    
    // clouds
    glPushMatrix();
    glTranslatef(-3, 9-animation, 4.5);
    if(isTwilight) {
        glColor4d(1, 0.85, 0, 0.8);
    } else {
        glColor4d(1, 1, 1, 0.8);
    }
    glScalef(1.2, 0.5, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-3.4, 8.7-animation, 4.5);
    glScalef(1.5, 0.7, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2.6, 8.7-animation, 4.5);
    glScalef(1.5, 0.5, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-3, 8.85-animation, 4.5);
    if(isTwilight) {
        glColor4d(1, 0.7, 0, 0.8);
    } else {
        glColor4d(1, 1, 1, 0.8);
    }
    glScalef(1.8, 0.5, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    
    // clouds
    glPushMatrix();
    glTranslatef(4, 10+animation, 1);
    if(isTwilight) {
        glColor4d(1, 0.85, 0, 0.8);
    } else {
        glColor4d(1, 1, 1, 0.8);
    }
    glScalef(1.2, 0.5, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3.6, 9.7+animation, 1);
    glScalef(1.5, 0.7, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(4.4, 9.7+animation, 1);
    glScalef(1.5, 0.5, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(4, 9.85+animation, 1);
    if(isTwilight) {
        glColor4d(1, 0.7, 0, 0.8);
    } else {
        glColor4d(1, 1, 1, 0.8);
    }
    glScalef(1.8, 0.5, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    
    // clouds
    glPushMatrix();
    glTranslatef(-2, 9-animation, -3);
    if(isTwilight) {
        glColor4d(1, 0.85, 0, 0.8);
    } else {
        glColor4d(1, 1, 1, 0.8);
    }
    glScalef(1.2, 0.5, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2.4, 8.7-animation, -3);
    glScalef(1.5, 0.7, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.6, 8.7-animation, -3);
    glScalef(1.5, 0.5, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2, 8.85-animation, -3);
    if(isTwilight) {
        glColor4d(1, 0.7, 0, 0.8);
    } else {
        glColor4d(1, 1, 1, 0.8);
    }
    glScalef(1.8, 0.5, 0.5);
    drawSphere(0.5);
    glPopMatrix();
    
	// =========================================
}

// ********** You do not need to edit any code beyond this point **********

// The following code supports loading textures from disk
// ========================================================================
GLuint texSet[45];
GLuint loadMyTextures(char *filename)
{
	GLuint myTexture;
	FILE * file;
	unsigned char *tex, *tex2;

	// texture data
	int width = 256;
	int height = 256;

	// allocate buffer
	tex = (unsigned char *)malloc(width * height * 3);
	tex2 = (unsigned char *)malloc(width * height * 3);

	// open and read texture data
	file = fopen(filename, "rb");

	if (file == NULL)
		cout << "Error! Missing texture!\n";

	fread(tex, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i<width*height; i++)
	{
		tex2[i * 3] = tex[i * 3 + 2];
		tex2[i * 3 + 1] = tex[i * 3 + 1];
		tex2[i * 3 + 2] = tex[i * 3];
	}

	// allocate a texture name
	glGenTextures(1, &myTexture);
	glBindTexture(GL_TEXTURE_2D, myTexture);

	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	// when texture area is large, bilinear filter the first mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// texture should tile
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// build texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tex2);
    

	// free buffers
	free(tex);
	free(tex2);
	return myTexture;
}
// ========================================================================

// The following code is used to support rotation of the scene with your mouse
// ========================================================================
bool isDraggingLeft = false;
bool isDraggingRight = false;
int prevX = 0, prevY = 0;
int curX = 0, curY = 0;
float angle1 = M_PI, angle2 = -1;	// angles are in radians
float dist = 12.0;
float lookY = 5;
float aspectRatio = 1.0;

void LMBDragged(float dx, float dy) {
	angle1 -= ((float)dx) / 150.0;
	angle2 += ((float)dy) / 150.0;

	if (angle1 < 0)	angle1 += 2 * M_PI;
	else if (angle1 > 2 * M_PI) angle1 -= 2 * M_PI;
	if (angle2 < 0)	angle2 += 2 * M_PI;
	else if (angle2 > 2 * M_PI) angle2 -= 2 * M_PI;
}

void RMBDragged(float dx, float dy) {
	dist += ((float)dx) / 100.0;
	lookY += ((float)dy) / 50.0;
}

void computeCameraPosition() {
	float camX = dist * sin(angle1) * sin(angle2);
	float camY = dist * cos(angle2);
	float camZ = dist * cos(angle1) * sin(angle2);

	float upVectorY = 1.0;
	if (angle2 >= 0 && angle2 < M_PI) {
		upVectorY = -1.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, aspectRatio, 1, 75);
	gluLookAt(camX, camY+lookY, camZ, 0, lookY, 0, 0, upVectorY, 0);
	glMatrixMode(GL_MODELVIEW);
}

void resetCamera() {
	angle1 = M_PI;
	angle2 = -1;
	lookY = 5;
	dist = 15.0;
}
// ========================================================================


// The following code is the usual stuff you give OpenGL
// ========================================================================

void init(void)
{
    glClearColor (0.73, 0.90, 0.96, 1.0);
	glShadeModel (GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	texSet[0] = loadMyTextures("brick1.bmp");
	texSet[1] = loadMyTextures("brick2.bmp");
	texSet[2] = loadMyTextures("brick3.bmp");
	texSet[3] = loadMyTextures("brick4.bmp");
	texSet[4] = loadMyTextures("door1.bmp");
	texSet[5] = loadMyTextures("door2.bmp");
	texSet[6] = loadMyTextures("flower1.bmp");
	texSet[7] = loadMyTextures("flower2.bmp");
	texSet[8] = loadMyTextures("flower3.bmp");
	texSet[9] = loadMyTextures("grass1.bmp");

	texSet[10] = loadMyTextures("grass2.bmp");
	texSet[11] = loadMyTextures("leaves1.bmp");
	texSet[12] = loadMyTextures("leaves2.bmp");
	texSet[13] = loadMyTextures("roof1.bmp");
	texSet[14] = loadMyTextures("roof2.bmp");
	texSet[15] = loadMyTextures("roof3.bmp");
	texSet[16] = loadMyTextures("roof4.bmp");
	texSet[17] = loadMyTextures("roof5.bmp");
	texSet[18] = loadMyTextures("roof6.bmp");
	texSet[19] = loadMyTextures("stone1.bmp");

	texSet[20] = loadMyTextures("stone2.bmp");
	texSet[21] = loadMyTextures("tile1.bmp");
	texSet[22] = loadMyTextures("tile2.bmp");
	texSet[23] = loadMyTextures("tile3.bmp");
	texSet[24] = loadMyTextures("tile4.bmp");
	texSet[25] = loadMyTextures("tile5.bmp");
	texSet[26] = loadMyTextures("tile6.bmp");
	texSet[27] = loadMyTextures("window1.bmp");
	texSet[28] = loadMyTextures("window2.bmp");
	texSet[29] = loadMyTextures("window3.bmp");

	texSet[30] = loadMyTextures("window4.bmp");
	texSet[31] = loadMyTextures("window5.bmp");
	texSet[32] = loadMyTextures("window6.bmp");
	texSet[33] = loadMyTextures("wood1.bmp");
	texSet[34] = loadMyTextures("wood2.bmp");
	texSet[35] = loadMyTextures("wood3.bmp");
	texSet[36] = loadMyTextures("wood4.bmp");
	texSet[37] = loadMyTextures("wood5.bmp");
	texSet[38] = loadMyTextures("wood6.bmp");
	texSet[39] = loadMyTextures("wood7.bmp");

	texSet[40] = loadMyTextures("custom/custom1.bmp");
	texSet[41] = loadMyTextures("custom/custom2.bmp");
	texSet[42] = loadMyTextures("custom/custom3.bmp");
	texSet[43] = loadMyTextures("custom/custom4.bmp");
	texSet[44] = loadMyTextures("custom/custom5.bmp");

	cout << "Texture loading complete" << endl;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, 1.0, 1, 75);
	computeCameraPosition();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	aspectRatio = (float)w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, aspectRatio, 1, 75);
	computeCameraPosition();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(void)
{
	int startTime=glutGet(GLUT_ELAPSED_TIME);
	int counter = 1;
	
	glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawMyHouse(texSet);
	
	int endTime=glutGet(GLUT_ELAPSED_TIME);
	// cout<<"Frame Rate: "<<(float)1000/(endTime-startTime)<<"\n";
	glFlush();
	glutSwapBuffers();

}

void mouse(int button, int state, int x, int y)
{

	if(!isDraggingLeft && button == GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		isDraggingLeft = true;
		isDraggingRight = false;
		prevX = x;
		prevY = y;
	}

	else if(button == GLUT_LEFT_BUTTON && state==GLUT_UP)
	{		
		isDraggingLeft = false;
		prevX = 0;
		prevY = 0;
	}

	if (!isDraggingRight && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		isDraggingLeft = false;
		isDraggingRight = true;
		prevX = x;
		prevY = y;
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		isDraggingRight = false;
		prevX = 0;
		prevY = 0;
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
		resetCamera();
		computeCameraPosition();
		glutPostRedisplay();
	}

}

void mouseMotion(int x, int y) {
	if (isDraggingLeft) {
		float dx = x - prevX;
		float dy = y - prevY;

		LMBDragged(dx, dy);
		computeCameraPosition();
		glutPostRedisplay();

		prevX = x;
		prevY = y;
	}

	if (isDraggingRight) {
		float dx = x - prevX;
		float dy = y - prevY;

		RMBDragged(dx, dy);
		computeCameraPosition();
		glutPostRedisplay();

		prevX = x;
		prevY = y;
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'w' || key == 'W') {
		dist -= 1.0;
		computeCameraPosition();
		glutPostRedisplay();
	}

	if (key == 's' || key == 'S') {
		dist += 1.0;
		computeCameraPosition();
		glutPostRedisplay();
	}
    
    if (key == 'e' || key == 'E') {
        isTwilight = !isTwilight;
        if(isTwilight) {
            glClearColor (1, 0.6, 0.1, 1.0);
        } else {
            glClearColor (0.73, 0.90, 0.96, 1.0);
        }
            
        glutPostRedisplay();
    }
    
	if (key == 27) {
		exit(0);
	}
}

int main(int argc, char **argv)
{
	cout << "CS3241 Lab 5\n\n";
	cout << "+++++CONTROLS+++++++\n\n";
	cout << "Left Click and Drag: Rotate camera\n";
	cout << "Right Click and Drag:\n";
	cout << "\tVertical: Change camera elevation\n";
	cout << "\tHorizontal: Zoom in and out\n";
	cout << "Middle Click: Reset camera\n";
	cout << "W: Zoom In\n";
	cout << "S: Zoom Out\n";
	cout <<"ESC: Quit\n";

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
    
    glutTimerFunc(0, animate, 0);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}

// ========================================================================

