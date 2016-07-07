// CS3241Lab1.cpp : Defines the entry point for the console application.
#include <cmath>
#include <iostream>

/* Include header files depending on platform */
#ifdef _WIN32
	#include "glut.h"
	#define M_PI 3.14159
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>
#endif

#define TWICE_PI 2.0 * 3.142
#define PI 3.142
#define FULL 'F'  // full circle
#define HALF 'H'  // half cirlce

using namespace std;

float alpha = 0.0, k = 1;
float tx = 0.0, ty = 0.0;

float axM = 0.0, ayM = 0.0, xDiff = 0.075, yDiff = 0.075;   // controls mosquito animation
float anger = 0.0;  // anger gauge

/* method to draw full circle (filled)
 * @param radius
 */
void drawFilledCircle(double radius){
    int x = 0, y = 0;
    
    glBegin(GL_TRIANGLE_FAN); // begin circle
        glVertex2f(x, y); // center of circle
        for (int i = 0; i <= 360; i++)   {
            glVertex2f ((x + (radius * cos(i * TWICE_PI / 360))), (y + (radius * sin(i * TWICE_PI / 360))));
        }
    glEnd();
}

/* method to draw outlines to circles
 * @param radius, half/full circle
 */
void outlineCircles(double radius, char type) {
    int x = 0, y = 0;
    
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP); // begin circle
        for (int i = 0; i <= 360; i++)   {
            if (type == HALF) {
                glVertex2f ((x + (radius * cos(i * PI / 360))), (y + (radius * sin(i * PI / 360))));
            }
            else if (type == FULL) {
                glVertex2f ((x + (radius * cos(i * TWICE_PI / 360))), (y + (radius * sin(i * TWICE_PI / 360))));
            }
        }
    glEnd();
}

/* method to half circle (filled)
 * @param radius
 */
void drawHalfFilledCircle(double radius) {
    int x = 0, y = 0;
    
    glBegin(GL_TRIANGLE_FAN); // begin circle
        glVertex2f(x, y); // center of circle
        for (int i = 0; i <= 20; i++)   {
            glVertex2f ((x + (radius * cos(i * PI / 20))), (y + (radius * sin(i * PI / 20))));
        }
    glEnd(); //END
}

/* method to draw lines
 * @param start coordinates, end coordinates
 */
void drawStroke(double xEnd, double yEnd, double xStart, double yStart) {
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
        glVertex2f(xStart, yStart);
        glVertex2f(xEnd, yEnd);
    glEnd();
}

/* method to draw angry symbol
 * @param opacity
 */
