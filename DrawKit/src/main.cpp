//  DrawKit
//  Created by David Spry on 15/1/21.

#include "DrawKit.h"

class RendererSketch: public DrawKit::Application
{
private:
    std::array<DrawKit::Circle,    15> circles;
    std::array<DrawKit::Rectangle, 15> rectangles;
    std::array<DrawKit::Colour,    15> circleColours;
    std::array<DrawKit::Colour,    15> rectangleColours;
    
    float phase = 0.0f;
    
public:
    void prepare() override
    {
        const DrawKit::Colour red   (DrawKit::Colour::white, 55);
        const DrawKit::Colour white (DrawKit::Colour::red,   255);

        for (size_t k = 0; k < rectangles.size(); ++k)
        {
            DrawKit::Rectangle & rectangle = rectangles.at(k);
            DrawKit::Colour colour = {
                white, red, (float) k / (float) rectangles.size()
            };
            
            rectangleColours.at(k) = colour;
            uint16_t const size = 30 * (unsigned int) (rectangles.size() - k) + 20;
            rectangle.setSizeFromCentre(size, size);
            rectangle.setColour(colour);
        }
        
        for (size_t k = 0; k < circles.size(); ++k)
        {
            DrawKit::Circle & circle = circles.at(k);
            DrawKit::Colour   colour = {
                DrawKit::Colour(DrawKit::Colour::blue, 255),
                DrawKit::Colour(DrawKit::Colour::white, 55),
                (float) k / (float) circles.size()
            };
            
            circleColours.at(k) = colour;
            const uint32_t radius = 15 * (unsigned int) (circles.size() - k) + 10;
            circle.setNumberOfSegments(128);
            circle.setColour(colour);
            circle.setRadius(radius);
        }

    }
    
    void update() override
    {
        phase = phase + 0.035f;
        phase = phase - static_cast<int>(phase > TWO_PI) * TWO_PI;
        const float cos = std::cosf(phase);
        
        DrawKit::setBackgroundColour(DrawKit::Colour(DrawKit::Colour(
                                                     DrawKit::Colour::offwhite, DrawKit::Colour::yellow, 0.65f),
                                                     DrawKit::Colour::yellow,
                                                     std::fabsf(cos)));
        
        const auto wave = [&](size_t k, size_t && capacity) -> size_t
        {
            return std::fmod((k + std::fabsf(2.0f * cos * std::tan(phase)) * capacity), capacity);
        };
        
        for (size_t k = 0; k < rectangles.size(); ++k)
        {
            const float sin = std::sinf(phase + k * QRTR_PI * 0.25f);
            const size_t q = wave(k, rectangles.size());
            DrawKit::Rectangle & rectangle = rectangles.at(k);
            rectangle.setPositionWithCentre(centre.x * 1.5f + sin * k * size.w * 0.125f * 0.10f,
                                            centre.y, centre.z);
            rectangle.setColour(DrawKit::Colour(rectangleColours.at(k),
                                                rectangleColours.at(q),
                                                cos));
        }
        
        for (size_t k = 0; k < circles.size(); ++k)
        {
            const float sin = std::sinf(phase + k * QRTR_PI * 0.10f);
            DrawKit::Circle & circle = circles.at(k);
            const size_t q = wave(k, circles.size());
            circle.setPositionWithCentre(centre.x * 0.5f + sin * k * size.w * 0.125f * 0.10f,
                                         centre.y        + sin * k * size.h * 0.125f * 0.05f, centre.z);
            circle.setColour(DrawKit::Colour(circleColours.at(k),
                                             circleColours.at(q),
                                             cos));
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
