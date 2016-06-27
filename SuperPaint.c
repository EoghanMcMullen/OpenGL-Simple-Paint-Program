#include <GL/gl.h>
#include <GL/glext.h>
#include <C:\Users\mcmulle3\Desktop\Graphics\glut.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#define PI 3.1415926535897932384626433832795

/* 
	I am familiar with the University's policy on plagiarism and 
	that this program is all my own work and I have not copied from any other source.

	BASIC SYSTEM
    ============
	Items Implemented:
		>Points
		>Lines(multiple thickness available)
		>Rectangles
		>Polygons(any size up to 10)
		>Circles		
		>Menu implemented for all of above shapes
		>Colour option available on right click	
		>Clear Screen option available on right click
		
	ADVANCED SYSTEM
    ================
	Items Implemented:	
		>User can select colour from extended palette window
		>Brightness, available on right click on both windows, 
		 the colour palette will change brightness on click
		
	SUPER-ADVANCED SYSTEM
   	=======================
		Items Implemented:
		>Transparency option available on right click in varying intensities
		>this is also functional with the colour palette colours
		
	EXTRA FEATURES
	==============
		Items Implemented:
		> Random colour palette option available, 
*/

//Global Variables
GLfloat r = 1.0,g,b;
GLfloat brightnessController = 0.5;
GLfloat hh;
GLfloat Transparency = 1;
GLfloat colourRandomizerA = 0.0;
GLfloat colourRandomizerB = 0.0;
static int radius = 2;

int color;
int transparentMenu;
int lineThicknessMenu;
int brightnessMenu;
int mainMenu;
int colourMenuID;
int polyMenu;
int polyNumber;

GLint WindowID1, WindowID2;
GLint window2xSize = 400;
GLint window2ySize = 400;

//-------------------------- 

void display(void)
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(3.0);
	glColor3f(1.0,0.0,0.0);

	glFlush();
	return;
}

//Set up default colour palette
void displayColourpalette(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
	glColor3f(brightnessController, colourRandomizerA, colourRandomizerB); // red
	glVertex2f(-1.0, 1.0);
	glColor3f(colourRandomizerA, brightnessController, colourRandomizerB); // green
	glVertex2f(-1.0, -1.0);
	glColor3f(colourRandomizerA, colourRandomizerB, brightnessController); // blue
	glVertex2f(1.0, -1.0);
	glColor3f(brightnessController, brightnessController, brightnessController); // black
	glVertex2f(1.0, 1.0);
	glEnd();
	glutSwapBuffers();
}

//Point Code
//=================================================================
void drawPoint(GLint x0,GLint y0)
{
	glBegin(GL_POINTS);
	glVertex2f(x0, y0);
	glEnd();

	glFlush();
}
//Get point click
void createPoint(GLint button, GLint state, GLint x, GLint y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		GLfloat y0 = hh - y;
		drawPoint(x,y0);
	}
	return;
}
//=================================================================

//Line Code
//================================================================
void drawLine(GLint x0,GLint y0,GLint x01,GLint y01)
{
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x01, y01);
	glEnd();

	glFlush();
}
//get Line clicks
void createLine(GLint button, GLint state, GLint x, GLint y)
{

	static int linePoint = 1;
	static GLfloat x0;
	static GLfloat y0;
	static GLfloat x01;
	static GLfloat y01;

	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		if (linePoint)
		{
			x0 = x;
			y0 = hh - y;
		}
		else
		{
			x01 = x;
			y01 = hh - y;
			drawLine(x0,y0,x01,y01);
		}
		linePoint = !linePoint;
	}
	return;
}
//===============================================================

