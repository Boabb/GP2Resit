#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <memory>

class Camera {
public:
    Camera() : yaw(0.0f), pitch(0.0f) {}

    void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip) {
        this->pos = pos;
        this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
        this->up = glm::vec3(0.0f, 1.0f, 0.0f);
        this->projection = glm::perspective(fov, aspect, nearClip, farClip);
    }

    glm::mat4 GetViewProjection() const {
        return projection * glm::lookAt(pos, pos + forward, up);
    }

    glm::mat4 GetViewMatrix() const {
        return glm::lookAt(pos, pos + forward, up);
	}

    glm::mat4 GetProjectionMatrix() const {
        return projection;
	}

    void MoveForward(float amt) {
        pos += forward * amt;
    }
    void MoveRight(float amt) {
        pos += glm::normalize(glm::cross(forward, up)) * amt;
    }
    void Pitch(float angle) {
        pitch += angle;
        updateVectors();
    }
    void Yaw(float angle) {
        yaw += angle;
        updateVectors();
    }
    glm::vec3 getPosition() const { return pos; }
    void setPosition(const glm::vec3& p) { pos = p; }

private:
    void updateVectors() {
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        forward = glm::normalize(direction);
    }
    glm::mat4 projection;
    glm::vec3 pos;
    glm::vec3 forward;
    glm::vec3 up;
    float yaw, pitch;
};


