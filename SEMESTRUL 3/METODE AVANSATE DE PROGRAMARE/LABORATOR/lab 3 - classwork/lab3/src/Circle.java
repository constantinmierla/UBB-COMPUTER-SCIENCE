public class Circle {
    private int radius;

    public Circle(int radius){
        this.radius = radius;
    }

    @Override
    public String toString(){
        return "Circle with radius " + radius;
    }
}
