//  DrawKit
//  Created by David Spry on 15/1/21.

#include "DrawKit.h"

class RendererSketch: public DrawKit::Application
{
private:
    std::array<DrawKit::Circle,    40> circles;
    std::array<DrawKit::Rectangle, 35> rectangles;
    std::array<DrawKit::Colour,    40> circleColours;
    
    float phase = 0.0f;
    
public:
    void prepare() override
    {
        const DrawKit::Colour red   (DrawKit::Colour::red,      165);
        const DrawKit::Colour white (DrawKit::Colour::offwhite, 125);

        for (size_t k = 0; k < rectangles.size(); ++k)
        {
            DrawKit::Rectangle & rectangle = rectangles.at(k);
            DrawKit::Colour colour = {
                white, red, (float) k / (float) rectangles.size()
            };
            
            uint16_t const size = 5 + k * 10;
            rectangle.setPositionWithCentre(centre);
            rectangle.setSizeFromCentre(size, size);
            rectangle.setColour(colour);
        }
        
        for (size_t k = 0; k < circles.size(); ++k)
        {
            DrawKit::Circle & circle = circles.at(k);
            DrawKit::Colour   colour = {
                DrawKit::Colour::blue,
                DrawKit::Colour::white,
                (float) k / (float) circles.size()
            };
            
            circleColours.at(k) = colour;
            circle.setPositionWithCentre(centre);
            circle.setNumberOfSegments(128);
            circle.setColour(colour);
            circle.setRadius((unsigned int) (10 * (circles.size() - k) + 10));
        }
    }
    
    void update() override
    {
        phase = phase + 0.045f;
        phase = phase - static_cast<int>(phase > TWO_PI) * TWO_PI;
        const float sin  = std::sinf(phase);
        const float cos  = std::cosf(phase);
        
        DrawKit::setBackgroundColour(DrawKit::Colour(
                                                     DrawKit::Colour::salmon,
                                                     DrawKit::Colour::yellow,
                                                     std::fabsf(cos)));
        
        for (size_t k = 0; k < circles.size(); ++k)
        {
            DrawKit::Circle & circle = circles.at(k);
            DrawKit::Colour   colour = {
                DrawKit::Colour(DrawKit::Colour::blue, DrawKit::Colour::offwhite, 0.5f),
                circleColours.at(k),
                cos
            };
            
            circle.setColour(colour);
        }
        
        for (size_t k = 0; k < rectangles.size(); ++k)
        {
            DrawKit::Rectangle & rectangle = rectangles.at(k);
            rectangle.setPositionWithCentre(centre.x + sin * cos * k * 25.0f,
                                            centre.y + sin * 1.f * k * 20.0f,
                                            0.0f);
        }
    }
    
    void draw() override
    {
        for (auto & circle : circles)
        {
            DrawKit::drawCircle(circle);
        }
        
        for (auto & rectangle : rectangles)
        {
            DrawKit::drawRectangle(rectangle);
        }
    }
};

int main(int argc, char *argv[])
{
    RendererSketch sketch;
    DrawKit::Window::Attributes attr;
    
    attr.title  = "DrawKit";
    attr.width  = 1000;
    attr.height = 1000;

    DrawKit::launch(&sketch, attr, DrawKit::RendererType::OPENGL);

    return 0;
}
