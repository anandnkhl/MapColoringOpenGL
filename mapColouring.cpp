#include<iostream>
#include<GL/glut.h>
#include<string.h>
#include <algorithm>

#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4

using namespace std;

int rightClickx, rightClicky;
int R = 0, G = 0, B = 0, cityCount = 0;

void floodFill(int, int);
void makeCity(int,int);
int createGLUTMenus();

void Init(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f,0.0f);
	gluOrtho2D(0,1050,0,650);
	glFlush();
}

void mouse(int button, int press, int mx, int my){
	if (button == GLUT_LEFT_BUTTON && press == GLUT_DOWN){
		makeCity(mx, 650-my );
		cityCount++;
	}
	else if (button == GLUT_RIGHT_BUTTON && press == GLUT_DOWN){
		rightClickx = mx ;
		rightClicky = 650-my;
		createGLUTMenus();
	}
}

void key( unsigned char key, int x, int y )
{
	if (key == 13) { 
		glutDetachMenu(GLUT_RIGHT_BUTTON);; 
	}
}

void makeCity(int xcenter, int ycenter){
	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
	   glVertex2f(xcenter - 80, ycenter - 40);
	   glVertex2f(xcenter + 80, ycenter - 40);
	   glVertex2f(xcenter + 80, ycenter + 40);
	   glVertex2f(xcenter - 80, ycenter + 40);
	glEnd();
	glFlush();
}

void processMenuEvents(int option) {

float red, green, blue;

	switch (option) {
		case RED :
			cout<<"Red is selected"<<endl;
			R = 0, G = 0, B = 0;
			glColor3f(1,0,0);
			floodFill(rightClickx, rightClicky);
			
			break;
		case GREEN :
			cout<<"Green is selected"<<endl;
			R = 0, G = 0, B = 0;
			glColor3f(0,1,0);
			floodFill(rightClickx, rightClicky);
			//glutDetachMenu(GLUT_RIGHT_BUTTON);
			break;
		case BLUE :
			cout<<"Blue is selected"<<endl;
			R = 0, G = 0, B = 0;
			glColor3f(0,0,1);
			floodFill(rightClickx, rightClicky);
			//glutDetachMenu(GLUT_RIGHT_BUTTON);
			break;
	}
}

int createGLUTMenus() {

	int menu;

	// create the menu and
	// tell glut that "processMenuEvents" will
	// handle the events
	menu = glutCreateMenu(processMenuEvents);
	
	//add entries to our menu
	glutAddMenuEntry("Red",RED);
	glutAddMenuEntry("Green",GREEN);
	glutAddMenuEntry("Blue",BLUE);

	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

return 0;
}

int check(int x2, int y2){
	
	float pixel[4];
	glReadPixels(x2, y2, 1, 1, GL_RGB,  GL_FLOAT, pixel);
	R = (int)pixel[0];
	cout<<"R:"<<(int)pixel[0]<<endl;
	G = (int)pixel[1];
	cout<<"G:"<<(int)pixel[1]<<endl;
	B = (int)pixel[2];
	cout<<"B:"<<(int)pixel[2]<<endl;
	if( R == 0 && G == 0 && B == 0){
		return 1;
	}
	else {return 0;}
}

void floodFill(int x, int y){ //4 connected
	int checkColor = check(x,y);
	cout<<"checkColor:"<<checkColor<<endl;
	if( checkColor == 1){
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
		glFlush();
		int incx= x+1;
		int decx= x-1;
		int incy= y+1;
		int decy= y-1;
		floodFill(incx,y); //Left
		floodFill(x,incy); //Top
		floodFill(decx,y); //Right
		floodFill(x,decy); //Bottom		
	}
}

void myDisplay() {

	glFlush();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);//Initialize window
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); //Single Window
	glutInitWindowSize(1050, 650); //Initialize the size of Window
	glutInitWindowPosition(100, 0); //Initial position of the window
	glutCreateWindow("Map Colouring"); //Name of the Window
	Init();
	glutMouseFunc(mouse);
	glutKeyboardFunc(key);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}