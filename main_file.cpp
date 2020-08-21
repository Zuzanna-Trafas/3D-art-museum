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



float aspectRatio = 1;
Camera *camera;
GLuint tex; //texture handle

//Error processing callback procedure
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

GLuint readTexture(char* filename) {
    GLuint tex;
    glActiveTexture(GL_TEXTURE0);
//Read into computers memory
    std::vector<unsigned char> image; //Allocate memory
    unsigned width, height; //Variables for image size
//Read the image
    unsigned error = lodepng::decode(image, width, height, filename);
//Import to graphics card memory
    glGenTextures(1,&tex); //Initialize one handle
    glBindTexture(GL_TEXTURE_2D, tex); //Activate handle
//Copy image to graphics cards memory reprezented by the active handle
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return tex;
}

void windowResizeCallback(GLFWwindow *window, int width, int height) {
    if (height == 0) {
        return;
    }
    aspectRatio = (float) width / (float) height;
    glViewport(0,0,width,height);
}
//Initialization code procedure
void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
    glClearColor(0, 0, 0, 1); //Set color buffer clear color
	glEnable(GL_DEPTH_TEST); //Turn on pixel depth test based on depth buffer
    glfwSetCursorPos(window, 960, 0);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    tex=readTexture("textures/wood-texture.png");
    // initialize the camera in the center of a room
    camera = new Camera(glm::vec3(45.0f, 0.0f,  45.0f),
                        glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f));
}

//Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow* window) {
    glDeleteTextures(1,&tex);
    freeShaders();
}

void drawPainting(glm::mat4 M) {
    glm::mat4 M1 = glm::scale(M,glm::vec3(1.0f,1.0f,0.008f));
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M1));
    Models::cube.drawSolid();

    glm::mat4 M2 = glm::translate(M1, glm::vec3(0.0f, 0.0f, -1.2f));
    M2 = glm::scale(M2,glm::vec3(0.9f,0.9f,0.2f));
    glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M2));
    Models::cube.drawSolid();
}

void drawWalls() {
    glm::mat4 M = glm::mat4(1.0f); //Initialize model matrix with abn identity matrix
    M = glm::scale(M,glm::vec3(30.0f,7.0f,30.0f)); // scale the walls size

    // translate the floor up, so the camera is closer to the floor
    // and translate the first room so that the (0,0) point would be in the center of the museum
    M = glm::translate(M,glm::vec3(-1.5f,0.2f,1.5f));

    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));
    Models::walls.drawSolid(); //Draw object

    glm::mat4 M2 = glm::translate(M,glm::vec3(0.0f,0.0f,-3.0f));
    M2 = glm::rotate(M2, -90.0f * PI / 180.0f, glm::vec3(0.0f,1.0f,0.0f));
    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M2));
    Models::walls.drawSolid();

    glm::mat4 M3 = glm::translate(M2,glm::vec3(0.0f,0.0f,-3.0f));
    M3 = glm::rotate(M3, -90.0f * PI / 180.0f, glm::vec3(0.0f,1.0f,0.0f));
    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M3));
    Models::walls.drawSolid();

    glm::mat4 M4 = glm::translate(M3,glm::vec3(0.0f,0.0f,-3.0f));
    M4 = glm::rotate(M4, -90.0f * PI / 180.0f, glm::vec3(0.0f,1.0f,0.0f));
    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M4));
    Models::walls.drawSolid();

}

//Drawing procedure
void drawScene(GLFWwindow* window) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear color and depth buffers

	glm::mat4 V = camera->getView();
	glm::mat4 P = glm::perspective(glm::radians(50.0f), aspectRatio, 1.0f, 50.0f); //Compute projection matrix

    spTextured->use(); //Activate shader program
	glUniform4f(spTextured->u("color"), 1, 1, 1, 1); //Copy object color to shader program internal variable
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P)); //Copy projection matrix to shader program internal variable
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V)); //Copy view matrix to shader program internal variable

    glEnableVertexAttribArray(spTextured->a("texCoord"));
    glVertexAttribPointer(spTextured->a("texCoord"),2,GL_FLOAT,false,0, Models::walls.texCoords);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,tex);
    glUniform1i(spTextured->u("tex"),0);

	drawWalls();

    // PAINTINGS
    /*
     * Room corner coordinates:
     * (15,15)  (15,75)  (75,15)  (75,75)
     */

    glUniform4f(spTextured->u("color"), 0, 0, 1, 1); //Copy object color to shader program internal variable

    glm::mat4 Mp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.4f, 0.0f));
    glm::mat4 Mp1 = glm::translate(Mp, glm::vec3(34.0f, 0.0f, 75.0f));
    Mp1 = glm::scale(Mp1, glm::vec3(6.0f, 4.0f, 1.0f));
    drawPainting(Mp1);
    glm::mat4 Mp2 = glm::translate(Mp, glm::vec3(58.0f, 0.0f, 75.0f));
    Mp2 = glm::scale(Mp2, glm::vec3(8.0f, 4.0f, 1.0f));
    drawPainting(Mp2);


    glDisableVertexAttribArray(spTextured->a("texCoord"));
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

	glfwSetTime(0); //clear internal timer
	while (!glfwWindowShouldClose(window)) //As long as the window shouldnt be closed yet...
	{		
        camera->processInput(window);
        camera->mouseCallback(window);
		glfwSetTime(0); //clear internal timer
		drawScene(window); //Execute drawing procedure
		glfwPollEvents(); //Process callback procedures corresponding to the events that took place up to now
	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Delete OpenGL context and the window.
	glfwTerminate(); //Free GLFW resources
	exit(EXIT_SUCCESS);
}
