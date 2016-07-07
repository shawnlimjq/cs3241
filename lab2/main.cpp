// CS3241Lab2.cpp : Defines the entry point for the console application.
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

using namespace std;

#define numStars 100
#define numPlanets 7
#define numAsteroid 200
#define PI 3.14159


class Planet {
public:
    float distFromRef;
    float a, b;
    float velocity;     // speed around the sun
    float angularSpeed; // speed of self rotation
    float rotation;     // self rotation
    float angle;        // angle about the sun
    float radius;
    float alpha;
    int satellites;
    float color[3];
    
    Planet()
    {
        distFromRef = 0;
        a = b = 0;
        velocity = 0;
        angularSpeed = 0;
        rotation = 270;
        color[0] = color[1] = color[2] = 1;
        radius = 0;
        angle = 0;
        alpha = 1;
        satellites = 0;
    }
};

class Sun {
public:
    float radius;
    float alpha;
    GLfloat color[3];
    
    Sun()
    {
        color[0] = 1, color[1] = 0.7, color[2] = 0;
        radius = 2;
        alpha = 1;
    }
};

class Satellite {
public:
    float radius;
    float alpha;
    float angle;
    float distFromPlanet;
    float velocity;
    GLfloat color[3];
    
    Satellite()
    {
        color[0] = color[1] = color[2] = 1;
        radius = 0.1;
        angle = 10;
        distFromPlanet = 0.65;
        velocity = 0.1;
        alpha = 1;
    }
};

float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;

float asteroid[numAsteroid][3];
float stars[numStars][3];
float starColor = 1.0;
int toggleTime = 0;

const int secHandA = 0, secHandB = 3;
const int minHandA = 1, minHandB = 4;
const int hourHandA = 2, hourHandB = 5;

float ellipseOrbit = 0;
float steps = 180;
float orbitAngle = 5;
float offsetX = 0;
float offsetY = 0;
float offsetZ = 0;
float beta = -orbitAngle / 180 * PI;
float sinbeta = sin(beta);
float cosbeta = cos(beta);
float planetAlpha = 0;
float sinalpha = 0;
float cosalpha = 0;
float a = 90; // horizontal axis length
float b = 50; // vertical axis length
float x = 0;
float y = 0;
float z = 0;


Planet planetList[numPlanets];
Sun sun;
Satellite satellites;

