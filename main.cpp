//TEMPLATE BY: TROY ALDERSON, UNIVERSITY OF CALGARY
//MODIFICATIONS BY: SHANNON TJ 10101385
//CPSC 589, WINTER 2017


#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
using namespace std;

#define PI 3.14159265359

GLFWwindow *window;
int w, h;
double mouseX, mouseY;

float k = 3.f;
float smallR = 1/3.f;
float bigR = k*smallR;

float theta = 0.f;
float theta2 = 0.f;
float theta3 = 0.f;

float scale = 0.7f;
int cycles = 1;

float x = 0.f;
float y = 0.f;

float xNew = 0.f;
float yNew = 0.f;

float xNew2 = 0.f;
float yNew2 = 0.f;

float xRad = 0.f;
float yRad = 0.f;

bool bonus = false;


void reset ()
{
	
		//Reset values
		k = 3.f;
		smallR = 1/3.f;	
		bigR = k*smallR;

		scale = 0.7f;
		theta3 = 0.f;
		theta2 = 0.f;
		theta = 0.f;
		cycles = 1;

		x = 0.f;
		y = 0.f;

		xNew = 0.f;
		yNew = 0.f;
		
		xNew2 = 0.f;
		yNew2 = 0.f;
		
		xRad = 0.f;
		yRad = 0.f;
		
		bonus = false;
}

void render () {
	glEnable (GL_DEPTH_TEST);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Functions for changing transformation matrix
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glTranslatef (0.0f, 0.0f, 0.0f);
	glRotatef (0.0f, 0.0f, 0.0f, 0.0f);
	glScalef (scale, scale, scale);

	//Functions for changing projection matrix
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (-1, 1, -1, 1, -1, 1);
	//gluPerspective (fov, aspect ratio, near plane, far plane)
	//glFrustum


	//LARGE CIRCLE
	glBegin (GL_LINE_STRIP);
	for(float i = 0.f; i <= 100.f; i = i + 0.1f)
	{
		theta = 2.0f*PI*i/100.f;
		xNew = bigR*cos(theta); 
		yNew = bigR*sin(theta);
		
		glColor3f (1.0f, 1.0f, 1.0f);
		glVertex2f (xNew/(bigR),yNew/(bigR));
	}
		glEnd ();
		
	
	if(!bonus)
	{
		//HYPOCYCLOID LINES
		glBegin (GL_LINE_STRIP);
		for(theta = 0.f; theta <= (2*PI*cycles); theta = theta + 0.01f)
		{	
			x = (bigR - smallR)*cos(theta) + smallR*cos(((bigR-smallR)/smallR)*theta);
			y = (bigR - smallR)*sin(theta) - smallR*sin(((bigR-smallR)/smallR)*theta);

			float temp = x;
			x = x*cos(theta2) - y*sin(theta2);
			y = temp*sin(theta2) + y*cos(theta2);
			
			
			glColor3f (1.0f, 0.6f, 0.0f);
			glVertex2f (x/(bigR),y/(bigR));
		}
			glEnd ();
	}

	else if(bonus)
	{
		
		//SMALL CIRCLE
		glBegin (GL_LINE_STRIP);
		for(float i = 0.f; i <= 100.f; i = i + 0.1f)
		{
			theta = 2.0f*PI*i/100.f;
			xNew2 = smallR*cos(theta) + xNew - smallR; 
			yNew2 = smallR*sin(theta) + yNew;
			
			float temp2 = xNew2;
			xNew2 = xNew2*cos(theta2) - yNew2*sin(theta2);
			yNew2 = temp2*sin(theta2) + yNew2*cos(theta2);
			
			temp2 = xNew2;
			xNew2 = xNew2*cos(theta3) - yNew2*sin(theta3);
			yNew2 = temp2*sin(theta3) + yNew2*cos(theta3);
			
			
			glColor3f (1.0f, 1.0f, 1.0f);
			glVertex2f (xNew2/(bigR),yNew2/(bigR));
		}
			glEnd ();
		
		//HYPOCYCLOID LINES
		glBegin (GL_LINE_STRIP); //GL_LINE_STRIP, GL_POINTS, GL_QUADS, etc...
		for(theta = 0.f; theta <= theta3; theta = theta + 0.01f)
		{	
			x = (bigR - smallR)*cos(theta) + smallR*cos(((bigR-smallR)/smallR)*theta);
			y = (bigR - smallR)*sin(theta) - smallR*sin(((bigR-smallR)/smallR)*theta);

			float temp = x;
			x = x*cos(theta2) - y*sin(theta2);
			y = temp*sin(theta2) + y*cos(theta2);
			
			
			glColor3f (1.0f, 0.6f, 0.0f);
			glVertex2f (x/(bigR),y/(bigR));
		}
			glEnd ();
	
	
		//LINE
		glBegin (GL_LINE_STRIP);
		for(float i = 0.f; i <= 1.f; i = i + 0.1f)
		{
			
			theta = PI;
			xRad = x;
			yRad = y;
			
			glColor3f (1.0f, 0.0f, 0.0f);
			glVertex2f (xRad/(bigR),yRad/(bigR));
			
			float temp2 = xRad;
			xRad = xRad*cos(theta2) - yRad*sin(theta2);
			yRad = temp2*sin(theta2) + yRad*cos(theta2);
			
			temp2 = xRad;
			xRad = xRad*cos(theta3) - yRad*sin(theta3);
			yRad = temp2*sin(theta3) + yRad*cos(theta3);
			
			xRad = smallR*cos(theta) + xNew; 
			yRad = smallR*sin(theta) + yNew;
			
			temp2 = xRad;
			xRad = xRad*cos(theta2) - yRad*sin(theta2);
			yRad = temp2*sin(theta2) + yRad*cos(theta2);
			
			temp2 = xRad;
			xRad = xRad*cos(theta3) - yRad*sin(theta3);
			yRad = temp2*sin(theta3) + yRad*cos(theta3);
			
			glColor3f (1.0f, 0.0f, 0.0f);
			glVertex2f (xRad/(bigR),yRad/(bigR));
		}
		glEnd ();
	
	}
	
}


