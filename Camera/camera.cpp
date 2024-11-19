#include "camera.h"

Camera::Camera(glm::vec3 startPosition, int width, int height, float zoomFactor)
    : position(startPosition), zoomFactor(zoomFactor), width(width), height(height) {}

void Camera::setDimensions(int width, int height) {
    this->width = width;
    this->height = height;
}

glm::mat4 Camera::getProjectionMatrix() const {
    float aspectRatio = (float)width / (float)height;
    return glm::ortho(
        -0.5f * width / zoomFactor, 0.5f * width / zoomFactor,
        -0.5f * height / zoomFactor, 0.5f * height / zoomFactor,
        -1.0f, 1.0f
    );
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::translate(glm::mat4(1.0f), -position);
}

glm::vec3 Camera::getPosition() const {
    return position;
}

void Camera::setPosition(glm::vec3 newPosition) {
    position = newPosition;
}
