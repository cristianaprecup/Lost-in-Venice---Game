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

#include "dependencies\SDL2_mixer-2.8.0\include\SDL_mixer.h"
#include "dependencies\SDL2-2.30.9\include\SDL.h"
#include "dependencies\SDL2-2.30.9\include\SDL_main.h"

//sound variable
Mix_Chunk* horrorSound = NULL;

// global variables
GLFWwindow* window;
const int width = 1904, height = 1424;

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

glm::vec3 keyPosition;

glm::vec3 characterPosition(-0.7f, 0.7f, 0.0f);
const float characterSpeed = 0.0001f;

glm::vec3 enemyPosition(-0.7f, -0.7f, 0.0f);
const float enemySpeed = 0.0001f;

glm::vec3 enemy2Position(0.7f, 0.7f, 0.0f); 
const float enemy2Speed = 0.0001f;

glm::vec3 ghostPosition(0.7f, -0.7, 0.0f); 
const float ghostSpeed = 0.00005f;

bool isCharacterVisible = true;  
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

// function for backgrounds
GLuint loadTexture(const char* filepath) {
    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
   
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

bool isCharacterorEnemyInWater(const glm::vec3& position) {
    // long river
    float water1X = -0.1f;
    float water1Y = -0.9f;
    float water1Width = 0.25f;
    float water1Height = 1.9f;

    // shorter river
    float water1aX = -0.1f;
    float water1aY = -0.9f;
    float water1aWidth = 0.32f;
    float water1aHeight = 0.3f;

    // vertical short river
    float water2X = -0.66f;
    float water2Y = -0.57f;
    float water2Width = 0.14f;
    float water2Height = 0.37f;

    // horizontal short river
    float water3X = -0.52f;
    float water3Y = -0.57f;
    float water3Width = 0.35f;
    float water3Height = 0.13f;

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

bool checkCollision(const glm::vec3& playerPos, const glm::vec3& staticPos, float size) {
    float halfSize = size / 2.0f;

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

                characterPosition = glm::vec3(-0.7f, 0.7f, 0.0f);;
                enemyPosition = glm::vec3(-0.7f, -0.7f, 0.0f);
				enemy2Position = glm::vec3(0.7f, 0.7f, 0.0f);
                ghostPosition = glm::vec3(0.7f, -0.7, 0.0f);
            }
        }
    }
    else if (isStartPage) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            if (ndc_x >= start_page_min_x && ndc_x <= start_page_max_x &&
                ndc_y >= start_page_min_y && ndc_y <= start_page_max_y) {
                isStartPage = false;
                gameOver = false;

                characterPosition = glm::vec3(-0.7f, 0.7f, 0.0f);;
                enemyPosition = glm::vec3(-0.7f, -0.7f, 0.0f);
                enemy2Position = glm::vec3(0.7f, 0.7f, 0.0f);
                ghostPosition = glm::vec3(0.7f, -0.7, 0.0f);
            }
        }
    }
}


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

    for (const auto& buildingPos : positions) {
        if (checkCollision(newPosition, buildingPos, 0.1f)) {
            return;
        }
    }

	// to keep the character inside the window
    if (newPosition.x > 1.0f) newPosition.x = 1.0f;
    if (newPosition.x < -1.0f) newPosition.x = -1.0f;
    if (newPosition.y > 1.0f) newPosition.y = 1.0f;
    if (newPosition.y < -1.0f) newPosition.y = -1.0f;

    characterPosition = newPosition;
}

void enemyFollow(glm::vec3& enemyPosition, const glm::vec3& characterPosition, float enemySpeed, const glm::vec3* obstacles, size_t obstacleCount, float obstacleSize) {
    glm::vec3 direction = characterPosition - enemyPosition;
    float length = glm::length(direction);

    if (length > 0.0f) {
        direction /= length; 

        glm::vec3 nextPosition = enemyPosition + direction * enemySpeed;

        bool collisionDetected = false;
        bool inWater = isCharacterorEnemyInWater(nextPosition);

        for (size_t i = 0; i < obstacleCount; ++i) {
            if (checkCollision(nextPosition, obstacles[i], obstacleSize)) {
                collisionDetected = true;
                break;
            }
        }

        if (collisionDetected || inWater) {
            float avoidDistance = enemySpeed * 1.5f;
			glm::vec3 avoidDirection1 = glm::normalize(glm::vec3(-direction.y, direction.x, 0.0f)); // 90 degrees 
			glm::vec3 avoidDirection2 = glm::normalize(glm::vec3(direction.y, -direction.x, 0.0f)); // -90 degrees

            glm::vec3 alternativePosition1 = enemyPosition + avoidDirection1 * avoidDistance;
            glm::vec3 alternativePosition2 = enemyPosition + avoidDirection2 * avoidDistance;

            bool collision1 = false, collision2 = false;

            for (size_t i = 0; i < obstacleCount; ++i) {
                if (checkCollision(alternativePosition1, obstacles[i], obstacleSize) || isCharacterorEnemyInWater(alternativePosition1)) {
                    collision1 = true;
                }
                if (checkCollision(alternativePosition2, obstacles[i], obstacleSize) || isCharacterorEnemyInWater(alternativePosition2)) {
                    collision2 = true;
                }
            }

            if (!collision1) {
                enemyPosition = alternativePosition1;
            }
            else if (!collision2) {
                enemyPosition = alternativePosition2;
            }
        }
        else {
            enemyPosition = nextPosition;
        }
    }
}

void ghostFollow(glm::vec3& ghostPosition, const glm::vec3& characterPosition, float ghostSpeed) {
    glm::vec3 direction = characterPosition - ghostPosition;
    float length = glm::length(direction);

    if (length > 0.0f) {
        direction /= length; 
        ghostPosition += direction * ghostSpeed; 
    }
}


