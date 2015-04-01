package iut.distrib.tpfinal;

public class BankAccountInfos {
    private String name;
    private String firstname;

    public BankAccountInfos() {
    }

    public BankAccountInfos(String name, String firstname) {
        this.name = name;
        this.firstname = firstname;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getFirstname() {
        return firstname;
    }

    public void setFirstname(String firstname) {
        this.firstname = firstname;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        BankAccountInfos that = (BankAccountInfos) o;

        return !(name != null ? !name.equals(that.name) : that.name != null) && !(firstname != null ? !firstname.equals(that.firstname) : that.firstname != null);
    }

    @Override
    public int hashCode() {
        int result = name != null ? name.hashCode() : 0;
        result = 31 * result + (firstname != null ? firstname.hashCode() : 0);
        return result;
    }

    @Override
    public String toString() {
        return "BankAccountInfos(" +
               "name='" + name + '\'' +
               ", firstname='" + firstname + '\'' +
               ')';
    }
}
