//  DrawKit
//  Created by David Spry on 15/1/21.

#include "DrawKit.h"

class RendererSketch: public DrawKit::Application
{
private:
    std::array<DrawKit::Circle,    25> circles;
    std::array<DrawKit::Rectangle, 6> rectangles;
    
    DrawKit::Rectangle a;
    DrawKit::Rectangle b;
    DrawKit::Circle c;
    
    float phase = 0.0f;
    
public:
    void prepare() override
    {
        const DrawKit::Colour red (DrawKit::Colour::red,   165);
        const DrawKit::Colour ylw (DrawKit::Colour::white, 125);

        
        for (size_t k = 0; k < circles.size(); ++k)
        {
            DrawKit::Circle & circle = circles.at(k);
            DrawKit::Colour   colour = {
                DrawKit::Colour::blue,
                DrawKit::Colour::white,
                (float) k / (float) circles.size()
            };
            
            circle.setPositionWithCentre(centre);
            circle.setNumberOfSegments(128);
            circle.setColour(colour);
            circle.setRadius((unsigned int) (10 * (circles.size() - k) + 10));
        }
        
        a.setSizeFromCentre(125, 125);
        b.setSizeFromCentre( 65,  65);
        a.setColour(red);
        b.setColour(ylw);
    }
    
    void update() override
    {
        phase = phase + 0.0125f;
        phase = phase - static_cast<int>(phase > TWO_PI) * TWO_PI;
        
        DrawKit::setBackgroundColour(DrawKit::Colour(
                                                     DrawKit::Colour::pink,
                                                     DrawKit::Colour::yellow,
                                                     std::fabsf(std::sinf(phase))));
    }
    
    void draw() override
    {
        phase = phase + 0.025f;
        phase = phase - static_cast<int>(phase > TWO_PI) * TWO_PI;
        
        const float x = std::sinf(phase) * 250.0f;
        const float y = std::sinf(phase) * 125.0f;

        a.setPositionWithCentre(centre.x + x, centre.y + x, centre.z);
        b.setPositionWithCentre(centre.x + y, centre.y + y, centre.z);
        c.setPositionWithCentre(centre);
        c.setRadius(30 + x);
        
        for (auto & circle : circles)
        {
            DrawKit::drawCircle(circle);
        }
        
        DrawKit::drawRectangle(b);
        DrawKit::drawRectangle(a);
    }
};

int main(int argc, char *argv[])
{
    RendererSketch sketch;
    DrawKit::Window::Attributes attr;
    
    attr.title  = "DrawKit";
    attr.width  = 800;
    attr.height = 800;

    DrawKit::launch(&sketch, attr, DrawKit::RendererType::OPENGL);

    return 0;
}
