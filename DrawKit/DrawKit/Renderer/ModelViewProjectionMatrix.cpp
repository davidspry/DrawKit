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
    origin = identity;
    scaled = identity;
    projection = identity;
}

const glm::mat4 & ModelViewProjectionMatrix::getMVPMatrix() const
{
    return matrix;
}

const glm::mat4 & ModelViewProjectionMatrix::getViewMatrix() const
{
    return view;
}

const glm::mat4 & ModelViewProjectionMatrix::getModelMatrix() const
{
    return model;
}

const glm::mat4 & ModelViewProjectionMatrix::getProjectionMatrix() const
{
    return projection;
}

void ModelViewProjectionMatrix::setViewMatrix(const glm::mat4 & matrix)
{
    view = matrix;
    
    update();
}

void ModelViewProjectionMatrix::setModelMatrix(const glm::mat4 & matrix)
{
    model = matrix;
    
    update();
}

void ModelViewProjectionMatrix::setProjectionMatrix(const glm::mat4 & matrix)
{
    projection = matrix;
    
    update();
}

void ModelViewProjectionMatrix::setTranslation(float x, float y, float z)
{
    view = glm::translate(glm::mat4(1.0f), {x, y, z});

    update();
}

void ModelViewProjectionMatrix::scale(float x, float y, float z)
{
    scaled = glm::scale(scaled, {x, y, z});
    
    update();
}

void ModelViewProjectionMatrix::rotateModel(float radians, float x, float y, float z)
{
    model = glm::rotate(model, radians, {x, y, z});

    update();
}

void ModelViewProjectionMatrix::rotateProjection(float radians, float x, float y, float z)
{
    projection = glm::rotate(projection, radians, {x, y, z});

    update();
}

void ModelViewProjectionMatrix::translate(float x, float y, float z)
{
    view = glm::translate(view, {x, y, z});

    update();
}

void ModelViewProjectionMatrix::update()
{
    matrix = projection * scaled * view * model * origin;
}

}
