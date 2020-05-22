package coollist;

import java.util.Calendar;

public class PF extends P {

    public class CPF {
        String CPFAsString;
        int identifier;

        public int getIdentifier() {
            return identifier;
        }

        public String getCPF() {
            return CPFAsString;
        }

        public void setCPF(String param) throws CPFException {
            if (param.length() != 11) {
                throw new CPFException();
            }

            CPFAsString = param;
            identifier = Integer.parseInt(CPFAsString.substring(0, 8));
        }

        @Override
        public String toString() {
            //Format 000.000.000-00
            StringBuilder formattedCPF = new StringBuilder();

            formattedCPF.insert(0, CPFAsString.charAt(0));
            formattedCPF.insert(1, CPFAsString.charAt(1));
            formattedCPF.insert(2, CPFAsString.charAt(2));
            formattedCPF.insert(3, ".");
            formattedCPF.insert(4, CPFAsString.charAt(3));
            formattedCPF.insert(5, CPFAsString.charAt(4));
            formattedCPF.insert(6, CPFAsString.charAt(5));
            formattedCPF.insert(7, ".");
            formattedCPF.insert(8, CPFAsString.charAt(6));
            formattedCPF.insert(9, CPFAsString.charAt(7));
            formattedCPF.insert(10, CPFAsString.charAt(8));
            formattedCPF.insert(11, "-");
            formattedCPF.insert(12, CPFAsString.charAt(9));
            formattedCPF.insert(13, CPFAsString.charAt(10));

            return formattedCPF.toString();
        }

        public class CPFException extends Exception {}

    }

    /*CPF specific attributes*/
    String birthday;
    String civilStatus;
    CPF CPFNumber;

    PF() {
        CPFNumber = new CPF();
    }

    /*Getters and setters*/
    public String getBirthday() {
	return birthday;
    }

    public String getCivilStatus() {
	return civilStatus;
    }

    public void setBirthday(String prop) {
	birthday = prop;
    }

    public void setCivilStatus(String prop) {
	civilStatus = prop;
    }

    @Override
    public String getCNumber() {
        return CPFNumber.getCPF();
    }

    public void setCPF(String param) throws CPF.CPFException {
        CPFNumber.setCPF(param);
    }

    /*Print information about CPF person*/
    @Override
    public String toString() {
        return "CPF:" + CPFNumber +
            "\nBirthday:" + birthday +
    	    "\nName:" + name +
    	    "\nAddress:" + streetAddress +
    	    "\nPhone number:" + phoneNumber +
            "\ne-mail:" + emailAddress +
	    "\nCivil status:" + civilStatus + "\n";
    }

    /*Method so sorting can be implemented*/
    @Override
    public int getID() {
        return CPFNumber.getIdentifier();
    }

}