void keyboard (GLFWwindow *sender, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//Increase big circle radius 
		bigR = bigR + 0.2f;
	}
	
	else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//Decrease big circle radius 
		if(bigR > (smallR + 0.2f))
			bigR = bigR - 0.2f;
	}
	
	else if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//Increase small circle radius
		if(smallR < (bigR - 0.2f)) 
			smallR = smallR + 0.2f;
	}
	
	else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//Decrease small circle radius
		smallR = smallR - 0.2f;
	}
	
	else if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//Increase number of cycles
		cycles = ++cycles;
	}
	
	else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//Decrease number of cycles
		if(cycles != 1)
			cycles = --cycles;
	}
	
	else if(key == GLFW_KEY_K && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//Rotate counter-clockwise
		theta2 = theta2 + 0.1f;
	}
	
		else if(key == GLFW_KEY_L && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//Rotate clockwise
		theta2 = theta2 - 0.1f;
	}
	
	
	else if(key == GLFW_KEY_I && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//Turn on animation
		if(bonus)
			bonus = false;
			
		else if(!bonus)
			bonus = true;
	}
	
	else if(key == GLFW_KEY_P && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//Reset values
		reset();
	}
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void mouseClick (GLFWwindow *sender, int button, int action, int mods) {
	//if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		//cout << mouseX << ' ' << mouseY << '\n';
}

void mousePos (GLFWwindow *sender, double x, double y) {
	//mouseX = x;
	//mouseY = y;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//zoom out (limited zoom)
	if(yoffset < 0 && scale > 0.2f)
    {
      //if zoom is not on lowest level...
      //decrease zoom level
      scale = scale - 0.1f;
    }

  //zoom in (limited zoom)
	if(yoffset > 0 && scale < 5.f)
    {
      //if zoom is not on highest level...
      //increase zoom level
      scale = scale + 0.1f;
	}
}

int main () {
	if (!glfwInit())
		return 1;

	window = glfwCreateWindow (640, 640, "My Window", NULL, NULL);
	if (!window)
		return 1;

	glfwMakeContextCurrent (window);
	glfwSetKeyCallback (window, keyboard);
	glfwSetMouseButtonCallback (window, mouseClick);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback (window, mousePos);
	while (!glfwWindowShouldClose (window)) 
	{
		glfwGetFramebufferSize (window, &w, &h);
		glViewport (0, 0, w, h);

		//Increment animation values
		if(bonus)
		{
			theta3 = theta3 + 0.03f;
			if(theta3 > (2*PI*cycles))
				theta3 = 0.f;
		}	
		//Else, no animation
		else if(!bonus)
			theta3 = 0.f;
			
		render();

		glfwSwapBuffers (window);
		glfwPollEvents();
	}

	glfwDestroyWindow (window);
	glfwTerminate();
	return 0;
}

