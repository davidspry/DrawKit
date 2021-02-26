//  DrawKit
//  Created by David Spry on 26/2/21.

#ifndef ORTHOGRAPHIC_CAMERA_HPP
#define ORTHOGRAPHIC_CAMERA_HPP

#include "Camera.hpp"

namespace DrawKit {

/// @brief An orthographic camera capable of isometric projection.

class OrthographicCamera: public Camera
{
public:
    /// @brief Create an orthographic camera at origin (0, 0, 0).
    
    OrthographicCamera();
    
    /// @brief Create an orthographic camera at the given origin point.
    /// @param x The x-coordinate of the desired origin point.
    /// @param y The y-coordinate of the desired origin point.
    /// @param z The z-coordinate of the desired origin point.

    OrthographicCamera(float x, float y, float z);
    
    /// @brief Create an orthographic camera at the given origin point.
    /// @param origin The desired origin point.

    OrthographicCamera(const UIPoint<float> & origin);

public:
    /// @brief Begin using the orthographic camera.

    void begin() override;
    
public:
    /// @brief The available isometric view orientations.

    enum class IsometricOrientation { L, R };

public:
    /// @brief Use the orthographic camera's isometric view.

    void viewIsometric() noexcept;

    /// @brief Use the orthographic camera's birdseye view.

    void viewFromAbove() noexcept;

    /// @brief Indicate whether the camera is currently using its birdseye view or not.

    bool isViewingFromAbove() noexcept;
    
public:
    /// @brief Set the orientation fo the camera's isometric view.
    /// @param orientation The index of the desired orientation.

    void setIsometricOrientation(uint8_t orientation) noexcept;
    
    /// @brief Set the orientation of the camera's isometric view.
    /// @param orientation The desired orientation.

    void setIsometricOrientation(IsometricOrientation orientation) noexcept;

private:
    /// @brief Initialise the camera's attributes.
    /// @param x The x-coordinate of the camera's origin point.
    /// @param y The y-coordinate of the camera's origin point.
    /// @param z The z-coordinate of the camera's origin point.

    void initialise(float x, float y, float z);
    
    /// @brief Set the camera's orientation by computing its underlying projection matrix.
    /// @param W The width of the viewport.
    /// @param H The height of the viewport.

    void setCameraOrientation(const int W, const int H);
    
private:
    float farClip;
    float nearClip;
    
private:
    bool viewingFromAbove;
    
private:
    IsometricOrientation isometricOrientation;
};

}

#endif
