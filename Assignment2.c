#include <GL/gl.h>
#include <GL/glext.h>
#include <H:/graphics/glut.h>
#include <math.h>
#include <stdio.h>

/*
polygons cases:
start
start middle
end middle
end even
end odd

put methods in order of name them all at the start, doesn't work like java
we take y away from hh ( the height ) y is inverted, hh-y always 
change mouse to left click
make a method for each shape
colours RGB and Alpha

*/

GLfloat xx1,xx2,yy1,yy2;
GLfloat hh;
int action;
int mainMenu;
float transparent = 1.0;

//structure for rectangle
void Display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glPointSize(3.0);
	glColor3f(1.0,0.0,0.0);

	glFlush();
	return;
}

void DisplayPoint(){
	glBegin(GL_POINTS);
		glVertex2f(xx1,yy1);
	glEnd();

	glFlush();
	return;
}

void DisplayLine(){
	glBegin(GL_LINES);
		glVertex2f(xx1,yy1);
		glVertex2f(xx2,yy2);
	glEnd();

	glFlush();
	return;
}

void DisplayRectangle(){
	glBegin(GL_POLYGON);
		glVertex2f(xx1,yy1);
		glVertex2f(xx1,yy2);
		glVertex2f(xx2,yy2);
		glVertex2f(xx2,yy1);
	glEnd();

	glFlush();
	return;
}

void DisplayTriangle(){
	glBegin(GL_POLYGON);
		glVertex2f(xx1,yy1);
		glVertex2f(xx1,yy2);
		glVertex2f(xx2,yy2);
		glVertex2f(xx2,yy1);
	glEnd();

	glFlush();
	return;
}

// mouse listener
void MouseDraw(GLint button, GLint state, GLint x, GLint y)
{
	static int first=1;

	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		//Point
		if(action == 0){

			xx1=x; 
			yy1=hh-y;

			DisplayPoint();	
		}
		
		//Line
		if(action == 1){
			
			printf("Line MouseDraw");
			if (first)
			{
				xx1=x; 
				yy1=hh-y;
			}
			else
			{
				xx2=x;
				yy2=hh-y;
				DisplayLine();
			}
			first = !first;
			
		}
		
		// Rectangle
		if(action == 2){
			if (first)
			{
				xx1=x; 
				yy1=hh-y;
			}
			else
			{
				xx2=x;
				yy2=hh-y;
				DisplayRectangle();
			}
			first = !first;
		}
		
	}

	return;
}

void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLfloat)w,0.0,(GLfloat)h);
	glViewport(0,0,w,h);
	hh=h;
	return;
}

void displayColour() {
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glBegin(GL_QUADS);
               glColor3f(0.5f, 0.0f, 1.0f); // make this vertex purple
               glVertex2f(-0.75, 0.75);
               glColor3f(1.0f, 0.0f, 0.0f); // make this vertex red
               glVertex2f(-0.75, -0.75);
               glColor3f(0.0f, 1.0f, 0.0f); // make this vertex green
               glVertex2f(0.75, -0.75);
               glColor3f(1.0f, 1.0f, 0.0f); // make this vertex yellow
               glVertex2f(0.75, 0.75);
       glEnd();
       glutSwapBuffers();
}

void ColourMenu(int op){
	switch(op) {
		case('r'):
		    glColor4f(1.0, 0.0, 0.0, transparent); // red
			break;
		case('g'):
		    glColor4f(0.0, 1.0, 0.0, transparent); // green
			break;
		case('b'):
		    glColor4f(0.0, 0.0, 1.0, transparent); // blue
			break;
	}
}

void menu(int op){
	printf("op: %d", op);
	
	switch(op) {
		case(0):
			printf("Point Menu");
			action = 0; // point
			break;
		case(1):
			printf("Line Menu");
			action = 1; // line
			break;
		case(2):
			printf("Rect Menu");
			action = 2; // rectangle
			break;
		case(3):
			action = 3; // tirangle
			break;
		case(4):
			action = 4; // polygon
			break;
		case(5):
			break;
		case(6):
			glClear(GL_COLOR_BUFFER_BIT); // clear
			glFlush();
	}
}

int main(int argc, char **argv)
{
	// Draw Window
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	mainMenu = glutCreateWindow("Assignment2: Paint");
	glutDisplayFunc(DisplayRectangle);
	glutReshapeFunc(MyReshape);
	glutMouseFunc(MouseDraw);
	
	// Colour Menu
	int colourList = glutCreateMenu(ColourMenu);
	glutAddMenuEntry("Red", 'r');
	glutAddMenuEntry("Green", 'g');
	glutAddMenuEntry("Blue", 'b');
	
	
	// Main Menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Point", 0);
	glutAddMenuEntry("Line", 1);
	glutAddMenuEntry("Rectangle", 2);
	glutAddMenuEntry("Triangle", 3);
	glutAddMenuEntry("Polygon", 4);
	printf("%d",colourList);
	glutAddSubMenu("Colour", colourList);
	glutAddMenuEntry("Clear", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Colour Window
	glutInitWindowPosition(1100,200);
	glutCreateWindow("Colours");
	glutDisplayFunc(displayColour);
	
	glutMainLoop();
}