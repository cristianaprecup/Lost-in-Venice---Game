// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>


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
glm::vec3 keyPosition;//Stores the position of the key in the game 


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

    glm::vec3(-0.7f, 0.88f, 0.0f),  //16

    glm::vec3(-0.78f, 0.52f, 0.0f),  //5
    glm::vec3(-0.78f, 0.46f, 0.0f),
    glm::vec3(-0.9f, 0.52f, 0.0f),
    glm::vec3(-0.9f, 0.46f, 0.0f),

    glm::vec3(-0.9f, 0.27f, 0.0f),   //6

    glm::vec3(-0.87f, 0.05f, 0.0f),  //7

    glm::vec3(-0.86f, -0.15f, 0.0f),   //8

    glm::vec3(-0.85f, -0.4f, 0.0f),  //9
    glm::vec3(-0.85f, -0.48f, 0.0f),

    glm::vec3(-0.95f, -0.7f, 0.0f),   //10
    glm::vec3(-0.95f, -0.8f, 0.0f),

    glm::vec3(-0.6f, -0.7f, 0.0f),   //17
    glm::vec3(-0.6f, -0.75f, 0.0f),

    glm::vec3(-0.38f, -0.85f, 0.0f),   //18
    glm::vec3(-0.38f, -0.9f, 0.0f),

    glm::vec3(-0.88f, -0.88f, 0.0f),   //11

    glm::vec3(-0.27f, -0.09f, 0.0f), //12

    glm::vec3(-0.27f, -0.35f, 0.0f),  //13

    glm::vec3(-0.37f, -0.08f, 0.0f), //14
    glm::vec3(-0.4f, -0.2f, 0.0f),
    glm::vec3(-0.4f, -0.35f, 0.0f),

    glm::vec3(-0.2f, 0.88f, 0.0f), //15
    glm::vec3(-0.2f, 0.83f, 0.0f),





   glm::vec3(0.6f, -0.22f, 0.0f),  //8**
   glm::vec3(0.55f, -0.22f, 0.0f),

   glm::vec3(0.5f, -0.65f, 0.0f),  //10**
   glm::vec3(0.5f, -0.75f, 0.0f),
   glm::vec3(0.6f, -0.65f, 0.0f),
   glm::vec3(0.6f, -0.75f, 0.0f),

   glm::vec3(0.22f, -0.35f, 0.0f),  //12*
   glm::vec3(0.22f, -0.45f, 0.0f),
   glm::vec3(0.3f, -0.35f, 0.0f),
   glm::vec3(0.3f, -0.45f, 0.0f),

   glm::vec3(0.5f, 0.24f, 0.0f),  //3*
   glm::vec3(0.5f, 0.15f, 0.0f),
   glm::vec3(0.6f, 0.24f, 0.0f),
   glm::vec3(0.6f, 0.15f, 0.0f),

   glm::vec3(0.22f, 0.24f, 0.0f),  //2*
   glm::vec3(0.22f, 0.05f, 0.0f),

   glm::vec3(0.22f, 0.7f, 0.0f),  //1*
   glm::vec3(0.22f, 0.55f, 0.0f),

   glm::vec3(0.4f, 0.85f, 0.0f),  //111
   glm::vec3(0.4f, 0.8f, 0.0f),
   glm::vec3(0.5f, 0.8f, 0.0f),
   glm::vec3(0.22f, 0.85f, 0.0f),
   glm::vec3(0.22f, 0.8f, 0.0f),

   glm::vec3(0.75f, 0.85f, 0.0f),  //4*
   glm::vec3(0.75f, 0.8f, 0.0f),
   glm::vec3(0.9f, 0.85f, 0.0f),
   glm::vec3(0.9f, 0.8f, 0.0f),

   glm::vec3(0.9f, 0.7f, 0.0f),  //5*

   glm::vec3(0.78f, 0.45f, 0.0f),  //6*
   glm::vec3(0.78f, 0.5f, 0.0f),
   glm::vec3(0.9f, 0.45f, 0.0f),
   glm::vec3(0.9f, 0.5f, 0.0f),


    glm::vec3(0.85f, 0.1f, 0.0f),  //7*

    glm::vec3(0.85f, -0.2f, 0.0f),  //8*

    glm::vec3(0.82f, -0.45f, 0.0f),  //9*
    glm::vec3(0.82f, -0.48f, 0.0f),

    glm::vec3(0.9f, -0.7f, 0.0f),   //10*
    glm::vec3(0.9f, -0.8f, 0.0f),

    glm::vec3(0.85f, -0.88f, 0.0f),   //11*

};

