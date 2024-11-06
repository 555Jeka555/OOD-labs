#ifndef LAB4_CLIENT_H
#define LAB4_CLIENT_H

#include "Canvas/ICanvas.h"
#include "version1.h"

class Client
{
public:
    explicit Client(version1::SlideService & slideService)
        : m_slideService(slideService)
    {}

    void HandleCommand(std::istream & inputData, gfx::ICanvas & canvas)
    {
        m_slideService.CreateSlide(inputData);

        m_slideService.DrawSlide(canvas);
    }

private:
    version1::SlideService & m_slideService;
};

#endif //LAB4_CLIENT_H
