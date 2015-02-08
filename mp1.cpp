/* James Maila
 * CS418 - Spring 2015
 * 
 * MP1: Dancing I
 */ 

#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

#define FPS 60
#define FONT GLUT_BITMAP_TIMES_ROMAN_24

float angle;
bool paused;
bool wired;

int frameCount = 0;
float fps;
int previousTime;


/*
 * DrawI
 *     Inputs: None.
 *     Returns: None.
 *     Description: Creates the vertices that make up
 *                  the block I. The points are mapped below.
 *                  Also offsets the positions with respect to
 *                  time using sinusoidal functions.
 *
 *           3__________________4
 *          |                   |
 *          |2______1   6______5|
 *                  |   |
 *                  |   |
 *                  |   |
 *                  |   |
 *           11___12|   |7______8
 *          |                   |
 *          |10_________________|9
 *
 */
void DrawI()
{
    // if wired state, apply line polygon mode
    if (wired) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

    float a = 0.025 * sin(angle);
    float b = 0.025 * cos(angle);

    glRotatef(angle, 0.0, 0.0, 1.0);

    // top left triangle fan
    glBegin(GL_TRIANGLE_FAN);
    {
        wired ? glColor3f(1.0, 0.5, 0.0) : glColor3f(0.8, 0.3, 0.0);
            glVertex2f(-0.1,  0.3 + b);           // #1

        wired ? glColor3f(1.0, 0.5, 0.0) : glColor3f(1.0, 0.5, 0.0);
            glVertex2f(-0.3 - b,  0.3 + a);       // #2
            glVertex2f(-0.3 - b,  0.5 - a);       // #3

        wired ? glColor3f(1.0, 0.5, 0.0) : glColor3f(0.0, 0.0, 0.0);
            glVertex2f( 0.3 + b,  0.5 + a);       // #4

        wired ? glColor3f(1.0, 0.5, 0.0) : glColor3f(0.6, 0.15, 0.0);
            glVertex2f( 0.1,  0.3 + b);           // #6
            glVertex2f( 0.1, -0.3 + b);           // #7

        wired ? glColor3f(1.0, 0.5, 0.0) : glColor3f(0.8, 0.3, 0.0);
            glVertex2f(-0.1, -0.3 + b);           // #12
    }
    glEnd();

    // bottom-right triangle fan
    glBegin(GL_TRIANGLE_FAN);
    {
        wired ? glColor3f(1.0, 0.5, 0.0) : glColor3f(0.0, 0.0, 0.0);
            glVertex2f( 0.3 + b, -0.5 - a);       // #9
            glVertex2f( 0.3 + b, -0.3);           // #8

        wired ? glColor3f(1.0, 0.5, 0.0) : glColor3f(0.6, 0.15, 0.0);
            glVertex2f( 0.1, -0.3 + b);           // #7

        wired ? glColor3f(1.0, 0.5, 0.0) : glColor3f(0.8, 0.3, 0.0);
            glVertex2f(-0.1, -0.3 + b);           // #12

        wired ? glColor3f(1.0, 0.5, 0.0) : glColor3f(1.0, 0.5, 0.0);
            glVertex2f(-0.3 - b, -0.5 + a);       // #10
    }
    glEnd();

    // last two missing triangles (top-right and bottom-left)
    glBegin(GL_TRIANGLES);
    {
        wired ? glColor3f(1.0, 0.5, 0.0) : glColor3f(1.0, 0.5, 0.0);
            glVertex2f(-0.3 - b, -0.5 + a);       // #10
            glVertex2f(-0.3 - b, -0.3);           // #11

        wired ? glColor3f(1.0, 0.5, 0.0) : glColor3f(0.8, 0.3, 0.0);
            glVertex2f(-0.1, -0.3 + b);           // #12

        wired ? glColor3f(1.0, 0.5, 0.0) : glColor3f(0.0, 0.0, 0.0);
            glVertex2f( 0.3 + b, 0.5 + a);        // #4
            glVertex2f( 0.3 + b, 0.3 + a);        // #5

        wired ? glColor3f(1.0, 0.5, 0.0) : glColor3f(0.6, 0.15, 0.0);
            glVertex2f( 0.1, 0.3 + b);            // #6
    }
    glEnd();

    // border around I
    glBegin(GL_LINE_LOOP);
    {
        wired ? glColor3f(1.0, 0.5, 0.0) : glColor3f(0.0, 0.0, 0.0);
        glVertex2f(-0.1,  0.3 + b);           // #1
        glVertex2f(-0.3 - b,  0.3 + a);       // #2
        glVertex2f(-0.3 - b,  0.5 - a);       // #3
        glVertex2f( 0.3 + b,  0.5 + a);       // #4
        glVertex2f( 0.3 + b, 0.3 + a);        // #5
        glVertex2f( 0.1,  0.3 + b);           // #6
        glVertex2f( 0.1, -0.3 + b);           // #7
        glVertex2f( 0.3 + b, -0.3);           // #8
        glVertex2f( 0.3 + b, -0.5 - a);       // #9
        glVertex2f(-0.3 - b, -0.5 + a);       // #10
        glVertex2f(-0.3 - b, -0.3);           // #11
        glVertex2f(-0.1, -0.3 + b);           // #12
    }
    glEnd();

}

