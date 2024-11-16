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
const int width = 1024, height = 1024;

glm::vec3 characterPosition(-0.7f, 0.7f, 0.0f); 
const float characterSpeed = 0.001f; 

glm::vec3 enemyPosition(0.0f, 0.0f, 0.0f); 
const float enemySpeed = 0.001f;

bool gameOver = false;
bool isStartPage = true;

float game_over_min_x = -0.5f, game_over_max_x = 0.5f;
float game_over_min_y = -0.4f, game_over_max_y = 0.4f;

float start_page_min_x = -0.2f, start_page_max_x = 0.2f;
float start_page_min_y = -0.8f, start_page_max_y = -0.6f;

// function to draw and transform the characters
void drawAndTransformCharacter(GLuint shader, GLuint VAO, glm::vec3 squarePosition) {
    glUseProgram(shader);

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, squarePosition);

    unsigned int transformLoc = glGetUniformLocation(shader, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0); 
}



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

// function to handle the mouse button callback for the game over and start page
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    float ndc_x = (2.0f * xpos) / width - 1.0f;
    float ndc_y = 1.0f - (2.0f * ypos) / height;

    if (gameOver == true) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            if (ndc_x >= game_over_min_x && ndc_x <= game_over_max_x &&
                ndc_y >= game_over_min_y && ndc_y <= game_over_max_y) {
                gameOver = false;
                isStartPage = true;

                characterPosition = glm::vec3(-0.7f, 0.7f, 0.0f);
                enemyPosition = glm::vec3(0.0f, 0.0f, 0.0f);
            }
        }
    }
    else if (isStartPage) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            if (ndc_x >= start_page_min_x && ndc_x <= start_page_max_x &&
                ndc_y >= start_page_min_y && ndc_y <= start_page_max_y) {
                isStartPage = false;
				gameOver = false;

                characterPosition = glm::vec3(-0.7f, 0.7f, 0.0f);
                enemyPosition = glm::vec3(0.0f, 0.0f, 0.0f);
            }
        }
    }
}


// function to process the movements of the square
void processMovements(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)  
		characterPosition.y += characterSpeed; 
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        characterPosition.y -= characterSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        characterPosition.x += characterSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        characterPosition.x -= characterSpeed;
}

// function to make the enemy follow the character
void enemyFollow(glm::vec3& enemyPosition, const glm::vec3& characterPosition, float enemySpeed) {
    glm::vec3 direction = characterPosition - enemyPosition;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0.0f) {
        direction /= length;
        enemyPosition += direction * enemySpeed;
    }
}

