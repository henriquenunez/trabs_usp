package coollist;

import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
import java.util.stream.Collectors;

import java.io.IOException;

import entradateclado.EntradaTeclado;

public class ContactList {

    static class heapSort { //Works with contacts object.

        //eu to enrolando pra implementar um heapsort
        static int findParent(int node) {
            return (int) Math.floor((node - 1)/2);
        }

        static int leftChild(int node) {
            return (2*node + 1);
        }

        static int rightChild(int node) {
            return (2*node + 2);
        }

        //Creates a maximum heap.
        static void heapify(List<P> list) {
            int startIndex;

            for (startIndex = findParent(list.size() - 1) ;
                                                startIndex >= 0;
                                                startIndex--)
                siftDown(list, startIndex, list.size() - 1);
        }

        //Swaps elements until max heap condition is acheived.
        static void siftDown(List<P> list, int start, int end) {
            int rootNode = start;
            int swapNode;
            int childNode;

            while (leftChild(rootNode) <= end){
                childNode = leftChild(rootNode);
                swapNode = rootNode;

                if (list.get(swapNode).getID() < list.get(childNode).getID()) {
                    swapNode = childNode;
                }

                if (childNode + 1 <= end &&
                        list.get(swapNode).getID() < list.get(childNode+1).getID()) {

                    swapNode = childNode + 1;
                }

                if (swapNode == rootNode) {
                    return;
                } else {
                    Collections.swap(list, swapNode, rootNode);
                }
            }
        }

        static void sort(List<P> list) {
            int endIndex = list.size() - 1;

            heapify(list);

            while (endIndex > 0) {
                Collections.swap(list, 0, endIndex);
                endIndex--;
                siftDown(list, 0, endIndex);
            }

        }
    }

    /*Top level members*/
    List<P> contacts;

    ContactList() {
        contacts = new ArrayList<>();
    }

    public void addPF() throws IOException, PF.CPF.CPFException {
        String temp;

        PF currentPerson = new PF();
        System.out.println("Adding PF (pessoa física)");

        System.out.println("Insert CPF:");
        temp = EntradaTeclado.leString();
        currentPerson.setCPF(temp);

        System.out.println("Insert name:");
        temp = EntradaTeclado.leString();
        currentPerson.setName(temp);

        System.out.println("Insert birthday (DD/MM/YYYY):");
        temp = EntradaTeclado.leString();
        currentPerson.setBirthday(temp);

        System.out.println("Insert Civil Status:");
        temp = EntradaTeclado.leString();
        currentPerson.setCivilStatus(temp);

        System.out.println("Insert phone number:");
        temp = EntradaTeclado.leString();
        currentPerson.setPhoneNumber(temp);

        System.out.println("Insert e-mail address:");
        temp = EntradaTeclado.leString();
        currentPerson.setEmailAddress(temp);

        System.out.println("Insert street address:");
        temp = EntradaTeclado.leString();
        currentPerson.setStreetAddress(temp);

        System.out.println("This was the entry.\n" + currentPerson);
        System.out.println("Save? (Y/N)");
        temp = EntradaTeclado.leString();
        if (!temp.equalsIgnoreCase("Y")) {
            System.out.println("Discarded.");
            return;
        }

        contacts.add(currentPerson);
        System.out.println("Saved.");
    }

    public void addPJ() throws IOException, PJ.CNPJ.CNPJException {
        String temp;

        PJ currentPerson = new PJ();

        System.out.println("Adding PJ (pessoa jurídica)");

        System.out.println("Insert CNPJ:");
        temp = EntradaTeclado.leString();
        currentPerson.setCNPJ(temp);

        System.out.println("Insert name:");
        temp = EntradaTeclado.leString();
        currentPerson.setName(temp);

        System.out.println("Insert actual name (razão social):");
        temp = EntradaTeclado.leString();
        currentPerson.setActualName(temp);

        System.out.println("Insert phone number:");
        temp = EntradaTeclado.leString();
        currentPerson.setPhoneNumber(temp);

        System.out.println("Insert e-mail address:");
        temp = EntradaTeclado.leString();
        currentPerson.setEmailAddress(temp);

        System.out.println("Insert street address:");
        temp = EntradaTeclado.leString();
        currentPerson.setStreetAddress(temp);

        System.out.println("Insert state inscription:");
        temp = EntradaTeclado.leString();
        currentPerson.setStateInscription(temp);

        System.out.println("This was the entry.\n" + currentPerson);
        System.out.println("Save? (Y/N)");
        temp = EntradaTeclado.leString();
        if (!temp.equalsIgnoreCase("Y")) {
            System.out.println("Discarded.");
            return;
        }

        contacts.add(currentPerson);
        System.out.println("Saved.");
    }

    public void removeByName() throws IOException {
        String temp;
        temp = EntradaTeclado.leString();
        contacts.removeIf(c -> c.getName().equals(temp));
    }

    public void removeByCPF() throws IOException {
        String temp;
        temp = EntradaTeclado.leString();
        contacts.removeIf(c -> c.getCNumber().equals(temp));
    }

    public void removeByCNPJ() throws IOException {
        String temp;
        temp = EntradaTeclado.leString();
        contacts.removeIf(c -> c.getCNumber().equals(temp));
    }

    public String search() throws IOException {
        String key = EntradaTeclado.leString();
        return contacts.stream()
                        .filter(c ->    c.getName().equals(key) ||
                                        c.getCNumber().equals(key))
                        .map(c -> c.toString())
                        .collect( Collectors.joining("\n"));
    }

    public void sortContacts() {
        heapSort.sort(contacts);
    }

    @Override
    public String toString() {
        return
                    contacts.stream()
                        .filter(c -> c instanceof PF)
                        .map(c -> c.toString())
                        .collect( Collectors.joining("\n")) +

                    contacts.stream()
                        .filter(c -> c instanceof PJ)
                        .map(c -> c.toString())
                        .collect( Collectors.joining("\n"));
    }

}