/*
 * DrawBackground
 *     Inputs: None.
 *     Outputs: None.
 *     Description: Creates a gradient black to blue background.
 */
void DrawBackground()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_QUADS);
    {
        glColor3f(0.0, 0.0, 0.0);
        glVertex2f(-1.0,  1.0);
        glVertex2f(-1.0, -1.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(1.0, -1.0);
        glVertex2f(1.0, 1.0);
    }
    glEnd();
}

/*
 * DrawFPS
 *     Inputs: None.
 *     Outputs: None.
 *     Description: Draws the frames per second to the screen.
 */
void DrawFPS()
{
    // orange
    glColor3f(1.0, 0.5, 0.0);

    // rotate opposite direction to I to keep FPS stationary
    glRotatef(-angle, 0.0, 0.0, 1.0);

    glRasterPos2f(-.75, .75);

    ostringstream stream;
    
    (fps == 0) ? (stream << "Calculating FPS...") 
               : (stream << "FPS: " << fps);

    string fpsString = stream.str();
    int length = fpsString.length();

    for (int i = 0; i < length; i++)
    {
        glutBitmapCharacter(FONT, fpsString[i]);
    }
}

/*
 * CalculateFPS
 *     Inputs: None.
 *     Outputs: None.
 *     Description: Calculates the running frames per second.
 */
void CalculateFPS()
{
    frameCount++;
 
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
 
    int timeInterval = currentTime - previousTime;
 
    if (timeInterval > 1000)
    {
        fps = frameCount / (timeInterval/1000.0);
 
        previousTime = currentTime;
 
        frameCount = 0;
    }   
}


/*
 * Display
 *     Inputs: None.
 *     Returns: None.
 *     Description: The Glut display function. 
 *                  Responsible for drawing to the screen.
 */
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    DrawBackground();
    DrawI();
    DrawFPS();

    glFlush();
    glutSwapBuffers();
}

/*
 * Keyboard
 *     Inputs: key - Ascii key pressed.
 *             x - X mouse position when key pressed.
 *             y - Y mouse position when key pressed.
 *     Outputs: None.
 *     Description: The Glut keyboard function.
 *                  Responsible for interpreting keyboard interrupts.
 */
void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        // exposes wires
        case 'w': wired = !wired; break;
        // pauses animation
        case 'p': paused = !paused; break;
        // exits animation
        case 27: exit(0);
    }
}

/*
 * Timer
 *     Inputs: v - Value of the glutTimerFunc value parameter.
 *     Outputs: None.
 *     Description: The Glut timer function. 
 *                  Responsible for synchronizing our animation.
 */
void Timer(int v)
{
    if (!paused)
    { 
        angle += .15; 
        CalculateFPS();
    }

    glutPostRedisplay();
    glutTimerFunc(1000/FPS, Timer, v);
}

int main(int argc, char** argv)
{
    // initialize glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // create window
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("MP1: Dancing I");

    // map display, keyboard, and timer glut functions
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glutTimerFunc(100, Timer, FPS);

    glutMainLoop();

    return 0;
}
