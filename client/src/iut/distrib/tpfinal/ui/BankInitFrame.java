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

    JTextField address, port;
    JTextField name, firstname, id;
    JButton submit;

    private BankInitFrame() {
        JLabel addressLabel = new JLabel("Adresse IPv4 de la Banque");
        address = new JTextField("localhost");

        JLabel portLabel = new JLabel("Port du serveur");
        port = new JTextField("64646");

        JLabel nameLabel = new JLabel("Nom");
        name = new JTextField();
        name.requestFocus();

        JLabel firstnameLabel = new JLabel("Prenom");
        firstname = new JTextField();

        JLabel idLabel = new JLabel("ID du Compte");
        id = new JTextField();

        submit = new JButton("Connect");


        setLayout(new GridLayout(6, 2));
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
        idLabel.setHorizontalAlignment(SwingConstants.RIGHT);
        add(idLabel);
        add(id);
        add(new JLabel());//spacing
        add(submit);

        submit.addActionListener(this);


        setTitle("The Bank");
        setVisible(true);
        pack();
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    }

    @Override
    public void actionPerformed(ActionEvent evt) {
        if (evt.getSource() == submit) {
            Client client = new UdpClient(address.getText(), Integer.parseInt(port.getText()));

            int id = Integer.parseInt(this.id.getText());
            String name = this.name.getText();
            String firstname = this.firstname.getText();

            BankAccount account;
            try {
                account = client.query(id);
            } catch (NotFoundException e) {
                JOptionPane.showMessageDialog(this, "Le compte "+id+" n'existe pas, il sera donc créé.");
                account = client.create(new BankAccountInfos(name, firstname));
            }

            new BankFrame(client, account);
            dispose();
        }
    }
}
