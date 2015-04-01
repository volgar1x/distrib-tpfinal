package iut.distrib.tpfinal.client;

import iut.distrib.tpfinal.BankAccount;
import iut.distrib.tpfinal.BankAccountInfos;

public interface Client {
    BankAccount create(BankAccountInfos infos);
    int deposit(int id, int amount);
    int withdraw(int id, int amount);
    int transfer(int from, int to, int amount);
    BankAccount query(int id);
    void infos(int id, BankAccountInfos infos);
}