// Function to generate a random position within bounds
glm::vec3 getRandomPosition(float minX, float maxX, float minY, float maxY) {
    float x = minX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxX - minX)));
    float y = minY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxY - minY)));
    return glm::vec3(x, y, 0.0f);
}

glm::vec3 characterPosition(-0.7f, 0.7f, 0.0f);
const float characterSpeed = 0.0001f;

bool isCharacterVisible = true;  // Used to control the character's visibility

// Check if the character is within the water area
bool isCharacterInWater() {
    // First water area coordinates (long river)
    float water1X = -0.1f;
    float water1Y = -0.9f;
    float water1Width = 0.25f;
    float water1Height = 1.9f;

    // First* water area coordinates (shorter river)
    float water1aX = -0.1f;
    float water1aY = -0.9f;
    float water1aWidth = 0.32f;
    float water1aHeight = 0.3f;

    // Second water area coordinates (vertical short river)
    float water2X = -0.66f;
    float water2Y = -0.57f;
    float water2Width = 0.14f;
    float water2Height = 0.37f;

    // Third water area coordinates (horizontal short river)
    float water3X = -0.52f;
    float water3Y = -0.57f;
    float water3Width = 0.35f;
    float water3Height = 0.13f;

    bool inFirstWater = (characterPosition.x > water1X && characterPosition.x < water1X + water1Width &&
        characterPosition.y > water1Y && characterPosition.y < water1Y + water1Height);

    bool inFirstaWater = (characterPosition.x > water1aX && characterPosition.x < water1aX + water1aWidth &&
        characterPosition.y > water1aY && characterPosition.y < water1aY + water1aHeight);

    bool inSecondWater = (characterPosition.x > water2X && characterPosition.x < water2X + water2Width &&
        characterPosition.y > water2Y && characterPosition.y < water2Y + water2Height);

    bool inThirdWater = (characterPosition.x > water3X && characterPosition.x < water3X + water3Width &&
        characterPosition.y > water3Y && characterPosition.y < water3Y + water3Height);

    return inFirstWater || inFirstaWater || inSecondWater || inThirdWater;
}



glm::vec3 enemyPosition(0.0f, 0.0f, 0.0f);
const float enemySpeed = 0.00001f;

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