void checkIfEnemyCaughtCharacter(const glm::vec3& enemyPosition, const glm::vec3& characterPosition) {
    float distance = sqrt((enemyPosition.x - characterPosition.x) * (enemyPosition.x - characterPosition.x) +
        (enemyPosition.y - characterPosition.y) * (enemyPosition.y - characterPosition.y));
    if (distance < 0.1f) {
        gameOver = true;
    }
}

glm::vec3 getRandomPosition(float minX, float maxX, float minY, float maxY) {
    float x = minX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxX - minX)));
    float y = minY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxY - minY)));
    return glm::vec3(x, y, 0.0f);
}


glm::vec3 getRandomKeyPosition(float minX, float maxX, float minY, float maxY) {
    glm::vec3 newPosition;
    bool validPosition = false;

    while (!validPosition) {
        newPosition = getRandomPosition(minX + 0.2f, maxX - 0.2f, minY + 0.2f, maxY - 0.2f);

        validPosition = true;

        if (isCharacterorEnemyInWater(newPosition)) {
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

int SDL_main(int argc, char* argv[]) 
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
    glewExperimental = true; 
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

    // Initialize SDL and SDL_mixer
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    // Load the horror sound
    horrorSound = Mix_LoadWAV("assets/horrorSound.wav");


    // Play the sound in a loop
    if (horrorSound != NULL) {
        Mix_PlayChannel(-1, horrorSound, -1);  // -1 to play on any available channel, -1 for infinite loop
    }

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

    // ----------------- Water Blocks ------------

    GLfloat waterVertices[] = {
        // long river
        -0.1f, 1.0f, 0.0f, 
        0.15f, 1.0f, 0.0f,  
        0.15f, -0.9f, 0.0f,  
        -0.1f, -0.9f, 0.0f,  

        // shorter river
        -0.1f, -0.6f, 0.0f, 
        0.22f, -0.6f, 0.0f,  
        0.22f, -0.9f, 0.0f,  
        -0.1f, -0.9f, 0.0f,

        // vertical short river
        -0.66f, -0.2f, 0.0f, 
        -0.52f, -0.2f, 0.0f,  
        -0.52f, -0.57f, 0.0f, 
        -0.66f, -0.57f, 0.0f, 

        // horizontal short river
        -0.52f, -0.44f, 0.0f, 
        -0.17f, -0.44f, 0.0f,  
        -0.17f, -0.57f, 0.0f,  
        -0.52f, -0.57f, 0.0f   
    };



    GLuint waterIndices[] = {
        //long river
        0, 1, 2,   
        2, 3, 0,   

        // shorter river
        4, 5, 6,   
        6, 7, 4,   

        // vertical short river
        8, 9, 10,  
        10, 11, 8, 

        // horizontal short river
        12, 13, 14, 
        14, 15, 12  
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ----------------- Key ------------
    keyPosition = glm::vec3(0.3f, 0.3f, 0.0f);

    //-------------------key----------------------

    float keyVertices[] = {
        0.015f,  0.015f, 0.0f,  
        0.015f, -0.015f, 0.0f,  
        -0.015f, -0.015f, 0.0f, 
        -0.015f,  0.015f, 0.0f, 

        -0.009f, -0.009f, 0.0f, 
        0.009f, -0.009f, 0.0f,  
        0.009f, -0.06f, 0.0f,  
        -0.009f, -0.06f, 0.0f  
    };

    unsigned int keyIndices[] = {
        0, 1, 2,
        2, 3, 0,

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


    GLint objectColorLocation = glGetUniformLocation(waterShader, "objectColor");

    int colorLocation = glGetUniformLocation(characterShader, "objectColor");

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Check for events
        glfwPollEvents();

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

				enemyFollow(enemyPosition, characterPosition, enemySpeed, positions, sizeof(positions) / sizeof(glm::vec3), 0.1f);
                enemyFollow(enemy2Position, characterPosition, enemy2Speed, positions, sizeof(positions) / sizeof(glm::vec3), 0.1f);
                ghostFollow(ghostPosition, characterPosition, ghostSpeed);

                glUseProgram(waterShader);
                glUniform4f(objectColorLocation, 0.0f, 0.0f, 0.0f, 0.0f); // transparent water 
                glBindVertexArray(waterVAO);
                glDrawElements(GL_TRIANGLES, sizeof(waterIndices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

                isCharacterVisible = !isCharacterorEnemyInWater(characterPosition);

                if (isCharacterVisible) {
                    glUseProgram(characterShader);
                    glUniform3f(colorLocation, 1.0f, 1.0f, 1.0f);
                    drawAndTransformCharacter(characterShader, VAO, characterPosition);
                }

                glUseProgram(characterShader);

                glUniform3f(colorLocation, 0.0f, 0.0f, 0.0f);
                drawAndTransformCharacter(characterShader, VAOenemy, enemyPosition);

                glUniform3f(colorLocation, 0.0f, 0.0f, 0.0f); 
                drawAndTransformCharacter(characterShader, VAOenemy, enemy2Position);

                glUniform3f(colorLocation, 0.7f, 0.7f, 0.7f);
                drawAndTransformCharacter(characterShader, VAOenemy, ghostPosition);

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

                
                checkIfEnemyCaughtCharacter(enemyPosition, characterPosition);
				checkIfEnemyCaughtCharacter(enemy2Position, characterPosition);
                checkIfEnemyCaughtCharacter(ghostPosition, characterPosition);
            }
        }

        glfwSwapBuffers(window);
    }

    // Cleanup code 
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

    // Cleanup and close SDL_mixer
    Mix_FreeChunk(horrorSound);
    Mix_CloseAudio();
    SDL_Quit();

    glfwTerminate(); // close the program
    return 0;
}