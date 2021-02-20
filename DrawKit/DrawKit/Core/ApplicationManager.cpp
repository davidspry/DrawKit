//  DrawKit
//  Created by David Spry on 2/2/21.

#include "ApplicationManager.hpp"

namespace DrawKit {

ApplicationManager * ApplicationManager::create()
{
    return new ApplicationManager();
}

void ApplicationManager::run(Application* application, const RendererType& rendererType, const Window::Attributes& attributes)
{
    Window   * const W = createPlatformWindow(attributes);
    Renderer * const R = createRenderer(rendererType);

    setFrameRate(60);
    W->setRenderer(renderer);
    W->setEventResponder(application);

    application->windowResized(W->getWidth(), W->getHeight());
    application->windowDidResize();
    application->prepare();

    while (!glfwWindowShouldClose(window))
    {
        matchDesiredFrameRate();
        
        R->beginRender();
        
        application->update();
        application->draw();
        
        W->update();

        R->complRender();
        
        frameStartTime = glfwGetTime();
    }
    
    R->destroy();
    glfwTerminate();
}

Window * ApplicationManager::createPlatformWindow(const Window::Attributes& attributes)
{
    Window * const W = Window::create(attributes);
    window = W->getGLFWWindow();
    platformWindow = W;

    return W;
}

Renderer * ApplicationManager::createRenderer(const RendererType & renderer)
{
    switch (renderer)
    {
        case RendererType::OPENGL:
        {
            return (this->renderer = new OpenGLRenderer());
        }

        default: break;
    }

    DK_FATAL_ERROR("GlobalInterface", "Undefined RendererType.");
}

Renderer * const ApplicationManager::getRenderer() const
{
    return renderer;
}

GLFWwindow * const ApplicationManager::getGLFWWindow() const
{
    return window;
}

Window * const ApplicationManager::getPlatformWindow() const
{
    return platformWindow;
}

void ApplicationManager::matchDesiredFrameRate()
{
    const auto time = glfwGetTime();

    if (time - frameStartTime < frameDeltaTime)
    {
        const auto milliseconds = 1000.0f * (frameDeltaTime - (time - frameStartTime));
        const auto sleep = std::chrono::milliseconds((int) milliseconds);
        std::this_thread::sleep_for(sleep);
    }
}

void ApplicationManager::setFrameRate(uint16_t frameRate)
{
    framesPerSecond = bound((int) frameRate, 1, 60);
    frameDeltaTime  = 1.0f / static_cast<float>(framesPerSecond);
}

}
