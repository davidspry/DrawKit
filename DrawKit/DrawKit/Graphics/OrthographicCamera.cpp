//  DrawKit
//  Created by David Spry on 26/2/21.

#include "OrthographicCamera.hpp"

namespace DrawKit {

OrthographicCamera::OrthographicCamera()
{
    initialise(0.0f, 0.0f, 0.0f);

    viewFromAbove();
}

OrthographicCamera::OrthographicCamera(float x, float y, float z)
{
    initialise(x, y, z);
    
    viewFromAbove();
}

OrthographicCamera::OrthographicCamera(const UIPoint<float> & origin)
{
    initialise(origin.x, origin.y, origin.z);

    viewFromAbove();
}

void OrthographicCamera::initialise(float x, float y, float z)
{
    farClip  = +10000.0f;
    nearClip = -10000.0f;

    setPosition(x, y, z);
}

void OrthographicCamera::begin()
{
    float const W = static_cast<float>(getWindowWidth());
    float const H = static_cast<float>(getWindowHeight());
    
    if (!(windowSize.w == W && windowSize.h == H && initialised))
    {
        windowSize.w = W;
        windowSize.h = H;
        
        setCameraOrientation(W, H);
    }

    Camera::begin();
}

void OrthographicCamera::viewFromAbove() noexcept
{
    viewingFromAbove = true;
    
    setCameraOrientation(windowSize.w, windowSize.h);
}

void OrthographicCamera::viewIsometric() noexcept
{
    viewingFromAbove = false;

    setCameraOrientation(windowSize.w, windowSize.h);
}

bool OrthographicCamera::isViewingFromAbove() noexcept
{
    return viewingFromAbove;
}

void OrthographicCamera::setIsometricOrientation(uint8_t orientation) noexcept
{
    const auto index = static_cast<bool>(orientation);
    const auto k = static_cast<IsometricOrientation>(index);

    setIsometricOrientation(k);
}

void OrthographicCamera::setIsometricOrientation(IsometricOrientation orientation) noexcept
{
    isometricOrientation = orientation;
    
    if (!isViewingFromAbove())
    {
        viewIsometric();
    }
}

void OrthographicCamera::setCameraOrientation(const int W, const int H)
{
    glm::mat4 ortho = glm::ortho(-0.5f * W, 0.5f * W, 0.5f * H, -0.5f * H, nearClip, farClip);

    if (!viewingFromAbove)
    {
        const float k = isometricOrientation == IsometricOrientation::L ? -1.0f : 1.0f;
        ortho = glm::rotate(ortho, glm::radians(35.264f), glm::vec3(1.0f, 0.0f, 0.0f));
        ortho = glm::rotate(ortho, glm::radians(45.000f), glm::vec3(0.0f, 0.0f, k));
    }

    matrix.setProjectionMatrix(ortho);
    matrix.setTranslation(-0.5f * W, -0.5f * H, 0.0f);
    
    initialised = true;
}

// MARK: - Coordinate space conversion

}
