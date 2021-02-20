//  DrawKit
//  Created by David Spry on 1/2/21.

#include "AppleWindow.hpp"

namespace DrawKit {

Window * Window::create(const Attributes & attributes)
{
    return new AppleWindow(attributes);
}

AppleWindow::AppleWindow(const Attributes & attributes)
{
    initialise(attributes);
}

AppleWindow::~AppleWindow()
{
    deinitialise();
}

void AppleWindow::update()
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void AppleWindow::setPosition(uint32_t x, uint32_t y)
{
    glfwSetWindowPos(window, x, y);
}

void AppleWindow::setRenderer(Renderer * const renderer)
{
    this->renderer = renderer;
}

void AppleWindow::setEventResponder(Application * const responder)
{
    data.responder = responder;
}

uint32_t AppleWindow::getWidth() const
{
    return data.attributes.width;
}

uint32_t AppleWindow::getHeight() const
{
    return data.attributes.height;
}

std::string_view AppleWindow::getTitle() const
{
    return data.attributes.title;
}

GLFWwindow* AppleWindow::getGLFWWindow() const
{
    return window;
}

Renderer* AppleWindow::getRenderer() const
{
    return renderer;
}

void AppleWindow::initialise(const Attributes & attr)
{
    data.attributes.title  = attr.title;
    data.attributes.width  = attr.width;
    data.attributes.height = attr.height;
    
    if (!glfwInitialised)
    {
        glfwInitialised = glfwInit();
        glfwSetErrorCallback(&glfwErrorCallback);
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(attr.width, attr.height, attr.title.c_str(), nullptr, nullptr);
    
    glfwSetWindowUserPointer(window, &data);
    glfwSetWindowPos(window, 35, 65);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
    {
        WindowData const & data = *((WindowData*) glfwGetWindowUserPointer(window));
        
        data.responder->windowClosed();
    });
    
    glfwSetScrollCallback(window, [](GLFWwindow* window, double x, double y)
    {
        WindowData const & data = *((WindowData*) glfwGetWindowUserPointer(window));
        
        data.responder->mouseScrolled(static_cast<float>(x), static_cast<float>(y));
    });
    
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y)
    {
        WindowData const & data = *((WindowData*) glfwGetWindowUserPointer(window));
        
        data.responder->mouseMoved(static_cast<float>(x), static_cast<float>(y));
    });
    
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        WindowData & data = *((WindowData*) glfwGetWindowUserPointer(window));
        
        const uint32_t W = static_cast<uint32_t>(width);
        const uint32_t H = static_cast<uint32_t>(height);
        
        data.attributes.width  = W;
        data.attributes.height = H;
        data.responder->windowResized(W, H);
        data.responder->windowDidResize();
    });
    
    glfwSetDropCallback(window, [](GLFWwindow* window, int pathsCount, const char * paths [])
    {
        WindowData const & data = *((WindowData*) glfwGetWindowUserPointer(window));
        
        return data.responder->windowReceivedPaths(pathsCount, paths);
    });
    
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int modifiers)
    {
        WindowData const & data = *((WindowData*) glfwGetWindowUserPointer(window));
        
        switch (action)
        {
            case GLFW_PRESS:   { return data.responder->mouseButtonPressed (button, modifiers); }
            case GLFW_RELEASE: { return data.responder->mouseButtonReleased(button, modifiers); }
        }
    });
    
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scode, int action, int modifiers)
    {
        WindowData const & data = *((WindowData*) glfwGetWindowUserPointer(window));
        
        switch (action)
        {
            case GLFW_PRESS:
            case GLFW_REPEAT:  { return data.responder->keyPressed (key, modifiers); }
            case GLFW_RELEASE: { return data.responder->keyReleased(key, modifiers); }
        }
    });
}

void AppleWindow::deinitialise()
{
    DK_LOG("AppleWindow", "Destructing");
    
    glfwDestroyWindow(window);
}

}
