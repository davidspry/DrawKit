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
    const glm::mat4 & getMVPMatrix();
    
public:
    void useOrthographicProjection();
    void usePerspectiveProjection(float fieldOfView);
    void setProjectionBounds(uint32_t width, uint32_t height);

public:
    void scale(float x, float y, float z);
    void rotate(float radians, float x, float y, float z);
    void translate(float x, float y, float z);
    
private:
    void update();
    
private:
    glm::mat4 matrix;
    glm::mat4 view;
    glm::mat4 model;
    glm::mat4 position;
    glm::mat4 projection;
    
private:
    UISize<uint32_t> windowSize;
};

}

#endif
