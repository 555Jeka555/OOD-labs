#ifndef INC_4_SHAPECONTROLLER_H
#define INC_4_SHAPECONTROLLER_H

#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <vector>
#include "../Picture/Picture.h"
#include "../Picture/ShapeType.h"
#include "../Picture/ShapeTypeConverter.h"
#include "../Shape/DrawingStrategy/RectangleDrawingStrategy.h"

class ShapeController
{
public:
    ShapeController(std::istream& in, std::ostream& out, shapes::Picture& picture)
            : m_in(in), m_out(out), m_picture(picture) {}

    void ReadCommands();

private:
    std::istream& m_in;
    std::ostream& m_out;
    shapes::Picture& m_picture;

    void AddShape(std::istringstream& iss);

    void MoveShape(std::istringstream& iss);

    void DeleteShape(std::istringstream& iss);

    void ListShape();

    void ChangeColor(std::istringstream& iss);

    void MovePicture(std::istringstream& iss);

    void ChangeShape(std::istringstream& iss);
};


#endif //INC_4_SHAPECONTROLLER_H
