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

#include <iostream>
#include <sstream>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "res/models/allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "Camera.cpp"
#include "Camera.h"


float aspectRatio = 1;
Camera *camera;

GLuint walls;
GLuint floors;
GLuint ceilings;
GLuint frame;
GLuint paintings[40];

//Error processing callback procedure
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

GLuint readTexture(char* filename, int i = 0) {
    GLuint tex;
    glActiveTexture(GL_TEXTURE0 + i);
    //Read into computers memory
    std::vector<unsigned char> image; //Allocate memory
    unsigned width, height; //Variables for image size
    //Read the image
    unsigned error = lodepng::decode(image, width, height, filename);
    //Import to graphics card memory
    glGenTextures(1,&tex); //Initialize one handle
    glBindTexture(GL_TEXTURE_2D, tex); //Activate handle
    //Copy image to graphics cards memory represented by the active handle
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
    walls=readTexture("res/textures/walls.png");
    floors=readTexture("res/textures/floor.png");
    ceilings=readTexture("res/textures/ceiling.png");
    frame=readTexture("res/textures/frame.png");
    // read all painting textures
    char path[50];
    for (int i=0; i<38 ; i++) {
        std::string s = std::to_string(i+1);
        char const *pchar = s.c_str();
        strcpy(path,"res/textures/painting");
        strcat(path, pchar);
        strcat(path, ".png");
        printf("%s\n", path);
        paintings[i] = readTexture(path, i+1);
    }
    // initialize the camera in the center of a room
    camera = new Camera(glm::vec3(45.0f, 0.0f,  45.0f),
                        glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f));
}

//Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow* window) {
    glDeleteTextures(1,&walls);
    glDeleteTextures(1,&floors);
    glDeleteTextures(1,&ceilings);
    glDeleteTextures(1,&frame);
    glDeleteTextures(7, paintings);
    freeShaders();
}

void drawPainting(glm::mat4 M, GLuint tex) {
    glm::mat4 M1 = glm::scale(M,glm::vec3(1.0f,1.0f,0.15f));
    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M1));
    Models::cube.drawCube(frame);

    glm::mat4 M2 = glm::translate(M1, glm::vec3(0.0f, 0.0f, -1.4f));
    M2 = glm::scale(M2,glm::vec3(0.9f,0.9f,0.2f));
    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M2));
    Models::cube.drawCube(tex);
}

void drawWalls() {

    glm::mat4 M = glm::mat4(1.0f); //Initialize model matrix with abn identity matrix
    M = glm::scale(M,glm::vec3(30.0f,9.0f,30.0f)); // scale the walls size

    // translate the floor up, so the camera is closer to the floor
    // and translate the first room so that the (0,0) point would be in the center of the museum
    M = glm::translate(M,glm::vec3(-1.5f,0.2f,1.5f));

    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));
    Models::walls.drawWalls(walls, floors, ceilings); //Draw object

    glm::mat4 M2 = glm::translate(M,glm::vec3(0.0f,0.0f,-3.0f));
    M2 = glm::rotate(M2, -90.0f * PI / 180.0f, glm::vec3(0.0f,1.0f,0.0f));
    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M2));
    Models::walls.drawWalls(walls, floors, ceilings);

    glm::mat4 M3 = glm::translate(M2,glm::vec3(0.0f,0.0f,-3.0f));
    M3 = glm::rotate(M3, -90.0f * PI / 180.0f, glm::vec3(0.0f,1.0f,0.0f));
    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M3));
    Models::walls.drawWalls(walls, floors, ceilings);

    glm::mat4 M4 = glm::translate(M3,glm::vec3(0.0f,0.0f,-3.0f));
    M4 = glm::rotate(M4, -90.0f * PI / 180.0f, glm::vec3(0.0f,1.0f,0.0f));
    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M4));
    Models::walls.drawWalls(walls, floors, ceilings);
}

