#ifndef INC_4_SHAPECONTROLLER_H
#define INC_4_SHAPECONTROLLER_H

#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <vector>
#include "../Service/ShapeService.h"
#include "../Service/ShapeType.h"
#include "../Service/ShapeTypeConverter.h"
#include "../Shape/DrawingStrategy/RectangleDrawingStrategy.h"

class ShapeController
{
public:
    ShapeController(std::istream& in, std::ostream& out, ShapeService& shapeService)
            : m_in(in), m_out(out), m_shapeService(shapeService) {}

    void ReadCommands();

private:
    std::istream& m_in;
    std::ostream& m_out;
    ShapeService& m_shapeService;

    void AddShape(std::istringstream& iss);

    void MoveShape(std::istringstream& iss);

    void DeleteShape(std::istringstream& iss);

    void ListShape();

    void ChangeColor(std::istringstream& iss);

    void MovePicture(std::istringstream& iss);
};


#endif //INC_4_SHAPECONTROLLER_H
