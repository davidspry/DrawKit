//  DrawKit
//  Created by David Spry on 26/2/21.

#include "Camera.hpp"

namespace DrawKit {

void Camera::begin()
{
    getRenderer()->pushMatrix(matrix);
}

void Camera::end()
{
    getRenderer()->popMatrix();
}

void Camera::lookAtPoint(const UIPoint<float> &xyz)
{
    lookAtPoint(xyz.x, xyz.y, xyz.z);
}

void Camera::lookAtPoint(float x, float y, float z)
{
    glm::vec3 const target = { x, y, z };
    glm::vec3 const upward = { 0.0f, 1.0f, 0.0f };
    glm::vec3 const camera = { position.x, position.y, position.z };
    glm::mat4 const viewMatrix = glm::lookAt(camera, target, upward);

    matrix.setViewMatrix(viewMatrix);
}

void Camera::setPosition(const UIPoint<float> &xyz)
{
    setPosition(xyz.x, xyz.y, xyz.z);
}

void Camera::setPosition(float x, float y, float z)
{
    translate(std::fabsf(position.x) - x,
              std::fabsf(position.y) - y,
              std::fabsf(position.z) - z);

    position.x = x;
    position.y = y;
    position.z = z;
}

void Camera::scale(float scaleFactor)
{
    matrix.scale(scaleFactor, scaleFactor, scaleFactor);
}

void Camera::translate(float x, float y, float z)
{
    matrix.translate(x, y, z);
}

void Camera::rotateByDegrees(float degrees, float x, float y, float z)
{
    float const radians = glm::radians(degrees);
    
    matrix.rotateProjection(radians, x, y, z);
}

void Camera::rotateByRadians(float radians, float x, float y, float z)
{
    matrix.rotateModel(radians, x, y, z);
}

}
