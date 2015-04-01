package iut.distrib.tpfinal.client;

import iut.distrib.tpfinal.BankAccount;
import iut.distrib.tpfinal.BankAccountInfos;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.SocketException;

public class UdpClient implements Client {
    private final DatagramSocket socket;
    private final String address;
    private final int port;

    public UdpClient(String address, int port) {
        this.address = address;
        this.port = port;
        try {
            this.socket = new DatagramSocket();
            this.socket.setSoTimeout(5000);
        } catch (SocketException e) {
            throw new RuntimeException(e);
        }
    }

    private void send(String format, Object... args) {
        byte[] bytes = String.format(format + "\n", args).getBytes();
        DatagramPacket packet = new DatagramPacket(bytes, bytes.length);
        packet.setSocketAddress(new InetSocketAddress(address, port));
        try {
            socket.send(packet);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private String receive() {
        byte[] buf = new byte[64];
        DatagramPacket packet = new DatagramPacket(buf, buf.length);
        packet.setSocketAddress(new InetSocketAddress(address, port));
        try {
            socket.receive(packet);
            return new String(buf, 0, packet.getLength());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private BankAccount receiveBankAccount() {
        String msg = receive();
        String[] args = msg.split(",|\\n");

        switch (args[0]) {
            case "success":
                if (args.length >= 5) {
                    return new BankAccount(Integer.parseInt(args[1]),
                                           Integer.parseInt(args[4]),
                                           new BankAccountInfos(args[2], args[3]));
                }

            case "error":
                switch (args[1]) {
                    case "amount_negative":
                        throw new AmountNegativeException();
                    case "amount_too_high":
                        throw new AmountTooHighException();
                    case "not_found":
                        if (args.length > 2) {
                            switch (args[2]) {
                                case "from":
                                    throw new NotFoundOriginException();
                                case "to":
                                    throw new NotFoundDestinationException();
                            }
                        }
                        throw new NotFoundException();
                }

            default:
                throw new UnexpectedResponseException();
        }
    }

    public BankAccount create(BankAccountInfos infos) {
        send("create,%s,%s", infos.getName(), infos.getFirstname());
        return receiveBankAccount();
    }

    public int deposit(int id, int amount) {
        send("deposit,%d,%d", id, amount);
        return receiveBankAccount().getAmount();
    }

    public int withdraw(int id, int amount) {
        send("withdraw,%d,%d", id, amount);
        return receiveBankAccount().getAmount();
    }

    public int transfer(int from, int to, int amount) {
        send("transfer,%d,%d,%d", from, to, amount);
        return receiveBankAccount().getAmount();
    }

    public BankAccount query(int id) {
        send("query,%d", id);
        return receiveBankAccount();
    }

    public void infos(int id, BankAccountInfos infos) {
        send("infos,%d,%s,%s", id, infos.getName(), infos.getFirstname());
        receiveBankAccount();
    }
}
