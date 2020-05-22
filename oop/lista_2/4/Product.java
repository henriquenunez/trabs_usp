package store;

public class Product {

    String barcode;
    String name;

    public void setBarcode(String param) {
        barcode = param;
    }

    public String getBarcode() {
        return barcode;
    }

    public void setName(String param) {
        name = param;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "Name is " + name + ", and barcode is: " + barcode + "\n" ;
    }

}
