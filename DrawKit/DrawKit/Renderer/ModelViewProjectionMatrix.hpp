//  DrawKit
//  Created by David Spry on 23/2/21.

#ifndef MODEL_VIEW_PROJECTION_MATRIX_HPP
#define MODEL_VIEW_PROJECTION_MATRIX_HPP

#include "dk.pch"

namespace DrawKit {

class ModelViewProjectionMatrix
{
public:
    ModelViewProjectionMatrix();
    
public:
    const glm::mat4 & getMVPMatrix() const;
    const glm::mat4 & getViewMatrix() const;
    const glm::mat4 & getModelMatrix() const;
    const glm::mat4 & getProjectionMatrix() const;

public:
    void setViewMatrix(const glm::mat4 & matrix);
    void setModelMatrix(const glm::mat4 & matrix);
    void setProjectionMatrix(const glm::mat4 & matrix);
    void setTranslation(float x, float y, float z);

public:
    void scale(float x, float y, float z);
    void rotateModel(float radians, float x, float y, float z);
    void rotateProjection(float radians, float x, float y, float z);
    void translate(float x, float y, float z);
    
private:
    void update();
    
private:
    glm::mat4 matrix;
    glm::mat4 view;
    glm::mat4 model;
    glm::mat4 scaled;
    glm::mat4 origin;
    glm::mat4 projection;
};

}

#endif