bool checkCollision(const glm::vec3& playerPos, const glm::vec3& staticPos, float size) {
    float halfSize = size / 2.0f;

    // Check if the player's square intersects with the static square
    return (playerPos.x + halfSize > staticPos.x - halfSize &&
        playerPos.x - halfSize < staticPos.x + halfSize &&
        playerPos.y + halfSize > staticPos.y - halfSize &&
        playerPos.y - halfSize < staticPos.y + halfSize);
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


// Function to process the movements of the character
void processMovements(GLFWwindow* window) {
    glm::vec3 newPosition = characterPosition;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        newPosition.y += characterSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        newPosition.y -= characterSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        newPosition.x += characterSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        newPosition.x -= characterSpeed;

    // Check for collisions with buildings (not in the water logic)
    for (const auto& buildingPos : positions) {
        if (checkCollision(newPosition, buildingPos, 0.1f)) {
            return; // Cancel movement on collision
        }
    }

    // Update character position and visibility based on water area
    characterPosition = newPosition;
    isCharacterVisible = !isCharacterInWater();  // Hide character if in water
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

//the key doesn't generate in water/blocks 

bool isPositionInWater(const glm::vec3& position) {
    float water1X = -0.1f, water1Y = -0.9f, water1Width = 0.25f, water1Height = 1.9f;
    float water1aX = -0.1f, water1aY = -0.9f, water1aWidth = 0.32f, water1aHeight = 0.3f;
    float water2X = -0.66f, water2Y = -0.57f, water2Width = 0.14f, water2Height = 0.37f;
    float water3X = -0.52f, water3Y = -0.57f, water3Width = 0.35f, water3Height = 0.13f;

    bool inFirstWater = (position.x > water1X && position.x < water1X + water1Width &&
        position.y > water1Y && position.y < water1Y + water1Height);
    bool inFirstaWater = (position.x > water1aX && position.x < water1aX + water1aWidth &&
        position.y > water1aY && position.y < water1aY + water1aHeight);
    bool inSecondWater = (position.x > water2X && position.x < water2X + water2Width &&
        position.y > water2Y && position.y < water2Y + water2Height);
    bool inThirdWater = (position.x > water3X && position.x < water3X + water3Width &&
        position.y > water3Y && position.y < water3Y + water3Height);

    return inFirstWater || inFirstaWater || inSecondWater || inThirdWater;
}
//Generates a random valid position for the within given range 

glm::vec3 getRandomKeyPosition(float minX, float maxX, float minY, float maxY) {
    glm::vec3 newPosition;
    bool validPosition = false;

    while (!validPosition) {
        // Generate a random position within a slightly smaller range to avoid borders
        newPosition = getRandomPosition(minX + 0.2f, maxX - 0.2f, minY + 0.2f, maxY - 0.2f);

        validPosition = true;
        // Check if the key is in water
        if (isPositionInWater(newPosition)) {
            validPosition = false;
            continue;
        }
        // Check for collision with blocks
        for (const auto& blockPos : positions) {
            if (checkCollision(newPosition, blockPos, 0.1f)) {
                validPosition = false;
                break;
            }
        }
    }
    return newPosition;
}


//-----------------


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
  

    // Initialize specific key position to a place

    keyPosition = glm::vec3(0.3f, 0.3f, 0.0f); 

    //-------------------key----------------------

    float keyVertices[] = {
        // Head of the key (square)
        0.015f,  0.015f, 0.0f,  // top right
        0.015f, -0.015f, 0.0f,  // bottom right
        -0.015f, -0.015f, 0.0f, // bottom left
        -0.015f,  0.015f, 0.0f, // top left

        // Stem of the key (rectangle)
        -0.009f, -0.009f, 0.0f, // top left of the stem
        0.009f, -0.009f, 0.0f,  // top right of the stem
        0.009f, -0.06f, 0.0f,  // bottom right of the stem
        -0.009f, -0.06f, 0.0f  // bottom left of the stem
    };

    unsigned int keyIndices[] = {
        // Indices for the square (head)
        0, 1, 2,
        2, 3, 0,

        // Indices for the rectangle (stem)
        4, 5, 6,
        6, 7, 4
    };


    GLuint keyVAO, keyVBO, keyEBO;
    glGenVertexArrays(1, &keyVAO);
    glGenBuffers(1, &keyVBO);
    glGenBuffers(1, &keyEBO);

    glBindVertexArray(keyVAO);
    glBindBuffer(GL_ARRAY_BUFFER, keyVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(keyVertices), keyVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, keyEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(keyIndices), keyIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    //keyPosition = getRandomKeyPosition(-1.0f, 1.0f, -1.0f, 1.0f);
  
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
          0.5f,  0.4f, 0.0f,  1.0f, 1.0,
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

    // ----------------- Water Blocks ------------

    GLfloat waterVertices[] = {
        // First water area (long river)
        -0.1f, 1.0f, 0.0f, // Top left
        0.15f, 1.0f, 0.0f,  // Top right
        0.15f, -0.9f, 0.0f,  // Bottom right
        -0.1f, -0.9f, 0.0f,  // Bottom left

        // First* water area (shorter river)
        -0.1f, -0.6f, 0.0f, // Top left
        0.22f, -0.6f, 0.0f,  // Top right
        0.22f, -0.9f, 0.0f,  // Bottom right
        -0.1f, -0.9f, 0.0f,  // Bottom left

        // Second water area (vertical short river)
        -0.66f, -0.2f, 0.0f, // Top left
        -0.52f, -0.2f, 0.0f,  // Top right
        -0.52f, -0.57f, 0.0f,  // Bottom right
        -0.66f, -0.57f, 0.0f,  // Bottom left

        // Third water area (horizontal short river)
        -0.52f, -0.44f, 0.0f, // Top left
        -0.17f, -0.44f, 0.0f,  // Top right
        -0.17f, -0.57f, 0.0f,  // Bottom right
        -0.52f, -0.57f, 0.0f   // Bottom left
    };



    GLuint waterIndices[] = {
        // First water area (long river)
        0, 1, 2,   // First triangle
        2, 3, 0,   // Second triangle

        // First* water area (shorter river)
        4, 5, 6,   // First triangle
        6, 7, 4,   // Second triangle

        // Second water area (vertical short river)
        8, 9, 10,  // First triangle
        10, 11, 8, // Second triangle

        // Third water area (horizontal short river)
        12, 13, 14, // First triangle
        14, 15, 12  // Second triangle
    };




    GLuint waterVAO, waterVBO, waterEBO;
    glGenVertexArrays(1, &waterVAO);
    glGenBuffers(1, &waterVBO);
    glGenBuffers(1, &waterEBO);

    glBindVertexArray(waterVAO);
    glBindBuffer(GL_ARRAY_BUFFER, waterVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(waterVertices), waterVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, waterEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(waterIndices), waterIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint waterShader = LoadShaders("WaterVertexShader.vertexshader", "WaterFragmentShader.fragmentshader");
    if (waterShader == 0) {
        std::cerr << "Failed to load water shaders!" << std::endl;
        return -1;
    }

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Bind the water shader program
    glUseProgram(waterShader);

    // Set the objectColor uniform to fully transparent
    GLint objectColorLocation = glGetUniformLocation(waterShader, "objectColor");
    glUniform4f(objectColorLocation, 0.0f, 0.0f, 0.0f, 0.0f);  // RGBA values for fully transparent

    // Now you can draw the water object
    glBindVertexArray(waterVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // The main loop of the program where the window is created and the program runs
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Check for events
        glfwPollEvents();

        // Render background texture
        glUseProgram(backgroundShader);
        glBindVertexArray(backgorundVAO);
        glBindTexture(GL_TEXTURE_2D, backgroundTexture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

                // Update character's visibility based on water area
                isCharacterVisible = !isCharacterInWater();

                // Render the water
                glUseProgram(waterShader);
                glUniform4f(objectColorLocation, 0.0f, 0.0f, 0.0f, 0.0f);  // Ensure the water is fully transparent  
                glBindVertexArray(waterVAO);
                glDrawElements(GL_TRIANGLES, sizeof(waterIndices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

                // Render the character if visible
                if (isCharacterVisible) {
                    glUseProgram(characterShader);
                    glUniform3f(colorLocation, 1.0f, 1.0f, 1.0f); // Character color
                    drawAndTransformCharacter(characterShader, VAO, characterPosition);
                }

                // Render the enemy
                glUseProgram(characterShader);
                glUniform3f(colorLocation, 0.0f, 0.0f, 0.0f); // Enemy color
                drawAndTransformCharacter(characterShader, VAOenemy, enemyPosition);

                // Check if the enemy caught the character
                checkIfEnemyCaughtCharacter(enemyPosition, characterPosition);

                // Render the key
                glUseProgram(characterShader);
                glUniform3f(glGetUniformLocation(characterShader, "objectColor"), 1.0f, 1.0f, 0.0f); // Yellow color for the key
                glBindVertexArray(keyVAO);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), keyPosition); // Use keyPosition here
                glUniformMatrix4fv(glGetUniformLocation(characterShader, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
                glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0); // Adjust the count to match the new indices

                // Check if the key is caught by the character
                if (checkCollision(characterPosition, keyPosition, 0.05f)) { // Use keyPosition here
                    std::cout << "Key caught! Repositioning key." << std::endl;
                    keyPosition = getRandomKeyPosition(-1.0f, 1.0f, -1.0f, 1.0f); // Use keyPosition here
                }
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

    glDeleteVertexArrays(1, &waterVAO);
    glDeleteBuffers(1, &waterVBO);
    glDeleteBuffers(1, &waterEBO);

    glfwTerminate(); // Close the program
    return 0;
}