void decorateWalls() {
    /*
     * Room corner coordinates:
     * (15,15)  (15,75)  (75,15)  (75,75)
     */

    //glUniform4f(spTextured->u("color"), 0, 0, 1, 1); //Copy object color to shader program internal variable

    glm::mat4 M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.8f, 0.0f)); // move up so the painting will be at the center


    // ROOM 1

    glm::mat4 Mp = glm::translate(M, glm::vec3(34.0f, 0.0f, 75.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    drawPainting(Mp, paintings[0]);

    Mp = glm::translate(M, glm::vec3(58.0f, 0.0f, 75.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    drawPainting(Mp, paintings[1]);

    Mp = glm::translate(M, glm::vec3(75.0f, 0.0f, 34.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, 90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[2]);

    Mp = glm::translate(M, glm::vec3(75.0f, 0.0f, 58.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, 90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[3]);

    Mp = glm::translate(M, glm::vec3(15.0f, 0.0f, 30.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, -90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[4]);

    Mp = glm::translate(M, glm::vec3(15.0f, 0.0f, 60.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, -90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[5]);

    Mp = glm::translate(M, glm::vec3(30.0f, 0.0f, 15.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    Mp = glm::rotate(Mp, 180.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[6]);

    Mp = glm::translate(M, glm::vec3(60.0f, 0.0f, 15.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    Mp = glm::rotate(Mp, 180.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[7]);


    // ROOM 2

    Mp = glm::translate(M, glm::vec3(-34.0f, 0.0f, 75.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    drawPainting(Mp, paintings[8]);

    Mp = glm::translate(M, glm::vec3(-58.0f, 0.0f, 75.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    drawPainting(Mp, paintings[9]);

    Mp = glm::translate(M, glm::vec3(-75.0f, 0.0f, 34.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, -90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[10]);

    Mp = glm::translate(M, glm::vec3(-75.0f, 0.0f, 58.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, -90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[11]);

    Mp = glm::translate(M, glm::vec3(-15.0f, 0.0f, 30.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, 90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[12]);

    Mp = glm::translate(M, glm::vec3(-15.0f, 0.0f, 60.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, 90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[13]);

    Mp = glm::translate(M, glm::vec3(-30.0f, 0.0f, 15.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    Mp = glm::rotate(Mp, 180.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[14]);

    Mp = glm::translate(M, glm::vec3(-60.0f, 0.0f, 15.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    Mp = glm::rotate(Mp, 180.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[15]);

    // ROOM 3

    Mp = glm::translate(M, glm::vec3(34.0f, 0.0f, -75.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    Mp = glm::rotate(Mp, 180.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[16]);

    Mp = glm::translate(M, glm::vec3(58.0f, 0.0f, -75.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    Mp = glm::rotate(Mp, 180.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[17]);

    Mp = glm::translate(M, glm::vec3(75.0f, 0.0f, -34.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, 90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[18]);

    Mp = glm::translate(M, glm::vec3(75.0f, 0.0f, -58.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, 90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[19]);

    Mp = glm::translate(M, glm::vec3(15.0f, 0.0f, -30.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, -90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[20]);

    Mp = glm::translate(M, glm::vec3(15.0f, 0.0f, -60.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, -90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[21]);

    Mp = glm::translate(M, glm::vec3(30.0f, 0.0f, -15.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    drawPainting(Mp, paintings[22]);

    Mp = glm::translate(M, glm::vec3(60.0f, 0.0f, -15.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    drawPainting(Mp, paintings[23]);

    // ROOM 4

    Mp = glm::translate(M, glm::vec3(-34.0f, 0.0f, -75.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    Mp = glm::rotate(Mp, 180.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[24]);

    Mp = glm::translate(M, glm::vec3(-58.0f, 0.0f, -75.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    Mp = glm::rotate(Mp, 180.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[25]);

    Mp = glm::translate(M, glm::vec3(-75.0f, 0.0f, -34.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, -90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[26]);

    Mp = glm::translate(M, glm::vec3(-75.0f, 0.0f, -58.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, -90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[27]);

    Mp = glm::translate(M, glm::vec3(-15.0f, 0.0f, -30.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, 90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[28]);

    Mp = glm::translate(M, glm::vec3(-15.0f, 0.0f, -60.0f));
    Mp = glm::scale(Mp, glm::vec3(1.0f, 6.0f, 6.0f));
    Mp = glm::rotate(Mp, 90.0f*PI/180.0f,glm::vec3(0.0f, 1.0f, 0.0f));
    drawPainting(Mp, paintings[29]);

    Mp = glm::translate(M, glm::vec3(-30.0f, 0.0f, -15.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    drawPainting(Mp, paintings[30]);

    Mp = glm::translate(M, glm::vec3(-60.0f, 0.0f, -15.0f));
    Mp = glm::scale(Mp, glm::vec3(6.0f, 6.0f, 1.0f));
    drawPainting(Mp, paintings[31]);
}

//Drawing procedure
void drawScene(GLFWwindow* window) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear color and depth buffers

	glm::mat4 V = camera->getView();
	glm::mat4 P = glm::perspective(glm::radians(50.0f), aspectRatio, 1.0f, 50.0f); //Compute projection matrix

    spTextured->use(); //Activate shader program
	// glUniform4f(spTextured->u("color"), 1, 1, 1, 1); //Copy object color to shader program internal variable
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P)); //Copy projection matrix to shader program internal variable
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V)); //Copy view matrix to shader program internal variable

	drawWalls();
	decorateWalls();

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
