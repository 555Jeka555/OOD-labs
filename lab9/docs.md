```mermaid
classDiagram
    Image <.. ImageService : "Use"

    CoW *.. WriteProxy : "Use"
    CoW *.. Tile : "Use"

    Image <.. Drawer : "Use"
    Point <.. Drawer : "Use"

    Image *-- CoW
    Image *-- Size
    Point <.. Image : "Use"

    class ImageService {
        + Print(img: & const Image, out: & std::ostream)$
        + LoadImage(pixels: & const std::string) Image $
    }

    class Drawer {
        + DrawLine(image: & Image, from: Point, to: Point, color: char)$
        - DrawSteepLine(image: & Image, from: Point, to: Point, color: char)$
        - DrawSlopeLine(image: & Image, from: Point, to: Point, color: char)$
        - Sign()$
    }

    class WriteProxy {
        - value_ptr: Value*
    }

    class CoW {
        + Write()
        + WriteBad()
        - value: std::shared_ptr Value
        - EnsureUnique()
    }

    class Image {
        + GetSize() Size
        + GetPixel(p: Point) char
        + SetPixel(p: Point, color: char)
        - m_size: Size
        - m_tiles: std::vector std::vector CoW Tile
    }

    class Tile {
        + SIZE: int = 8 $
        + SetPixel(p: Point, color char)
        + GetPixel(p: Point) char
        + GetInstanceCount() int $
        - m_pixels: std::array std::array char, SIZE, SIZE
        - m_instanceCount: int $
    }

    class Point {
        + x: int
        + y: int
    }

    class Size {
        + width: int
        + height: int
    }
```