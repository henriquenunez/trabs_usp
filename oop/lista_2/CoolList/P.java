package coollist;

public abstract class P {

    String name;
    String streetAddress;
    String emailAddress;
    String phoneNumber;

    String getName() {
        return name;
    }

    String getStreetAddress() {
        return streetAddress;
    }

    String getEmailAddress() {
        return emailAddress;
    }

    String getPhoneNumber() {
        return phoneNumber;
    }

    void setName(String prop) {
        name = prop;
    }

    void setStreetAddress(String prop) {
        streetAddress = prop;
    }

    void setEmailAddress(String prop) {
        emailAddress = prop;
    }

    void setPhoneNumber(String prop) {
        phoneNumber = prop;
    }

    public abstract int getID();
    public abstract String getCNumber();
}
