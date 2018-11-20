

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "SOIL2\SOIL2.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const GLint SCREENT_WIDTH = 800, SCREENT_HEIGHT = 600;


int main()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCREENT_WIDTH, SCREENT_HEIGHT, "Hello World", NULL, NULL);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Set this to true so glew knows to use a modern approach to retrewving function pointers and extensions
	glewExperimental = GL_TRUE;
	//glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	glViewport(0, 0, screenWidth, screenHeight);
	 
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	Shader ourShader("core.vs", "core.frag");
	 
	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection
	/*GLfloat vertices[] = {
	-0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,
	0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 0.0f,
	0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
	0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
	-0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
	-0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,

	-0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
	0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,
	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,
	-0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 1.0f,
	-0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,

	-0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
	-0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
	-0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
	-0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
	-0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
	-0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,

	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
	0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
	0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
	0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
	0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,

	-0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
	0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
	0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
	0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
	-0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
	-0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,

	-0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
	0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
	-0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
	-0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f
	};  */
	// use with Perspective Projection
		GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); 

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
 
	// 纹理坐标属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// 释放
	glBindVertexArray(0);

	GLuint texture;

	int width, height;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *image = SOIL_load_image("res/images/image1.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glm::mat4 projection;
	projection = glm::perspective(45.0f,(GLfloat)screenWidth/ (GLfloat)screenHeight,0.1f,1000.0f);
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Poll for and process events */
		glfwPollEvents();
	    // Render
		// Clear the colorbuffer
		glClearColor(0.2f,0.3f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture"), 0);

		ourShader.Use();
 
		glm::mat4 model;
		glm::mat4 view;
		model = glm::rotate(model, (GLfloat)glfwGetTime()*1.0f, glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		//model = glm::rotate(model, (GLfloat)glfwGetTime()*0.5f, glm::vec3(1.0f, 0.5f, 0.0f));
		//view = glm::translate(view, glm::vec3(screenWidth / 2, screenHeight / 2, -700.0f));


		GLint modelLoc = glGetUniformLocation(ourShader.Program,"model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projectionLoc = glGetUniformLocation(ourShader.Program, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO); 
	glfwTerminate();
	return EXIT_SUCCESS;
}




