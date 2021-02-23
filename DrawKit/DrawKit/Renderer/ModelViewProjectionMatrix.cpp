//  DrawKit
//  Created by David Spry on 23/2/21.

#include "ModelViewProjectionMatrix.hpp"

namespace DrawKit {

ModelViewProjectionMatrix::ModelViewProjectionMatrix()
{
    glm::mat4 const identity = glm::identity<glm::mat4>();

    view   = identity;
    model  = identity;
    matrix = identity;
    position   = identity;
    projection = identity;
}

const glm::mat4 & ModelViewProjectionMatrix::getMVPMatrix()
{
    return matrix;
}

void ModelViewProjectionMatrix::setProjectionBounds(uint32_t width, uint32_t height)
{
    if (windowSize.w != width ||
        windowSize.h != height)
    {
        windowSize.w = width;
        windowSize.h = height;
        useOrthographicProjection();
    }
}

void ModelViewProjectionMatrix::useOrthographicProjection()
{
    const float W = windowSize.w;
    const float H = windowSize.h;

    projection = glm::ortho(-0.5f * W, +0.5f * W, +0.5f * H, -0.5f * H, -10000.0f, +10000.0f);
    position   = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f * W, -0.5f * H, 0.0f));

    update();
}

void ModelViewProjectionMatrix::usePerspectiveProjection(float fieldOfView)
{
    const float W = windowSize.w;
    const float H = windowSize.h;
    const float aspectRatio = W / H;

    projection = glm::perspective(fieldOfView, aspectRatio, 1.0f, 950.0f);
    position   = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f * W, -0.5f * H, 0.0f));

    update();
}

void ModelViewProjectionMatrix::scale(float x, float y, float z)
{
    projection = glm::scale(projection, {x, y, z});
    
    update();
}

void ModelViewProjectionMatrix::rotate(float radians, float x, float y, float z)
{
    projection = glm::rotate(projection, radians, {x, y, z});

    update();
}

void ModelViewProjectionMatrix::translate(float x, float y, float z)
{
    model = glm::translate(glm::mat4(1.0f), {x, y, z});

    update();
}

void ModelViewProjectionMatrix::update()
{
    matrix = projection * view * position * model;
}

}
