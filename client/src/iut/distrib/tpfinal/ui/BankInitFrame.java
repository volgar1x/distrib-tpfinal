package iut.distrib.tpfinal.ui;

import iut.distrib.tpfinal.BankAccount;
import iut.distrib.tpfinal.BankAccountInfos;
import iut.distrib.tpfinal.client.Client;
import iut.distrib.tpfinal.client.NotFoundException;
import iut.distrib.tpfinal.client.UdpClient;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class BankInitFrame extends JFrame implements ActionListener {
    public static void main(String[] args) throws Exception {
        UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());

        new BankInitFrame();
    }

    JTextField address, port, id, name, firstname;
    JButton submit, create;

    int state;

    public BankInitFrame() {
        address = new JTextField("localhost");
        port = new JTextField("64646");
        id = new JTextField();
        name = new JTextField();
        firstname = new JTextField();
        submit = new JButton();
        create = new JButton();


        connectLayout();


        submit.addActionListener(this);
        create.addActionListener(this);


        setTitle("The Bank");
        setVisible(true);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    }

    private void connectLayout() {
        state = 1;
        getContentPane().removeAll();

        submit.setText("Connect");
        create.setText("I'm new!");

        JLabel addressLabel = new JLabel("IPv4 address");
        JLabel portLabel = new JLabel("Port");
        JLabel idLabel = new JLabel("Account ID");
        setLayout(new GridLayout(4, 2));
        addressLabel.setHorizontalAlignment(SwingConstants.RIGHT);
        add(addressLabel);
        add(this.address);
        portLabel.setHorizontalAlignment(SwingConstants.RIGHT);
        add(portLabel);
        add(this.port);
        idLabel.setHorizontalAlignment(SwingConstants.RIGHT);
        add(idLabel);
        add(id);
        add(create);
        add(submit);

        pack();
    }

    private void createLayout() {
        state = 2;
        getContentPane().removeAll();

        submit.setText("Have an account?");
        create.setText("Create");

        JLabel addressLabel = new JLabel("IPv4 address");
        JLabel portLabel = new JLabel("Port");
        JLabel nameLabel = new JLabel("Name");
        JLabel firstnameLabel = new JLabel("First Name");
        setLayout(new GridLayout(5, 2));
        addressLabel.setHorizontalAlignment(SwingConstants.RIGHT);
        add(addressLabel);
        add(address);
        portLabel.setHorizontalAlignment(SwingConstants.RIGHT);
        add(portLabel);
        add(port);
        nameLabel.setHorizontalAlignment(SwingConstants.RIGHT);
        add(nameLabel);
        add(name);
        firstnameLabel.setHorizontalAlignment(SwingConstants.RIGHT);
        add(firstnameLabel);
        add(firstname);
        add(submit);
        add(create);

        pack();
    }

    @Override
    public void actionPerformed(ActionEvent evt) {
        if (evt.getSource() == submit) {
            if (state == 2) {
                connectLayout();
                return;
            }

            Client client = new UdpClient(address.getText(), Integer.parseInt(port.getText()));

            int id = Integer.parseInt(this.id.getText());

            BankAccount account;
            try {
                account = client.query(id);
            } catch (NotFoundException e) {
                JOptionPane.showMessageDialog(this, "Account "+id+" does not exist");
                return;
            }

            new BankFrame(client, account);
            dispose();
        } else if (evt.getSource() == create) {
            if (state == 1) {
                createLayout();
                return;
            }

            Client client = new UdpClient(address.getText(), Integer.parseInt(port.getText()));

            String name = this.name.getText();
            String firstname = this.firstname.getText();

            BankAccount account = client.create(new BankAccountInfos(name, firstname));

            new BankFrame(client, account);
            dispose();
        }
    }
}
