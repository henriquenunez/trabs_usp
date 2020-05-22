package shapes;

public class Circle extends Shape {
    float radius;

    public void setRadius(float _radius) {
        radius = _radius;
    }

    @Override
    public float getArea() {
        return (float) Math.PI * radius * radius;
    }

    @Override
    public float getPerimeter() {
        return (float) Math.PI * radius * 2;
    }
}
