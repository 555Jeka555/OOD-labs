#ifndef LAB7_SLIDESERVICE_H
#define LAB7_SLIDESERVICE_H

#include <sstream>
#include "../ShapeFactory/IShapeFactory.h"
#include "../Shape/GroupShape.h"
#include "../Slide/Slide.h"

class SlideService {
public:
    explicit SlideService(IShapeFactory &shapeFactory)
            : m_shapeFactory(shapeFactory) {}

    void CreateSlide(std::istream &inputData) {
        std::string line;
        auto firstGroup = std::make_shared<GroupShape>();
        std::vector<std::shared_ptr<GroupShape>> groupStack;
        groupStack.push_back(firstGroup);
        int i = 0;

        while (getline(inputData, line)) {
            if (IsStartOrEndCreateGroup(line, groupStack, i)) {
                continue;
            }

            auto shape = m_shapeFactory.CreateShape(line);
            if (shape) {
                groupStack.back()->InsertShape(shape, groupStack.back()->GetShapesCount());
            }
        }

        m_currentSlide = std::make_unique<Slide>(firstGroup);
    }

    void DrawSlide(gfx::ICanvas &canvas) {
        if (m_currentSlide != nullptr) {
            m_currentSlide->Draw(canvas);
        }
    }

    static bool IsStartOrEndCreateGroup(
            const std::string &line,
            std::vector<std::shared_ptr<GroupShape>> &groupStack,
            int &i) {
        if (line == GroupShape::typeStart) {
            auto newGroup = std::make_shared<GroupShape>();
            groupStack.back()->InsertShape(std::static_pointer_cast<IShape>(newGroup),
                                           groupStack.back()->GetShapesCount());
            groupStack.push_back(newGroup);
            return true;
        }

        if (line == GroupShape::typeEnd) {
            if (groupStack.size() > 1) {
                groupStack.pop_back();
            }
            return true;
        }

        return false;
    }


private:
    IShapeFactory &m_shapeFactory;
    std::unique_ptr<ISlide> m_currentSlide;
};

#endif //LAB7_SLIDESERVICE_H
