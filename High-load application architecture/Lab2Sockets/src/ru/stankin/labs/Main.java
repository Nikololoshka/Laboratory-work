package ru.stankin.labs;

public class Main {

    private static final String ADDRESS = "localhost";
    private static final int PORT = 25665;

    public static void main(String[] args) {
        // Реализовать приложение позволяющее скачивать файл с ограниченной скоростью.

        Server server = new Server(32);
        server.start(ADDRESS, PORT);

        Client client = new Client(16);
        client.start(ADDRESS, PORT);
        Client client2 = new Client(64);
        client2.start(ADDRESS, PORT);

        server.listen();
    }
}