//Rectangle Code
//================================================================
void drawRec(GLint x0,GLint y0,GLint x01,GLint y01)
{
	glBegin(GL_POLYGON);
	glVertex2f(x0, y0);
	glVertex2f(x0, y01);
	glVertex2f(x01, y01);
	glVertex2f(x01, y0);
	
	glEnd();
	glFlush();
}
//Get rectangle clicks
void createRec(GLint button, GLint state, GLint x, GLint y)
{
	static int first=1;
	
	static GLfloat x0;
	static GLfloat y0;
	static GLfloat x01;
	static GLfloat y01;

	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		if (first)
		{
			x0=x; 
			y0=hh-y;
		}
		else
		{
			x01=x;
			y01=hh-y;
			drawRec(x0,y0,x01,y01);
		}
		first = !first;
	}

	return;
}
//Triangle Code
//===============================================================
void drawTriangle(GLint x0,GLint y0,GLint x01,GLint y01,GLint x02,GLint y02)
{
	glBegin(GL_TRIANGLES);
	glVertex2i(x0, y0);
	glVertex2i(x01, y01);
	glVertex2i(x02, y02);

	glEnd();
	glFlush();
}
//get triangle clicks
void createTriangle(GLint button, GLint state, GLint x, GLint y)
{
	static int triangleClick = 1;
	
	static GLfloat x0;
	static GLfloat y0;
	static GLfloat x01;
	static GLfloat y01;
	static GLfloat x02;
	static GLfloat y02;

	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		if (triangleClick == 1)
		{
			x0 = x;
			y0 = hh - y;
			triangleClick++;
			//first = !first;
		}
		else if (triangleClick == 2)
		{
			x01 = x;
			y01 = hh - y;
			triangleClick++;
			//second = !second;
		}
		else if (triangleClick == 3)
		{
			x02 = x;
			y02 = hh - y;
			drawTriangle(x0,y0,x01,y01,x02,y02);
			triangleClick = 1;
		}		
	}
	return;
}
//=================================================================

//Cirlce code
//=================================================================
//Need to include math library for this
void drawCircle(GLint circleX1,GLint circleY1,GLint circleX2,GLint circleY2)
{
	int circleDefinition = 35;
	
	float x = circleX1 - circleX2;
	float y = circleY1 - circleY2;
	
	//distance formulae:
	float radius = sqrt( (x*x) + (y*y) );
	
	glBegin(GL_TRIANGLE_FAN);
	
	int count = 0;
	
	while(count < circleDefinition)
	{
		//get angle
		float t = 2.0f * PI * (float) count / (float) circleDefinition;
		float x0 = radius * cosf(t);
		float y0 = radius * sinf(t);
		
		glVertex2f(x0 + circleX1, y0 + circleY1);
		
		count++;
	}
	
	glEnd();
	glFlush();
}
//get circle clicks
void createCircle(GLint button, GLint state, GLint x, GLint y)
{
	//get the two points
	static GLfloat circleX1;
	static GLfloat circleY1;
	static GLfloat circleX2;
	static GLfloat circleY2;
	
	static int linePoint = 1;
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		if (linePoint)
		{
			circleX1 = x;
			circleY1 = hh - y;
		}
		else
		{
			circleX2 = x;
			circleY2 = hh - y;
			drawCircle(circleX1,circleY1,circleX2,circleY2);
		}
		linePoint = !linePoint;
	}

	return;
}
//================================================================
//Polygon code
//================================================================
void drawPolygon(GLint xyValues[] , int count)
{
	
	//printf("%d\n",count);
	int numIterations = 0;
	int xCount = 0;
	int yCount = 1;
	
	glBegin(GL_POLYGON);
	
	while(numIterations < count)
	{
		glVertex2i(xyValues[xCount], xyValues[yCount]);
		xCount += 2;
		yCount += 2;
		numIterations++;
	}
	
	glEnd();
	glFlush();
}
//get desired number of polygon clicks
void createPolygon(GLint button, GLint state, GLint x, GLint y)
{
	static int polygonClick = 1;
	static int count = 0;
	static int xCount = 0;
	static int yCount = 1;
	//20 is the max size we need for the polygons
	static GLint xyValues[20];
	int temp = 0;
	GLint tempVals[20];

	//get all polyNumber clicks of the polygon
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		if(count < polyNumber)
		{
			xyValues[xCount] = x;
			xyValues[yCount] = hh - y;
			count++;
			xCount += 2;
			yCount+=2;
		}
		if(count == polyNumber)
		{
			temp = count;
			count = 0;
			xCount = 0;
			yCount = 1;
			int i = 0;
			while(i < temp*2)
			{
				tempVals[i] = xyValues[i];
				i++;
			}
			memset(xyValues, 0, sizeof(xyValues));
			drawPolygon(tempVals, temp);
		}	
	}
	return;
}
//================================================================

