//  DrawKit
//  Created by David Spry on 2/2/21.

#ifndef APPLICATION_MANAGER_HPP
#define APPLICATION_MANAGER_HPP

#include "dk.pch"
#include "Window.h"
#include "Application.hpp"
#include "OpenGLRenderer.hpp"

namespace DrawKit {

class ApplicationManager
{
private:
    ApplicationManager() = default;

public:
    static ApplicationManager * create();
    
public:
    void run(Application* application, const RendererType& rendererType, const Window::Attributes& attributes);
    
public:
    Renderer   * const getRenderer() const;
    GLFWwindow * const getGLFWWindow() const;
    Window     * const getPlatformWindow() const;
    
public:
    void setFrameRate(uint16_t frameRate);
    void setWindowPosition(int32_t x, int32_t y);

private:
    void matchDesiredFrameRate();
    
private:
    /// @brief   Construct the specified renderer.
    /// @param   renderer The desired renderer type.
    /// @warning The renderer should be constructed after the platform window has been initialised.

    Renderer * createRenderer(const RendererType & renderer);
    
    /// @brief Construct a concrete window implementation.
    /// @param attributes The desired window attributes.

    Window   * createPlatformWindow(const Window::Attributes& attributes);
    
private:
    GLFWwindow * window;
    Window     * platformWindow;
    Renderer   * renderer;
    
private:
    float frameStartTime;
    float frameDeltaTime;
    uint16_t framesPerSecond;
    
private:
    int32_t windowPositionX;
    int32_t windowPositionY;
};

}

#endif
