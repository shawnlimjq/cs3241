// CS3241Lab3.cpp : Defines the entry point for the console application.
//#include <cmath>
#include "math.h"
#include <iostream>
#include <fstream>

#ifdef _WIN32
	#include <Windows.h>
	#include "glut.h"
	#define M_PI 3.141592654
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>
#endif

// global variable

bool m_Smooth = false;
bool m_Highlight = false;
GLfloat angle = 0;   /* in degrees */
GLfloat angle2 = 0;   /* in degrees */
GLfloat zoom = 1.0;
int mouseButton = 0;
int moving, startx, starty;

#define NO_OBJECT 4;
int maxChain = 500;
int current_object = 0;
float animationAngle = 0;
float animationMovement = 5;

using namespace std;

void setupLighting()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	// Lights, material properties
    GLfloat	ambientProperties[]  = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat	diffuseProperties[]  = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat	specularProperties[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPosition[] = {-100.0f,100.0f,100.0f,1.0f};
	
    glClearDepth( 1.0 );

    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularProperties);
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition);
	
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

	// Default : lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

}

void drawCrown(double r, double h)
{
    float no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float mat_ambient[] = { 0.9f, 0.9f, 0.0f, 1.0f };
    float mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float mat_diffuse[] = { 0.5f, 0.1f, 0.0f, 1.0f };
    float no_shininess = 0.0f;
    float shininess = 30.0f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    if (m_Highlight)
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    }
    
    if (m_Smooth)
    {
        for (int a = 0; a <= 45; a++) {
            glBegin(GL_POLYGON);
            
            int i = 2 * a;
    
            glNormal3d(sin(M_PI*i / 45.0), cos(M_PI*i / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
            glNormal3d(sin(M_PI*i / 45.0), cos(M_PI*i / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
            glNormal3d(sin(M_PI*(i + 2) / 45.0), cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glNormal3d(sin(M_PI*(i + 2) / 45.0), cos(M_PI*(i + 2) / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);
            
            glEnd();
        }
    }
    else	{
        for (int a = 0; a <= 45; a++) {
            glBegin(GL_POLYGON);
            
            int i = 2 * a;
            glNormal3d(r*sin(M_PI*(i + 1) / 45.0), r*cos(M_PI*(i + 1) / 45.0), 0);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);
            
            glEnd();
        }
    }
}

void drawRing(double r, double h)
{
    float no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float mat_specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float no_shininess = 0.0f;
    float shininess = 20.0f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    if (m_Highlight)
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    }
    
    if (m_Smooth)
    {
        for (int a = 0; a <= 45; a++) {
            glBegin(GL_POLYGON);
            
            int i = 2 * a;
            
            glNormal3d(sin(M_PI*i / 45.0), cos(M_PI*i / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
            glNormal3d(sin(M_PI*i / 45.0), cos(M_PI*i / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
            
            glNormal3d(sin(M_PI*(i + 2) / 45.0), cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glNormal3d(sin(M_PI*(i + 2) / 45.0), cos(M_PI*(i + 2) / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);
            
            glEnd();
        }
    }
    else	{
        for (int a = 0; a <= 45; a++) {
            glBegin(GL_POLYGON);
            
            int i = 2 * a;
            glNormal3d(r*sin(M_PI*(i + 1) / 45.0), r*cos(M_PI*(i + 1) / 45.0), 0);
          
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), 0.5*h);
            glVertex3d(r*sin(M_PI*i / 45.0), r*cos(M_PI*i / 45.0), -0.5*h);
          
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), -0.5*h);
            glVertex3d(r*sin(M_PI*(i + 2) / 45.0), r*cos(M_PI*(i + 2) / 45.0), 0.5*h);
            
            glEnd();
        }
    }
}

void drawSphere(double r, int color)
{

	float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    
    float mat_ambient0[] = {0.3f, 0.3f, 0.3f, 1.0f};
    float mat_diffuse0[] = {0.1f, 0.5f, 0.8f, 1.0f};
    
    float mat_ambient1[] = {0.2f, 0.2f, 0.2f, 1.0f};
    float mat_diffuse1[] = {0.4f, 0.4f, 0.4f, 1.0f};
    
    float mat_ambient2[] = {0.8f, 0.8f, 0.8f, 1.0f};
    float mat_diffuse2[] = {0.6f, 0.6f, 0.6f, 1.0f};
    
    float mat_ambient3[] = {0.8f, 0.0f, 0.0f, 1.0f};
    float mat_diffuse3[] = {0.6f, 0.0f, 0.0f, 1.0f};
    
    float mat_specular[] = {0.3f, 0.3f, 0.3f, 1.0f};
	float no_shininess = 0.0f;
    
    if (color == 1) {
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    } else if (color == 2) {
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    } else if (color == 3) {
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
    } else {
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient0);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse0);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }

	if(m_Highlight)
	{
		// your codes for highlight here
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 80.0f);
	} else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	}

	
    int i,j;
	int n = 20;
    for(i=0;i<n;i++)
		for(j=0;j<2*n;j++)
		if(m_Smooth)
		{
			glBegin(GL_POLYGON);

			    // the normal of each vertex is actaully its own coordinates normalized for a sphere

			    // your normal here;
                glNormal3d(sin(i*M_PI/n)*cos(j*M_PI/n), cos(i*M_PI/n)*cos(j*M_PI/n), sin(j*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
			    // your normal here
                glNormal3d(sin((i+1)*M_PI/n)*cos(j*M_PI/n), cos((i+1)*M_PI/n)*cos(j*M_PI/n), sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
			    // your normal here
                glNormal3d(sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n), cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n), sin((j+1)*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
			    // your normal here
                glNormal3d(sin(i*M_PI/n)*cos((j+1)*M_PI/n),cos(i*M_PI/n)*cos((j+1)*M_PI/n),sin((j+1)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
 			glEnd();
		} else	{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),sin((j+0.5)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
 			glEnd();
		}

}

void drawChain(double r) {
    glPushMatrix();
        glTranslatef(-animationMovement, animationMovement, 0);
        glRotatef(-45, 0, 0, 1);
        glRotatef(-45, 1, 0, 0);
        for (int i = 0; i < maxChain; i++) {
                drawRing(r, r);
                glTranslatef(r*1.5, 0, 0);
                glRotatef(90, 1, 0, 0);
            }
    glPopMatrix();
}

void drawPokeball(double r) {
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glRotatef(animationAngle, 0, 1, 0);
        glPushMatrix();
            glTranslatef(0, 0, -0.05);
            drawSphere(r, 3);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0, 0, 0.05);
            drawSphere(r, 2);
        glPopMatrix();
        drawRing(r+0.005, r/4);
        glTranslatef(0, 0.6, 0);
        drawSphere(r/2, 1);
        glTranslatef(0, 0.3, 0);
        drawSphere(r/4, 2);
    glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0, 0, -6);

	    glRotatef(angle2, 1.0, 0.0, 0.0);
		glRotatef(angle, 0.0, 1.0, 0.0);

		glScalef(zoom,zoom,zoom);

		switch (current_object) {
		case 0:
			drawSphere(1, 0);
			break;
		case 1:
            drawCrown(1, 1);
			// draw your second primitive object here
			break;
		case 2:
			// draw your first composite object here
            drawChain(0.5);
			break;
		case 3:
			// draw your second composite object here
            drawPokeball(1);
			break;
		default:
			break;
		};
	glPopMatrix();
	glutSwapBuffers ();
}




void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
	case 'p':
	case 'P':
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		break;			
	case 'w':
	case 'W':
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		break;			
	case 'v':
	case 'V':
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
		break;			
	case 's':
	case 'S':
		m_Smooth = !m_Smooth;
		break;
	case 'h':
	case 'H':
		m_Highlight = !m_Highlight;
		break;

	case '1':
	case '2':
	case '3':
	case '4':
		current_object = key - '1';
		break;

	case 27:
		exit(0);
		break;
		
	default:
	break;
	}

	glutPostRedisplay();
}



void
mouse(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) {
	mouseButton = button;
    moving = 1;
    startx = x;
    starty = y;
  }
  if (state == GLUT_UP) {
	mouseButton = button;
    moving = 0;
  }
}

void motion(int x, int y)
{
  if (moving) {
	if(mouseButton==GLUT_LEFT_BUTTON)
	{
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
	}
	else zoom += ((y-starty)*0.001);
    startx = x;
    starty = y;
	glutPostRedisplay();
  }
  
}

void idle() {
    animationAngle += 0.5;
    animationMovement += 0.01;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 3"<< endl<< endl;

	cout << "1-4: Draw different objects"<<endl;
	cout << "S: Toggle Smooth Shading"<<endl;
	cout << "H: Toggle Highlight"<<endl;
	cout << "W: Draw Wireframe"<<endl;
	cout << "P: Draw Polygon"<<endl;
	cout << "V: Draw Vertices"<<endl;
	cout << "ESC: Quit" <<endl<< endl;

	cout << "Left mouse click and drag: rotate the object"<<endl;
	cout << "Right mouse click and drag: zooming"<<endl;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow ("CS3241 Assignment 3");
	glClearColor (1.0,1.0,1.0, 1.0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	setupLighting();
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); 
	glDepthMask(GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    gluPerspective( /* field of view in degree */ 40.0,
  /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 80.0);
	glMatrixMode(GL_MODELVIEW);
    glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}
