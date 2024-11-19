#pragma once
#include "..\dependencies\glm\glm.hpp"
#include "..\dependencies\glm\gtc\matrix_transform.hpp"

class Camera {
private:
    glm::vec3 position;
    float zoomFactor;
    int width, height; // Adăugăm aceste variabile

public:
    Camera(glm::vec3 startPosition, int width, int height, float zoomFactor = 2.0f);

    void setDimensions(int width, int height); // Metodă pentru a seta dimensiunile ferestrei

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    glm::vec3 getPosition() const;
    void setPosition(glm::vec3 newPosition);
};
