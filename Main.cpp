#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



// Vertices coordinates
GLfloat vertices[] = {
	// Positions                // Colors
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	 0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	 1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	 1.0f, 0.0f // Lower left
};

GLuint indices[] = {
	0, 2, 1, // Upper triangle
	0, 3, 2, // Lower triangle
};


int main() {
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "OpenGL - HuiShan"
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL - HuiShan", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failde to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// Generate Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generate Vertex Array Object and bind it
	VAO VAO1;
	VAO1.Bind();

	// Generate Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generate Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture

	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load("psyduck.png", &widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// float floatColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, floatColor);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		// Clean the back buffer and assign the new color to the buffer
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Assign value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		glBindTexture(GL_TEXTURE_2D, texture);// Bind the texture
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &texture);
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}