// function to check if the enemy caught the character
void checkIfEnemyCaughtCharacter(const glm::vec3& enemyPosition, const glm::vec3& characterPosition) {
	float distance = sqrt((enemyPosition.x - characterPosition.x) * (enemyPosition.x - characterPosition.x) +
		(enemyPosition.y - characterPosition.y) * (enemyPosition.y - characterPosition.y));
	if (distance < 0.1f) {
		gameOver = true;
	}
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

    GLuint gameOverTexture = loadTexture("res/game_over.png");
	if (gameOverTexture == 0) {
		std::cerr << "Failed to load game over" << std::endl;
		return -1;
	}

    GLuint startPage = loadTexture("res/start_page.png");
    if (gameOverTexture == 0) {
        std::cerr << "Failed to load the start page" << std::endl;
        return -1;
    }


    glViewport(0, 0, width, height);



	// ----------------- Background -----------------

    float backgorundVertices[] = {
		// background + start page
        -1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 
         1.0f, -1.0f, 0.0f,  1.0f, 0.0f, 
         1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 

         //Game Over
         -0.5f,  0.4f, 0.0f,  0.0f, 1.0f, 
         -0.5f, -0.4f, 0.0f,  0.0f, 0.0f, 
          0.5f, -0.4f, 0.0f,  1.0f, 0.0f, 
          0.5f,  0.4f, 0.0f,  1.0f, 1.0f  
    };

    unsigned int backgorundIndices[] = {
    0, 1, 2, 2, 3, 0, 
    4, 5, 6, 6, 7, 4  
    };


    GLuint backgorundVAO, backgorundVBO, backgorundEBO;
    glGenVertexArrays(1, &backgorundVAO);
    glGenBuffers(1, &backgorundVBO);
    glGenBuffers(1, &backgorundEBO);

    glBindVertexArray(backgorundVAO);

    glBindBuffer(GL_ARRAY_BUFFER, backgorundVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(backgorundVertices), backgorundVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, backgorundEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(backgorundIndices), backgorundIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    GLuint backgroundShader = LoadShaders("BackgroundVertexShader.vertexshader", "BackgroundFragmentShader.fragmentshader");
    if (backgroundShader == 0) {
        std::cerr << "Failed to load background shaders!" << std::endl;
        return -1;
    }

	// ----------------- Character ------------

    const float scale = 0.1f;

    float vertices[] = {
        // Head 
        -0.1f * scale,  0.6f * scale, 0.0f,  
         0.1f * scale,  0.6f * scale, 0.0f,  
         0.1f * scale,  0.4f * scale, 0.0f, 
        -0.1f * scale,  0.4f * scale, 0.0f,  

        // Neck
        -0.03f * scale, 0.4f * scale, 0.0f,
         0.03f * scale, 0.4f * scale, 0.0f,
         0.03f * scale, 0.35f * scale, 0.0f,
        -0.03f * scale, 0.35f * scale, 0.0f,

        // Body
        -0.1f * scale, 0.0f, 0.0f,
         0.1f * scale, 0.0f, 0.0f,
         0.1f * scale, 0.35f * scale, 0.0f,
        -0.1f * scale, 0.35f * scale, 0.0f,

        // Left Arm
        -0.15f * scale, 0.3f * scale, 0.0f,
        -0.1f * scale, 0.3f * scale, 0.0f,
        -0.1f * scale, 0.2f * scale, 0.0f,
        -0.15f * scale, 0.2f * scale, 0.0f,

        // Right Arm
         0.1f * scale, 0.3f * scale, 0.0f,
         0.15f * scale, 0.3f * scale, 0.0f,
         0.15f * scale, 0.2f * scale, 0.0f,
         0.1f * scale, 0.2f * scale, 0.0f,

         // Left Leg
         -0.05f * scale, -0.3f * scale, 0.0f,
         -0.02f * scale, -0.3f * scale, 0.0f,
         -0.02f * scale, 0.0f, 0.0f,
         -0.05f * scale, 0.0f, 0.0f,

         // Right Leg
          0.02f * scale, -0.3f * scale, 0.0f,
          0.05f * scale, -0.3f * scale, 0.0f,
          0.05f * scale, 0.0f, 0.0f,
          0.02f * scale, 0.0f, 0.0f,
    };

    unsigned int indices[] = {
        // Head
        0, 1, 2,
        0, 2, 3,

        // Neck
        4, 5, 6,
        4, 6, 7,

        // Body
        8, 9, 10,
        8, 10, 11,

        // Left Arm
        12, 13, 14,
        12, 14, 15,

        // Right Arm
        16, 17, 18,
        16, 18, 19,

        // Left Leg
        20, 21, 22,
        20, 22, 23,

        // Right Leg
        24, 25, 26,
        24, 26, 27,
    };
    
    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO); //generates one VAO and stores its ID in the variable VAO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // specifies how the vertex data is structured
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // specifies how the vertex data is structured
    glEnableVertexAttribArray(0);

	// ----------------- Enemy ------------


    float enemyVertices[] = {
        // Head 
        0.0f,  0.5f * scale, 0.0f,
        0.0f,  0.6f * scale, 0.0f, 
        0.1f * scale, 0.5f * scale, 0.0f,
        0.0f,  0.4f * scale, 0.0f,
        -0.1f * scale, 0.5f * scale, 0.0f,
    
        // Neck
        -0.03f * scale, 0.3f * scale, 0.0f,
        0.03f * scale, 0.3f * scale, 0.0f,
        0.03f * scale, 0.4f * scale, 0.0f,
        -0.03f * scale, 0.4f * scale, 0.0f,
    
        // Body
        -0.1f * scale, 0.0f, 0.0f,
        0.1f * scale, 0.0f, 0.0f,
        0.1f * scale, 0.3f * scale, 0.0f,
        -0.1f * scale, 0.3f * scale, 0.0f,
    
        // Left Arm
        -0.2f * scale, 0.2f * scale, 0.0f,
        -0.1f * scale, 0.2f * scale, 0.0f,
        -0.1f * scale, 0.1f * scale, 0.0f,
        -0.2f * scale, 0.1f * scale, 0.0f,
    
        // Right Arm
        0.1f * scale, 0.2f * scale, 0.0f,
        0.2f * scale, 0.2f * scale, 0.0f,
        0.2f * scale, 0.1f * scale, 0.0f,
        0.1f * scale, 0.1f * scale, 0.0f,
    
        // Left Leg
        -0.05f * scale, -0.5f * scale, 0.0f,
        -0.02f * scale, -0.5f * scale, 0.0f,
        -0.02f * scale, 0.0f, 0.0f,
        -0.05f * scale, 0.0f, 0.0f,
    
        // Right Leg
        0.02f * scale, -0.5f * scale, 0.0f,
        0.05f * scale, -0.5f * scale, 0.0f,
        0.05f * scale, 0.0f, 0.0f,
        0.02f * scale, 0.0f, 0.0f,
        };
    
    unsigned int enemyIndices[] = {
        // Head 
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 1,
    
        // Neck
        5, 6, 7,
        5, 7, 8,
    
        // Body
        9, 10, 11,
        9, 11, 12,
    
        // Left Arm
        13, 14, 15,
        13, 15, 16,
    
        // Right Arm
        17, 18, 19,
        17, 19, 20,
    
        // Left Leg
        21, 22, 23,
        21, 23, 24,
    
        // Right Leg
        25, 26, 27,
        25, 27, 28,
    };

    GLuint VAOenemy, VBOenemy, EBOenemy;

    glGenVertexArrays(1, &VAOenemy); //generates one VAO and stores its ID in the variable VAO
    glGenBuffers(1, &VBOenemy);
    glGenBuffers(1, &EBOenemy);

    glBindVertexArray(VAOenemy);
    glBindBuffer(GL_ARRAY_BUFFER, VBOenemy);
    glBufferData(GL_ARRAY_BUFFER, sizeof(enemyVertices), enemyVertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOenemy);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(enemyIndices), enemyIndices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // specifies how the vertex data is structured
    glEnableVertexAttribArray(0);

  
    GLuint characterShader = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
    if (characterShader == 0) {
        std::cerr << "Failed to load main shaders!" << std::endl;
        return -1;
    }

    int colorLocation = glGetUniformLocation(characterShader, "objectColor");

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // the main loop of the program where the window is created and the program runs
    // any code that you want to run in the game, you have to put it inside of this loop
    while (!glfwWindowShouldClose(window)) {
		// Check for events
        glfwPollEvents();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the background
        glUseProgram(backgroundShader);

        if (isStartPage) {
            glBindTexture(GL_TEXTURE_2D, startPage);
            glBindVertexArray(backgorundVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
        }
        else {
            glBindTexture(GL_TEXTURE_2D, backgroundTexture);
            glBindVertexArray(backgorundVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

            if (gameOver) {
                glBindTexture(GL_TEXTURE_2D, gameOverTexture);
                glBindVertexArray(backgorundVAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(GLuint)));
            }
            else {
                processMovements(window);
                enemyFollow(enemyPosition, characterPosition, enemySpeed);

                glUseProgram(characterShader);
                glUniform3f(colorLocation, 1.0f, 1.0f, 1.0f);
                drawAndTransformCharacter(characterShader, VAO, characterPosition);

                glUniform3f(colorLocation, 0.0f, 0.0f, 0.0f);
                drawAndTransformCharacter(characterShader, VAOenemy, enemyPosition);

				checkIfEnemyCaughtCharacter(enemyPosition, characterPosition);
            }
        }

        // Swap buffers
        glfwSwapBuffers(window);
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glDeleteVertexArrays(1, &VAOenemy);
    glDeleteBuffers(1, &VBOenemy);
    glDeleteBuffers(1, &EBOenemy);

    glDeleteVertexArrays(1, &backgorundVAO);
    glDeleteBuffers(1, &backgorundVBO);
    glDeleteBuffers(1, &backgorundEBO);


    glfwTerminate(); // close the program
    return 0;
}