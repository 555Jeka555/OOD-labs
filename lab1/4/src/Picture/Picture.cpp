#include "Picture.h"

// TODO Из List убрать вывод, как вариант передавать колбек
// TODO GetShapes() не вытаскивать наружу, убрать
// TODO Доставать Shape из Picture и вызывать методы из Shape

// TODO Переменовать класс ShapeService в Picture
// TODO В Picture Добавлять готовые фигуры через композицию, а не создавать их внутри сервиса
// TODO Canvas на mermaid
// TODO Проблема с change text
// TODO Убрать Вввод вывод из Shape
// TODO Переменовать IGeometryTypeStrategy
// TODO static type в mermaid underlined
// TODO namespaces
// TODO добавить Point

void shapes::Picture::AddShape(const std::string& id, std::unique_ptr<Shape> shape)
{
    if (m_shapes.contains(id))
    {
        throw std::invalid_argument("Shape with given Id already exists");
    }
    m_shapes.emplace(id, std::move(shape));
    m_shapeIds.push_back(id);
}

void shapes::Picture::MoveShape(const std::string &id, double dx, double dy)
{
    if (!m_shapes.contains(id))
    {
        throw std::invalid_argument("Shape with given Id not exists");
    }

    auto& shape = m_shapes.at(id);
    shape->Move(dx, dy);
}

void shapes::Picture::DeleteShape(const std::string &id)
{
    if (!m_shapes.contains(id))
    {
        throw std::invalid_argument("Shape with given Id not exists");
    }

    m_shapes.erase(id);
    std::erase(m_shapeIds, id);
}

void shapes::Picture::List()
{
    int count = 1;
    for (const auto& id : m_shapeIds) {
        auto& shape = m_shapes.at(id);

        std::cout << count << " "
                << shape->GetType() << " "
                << id << " "
                << "#" << std::hex << std::setw(6) << std::setfill('0') << shape->GetColor()
                << std::defaultfloat
                << " " << shape->GetStrategyToString() << std::endl;
        count++;
    }
}

void shapes::Picture::ChangeColor(const std::string &id, uint32_t color)
{
    if (!m_shapes.contains(id))
    {
        throw std::invalid_argument("Shape with given Id not exists");
    }

    auto& shape = m_shapes.at(id);
    shape->SetColor(color);
}

void shapes::Picture::MovePicture(double dx, double dy)
{
    for (const auto& pair : m_shapes)
    {
        pair.second->Move(dx, dy);
    }
}

void shapes::Picture::ChangeShape(const std::string &id, std::unique_ptr<IGeometryTypeStrategy> newGeometryTypeStrategy)
{
    if (!m_shapes.contains(id))
    {
        throw std::invalid_argument("Shape with given Id not exists");
    }

    m_shapes.at(id)->SetDrawingStrategy(std::move(newGeometryTypeStrategy));
}

void shapes::Picture::DrawShape(const std::string &id, gfx::ICanvas &canvas)
{
    if (!m_shapes.contains(id))
    {
        throw std::invalid_argument("Shape with given Id not exists");
    }

    m_shapes.at(id)->Draw(canvas);
}

void shapes::Picture::DrawPicture(gfx::ICanvas &canvas)
{
    for (const auto& id : m_shapeIds) {
        m_shapes.at(id)->Draw(canvas);
    }
}