//Color Palette handler
//=================================================================
void clickPallette(GLint button, GLint state, GLint x, GLint y)
{
	static float colourArray[3];
	
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		glReadPixels(x, (window2ySize - y), 1, 1, GL_RGB, GL_FLOAT, colourArray);
	}
	
	//Reference the window to change color on
	glutSetWindow(WindowID1);
	
	r = colourArray[0];
	g = colourArray[1];
	b = colourArray[2];
	
	glColor4f(r, g, b, Transparency);
}

//=================================================================

//Set up menu functions
//=================================================================
void menuHandler(int entry)
{
	switch(entry)
	{
		case 'a':
			glutMouseFunc(createRec);
			break;
		case 'b':
			glClear(GL_COLOR_BUFFER_BIT);
			glFlush();
			break;
		case 'c':
			glutMouseFunc(createPoint);
			break;
		case 'd':
			glutMouseFunc(createTriangle);
			break;
		case 'f':
			glutMouseFunc(createCircle);
			break;
		case 'p':
			glutMouseFunc(createPolygon);
			break;
		//handle random palette colour	
		case 'r':
			glutSetWindow(WindowID2);
			colourRandomizerA = (double)rand() / (double)RAND_MAX;
			colourRandomizerB = (double)rand() / (double)RAND_MAX;
			brightnessController = (double)rand() / (double)RAND_MAX;
			displayColourpalette();
			glFlush();			
			break;
		case 'o':
			glutSetWindow(WindowID2);
			colourRandomizerA = 0.0;
			colourRandomizerB = 0.0;
			brightnessController = 0.5;
			displayColourpalette();
			glFlush();			
			break;
	}
}
//Set up the menu colour chooser
void colorMenuHandler(int entry)
{
	switch (entry)
	{
	case 'r':
		r = 1.0; g = 0.0; b = 0.0;
		glColor4f(r, g, b, Transparency); //red
		break;
	case 'b':
		r = 0.0; g = 0.0; b = 1.0;
		glColor4f(r, g, b, Transparency); //blue
		break;
	case 'g':
		r = 0.0; g = 1.0; b = 0.0;
		glColor4f(r, g, b, Transparency); //green
		break;
	case 'y':
		r = 1.0; g = 1.0; b = 0.0;
		glColor4f(r, g, b, Transparency); //yellow
		break;
	case 'p':
		r = 1.0; g = 0.0; b = 1.0;
		glColor4f(r, g, b, Transparency); //purple
		break;
	case 'c':
		r = 0.0; g = 1.0; b = 1.0;
		glColor4f(r, g, b, Transparency); //cyan
		break;
	case 'w':
		r = 1.0; g = 1.0; b = 1.0;
		glColor4f(r, g, b, Transparency); //white
		break;
	case 'o':
		r = 1.0; g = 0.5; b = 0.0;
		glColor4f(r, g, b,  Transparency); //orange
		break;	
	case 'B':
		r = 0.0; g = 0.0; b = 0.0;
		glColor4f(r, g, b, Transparency); //Black
		break;
	}
}
//Set up the menu Transparency chooser
void transparencyHandler(int entry)
{
	switch (entry)
	{
	case 's':
		Transparency = 0.1;
		glColor4f(r, g, b, Transparency);
		break;
	case 'l':
		Transparency = 0.2;
		glColor4f(r, g, b, Transparency);
		break;
	case 'm':
		Transparency = 0.4;
		glColor4f(r, g, b, Transparency);
		break;
	case 'h':
		Transparency = 0.6;
		glColor4f(r, g, b, Transparency);
		break;
	case 'x':
		Transparency = 0.8;
		glColor4f(r, g, b, Transparency);
		break;
	case 'M':
		Transparency = 1.0;
		glColor4f(r, g, b, Transparency);
		break;		
	}
}
//Set up the menu Transparency chooser
void lineThicknesshandler(int entry)
{
	switch (entry)
	{
	case '0':
		glLineWidth(1.0);
		glutMouseFunc(createLine);
		break;
	case '1':
		glLineWidth(2.0);
		glutMouseFunc(createLine);
		break;
	case '2':		
		glLineWidth(3.0);
		glutMouseFunc(createLine);
		break;
	case '3':		
		glLineWidth(4.0);
		glutMouseFunc(createLine);
		break;
	case '4':		
		glLineWidth(5.0);
		glutMouseFunc(createLine);
		break;
	case '5':		
		glLineWidth(6.0);
		glutMouseFunc(createLine);
		break;
	case '6':		
		glLineWidth(7.0);
		glutMouseFunc(createLine);
		break;			
	}
}
//Handle brightness selector
void BrightnessHandler(int entry)
{
	switch (entry)
	{
	case '1':	
		glutSetWindow(WindowID2);
		brightnessController = 0.2;
		displayColourpalette();
		glFlush();
		break;
	case '2':
		glutSetWindow(WindowID2);
		brightnessController = 0.3;
		displayColourpalette();
		glFlush();
		break;
	case '3':	
		glutSetWindow(WindowID2);
		brightnessController = 0.4;
		displayColourpalette();
		glFlush();
		break;
	case '4':
		glutSetWindow(WindowID2);
		brightnessController = 0.5;
		displayColourpalette();
		glFlush();
		break;
	case '5':	
		glutSetWindow(WindowID2);
		brightnessController = 0.6;
		displayColourpalette();
		glFlush();
		break;
	case '6':	
		glutSetWindow(WindowID2);
		brightnessController = 0.7;
		displayColourpalette();
		glFlush();
		break;
	case '7':
		glutSetWindow(WindowID2);
		brightnessController = 0.8;
		displayColourpalette();
		glFlush();
		break;
	case '8':
		glutSetWindow(WindowID2);
		brightnessController = 0.9;
		displayColourpalette();
		glFlush();		
		break;	
	case '9':	
		glutSetWindow(WindowID2);
		brightnessController = 0.95;
		displayColourpalette();
		glFlush();
		break;	
	case 'T':
		glutSetWindow(WindowID2);
		brightnessController = 1.0;
		displayColourpalette();	
		glFlush();
		break;			
	}	
}
//Polygon size handler
void polyHandler(int entry)
{
	switch (entry)
	{
	case '5':		
		polyNumber = 5;
		glutMouseFunc(createPolygon);
		break;
	case '6':		
		polyNumber = 6;
		glutMouseFunc(createPolygon);
		break;
	case '7':		
		polyNumber = 7;
		glutMouseFunc(createPolygon);
		break;
	case '8':		
		polyNumber = 8;	
		glutMouseFunc(createPolygon);
		break;	
	case '9':		
		polyNumber = 9;
		glutMouseFunc(createPolygon);
		break;	
	case 'T':		
		polyNumber = 10;
		glutMouseFunc(createPolygon);
		break;			
	}	
}

