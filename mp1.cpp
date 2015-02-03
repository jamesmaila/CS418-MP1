/* James Maila
 * CS418 - Spring 2015
 * 
 * MP1: Dancing I
 */ 

#include <math.h>
#include <GL/glut.h>

#define FPS 60 

float angle;
bool paused;
bool wired;

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

    // color orange
    glColor3f(1.0, 0.5, 0.0);

    float a = 0.025 * sin(angle);
    float b = 0.025 * cos(angle);

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(-0.1,  0.3 + b);           // #1
        glVertex2f(-0.3 - b,  0.3 + a);       // #2
        glVertex2f(-0.3 - b,  0.5 - a);       // #3
        glVertex2f( 0.3 + b,  0.5 + a);       // #4
        glVertex2f( 0.1,  0.3 + b);           // #6
        glVertex2f( 0.1, -0.3 + b);           // #7
        glVertex2f(-0.1, -0.3 + b);           // #12
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f( 0.3 + b, -0.5 - a);       // #9
        glVertex2f( 0.3 + b, -0.3);           // #8
        glVertex2f( 0.1, -0.3 + b);           // #7
        glVertex2f(-0.1, -0.3 + b);           // #12
        glVertex2f(-0.3 - b, -0.5 + a);       // #10
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.3 - b, -0.5 + a);       // #10
        glVertex2f(-0.3 - b, -0.3);           // #11
        glVertex2f(-0.1, -0.3 + b);           // #12

        glVertex2f( 0.3 + b, 0.5 + a);        // #4
        glVertex2f( 0.3 + b, 0.3 + a);        // #5
        glVertex2f( 0.1, 0.3 + b);            // #6
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
        glColor3f(0.0, 0.0, 0.0);
        glVertex2f(-1.0,  1.0);
        glVertex2f(-1.0, -1.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(1.0, -1.0);
        glVertex2f(1.0, 1.0);
    glEnd();
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

    // gradient background first
    DrawBackground();

    // orange I on top of gradient background
    DrawI();

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
    if (!paused) { angle += .15; }

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
