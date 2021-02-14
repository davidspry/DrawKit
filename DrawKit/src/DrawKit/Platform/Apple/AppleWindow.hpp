//  DrawKit
//  Created by David Spry on 1/2/21.

#ifndef APPLEWINDOW_HPP
#define APPLEWINDOW_HPP

#include "dk.pch"
#include "Window.h"
#include "Application.hpp"
#include "OpenGLRenderer.hpp"

namespace DrawKit
{

class AppleWindow: public Window
{
public:
    AppleWindow(const Attributes & attributes);
    virtual ~AppleWindow();
    
public:
    void update() override;
    void setPosition(uint32_t x, uint32_t y) override;
    void setRenderer(Renderer* const renderer) override;
    void setEventResponder(Application* const responder) override;

public:
    uint32_t getWidth() const override;
    uint32_t getHeight() const override;
    std::string_view getTitle() const override;
    GLFWwindow* getGLFWWindow() const override;
    Renderer* getRenderer() const override;
    
private:
    virtual void initialise(const Attributes & attributes);
    virtual void deinitialise();

private:
    struct WindowData
    {
        Application*       responder;
        Window::Attributes attributes;
    }   data;
};

}

#endif
