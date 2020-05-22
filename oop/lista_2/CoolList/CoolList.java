package coollist;

import java.io.IOException;
import entradateclado.EntradaTeclado;

public class CoolList {

    public static void main(String[] args) throws IOException {
        ContactList thisList = new ContactList();
        String op;

        System.out.println("Welcome to the Cool List! © H.I.R.A.M. 2020");

        do {

            System.out.println("1-Insert CPF person\n2-Insert CNPJ person\n3-Sort and print contacts\n4-Seach by name, CPF or CNPJ\n5-Remove by CPF\n6-Remove by CNPJ\n7-Remove by Name\n*Any other will terminate!");

            op = EntradaTeclado.leString();

            try {
                switch (op) {

                    case "1":
                        thisList.addPF();
                        break;

                    case "2":
                        thisList.addPJ();
                    break;

                    case "3":
                        thisList.sortContacts();
                        System.out.println("List:\n\n" + thisList);
                        System.out.println("*****************\n\n");
                        break;

                    case "4":
                        System.out.println("Found:\n\n" + thisList.search());
                        System.out.println("*****************\n\n");
                        break;

                    case "5":
                        thisList.removeByCPF();
                        break;

                    case "6":
                        thisList.removeByCNPJ();
                        break;

                    case "7":
                        thisList.removeByName();
                        break;

                    default:
                        op = "N";
                        break;
                }

                } catch (IOException e) {
                    System.out.println("Invalid input");
                } catch (PF.CPF.CPFException e) {
                    System.out.println("Invalid CPF");
                } catch (PJ.CNPJ.CNPJException e) {
                    System.out.println("Invalid CNPJ");
                }
        } while (!op.equals("N"));

    }

}
