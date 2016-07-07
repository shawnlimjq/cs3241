    // CS3241Lab4.cpp : Defines the entry point for the console application.
    //#include <cmath>
    #include "math.h"
    #include <iostream>
    #include <fstream>

    /* Include header files depending on platform */
    #ifdef _WIN32
        #include "glut.h"
        #define M_PI 3.14159
    #elif __APPLE__
        #include <OpenGL/gl.h>
        #include <GLUT/GLUT.h>
    #endif

    #define MAXPTNO 1000
    #define NLINESEGMENT 32
    #define NOBJECTONCURVE 8
    #define PI 3.14159

    using namespace std;

    // Global variables that you can use
    struct Point {
        int x,y;
    };

    // Storage of control points
    int nPt = 0;
    Point ptList[MAXPTNO];
    Point ptC1List[MAXPTNO];

    // Display options
    bool displayControlPoints = true;
    bool displayControlLines = true;
    bool displayTangentVectors = false;
    bool displayObjects = false;
    bool C1Continuity = false;
    bool displayBezierCurve = true;
    bool displayAnimation = false;

    bool animationChange = true;

    void drawRightArrow()
    {
        glColor3f(0,1,0);
        glBegin(GL_LINE_STRIP);
            glVertex2f(0,0);
            glVertex2f(100,0);
            glVertex2f(95,5);
            glVertex2f(100,0);
            glVertex2f(95,-5);
        glEnd();
    }

    void drawBezierCurve() {
        for (int i = 0; i <= nPt-4; i+=3) {
            
            Point p1 = ptList[i];
            Point p2 = ptList[i + 1];
            Point p3 = ptList[i + 2];
            Point p4 = ptList[i + 3];
            
            if(i - 2 > 0 && C1Continuity) {
                Point tempP3 = ptList[i - 1];
                p2.x = 2*p1.x - tempP3.x;
                p2.y = 2*p1.y - tempP3.y;
                ptC1List[i + 1] = p2;
            }
            
            glBegin(GL_LINE_STRIP);
            for(int j = 0; j < NLINESEGMENT + 1; j++) {
                float t = j/32.0;
                float ctrlX = pow((1 - t), 3)*p1.x + 3*pow((1 - t), 2)*pow(t, 1)*p2.x + 3*pow((1 - t), 1)*pow(t, 2)*p3.x + pow(t, 3)*p4.x;
                float ctrlY = pow((1 - t), 3)*p1.y + 3*pow((1 - t), 2)*pow(t, 1)*p2.y + 3*pow((1 - t), 1)*pow(t, 2)*p3.y + pow(t, 3)*p4.y;
                if (displayAnimation) {
                    if (animationChange) {
                        if (j % 2) {
                             glColor3f(0, 0, 0);
                        } else {
                             glColor3f(1, 1, 1);
                        }
                    } else {
                        if (j % 2) {
                            glColor3f(1, 1, 1);
                            
                        } else {
                            glColor3f(0, 0, 0);
                        }

                    }
                    for (int i = 0; i <= 360; i++)   {
                        glVertex2f ((ctrlX+ (1 * cos(i * 2 * PI / 360))), (ctrlY + (1 * sin(i * 2 * PI / 360))));
                    }
                } else {
                    glColor3f(0, 0, 1);
                }
                glVertex2d(ctrlX, ctrlY);
            }
            glEnd();
        }
    }

    void drawCar() {
        glColor3f(0.7, 0.7, 0.7);
        glBegin(GL_POLYGON);
            glVertex2f(-13, 15);
            glVertex2f(-13, 5);
            glVertex2f(13, 5);
            glVertex2f(13, 15);
        glEnd();
        glColor3f(0.7, 0.7, 0.7);
        glBegin(GL_POLYGON);
            glVertex2f(-8, 20);
            glVertex2f(-8, 15);
            glVertex2f(8, 15);
            glVertex2f(8, 20);
        glEnd();
        glBegin(GL_TRIANGLE_FAN); // begin circle
        for (int i = 0; i <= 360; i++)   {
            glColor3f(0, 0, 0);
            glVertex2f ((6 + (3 * cos(i * 2 * PI / 360))), (2.5 + (3 * sin(i * 2 * PI / 360))));
        }
        glEnd();
        glBegin(GL_TRIANGLE_FAN); // begin circle
        for (int i = 0; i <= 360; i++)   {
            glColor3f(0, 0, 0);
            glVertex2f ((-6 + (3 * cos(i * 2 * PI / 360))), (2.5 + (3 * sin(i * 2 * PI / 360))));
        }
        glEnd();
    }


    void display(void)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        
        if(displayBezierCurve) {
            drawBezierCurve();
        }

        if(displayControlPoints)
        {

            glPointSize(5);
            glBegin(GL_POINTS);
            for(int i=0;i<nPt; i++)
            {
                if (C1Continuity) {
                    if (i > 3 && i%3 == 1) {
                        glColor3f(1,0,0);
                        glVertex2d(ptC1List[i].x,ptC1List[i].y);
                        glColor3f(0.8,0.8,0.8);
                        glVertex2d(ptList[i].x,ptList[i].y);
                    } else {
                        glColor3f(0,0,0);
                        glVertex2d(ptList[i].x,ptList[i].y);
                    }
                } else {
                    glColor3f(0,0,0);
                    glVertex2d(ptList[i].x,ptList[i].y);
                }
            }
            glEnd();
            glPointSize(1);

        }

        if(displayControlLines)
        {
            glBegin(GL_LINE_STRIP);
            for(int i = 0; i < nPt-1; i++) {
                if (C1Continuity) {
                    glColor3f(0,1,0);
                    glVertex2d(ptC1List[i].x,ptC1List[i].y);
                    glVertex2d(ptC1List[i+1].x,ptC1List[i+1].y);
                } else {
                    glColor3f(0,1,0);
                    glVertex2d(ptList[i].x,ptList[i].y);
                    glVertex2d(ptList[i+1].x,ptList[i+1].y);
                }
            }
            glEnd();
        }
        
        for(int i = 3; i < nPt; i += 3) {
            for(float j = 0; j < NOBJECTONCURVE+1; j++) {
                
                Point p1 = ptList[i];
                Point p2 = ptList[i - 1];
                Point p3 = ptList[i - 2];
                Point p4 = ptList[i - 3];
                
                if (C1Continuity) {
                    p1 = ptC1List[i];
                    p2 = ptC1List[i - 1];
                    p3 = ptC1List[i - 2];
                    p4 = ptC1List[i - 3];
                }
                
                float t = j/NOBJECTONCURVE;
                
                float ctrlX = pow((1 - t), 3)*p4.x + 3*pow((1 - t), 2)*pow(t, 1)*p3.x + 3*pow((1 - t), 1)*pow(t, 2)*p2.x + pow(t, 3)*p1.x;
                float ctrlY = pow((1 - t), 3)*p4.y + 3*pow((1 - t), 2)*pow(t, 1)*p3.y + 3*pow((1 - t), 1)*pow(t, 2)*p2.y + pow(t, 3)*p1.y;
                
                float tx = 3*((p3.x - p4.x) + (t*((2*p2.x) - (4*p3.x) + (2*p4.x))) + (pow(t, 2)*(p1.x - (3*p2.x) + (3*p3.x) - p4.x)));
                float ty = 3*((p3.y - p4.y) + (t*((2*p2.y) - (4*p3.y) + (2*p4.y))) + (pow(t, 2)*(p1.y - (3*p2.y) + (3*p3.y) - p4.y)));
                
                float angle = 180 * atan2(ty, tx) / PI;
                
                glPushMatrix();
        
                glTranslatef(ctrlX, ctrlY, 0);
                glRotatef(angle, 0, 0, 1);
                
                if (displayTangentVectors) {
                    drawRightArrow();
                }
                
                if(displayObjects) {
                    drawCar();
                }
                
                glPopMatrix();
            }
        }
        
        
        glPopMatrix();
        glutSwapBuffers ();
    }

    void reshape (int w, int h)
    {
        glViewport (0, 0, (GLsizei) w, (GLsizei) h);
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0,w,h,0);  
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
    }

    void init(void)
    {
        glEnable (GL_LINE_SMOOTH);
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
        glLineWidth (5);
        
        glClearColor (0, 0, 0, 1.0);
    }

    void readFile()
    {

        std::ifstream file;
        file.open("savefile.txt");
        file >> nPt;

        if(nPt>MAXPTNO)
        {
            cout << "Error: File contains more than the maximum number of points." << endl;
            nPt = MAXPTNO;
        }

        for(int i=0;i<nPt;i++)
        {
            file >> ptList[i].x;
            file >> ptList[i].y;
        }
        file.close();// is not necessary because the destructor closes the open file by default
    }

    void clearAll() {
        nPt = 0;
    }

    void writeFile()
    {
        std::ofstream file;
        file.open("savefile.txt");
        file << nPt << endl;

        for(int i=0;i<nPt;i++)
        {
            file << ptList[i].x << " ";
            file << ptList[i].y << endl;
        }
        file.close();// is not necessary because the destructor closes the open file by default
    }

    void animate(int value) {
        if(animationChange == true) {
            animationChange = false;
        } else {
            animationChange = true;
        }
        
        glutPostRedisplay();
        glutTimerFunc(500, animate, 0);
    }

    void keyboard (unsigned char key, int x, int y)
    {
        switch (key) {
            case 'a':
            case 'A':
                displayAnimation = !displayAnimation;
                break;
            
            case 'r':
            case 'R':
                readFile();
            break;

            case 'w':
            case 'W':
                writeFile();
            break;

            case 'T':
            case 't':
                displayTangentVectors = !displayTangentVectors;
            break;

            case 'o':
            case 'O':
                displayObjects = !displayObjects;
            break;

            case 'p':
            case 'P':
                displayControlPoints = !displayControlPoints;
            break;

            case 'L':
            case 'l':
                displayControlLines = !displayControlLines;
            break;

            case 'C':
            case 'c':
                C1Continuity = !C1Continuity;
            break;

            case 'e':
            case 'E':
                clearAll();
            break;

            case 27:
                exit(0);
            break;

            default:
            break;
        }

        glutPostRedisplay();
    }

    void mouse(int button, int state, int x, int y)
    {
        /*button: GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON */
        /*state: GLUT_UP or GLUT_DOWN */
        enum
        {
            MOUSE_LEFT_BUTTON = 0,
            MOUSE_MIDDLE_BUTTON = 1,
            MOUSE_RIGHT_BUTTON = 2,
            MOUSE_SCROLL_UP = 3,
            MOUSE_SCROLL_DOWN = 4
        };
        if((button == MOUSE_LEFT_BUTTON)&&(state == GLUT_UP))
        {
            if(nPt==MAXPTNO)
            {
                cout << "Error: Exceeded the maximum number of points." << endl;
                return;
            }
            ptList[nPt].x=x;
            ptList[nPt].y=y;
            ptC1List[nPt].x=x;
            ptC1List[nPt].y=y;
            nPt++;
        }
        glutPostRedisplay();
    }

    int main(int argc, char **argv)
    {
        cout<<"CS3241 Lab 4"<< endl<< endl;
        cout << "Left mouse click: Add a control point"<<endl;
        cout << "ESC: Quit" <<endl;
        cout << "P: Toggle displaying control points" <<endl;
        cout << "L: Toggle displaying control lines" <<endl;
        cout << "E: Erase all points (Clear)" << endl;
        cout << "C: Toggle C1 continuity" <<endl;	
        cout << "T: Toggle displaying tangent vectors" <<endl;
        cout << "O: Toggle displaying objects" <<endl;
        cout << "R: Read in control points from \"savefile.txt\"" <<endl;
        cout << "W: Write control points to \"savefile.txt\"" <<endl;
        glutInit(&argc, argv);
        glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize (600, 600);
        glutInitWindowPosition (50, 50);
        glutCreateWindow ("CS3241 Assignment 4");
        glutDisplayFunc(display);
         glutReshapeFunc(reshape);
        //glutIdleFunc(animate);
        glutTimerFunc(0, animate, 0);
          init();
        glutMouseFunc(mouse);
        glutKeyboardFunc(keyboard);
        glutMainLoop();

        return 0;
    }
