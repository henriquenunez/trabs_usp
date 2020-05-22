package shapes;

public class Rectangle extends Shape {
    float height;
    float width;

    public void setHeight(float _height) {
        height = _height;
    }

    public void setWidth(float _width) {
        width = _width;
    }

    @Override
    public float getArea() {
        return width * height;
    }

    @Override
    public float getPerimeter() {
        return 2 * (width + height);
    }
}