void drawAngryLines(int op) {
    glColor4f(0, 0, 0, op);
    glBegin(GL_LINE_STRIP);
        glVertex2f(0, 0);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, 1.5);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex2f(1.7, 0);
        glVertex2f(1.0, 0.5);
        glVertex2f(1.0, 1.5);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex2f(0.1, -0.5);
        glVertex2f(0.7, 0.1);
        glVertex2f(1.5, -0.5);
    glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();

        //controls transformation
        glScalef(k, k, k);	
        glTranslatef(tx, ty, 0);	
        glRotatef(alpha, 0, 0, 1);
        
        //draw your stuff here
        // draw face
        glPushMatrix();
            glColor3ub(255, 228, 196);
            glScalef(1, 1.35, 1);
            drawFilledCircle(7);
        glPopMatrix();
        
        // draw left eye
        glPushMatrix();
            glRotatef(180, 0, 0, 1);
            glTranslatef(3, -2, 0);
            glScalef(0.35, 0.35, 0);
            glColor3ub(255, 250, 250);
            drawHalfFilledCircle(5);
            glColor3f(0, 0, 0);
            outlineCircles(5, HALF);
            glTranslatef(0, 1, 0);
            glColor3f(0, 0, 0);
            if(anger < 4) {
                drawFilledCircle(0.5);
            }
        glPopMatrix();
        
        // draw right eye
        glPushMatrix();
            glRotatef(180, 0, 0, 1);
            glTranslatef(-3, -2, 0);
            glScalef(0.35, 0.35, 0);
            glColor3ub(255, 250, 250);
            drawHalfFilledCircle(5);
            glColor3f(0, 0, 0);
            outlineCircles(5, HALF);
            glTranslatef(0, 1, 0);
            glColor3f(0, 0, 0);
            if(anger < 4) {
                drawFilledCircle(0.5);
            }
        glPopMatrix();
        
        // draw mouth
        glPushMatrix();
            glRotatef(180, 0, 0, 1);
            glTranslatef(0, 5.5, 0);
            glScalef(0.15, 0.15, 0);
            if (anger >= 4) {
                glColor3f(1, 1, 1);
            } else {
                glColor3f(1, 0, 0);
            }
            drawHalfFilledCircle(5);
            glColor3f(0, 0, 0);
            outlineCircles(5, HALF);
        glPopMatrix();
        
        // draw eyebrows
        glPushMatrix();
            glTranslatef(1.5, 3, 0);
            if(anger >= 4) {
                drawStroke(3.9, 1.15, -0.6, -1.1);  // right eyebrows
            } else {
                drawStroke(3, 0, 0, 0);
            }
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-4.5, 3, 0);
            if(anger >= 4) {
                drawStroke(4, -1.25, -0.5, 1);  // left eyebrows
            } else {
                drawStroke(3, 0, 0, 0);
            }
        glPopMatrix();
        
        // draw nose
        glPushMatrix();
            glTranslatef(0, 0.5, 0);
            drawStroke(0, -3.5, 0, 0);
            glTranslatef(0, -3.5, 0);
            drawStroke(0.3, -0.3, 0, 0);
        glPopMatrix();
        
        // draw ears
        glPushMatrix();
            glRotatef(90, 0, 0, 1);
            glColor3ub(255, 228, 196);
            glTranslatef(-0.5, 6, 0);
            drawHalfFilledCircle(2);
            glTranslatef(-1, 0.75, 0);
            drawStroke(2, 0, 0, 0);
            glTranslatef(1, 0.03, 0);
            outlineCircles(0.5, HALF); // left ear
        glPopMatrix();
        glPushMatrix();
            glRotatef(270, 0, 0, 1);
            glColor3ub(255, 228, 196);
            glTranslatef(0.5, 6, 0);
            drawHalfFilledCircle(2);
            glTranslatef(-1, 0.75, 0);
            drawStroke(2, 0, 0, 0);
            glTranslatef(1, 0, 0);
            outlineCircles(0.5, HALF);  // right ear
        glPopMatrix();
        
        // draw head shine
        glPushMatrix();
            glTranslatef(2.5, 7, 0);
            glColor4f(1, 1, 0.9, 0.7);
            drawFilledCircle(1);
            glTranslatef(1.5, -0.5, 0);
            glColor4f(1, 1, 0.9, 0.5);
            drawFilledCircle(0.2);
        glPopMatrix();
    
        // draw animated mosquito
        glPushMatrix();
            glColor3f(0, 0, 0);
            glScalef(1.2, 0.6, 0);
            axM += xDiff;
            ayM += yDiff;
            if(axM >= 5.0 || axM <= -5.0) {
                xDiff = -xDiff;
            }
            if(ayM >= 8.0 || ayM <= -8.0) {
                yDiff = -yDiff;
            }
            glTranslatef(axM, ayM, 0.0);
            drawFilledCircle(0.25);
            glColor4f(1, 1, 1, 0.8);
            glScalef(0.4, 1.8, 0);
            drawFilledCircle(0.3);
            glutPostRedisplay();
        glPopMatrix();
    
        // draw anger mark
        glPushMatrix();
            glColor3f(0, 0, 0);
            if(anger >= 1) {
                glPushMatrix();
                    glTranslatef(1.0, 5.0, 0);
                    glRotatef(30, 0, 0, 1);
                    drawAngryLines(1);
                glPopMatrix();
            }
            if(anger >= 2) {
                glPushMatrix();
                    glTranslatef(-4.0, -4.0, 0);
                    glRotatef(80, 0, 0, 1);
                    glScalef(0.5, 0.5, 0);
                    drawAngryLines(1);
                glPopMatrix();
            }
            if(anger >= 3) {
                glPushMatrix();
                    glTranslatef(3.0, -5.0, 0);
                    glScalef(1.3, 0.8, 0);
                    drawAngryLines(1);
                glPopMatrix();
            }
            glPopMatrix();

	glPopMatrix();
	glFlush ();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor (0, 0, 0, 1.0);    // background black
	glShadeModel (GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



void keyboard (unsigned char key, int x, int y)
{
	//keys to control scaling - k
	//keys to control rotation - alpha
	//keys to control translation - tx, ty
	switch (key) {

		case 'a':
			alpha+=10;
			glutPostRedisplay();
		break;

		case 'd':
			alpha-=10;
			glutPostRedisplay();
		break;

		case 'q':
			k+=0.1;
			glutPostRedisplay();
		break;

		case 'e':
			if(k>0.1)
				k-=0.1;
			glutPostRedisplay();
		break;

		case 'z':
			tx-=0.1;
			glutPostRedisplay();
		break;

		case 'c':
			tx+=0.1;
			glutPostRedisplay();
		break;

		case 's':
			ty-=0.1;
			glutPostRedisplay();
		break;

		case 'w':
			ty+=0.1;
			glutPostRedisplay();
		break;
            
        /* control Saitama's anger
         * max 4
         */
        case 'm':
            if(anger < 4) {
                anger += 1;
                glutPostRedisplay();
            }
        break;
            
        case 'n':
            if (anger > 0) {
                anger -= 1;
                glutPostRedisplay();
            }
        break;
            
		case 27:
			exit(0);
		break;

		default:
		break;
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 1\n\n";
	cout<<"+++++CONTROL BUTTONS+++++++\n\n";
	cout<<"Scale Up/Down: Q/E\n";
	cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
	cout<<"Move Up/Down: W/S\n";
	cout<<"Move Left/Right: Z/C\n";
	cout <<"ESC: Quit\n";

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