//Call when window is reshaped
void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLfloat)w,0.0,(GLfloat)h);
	glViewport(0,0,w,h);
	hh=h;
	return;
}

//This makes the colour window a static size
void colorPaletteReshape(GLsizei w, GLsizei h)
{
	glutReshapeWindow( window2xSize, window2ySize);
	return;
}
int main(int argc, char **argv)
{
	//seed randomizer for random palette
	srand(time(NULL));
	
	glutInit(&argc, argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(500,200);
	WindowID1 = glutCreateWindow("Super Paint");
	
	//Transparency enabled
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutMouseFunc(createPoint);

	//set up color menu
	//=====================================================
	color = glutCreateMenu(colorMenuHandler);
	glutAddMenuEntry("Red", 'r');
	glutAddMenuEntry("Blue", 'b');
	glutAddMenuEntry("Green", 'g');
	glutAddMenuEntry("Yellow", 'y');
	glutAddMenuEntry("Purple", 'p');
	glutAddMenuEntry("Cyan", 'c');
	glutAddMenuEntry("White", 'w');
	glutAddMenuEntry("Orange", 'o');
	glutAddMenuEntry("Black", 'B');
	//======================================================

	//set up Transparency
	//=====================================================
	transparentMenu = glutCreateMenu(transparencyHandler);
	glutAddMenuEntry("Xtra high", 's');
	glutAddMenuEntry("Very High", 'l');
	glutAddMenuEntry("Medium", 'm');
	glutAddMenuEntry("Light", 'h');
	glutAddMenuEntry("Very light", 'x');
	glutAddMenuEntry("None", 'M');
	//======================================================
	
	//Set up line thickness selector
	//=======================================================
	lineThicknessMenu = glutCreateMenu(lineThicknesshandler);
	glutAddMenuEntry("Thickness: 1", '0');
	glutAddMenuEntry("Thickness: 2", '1');
	glutAddMenuEntry("Thickness: 3", '2');
	glutAddMenuEntry("Thickness: 4", '3');
	glutAddMenuEntry("Thickness: 5", '4');
	glutAddMenuEntry("Thickness: 6", '5');
	glutAddMenuEntry("Thickness: 7", '6');
	//========================================================
	
	//Set up Polygon size selector
	//=======================================================
	polyMenu = glutCreateMenu(polyHandler);
	glutAddMenuEntry("5 sides", '5');
	glutAddMenuEntry("6 sides", '6');
	glutAddMenuEntry("7 sides", '7');
	glutAddMenuEntry("8 sides", '8');
	glutAddMenuEntry("9 sides", '9');
	glutAddMenuEntry("10 sides", 'T');
	//========================================================
	
		//Brightness Selector
	//=================================================
	brightnessMenu = glutCreateMenu(BrightnessHandler);
	glutAddMenuEntry("1", '1');
	glutAddMenuEntry("2", '2');
	glutAddMenuEntry("3", '3');
	glutAddMenuEntry("4", '4');
	glutAddMenuEntry("5", '5');
	glutAddMenuEntry("6", '6');
	glutAddMenuEntry("7", '7');
	glutAddMenuEntry("8", '8');
	glutAddMenuEntry("9", '9');
	glutAddMenuEntry("10", 'T');
	//=================================================
	
	//Set main Menu
	mainMenu = glutCreateMenu(menuHandler);
	glutAddMenuEntry("Point", 'c');
	glutAddSubMenu("Line", lineThicknessMenu);
	glutAddMenuEntry("Rectangle", 'a');
	glutAddMenuEntry("Circle", 'f');
	glutAddMenuEntry("Triangle", 'd');
	glutAddSubMenu("Polygon", polyMenu);
	glutAddSubMenu("Colors", color);
	glutAddSubMenu("Trasparency",transparentMenu);
	glutAddSubMenu("Brightness", brightnessMenu);
	glutAddMenuEntry("Random Palette", 'r');
	glutAddMenuEntry("Original Palette", 'o');
	glutAddMenuEntry("Clear", 'b');
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//Create the Color Pallette Window
	//glutInit(&argc, argv);
	glutInitWindowSize(window2xSize, window2ySize);
	glutInitWindowPosition(0, 400);
	WindowID2 = glutCreateWindow("Colour Palette");
	glutReshapeFunc(colorPaletteReshape);
	glutDisplayFunc(displayColourpalette);
	glutMouseFunc(clickPallette);
	
	//Colour Palette right click menu
	//=================================================
	colourMenuID = glutCreateMenu(menuHandler);
	glutAddSubMenu("Brightness", brightnessMenu);
	glutAddMenuEntry("Random Palette", 'r');
	glutAddMenuEntry("Original Palette", 'o');
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutMainLoop();
}

//gcc Superpaint.c -o SuperPaint glut32.lib -lopengl32 -lglu32
