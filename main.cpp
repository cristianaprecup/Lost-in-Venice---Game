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

// Include STB
#define STB_IMAGE_IMPLEMENTATION
#include "dependencies\stb_image.h"

#include "shader.hpp"

// global variables
GLFWwindow* window;
const int width = 1100, height = 1100;

glm::vec3 squarePosition(0.0f, 0.0f, 0.0f); //track the position of the square
glm::vec3 staticSquarePosition(2.0f, 3.0f, 0.0f);
const float squareSpeed = 0.0007f; // speed of the square

// positions of the squares 
glm::vec3 positions[] = {
    glm::vec3(-0.53f, 0.8f, 0.0f),  //1
    glm::vec3(-0.35f, 0.8f, 0.0f),
    glm::vec3(-0.53f, 0.7f, 0.0f),
    glm::vec3(-0.35f, 0.7f, 0.0f),

    glm::vec3(-0.55f, 0.3f, 0.0f),  //2
    glm::vec3(-0.55f, 0.38f, 0.0f),
    glm::vec3(-0.35f, 0.3f, 0.0f),
    glm::vec3(-0.35f, 0.38f, 0.0f),

    glm::vec3(-0.6f, 0.08f, 0.0f),  //3
    glm::vec3(-0.6f, 0.05f, 0.0f),

    glm::vec3(-0.87f, 0.88f, 0.0f),  //4

    glm::vec3(-0.78f, 0.52f, 0.0f),  //5
    glm::vec3(-0.78f, 0.46f, 0.0f),
    glm::vec3(-0.9f, 0.52f, 0.0f),
    glm::vec3(-0.9f, 0.46f, 0.0f),

    glm::vec3(-0.9f, 0.27f, 0.0f),   //6

    glm::vec3(-0.87f, 0.05f, 0.0f),  //7

    glm::vec3(-0.86f, 0.0f, 0.0f),   //8

    glm::vec3(-0.85f, -0.4f, 0.0f),  //9
    glm::vec3(-0.85f, -0.48f, 0.0f),

    glm::vec3(-0.95f, -0.7f, 0.0f),   //10
    glm::vec3(-0.95f, -0.8f, 0.0f),

    glm::vec3(-0.88f, -0.88f, 0.0f),   //11

    glm::vec3(-0.27f, -0.09f, 0.0f), //12

    glm::vec3(-0.27f, -0.35f, 0.0f),  //13

    glm::vec3(-0.37f, -0.08f, 0.0f), //14
    glm::vec3(-0.4f, -0.2f, 0.0f),
    glm::vec3(-0.4f, -0.35f, 0.0f),

  
};




// function to load the background texture
GLuint loadTexture(const char* filepath) {
    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load the background" << std::endl;
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return texture;
}

bool checkCollision(const glm::vec3& playerPos, const glm::vec3& staticPos, float size) {
    float halfSize = size / 2.0f;

    // Check if the player's square intersects with the static square
    return (playerPos.x + halfSize > staticPos.x - halfSize &&
        playerPos.x - halfSize < staticPos.x + halfSize &&
        playerPos.y + halfSize > staticPos.y - halfSize &&
        playerPos.y - halfSize < staticPos.y + halfSize);
}



void processMovements(GLFWwindow* window) {
    glm::vec3 newPosition = squarePosition; // Store the player's current position

    // Update the position based on key input
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        newPosition.y += squareSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        newPosition.y -= squareSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        newPosition.x += squareSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        newPosition.x -= squareSpeed;

    // Check for collisions with all static squares
    for (const auto& staticPos : positions) {
        if (checkCollision(newPosition, staticPos, 0.1f)) { // Assuming square size is 0.1
            return; // Cancel movement if there's a collision
        }
    }

    // If no collisions, update the player's position
    squarePosition = newPosition;
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
    window = glfwCreateWindow(width, height, "Lost in Venice", NULL, NULL);
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

    GLuint backgroundTexture = loadTexture("res/background.png");
    if (backgroundTexture == 0) {
        std::cerr << "Failed to load background" << std::endl;
        return -1;
    }

    glViewport(0, 0, width, height);



    float quadVertices[] = {
        // positions      // texture coords
        -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
         1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,  1.0f, 1.0f
    };

    unsigned int quadIndices[] = {
        0, 1, 2,
        0, 2, 3
    };

    // VAO, VBO, EBO for the background
    GLuint quadVAO, quadVBO, quadEBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glGenBuffers(1, &quadEBO);

    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // vertices are used to define the shape of the square and indices are used to define the order in which the vertices are rendered
    float vertices_main_square[] = {
        0.05f,  0.05f, 0.0f,  // top right
        0.05f, -0.05f, 0.0f,  // bottom right
        -0.05f, -0.05f, 0.0f,  // bottom left
        -0.05f,  0.05f, 0.0f   // top left 
    };

    unsigned int indices_main_square[] = {
        0, 1, 3,
        1, 2, 3
    };

    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO); //generates one VAO and stores its ID in the variable VAO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_main_square), vertices_main_square, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_main_square), indices_main_square, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // specifies how the vertex data is structured
    glEnableVertexAttribArray(0);

    GLuint backgroundShader = LoadShaders("BackgroundVertexShader.vertexshader", "BackgroundFragmentShader.fragmentshader");
    if (backgroundShader == 0) {
        std::cerr << "Failed to load background shaders!" << std::endl;
        return -1;
    }
    GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
    if (programID == 0) {
        std::cerr << "Failed to load main shaders!" << std::endl;
        return -1;
    }


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

        // Render the background
        glUseProgram(backgroundShader);
        glBindTexture(GL_TEXTURE_2D, backgroundTexture);

        glBindVertexArray(quadVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        processMovements(window);

        // Render the square
        glUseProgram(programID); //the shader program is used for rendering the square

        // Create a transformation matrix and translate the square
        glm::mat4 transform = glm::mat4(1.0f); // identity matrix
        transform = glm::translate(transform, squarePosition); // move square to new position

        // Apply scaling to the mobile square (player square)
        transform = glm::scale(transform, glm::vec3(0.4f, 0.4f, 0.8f)); // scale down the mobile square

        // get the location of the transform matrix in the shader program
        unsigned int transformLoc = glGetUniformLocation(programID, "transform");
        // pass the transform matrix to the shader program using the glUniformMatrix4fv function
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // Draw the mobile square (player)
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        //for (int i = 0; i < 10; i++) {                                       //do not delete!!! (hidden squares)
        //    glm::mat4 transform = glm::mat4(1.0f);
        //    transform = glm::translate(transform, positions[i]);
        //    transform = glm::scale(transform, glm::vec3(1.8f, 1.2f, 1.0f)); // Scale static squares
        //    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        //    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //}


    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate(); // close the program
    return 0;
}