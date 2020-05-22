package coollist;

public class PJ extends P {

    /*Class for implementing CNPJ storing and formating*/
    public class CNPJ {
        String CNPJAsString;
        int identifier;

        public int getIdentifier() {
            return identifier;
        }

        public String getCNPJ() {
            return CNPJAsString;
        }

        public void setCNPJ(String param) throws CNPJException {
            if ((param).length() != 14) {
                throw new CNPJException();//"Invalid CNPJ number!");
            }

            CNPJAsString = param;
            identifier = Integer.parseInt(CNPJAsString.substring(0, 7));
        }

        public String toString() {
            //Format: 00.000.000/0000-00
            StringBuilder formattedCNPJ = new StringBuilder(18);

            formattedCNPJ.insert(0, CNPJAsString.charAt(0));
            formattedCNPJ.insert(1, CNPJAsString.charAt(1));
            formattedCNPJ.insert(2, ".");
            formattedCNPJ.insert(3, CNPJAsString.charAt(2));
            formattedCNPJ.insert(4, CNPJAsString.charAt(3));
            formattedCNPJ.insert(5, CNPJAsString.charAt(4));
            formattedCNPJ.insert(6, ".");
            formattedCNPJ.insert(7, CNPJAsString.charAt(5));
            formattedCNPJ.insert(8, CNPJAsString.charAt(6));
            formattedCNPJ.insert(9, CNPJAsString.charAt(7));
            formattedCNPJ.insert(10, "/");
            formattedCNPJ.insert(11, CNPJAsString.charAt(8));
            formattedCNPJ.insert(12, CNPJAsString.charAt(9));
            formattedCNPJ.insert(13, CNPJAsString.charAt(10));
            formattedCNPJ.insert(14, CNPJAsString.charAt(11));
            formattedCNPJ.insert(15, "-");
            formattedCNPJ.insert(16, CNPJAsString.charAt(12));
            formattedCNPJ.insert(17, CNPJAsString.charAt(13));

            return formattedCNPJ.toString();
        }

        public class CNPJException extends Exception {}
    }

    /*CNPJ specific attributes*/
    String stateInscription;
    String actualName;
    CNPJ CNPJNumber;

    PJ() {
        CNPJNumber = new CNPJ();
    }

    /*Getters and setters*/
    String getStateIncription() {
        return stateInscription;
    }

    String getActualName() {
        return actualName;
    }

    void setStateInscription(String prop) {
        stateInscription = prop;
    }

    void setActualName(String prop) {
        actualName = prop;
    }

    @Override
    public String getCNumber() {
        return CNPJNumber.getCNPJ();
    }

    public void setCNPJ(String param) throws CNPJ.CNPJException {
        CNPJNumber.setCNPJ(param);
    }

    @Override
    public String toString() {
        return "CNPJ:" + CNPJNumber +
            "\nName:" + name +
            "\nActual name:" + actualName +
            "\nPhone number:" + phoneNumber +
            "\ne-mail:" + emailAddress +
            "\nStateInscription:" + stateInscription + "\n";
    }

    @Override
    public int getID() {
        return CNPJNumber.getIdentifier();
    }

}
