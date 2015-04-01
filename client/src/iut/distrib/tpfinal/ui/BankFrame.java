package iut.distrib.tpfinal.ui;

import iut.distrib.tpfinal.BankAccount;
import iut.distrib.tpfinal.BankAccountInfos;
import iut.distrib.tpfinal.client.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class BankFrame extends JFrame implements ActionListener {

    private final Client client;
    private final BankAccount account;

    JLabel dollars;
    JButton deposit, withdraw, transfer, query, infos, exit;

    public BankFrame(Client client, BankAccount account) {
        this.client = client;
        this.account = account;

        dollars  = new JLabel();
        updateDollars();

        deposit  = new JButton("Deposit");
        withdraw = new JButton("Withdraw");
        transfer = new JButton("Transfer");
        query    = new JButton("Query an account");
        infos    = new JButton("Update your infos");
        exit     = new JButton("Exit");

        setLayout(new GridLayout(1, 2));

        add(dollars);

        Container buttonList = new Container();
        buttonList.setLayout(new GridLayout(6, 1));
        buttonList.add(deposit);
        buttonList.add(withdraw);
        buttonList.add(transfer);
        buttonList.add(query);
        buttonList.add(infos);
        buttonList.add(exit);

        add(buttonList);

        deposit.addActionListener(this);
        withdraw.addActionListener(this);
        transfer.addActionListener(this);
        query.addActionListener(this);
        infos.addActionListener(this);
        exit.addActionListener(this);


        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        updateInfos();
        setVisible(true);
        pack();
    }

    private void updateDollars() {
        int amount = account.getAmount();

        if (amount == 0) {
            dollars.setText("  0,00 $");
        } else if (amount > 0) {
            dollars.setText(String.format("+ %d,00 $", amount));
        } else {
            dollars.setText(String.format("- %d,00 $", amount));
        }
    }

    private void updateInfos() {
        setTitle(String.format("The Bank - %s %s", this.account.getInfos().getName(), this.account.getInfos().getFirstname()));
    }

    private int askAmount(String msg) {
        while (true) {
            String result = JOptionPane.showInputDialog(this, msg);
            if (result == null || result.isEmpty()) {
                return 0;
            }
            try {
                return Integer.parseInt(result);
            } catch (NumberFormatException ignored) {
                if (!msg.endsWith("Entrez un entier!")) {
                    msg += " Entrez un entier!";
                }
            }
        }
    }

    private int askAccount(String msg) {
        return askAmount(msg);
    }

    private BankAccountInfos askInfos(String msg) {
        String name = JOptionPane.showInputDialog(this, "Entrez votre nom", msg);
        String firstname = JOptionPane.showInputDialog(this, "Entrez votre prénom", msg);
        return new BankAccountInfos(name, firstname);
    }

    private void showAccount(BankAccount account) {
        JOptionPane.showMessageDialog(this, account.getInfos().getName() + " " + account.getInfos().getFirstname());
    }

    @Override
    public void actionPerformed(ActionEvent evt) {
        try {
            if (evt.getSource() == deposit) {
                int amount = askAmount("Please enter the amount to deposit.");
                account.setAmount(client.deposit(account.getId(), amount));
            } else if (evt.getSource() == withdraw) {
                int amount = askAmount("Please enter the amount to withdraw.");
                account.setAmount(client.withdraw(account.getId(), amount));
            } else if (evt.getSource() == transfer) {
                int to = askAccount("Please enter the destination account ID");
                int amount = askAmount("Please enter the amount to transfer.");
                account.setAmount(client.transfer(account.getId(), to, amount));
            } else if (evt.getSource() == query) {
                int id = askAccount("Please enter the account ID");
                showAccount(client.query(id));
            } else if (evt.getSource() == infos) {
                BankAccountInfos infos = askInfos("Please enter your new informations");
                client.infos(account.getId(), infos);
                account.setInfos(infos);
            } else if (evt.getSource() == exit) {
                dispose();
            }
        } catch (AmountNegativeException e) {
            JOptionPane.showMessageDialog(this, "You must enter a positive amount of money");
        } catch (AmountTooHighException e) {
            JOptionPane.showMessageDialog(this, "You do not have enough money to do this");
        } catch (NotFoundDestinationException e) {
            JOptionPane.showMessageDialog(this, "The transfer could not start because the account does not exist");
        } catch (NotFoundException e) {
            JOptionPane.showMessageDialog(this, "The account you queried does not exist");
        }

        updateDollars();
        updateInfos();
    }
}
