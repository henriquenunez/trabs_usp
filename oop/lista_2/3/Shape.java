package shapes;

public abstract class Shape {
    boolean filled;
    String color;

    /*Getters and setters*/

    public void setFilled(boolean state) {
        filled = state;
    }

    public boolean getFilled() {
        return filled;
    }

    public void setColor(String _color) {
        color = _color;
    }

    public String getColor() {
        return color;
    }

    public abstract float getArea ();
    public abstract float getPerimeter ();

}
