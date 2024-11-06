```mermaid
classDiagram

    Client o-- IDesigner
    IPainter <.. Client : "Use"
    ICanvas <.. Client : "Use"

    ICanvas <|.. PNGCanvas

    IDesigner <|.. Designer
    Designer o-- IShapeFactory
    PictureDraft <.. IDesigner : "Create"

    IPainter <|.. Painter
    PictureDraft <.. IPainter : "Use"
    ICanvas <.. IPainter : "Use"

    PictureDraft *-- Shape

    IShapeFactory <|.. ShapeFactory

    Color *-- Shape        
    Shape <.. IShapeFactory : "Create"
    Shape <|.. Rectangle
    Shape <|.. Ellipse
    Shape <|.. Triangle
    Shape <|.. RegularPolygon

    Point <.. ShapeFactory : "Use"
    Point *-- Rectangle
    Point *-- Ellipse
    Point *-- Triangle
    Point *-- RegularPolygon

    class Client {
        - IDesigner m_designer
        + HandleCommand(istream inputData, ICanvas canvas, IPainter painter)
    }

    namespace PainterNamespace {
        class IPainter {
            + DrawPicture(PictureDraft draft, ICanvas canvas)
        }

        class Painter {
            + DrawPicture(PictureDraft draft, ICanvas canvas)
        }
    }

    namespace CanvasNamespace {
        class ICanvas {
            + SetColor(uint32_t color)
            + DrawLine(double fromX, double fromY, double toX, double toY)
            + DrawEllipse(double centerX, double centerY, double radiusX, double radiusY)
        }

        class PNGCanvas {
            + SetColor(uint32_t color)
            + DrawLine(double fromX, double fromY, double toX, double toY)
            + DrawEllipse(double centerX, double centerY, double radiusX, double radiusY)
        }
    }

    namespace PictureDraftNamespace {
        class PictureDraft {
            - vector<Shape> m_shapes

            + AddShape(Shape)
        }
    }

    namespace DesignerNamespace {
        class IDesigner {
            + CreateDraft(istream inputData) PictureDraft
        }

        class Designer {
            + CreateDraft(istream inputData) PictureDraft
        }
    }    

    namespace ShapeFactoryNamespace {
        class IShapeFactory {
            + CreateShape(string description) Shape
        }

        class ShapeFactory {
            + CreateShape(string description) Shape
        }
    }

    namespace ShapeNamespace {
        class Color {
            <<Enumeration>>
            + GREEN
            + RED
            + BLUE
            + YELLOW
            + PINK
            + BLACK
        }

        class Shape {
            - IGeometryTypeStrategy m_geometyrTypeStrategy
            - Color m_color

            + Draw(ICanvas canvas)
            + GetColor() Color 
        }

        class Rectangle {
            + string type = "rectangle"$

            - Point m_leftTop
            - double m_width
            - double m_height

            + Draw(ICanvas canvas, Color color)
        }

        class Ellipse {
            + string type = "ellipse"$

            - Point m_center
            - double m_horizotalRadius
            - double m_verticalRadius

            + Draw(ICanvas canvas, Color color)
        }

        class Triangle {
            + string type = "triangle"$

            - Point m_point1
            - Point m_point2
            - Point m_point3      

            + Draw(ICanvas canvas, Color color)
        }

        class RegularPolygon {
            + string type = "regularPolygon"$

            - Point m_center
            - int m_pointsCount
            - double m_radius  

            + Draw(ICanvas canvas, Color color)
        }

        class Point {
            + double x
            + double y
        }
    }
```