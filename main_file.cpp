/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "Camera.cpp"
#include "Camera.h"


float speed = PI;//[radians/s]
Camera *camera;

//Error processing callback procedure
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Initialization code procedure
void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
    glClearColor(0, 0, 0, 1); //Set color buffer clear color
	glEnable(GL_DEPTH_TEST); //Turn on pixel depth test based on depth buffer
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    camera = new Camera(glm::vec3(0.0f, 0.0f,  3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f));

}
//Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
}

//Drawing procedure
void drawScene(GLFWwindow* window, float angle) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear color and depth buffers
	
	glm::mat4 M = glm::mat4(1.0f); //Initialize model matrix with abn identity matrix
	M = glm::rotate(M, angle, glm::vec3(0.0f, 1.0f, 0.0f)); //Multiply model matrix by rotation matrix, with rotation by /angle/ radians around Y axis
	glm::mat4 V = camera->getView();
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Compute projection matrix

	spLambert->use(); //Activate shader program
	glUniform4f(spLambert->u("color"), 0, 1, 0, 1); //Copy object color to shader program internal variable
	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P)); //Copy projection matrix to shader program internal variable
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V)); //Copy view matrix to shader program internal variable
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M)); //Copy model matrix to shader program internal variable

	Models::torus.drawSolid(); //Draw object

	glfwSwapBuffers(window); //Copy back buffer to the front buffer
}

int main(void)
{
	GLFWwindow* window; //Pointer to object that represents the application window

	glfwSetErrorCallback(error_callback);//Register error processing callback procedure

	if (!glfwInit()) { //Initialize GLFW library
		fprintf(stderr, "Can't initialize GLFW.\n");
		exit(EXIT_FAILURE); 
	}

	window = glfwCreateWindow(1920, 1080, "OpenGL", NULL, NULL);  //Create a window 500pxx500px titled "OpenGL" and an OpenGL context associated with it.

	if (!window) //If no window is opened then close the program
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Since this moment OpenGL context corresponding to the window is active and all OpenGL calls will refer to this context.
	glfwSwapInterval(1); //During vsync wait for the first refresh

	GLenum err;
	if ((err=glewInit()) != GLEW_OK) { //Initialize GLEW library
		fprintf(stderr, "Can't initialize GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Call initialization procedure

	//Main application loop
    float angle = 0; //declare variable for storing current rotation angle
	glfwSetTime(0); //clear internal timer
	while (!glfwWindowShouldClose(window)) //As long as the window shouldnt be closed yet...
	{		
        camera->processInput(window);
        camera->mouseCallback(window);
		glfwSetTime(0); //clear internal timer
		drawScene(window,angle); //Execute drawing procedure
		glfwPollEvents(); //Process callback procedures corresponding to the events that took place up to now
	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Delete OpenGL context and the window.
	glfwTerminate(); //Free GLFW resources
	exit(EXIT_SUCCESS);
}
