//  DrawKit
//  Created by David Spry on 23/1/21.

#ifndef WINDOW_H
#define WINDOW_H

#include "dk.pch"
#include "Renderer.hpp"
#include "Application.hpp"

namespace DrawKit
{

class Window
{
public:
    struct Attributes
    {
        uint32_t width;
        uint32_t height;
        std::string title;

        Attributes(const std::string & windowTitle = "DrawKit",
                   const uint32_t windowWidth  = 1100,
                   const uint32_t windowHeight = 1100):
        title(windowTitle), width(windowWidth), height(windowHeight)
        {
            
        }
    };
    
public:
    virtual ~Window() = default;

public:
    /// @brief Create a window with the given attributes.
    /// @param attributes The desired window attributes.
    /// @note  This should be defined in a platform window subclass.

    static Window * create(const Attributes & attributes = {});
    inline static bool glfwInitialised = false;

public:
    virtual void update() = 0;
    virtual void setPosition(uint32_t x, uint32_t y) = 0;
    virtual void setRenderer(Renderer* const renderer) = 0;
    virtual void setEventResponder(Application* const responder) = 0;
    
public:
    virtual uint32_t getWidth()  const = 0;
    virtual uint32_t getHeight() const = 0;
    virtual std::string_view getTitle() const = 0;
    virtual GLFWwindow* getGLFWWindow() const = 0;
    virtual Renderer* getRenderer() const = 0;
    
public:
    inline static void glfwErrorCallback(int error, const char* description)
    {
        DK_LOG("GLFW", "ERROR #", error, ": ", description);
    }

protected:
    GLFWwindow * window;
    Renderer   * renderer;
};

}

#endif
