#include <iostream>
#include <stdlib.h>
#include <C:\Users\gabri\OneDrive\Desktop\Lost-in-Venice---Game\dependencies\glew\glew.h>
#include <C:\Users\gabri\OneDrive\Desktop\Lost-in-Venice---Game\dependencies\glfw\glfw3.h>
#include <C:\Users\gabri\OneDrive\Desktop\Lost-in-Venice---Game\dependencies\glm\glm.hpp>

glm::vec3 squarePosition(0.0f, 0.0f, 0.0f); //track the position of the square
const float squareSpeed = 0.0005f;

//it's not allowed to put it inside the main fct
void processMovements(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)  //if up key is pressed
        squarePosition.y += squareSpeed;  // move upwards, on the y axis with that speed
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        squarePosition.y -= squareSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        squarePosition.x += squareSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        squarePosition.x -= squareSpeed;
}

int main(void)
{
    // initialize a variable window of type GLFWwindow 
    GLFWwindow* window;

    // initialize the library GLFW
    if (!glfwInit())
        return -1; // if the library is not initialized, return -1 and close the program

    // create the window with the size and the title Lost in Venice
    window = glfwCreateWindow(1000, 632, "Lost in Venice", NULL, NULL);
    if (!window)
    {
        glfwTerminate(); // if the window cannot be created close the program
        return -1;
    }

    // DO NOT DELETE THIS LINE, this is the line that makes the game to work
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        return -1;
    }

    // to make the square(player):
    GLfloat vertices[] = {
        0.05f, 0.05f, 0.0f, // top right
        0.05f, -0.05f, 0.0f, // bottom right
        -0.05f, -0.05f, 0.0f, // bottom left
        -0.05f, 0.05f, 0.0f  // top left
    };

    GLuint indices[] = {
        0, 3, 1, // first triangle
        1, 3, 2, // second triangle
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // the main loop of the program where the window is created and the program runs
    // any code that you want to run in the game, you have to put it inside of this loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT); // this have to be the first line of the loop, it clears the window

        // anything that you want to do in the game, put here

        processMovements(window);

        // Update the vertices based on the square's position
        GLfloat updatedVertices[] = {
            0.05f + squarePosition.x,  0.05f + squarePosition.y, 0.0f, // top right
            0.05f + squarePosition.x, -0.05f + squarePosition.y, 0.0f, // bottom right
            -0.05f + squarePosition.x, -0.05f + squarePosition.y, 0.0f, // bottom left
            -0.05f + squarePosition.x,  0.05f + squarePosition.y, 0.0f  // top left
        };

        // update the VBO with the new vertex data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(updatedVertices), updatedVertices, GL_STATIC_DRAW);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

        // these lines have to be the last lines of the loop
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate(); // close the program
    return 0;
}


