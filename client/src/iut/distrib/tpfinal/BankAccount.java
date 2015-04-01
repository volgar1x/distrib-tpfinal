package iut.distrib.tpfinal;

public class BankAccount {
    private int id;
    private int amount;
    private BankAccountInfos infos;

    public BankAccount() {
    }

    public BankAccount(int id, int amount, BankAccountInfos infos) {
        this.id = id;
        this.amount = amount;
        this.infos = infos;
    }

    public int getAmount() {
        return amount;
    }

    public void setAmount(int amount) {
        this.amount = amount;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public BankAccountInfos getInfos() {
        return infos;
    }

    public void setInfos(BankAccountInfos infos) {
        this.infos = infos;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        BankAccount that = (BankAccount) o;

        return id == that.id && amount == that.amount && !(infos != null ? !infos.equals(that.infos) : that.infos != null);

    }

    @Override
    public int hashCode() {
        int result = id;
        result = 31 * result + amount;
        result = 31 * result + (infos != null ? infos.hashCode() : 0);
        return result;
    }

    @Override
    public String toString() {
        return "BankAccount(" +
               "id=" + id +
               ", amount=" + amount +
               ", infos=" + infos +
               ')';
    }
}
