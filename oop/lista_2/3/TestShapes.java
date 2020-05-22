package shapes;

import java.io.IOException;
import entradateclado.EntradaTeclado;
import java.util.ArrayList;
import java.util.stream.Collectors;

public class TestShapes {

    public static void main(String[] args) throws IOException {
        ArrayList<Shape> myShapes = new ArrayList<>();
        String op;

        float tempParam;

        Circle tempC;
        Square tempS;
        Rectangle tempR;

        System.out.println("Testing shapes © H.I.R.A.M. 2020");
        Shape a = null;

        for (int i = 0 ; i < 10 ; i++) {
            System.out.println("C for circle, S for square, R for rectangle.");
            op = EntradaTeclado.leString();
            switch (op) {
                case "C":
                    tempC = new Circle();
                    System.out.println("Insert radius:");
                    tempParam = (float) EntradaTeclado.leDouble();
                    tempC.setRadius(tempParam);
                    myShapes.add(a);
                    a = tempC;
                    break;

                case "S":
                    tempS = new Square();
                    System.out.println("Insert side:");
                    tempParam = (float)EntradaTeclado.leDouble();
                    tempS.setSide(tempParam);
                    a = tempS;
                    break;

                case "R":
                    tempR = new Rectangle();
                    System.out.println("Insert height:");
                    tempParam = (float)EntradaTeclado.leDouble();
                    tempR.setHeight(tempParam);
                    System.out.println("Insert width:");
                    tempParam = (float)EntradaTeclado.leDouble();
                    tempR.setWidth(tempParam);
                    a = tempR;
                    break;
            }
            myShapes.add(a);
        }

        System.out.println("Circles:" +
        myShapes.stream()
                .filter(s -> s instanceof Circle)
                .map(s -> "Area " + s.getArea() + " Perimeter " + s.getPerimeter())
                .collect( Collectors.joining("\n")));

        System.out.println("Squares:" +
        myShapes.stream()
                .filter(s -> s instanceof Square)
                .map(s -> "Area " + s.getArea() + " Perimeter " + s.getPerimeter())
                .collect( Collectors.joining("\n")));

        System.out.println("Rectangles:" +
        myShapes.stream()
                .filter(s -> s instanceof Rectangle)
                .map(s -> "Area " + s.getArea() + " Perimeter " + s.getPerimeter())
                .collect( Collectors.joining("\n")));

    }
}
