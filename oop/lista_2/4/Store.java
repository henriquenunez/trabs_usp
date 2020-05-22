package store;

import java.util.ArrayList;
import java.util.stream.Collectors;
import java.io.IOException;

import entradateclado.EntradaTeclado;

public class Store {

    public static void main(String[] args) throws IOException {
        ArrayList<Product> myProducts = new ArrayList<>();
        String op;
        int count;
        Product tempProd;

        System.out.println("Welcome to this very store. © H.I.R.A.M. 2020");

        do {
            System.out.println("\n1-Add products into stock.\n2-Sell product.\n3-Search by name or barcode.\n4-Show stock.\n*Any other will terminate!\n");
            op = EntradaTeclado.leString();
            switch (op) {
                case "1":
                    System.out.println("Insert number of products:");
                    while (true) try {
                        count = EntradaTeclado.leInt();
                        break;
                    } catch (IOException e) {
                        System.out.println("Invalid input!");
                    }

                    for (int i = 0 ; i < count ; i++) {
                        System.out.println("1-Books\n2-DVD\n3-CD\n");
                        op = EntradaTeclado.leString();
                        switch (op) {
                            case "1":
                                tempProd = new Book();
                                break;
                            case "2":
                                tempProd = new DVD();
                                break;
                            case "3":
                                tempProd = new CD();
                                break;
                            default:
                                tempProd = null;
                        }
                        if (tempProd != null) {
                            System.out.println("Insert barcode:");
                            op = EntradaTeclado.leString();
                            tempProd.setBarcode(op);

                            System.out.println("Insert name:");
                            op = EntradaTeclado.leString();
                            tempProd.setName(op);

                            myProducts.add(tempProd);
                        }
                    }
                    break;

                case "2":
                    {
                    System.out.println("Insert barcode/name:");
                    String key = EntradaTeclado.leString();
                    myProducts.removeIf(p -> p.getName().equals(key) ||
                                            p.getBarcode().equals(key));
                    }
                    break;

                case "3":
                    {
                    System.out.println("Insert barcode/name:");
                    String key = EntradaTeclado.leString();
                    System.out.println("Found:\n\n" +
                            myProducts.stream()
                                .filter(p ->   p.getName().equals(key) ||
                                            p.getBarcode().equals(key))
                                    .map(p -> p.toString())
                                    .collect(Collectors.joining("\n")));
                    }
                    break;

                case "4":
                    System.out.println("Stock:\n\n");
                    System.out.println("Books\n");
                    System.out.println(myProducts.stream()
                                .filter(p -> p instanceof Book)
                                .map(p -> p.toString())
                                .collect( Collectors.joining("\n")));
                    System.out.println("DVDs\n");
                    System.out.println(myProducts.stream()
                                .filter(p -> p instanceof DVD)
                                .map(p -> p.toString())
                                .collect( Collectors.joining("\n")));
                    System.out.println("CDs\n");
                    System.out.println(myProducts.stream()
                                .filter(p -> p instanceof CD)
                                .map(p -> p.toString())
                                .collect( Collectors.joining("\n")));
                break;
                default:
                    op = "N";
}

        } while (!op.equals("N"));
    }

}
