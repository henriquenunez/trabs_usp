package shapes;

public class Square extends Shape {
    float side;

    public void setSide(float _side) {
        side = _side;
    }

    @Override
    public float getArea() {
        return side * side;
    }

    @Override
    public float getPerimeter() {
        return 4 * side;
    }
}
