#ifndef LAB4_CLIENT_H
#define LAB4_CLIENT_H

#include "Canvas/ICanvas.h"
#include "Slide/SlideService.h"

class Client
{
public:
    explicit Client(SlideService & slideService)
        : m_slideService(slideService)
    {}

    void HandleCommand(std::istream & inputData, gfx::ICanvas & canvas)
    {
        m_slideService.CreateSlide(inputData);

        m_slideService.DrawSlide(canvas);
    }

private:
    SlideService & m_slideService;
};

#endif //LAB4_CLIENT_H