void reshape (int w, int h)
{
    GLfloat nRange = 10.0f;
    
    // Prevent a divide by zero
    if(h == 0)
        h = 1;
    
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    
    // Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h)
        glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else
        glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void generatePlanets() {
    Planet mercury;
    mercury.radius = 0.2;
    mercury.angularSpeed = 0.1;
    mercury.velocity = 1.50;
    mercury.distFromRef = 2.7;
    mercury.angle = 0;
    mercury.color[0] = 0.66;
    mercury.color[1] = 0.65;
    mercury.color[2] = 0.37;
    
    Planet venus;
    venus.radius = 0.3;
    venus.angularSpeed = 0.1;
    venus.velocity = 1.10;
    venus.distFromRef = 3.6;
    venus.angle = 0;
    venus.color[0] = 0.91;
    venus.color[1] = 0.76;
    venus.color[2] = 0.65;
    
    Planet earth;
    earth.radius = 0.35;
    earth.a = earth.b = 5;
    earth.angularSpeed = 0.1;
    earth.velocity = 0.90;
    earth.distFromRef = 4.5;
    earth.angle = 0;
    earth.satellites = 1;
    earth.color[0] = 0;
    earth.color[1] = 0.49;
    earth.color[2] = 1;
    
    Planet mars;
    mars.radius = 0.23;
    mars.angularSpeed = 0.1;
    mars.velocity = 0.75;
    mars.distFromRef = 5.2;
    mars.angle = 0;
    mars.satellites = 2;
    mars.color[0] = 1.00;
    mars.color[1] = 0.30;
    mars.color[2] = 0.00;
    
    Planet jupiter;
    jupiter.radius = 0.6;
    jupiter.angularSpeed = 0.1;
    jupiter.velocity = 0.40;
    jupiter.distFromRef = 6.4;
    jupiter.angle = 0;
    jupiter.color[0] = 0.3;
    jupiter.color[1] = 0.6;
    jupiter.color[2] = 0.6;
    
    Planet saturn;
    saturn.radius = 0.5;
    saturn.angularSpeed = 0.1;
    saturn.velocity = 0.25;
    saturn.distFromRef = 7.5;
    saturn.angle = 0;
    saturn.satellites = 4;
    saturn.color[0] = 0.7;
    saturn.color[1] = 0.5;
    saturn.color[2] = 0.1;
    
    Planet deathStar;
    deathStar.distFromRef = 9;
    deathStar.color[0] = deathStar.color[1] = deathStar.color[2] = 0.7;
    deathStar.radius = 1.0;
    deathStar.velocity = 0.10;
    deathStar.satellites = 2;
    deathStar.angularSpeed = 0.1;
    deathStar.alpha = 1;
    
    planetList[0] = mercury;
    planetList[1] = venus;
    planetList[2] = earth;
    planetList[3] = mars;
    planetList[4] = jupiter;
    planetList[5] = saturn;
    planetList[6] = deathStar;
}

void generateStars() {
    for (int i = 0; i < numStars; i++) {
        stars[i][0] = (rand() % 2200-1000) *0.01;
        stars[i][1] = (rand() % 2200-1000) *0.01;
        stars[i][2] = (rand() % 100) * 0.01;
    }
}


void setup() {
    glShadeModel (GL_SMOOTH);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    
}

void init(void) {
    generatePlanets();
    generateStars();
    setup();
}

void drawStars() {
    glPointSize(2.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < numStars; i++) {
        glColor3f(stars[i][2] * starColor, stars[i][2] * starColor, stars[i][2] * starColor);
        glVertex3f(stars[i][0], stars[i][1], -2);
    }
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
    
    GLfloat colorAmbient[] = {0.8, 0.8, 0.8, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, colorAmbient);
    GLfloat lightColor[] = {0.6f, 0.6f, 0.6f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos[] = {0.0f, 0.0f, 0.0f, 1.0f}; //Positioned at (0, 0, 0)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    glPushMatrix();
    drawStars();
    glPopMatrix();
    
    //draw Sun
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glutSolidSphere(2, 39, 78); //Sun
    glPopMatrix();
    
    //draw asteroid
    glPushMatrix();
           planetAlpha = ellipseOrbit / 180 * PI;
           sinalpha = sin(planetAlpha);
           cosalpha = cos(planetAlpha);
           
           offsetX = x + (a * cosalpha * cosbeta - b * sinalpha * sinbeta) *0.2;
           offsetY = y + (a * cosalpha * sinbeta + b * sinalpha * cosbeta) *0.2;
           offsetZ = z + (a * cosalpha * sinbeta + b * sinalpha * cosbeta) *0.2;
           
           glRotatef(45, 0, 0, 1);
           glTranslatef(offsetX, 0.0, offsetZ);
           glColor3f(0.5, 0.35, 0.05);
           glutSolidSphere(0.5 , 13, 26);
    glPopMatrix();
    
    //draw Planets
    for (int i = 0; i < numPlanets; i++) {
        glPushMatrix();
            glRotatef(planetList[i].angle, 0, 0, 1);    // rotate about sun
            glTranslatef(planetList[i].distFromRef, 0, 0);
            glColor4fv(planetList[i].color);
            glRotatef(planetList[i].rotation, 0, 0, 1);    // rotate about own axis
            if  (i == 6) {
                glutSolidSphere(planetList[i].radius, 13, 26);
                glColor4f(0.5, 0.5, 0.5, 1);
                glutWireSphere(planetList[i].radius+0.01, 13, 26);
                glPushMatrix();
                    glRotatef(90, 0, 0.5, 0);
                    glColor4f(0.2, 0.2, 0.2, 1);
                    glutSolidTorus(0.4, 0.7, 3, 26);
                glPopMatrix();
                glTranslatef(0.5, 0.3, 0.3);
                glColor4f(0.2, 0.2, 0.2, 1);
            } else {
                glutSolidSphere(planetList[i].radius, 13, 26);
            }
        
        // draw Satellites
        for (int j = 0; j < planetList[i].satellites; j++) {
            glRotatef(satellites.angle/2, 0, 0, 1);    // rotate about planet
            glPushMatrix();
            if (i == 6) {
                glTranslatef(offsetX, 0, offsetZ);
                glColor3f(0.8, 0.8, 0.8);
                glutWireSphere(0.2, 13, 26);
            } else {
                glTranslatef(satellites.distFromPlanet, 0, 0);
                glColor3f(satellites.color[0], satellites.color[1], satellites.color[2]);
                glutSolidSphere(satellites.radius, 13, 26);
            }
                glColor3f(satellites.color[0], satellites.color[1], satellites.color[2]);
                glutSolidSphere(satellites.radius, 13, 26);
            glPopMatrix();
        }
        
        glPopMatrix();
    }
    
    glPopMatrix();
    glFlush ();
}

/** default animation of solar system **/
void animateSolarSystem() {
    for (int i = 0; i < numPlanets-1; i++) {
        planetList[i].angle += planetList[i].velocity;
        planetList[i].rotation += 0.02 * planetList[i].angularSpeed;
        if (planetList[i].angle > 360.0)
        {
            planetList[i].angle = planetList[i].angle - 360.0;
        }
    }
}

/** method to create working clock **/
void animateTime() {
    time_t seconds = time (NULL);
    struct tm * timeinfo = localtime(&seconds);
    double angleSec = 360 - (float)timeinfo -> tm_sec/60 * 360;
    double angleMin = 360 - (float)timeinfo -> tm_min/60 * 360;
    double angleHour = 360 - (float)timeinfo -> tm_hour/12 * 360;
    
    float diffSecA = angleSec - planetList[secHandA].angle + 90;
    float diffMinA = angleMin - planetList[minHandA].angle + 90;
    float diffHourA = angleHour - planetList[hourHandA].angle + 90;
    float diffSecB = angleSec - planetList[secHandB].angle + 90;
    float diffMinB = angleMin - planetList[minHandB].angle + 90;
    float diffHourB = angleHour - planetList[hourHandB].angle + 90;
    
    for (int i = 0; i < numPlanets; i++) {
        switch (i) {
            case secHandA:
                planetList[i].angle += diffSecA;
                break;
            case secHandB:
                planetList[i].angle += diffSecB;
                break;
            case minHandA:
                planetList[i].angle += diffMinA;
                break;
            case minHandB:
                planetList[i].angle += diffMinB;
                break;
            case hourHandA:
                planetList[i].angle += diffHourA;
                break;
            case hourHandB:
                planetList[i].angle += diffHourB;
                break;
            default:
                break;
        }
    }
}

void idle()
{
    if(toggleTime == 1) {
        animateTime();
    } else {
        animateSolarSystem();
    }
    
    starColor = (rand() % 100 * 0.01) + (rand() % 1000 * 0.001);
    
    ellipseOrbit += (360 / steps)*0.5;
    if(ellipseOrbit >= 360)
    {
        ellipseOrbit = 0;
    }
    planetList[6].angle += planetList[6].velocity;
    planetList[6].rotation += 0.02 * planetList[6].angularSpeed;
    satellites.angle += satellites.velocity;
    if (planetList[6].angle > 360.0)
    {
        planetList[6].angle = planetList[6].angle - 360.0;
    }


    
    glutSwapBuffers();
    glutPostRedisplay();    //after updating, draw the screen again
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
            
        case 'o':
            toggleTime = 1;
            glutPostRedisplay();
            break;
            
        case 'p':
            toggleTime = 0;
            glutPostRedisplay();
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
    cout<<"CS3241 Lab 2\n\n";
    cout<<"+++++CONTROL BUTTONS+++++++\n\n";
    cout<<"Scale Up/Down: Q/E\n";
    cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
    cout<<"Move Up/Down: W/S\n";
    cout<<"Move Left/Right: Z/C\n";
    cout <<"ESC: Quit\n";
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (50, 50);
    glutCreateWindow (argv[0]);
    init ();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    //glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    
    return 0;
}
