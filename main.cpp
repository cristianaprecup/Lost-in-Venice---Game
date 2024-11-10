// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#include "dependencies\glew\glew.h"

// Include GLFW
#include "dependencies\glfw\glfw3.h"

// Include GLM
#include "dependencies\glm\glm.hpp"
#include "dependencies\glm\gtc\matrix_transform.hpp"
#include "dependencies\glm\gtc\type_ptr.hpp"


#include "shader.hpp"

// global variables
GLFWwindow* window;
const int width = 2024, height = 2024;

glm::vec3 squarePosition(0.0f, 0.0f, 0.0f); //track the position of the square
const float squareSpeed = 0.005f; // speed of the square

// function to process the movements of the square
void processMovements(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)  
		squarePosition.y += squareSpeed; // move the square up by incrementing the y position 
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        squarePosition.y -= squareSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        squarePosition.x += squareSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        squarePosition.x -= squareSpeed;
}

int main(void)
{
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, "3D demo", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        return -1;
    }

    //specify the size of the rendering window
    glViewport(0, 0, width, height);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	// load the shaders
    GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");


	// vertices are used to define the shape of the square and indices are used to define the order in which the vertices are rendered
    float vertices[] = {
        0.05f,  0.05f, 0.0f,  // top right
        0.05f, -0.05f, 0.0f,  // bottom right
        -0.05f, -0.05f, 0.0f,  // bottom left
        -0.05f,  0.05f, 0.0f   // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

    // VAO, VBO, EBO
    GLuint VAO, //stores the configuration of vertex data
        VBO, //holds the vertex data (positions, colors, etc.)
        EBO; // stores indices that define the order in which vertices are rendered

    glGenVertexArrays(1, &VAO); //generates one VAO and stores its ID in the variable VAO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // specifies how the vertex data is structured
    glEnableVertexAttribArray(0);

    // the main loop of the program where the window is created and the program runs
    // any code that you want to run in the game, you have to put it inside of this loop
    while (!glfwWindowShouldClose(window))
    {
        // Swap buffers
        glfwSwapBuffers(window);

        // Check for events
        glfwPollEvents();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        processMovements(window);

		glUseProgram(programID); // use the shader program

		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first of 1.0f
		transform = glm::translate(transform, squarePosition); // translate the square to the new position

		// get the location of the transform matrix in the shader program
        unsigned int transformLoc = glGetUniformLocation(programID  , "transform"); 
		// pass the transform matrix to the shader program using the glUniformMatrix4fv function
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		// Draw the square
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate(); // close the program
    return 0;
}