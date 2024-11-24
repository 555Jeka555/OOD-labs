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
        + SaveImageToPPM(image: & const Image, filename: & const std::string)
    }

    class Drawer {
        + DrawLine(image: & Image, from: Point, to: Point, color: uint32_t)$
        + DrawCircle(image: & Image, center: Point, radius: int, color: uint32_t)
        + FillCircle(image: & Image, center: Point, radius: int, color: uint32_t)
        - DrawSteepLine(image: & Image, from: Point, to: Point, color: uint32_t)$
        - DrawSlopeLine(image: & Image, from: Point, to: Point, color: uint32_t)$
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
        + GetPixel(p: Point) uint32_t
        + SetPixel(p: Point, color: uint32_t)
        - m_size: Size
        - m_tiles: std::vector std::vector CoW Tile
    }

    class Tile {
        + SIZE: int = 8 $
        + SetPixel(p: Point, color uint32_t)
        + GetPixel(p: Point) uint32_t
        + GetInstanceCount() int $
        - m_pixels: std::array std::array uint32_t, SIZE, SIZE
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