package ru.stankin.labs;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.IntStream;

public class Server {

    private static final String FILENAME = "test_data.txt";

    private final ExecutorService service = Executors.newSingleThreadExecutor();
    private final int speed;
    private final int log;

    public Server(int speed) {
        this.speed = 1024 * speed;
        this.log = speed;
    }

    public void start(String address, int port) {
        service.execute(() -> {
            startServer(address, port);
            service.shutdown();
        });
    }

    private void startServer(String address, int port) {
        try (ServerSocketChannel serverSocket = ServerSocketChannel.open()) {
            serverSocket.bind(new InetSocketAddress(address, port));
            try (SocketChannel clientSocket = serverSocket.accept()) {
                sendData(clientSocket);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void sendData(SocketChannel channel) throws IOException {
        NumberFormat formatter = new DecimalFormat("#0.00");
        Path path = Path.of(FILENAME);
        createTestData();

        System.out.println(
                "[Server " + log + "] " +
                "Send to: " + channel.getLocalAddress() +
                ", speed: " + formatter.format(speed / 1024) + " kbyte/sec"
        );

        try (FileChannel fileChannel = FileChannel.open(path)) {
            ByteBuffer buffer = ByteBuffer.allocate(speed);

            long byteFileSize = 0;
            while (true) {
                long start = System.currentTimeMillis();
                int readCount =  fileChannel.read(buffer);
                if (readCount <= 0) {
                    break;
                }

                channel.write(buffer.flip());
                buffer.clear();

                long sentTime = System.currentTimeMillis() - start;
                byteFileSize += readCount;

                System.out.println(
                        "[Server " + log + "] " +
                        "Sent: " + formatter.format(byteFileSize / (1024.0 * 1024.0)) + " MB");

                long delta = 1000 - sentTime;
                if (delta > 0) {
                    Thread.sleep(delta);
                }
            }

            System.out.println("[Server " + log + "] File sent!");

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void createTestData() {
        Path path = Path.of(FILENAME);
        if (Files.notExists(path)) {
            System.out.println("[Server " + log + "] Creating data for sent...");
            try (FileChannel channel = FileChannel.open(
                    path,
                    StandardOpenOption.CREATE,
                    StandardOpenOption.TRUNCATE_EXISTING,
                    StandardOpenOption.WRITE)) {

                IntStream.iterate(0, (i) -> i + 1)
                        .limit(100_000)
                        .mapToObj((i) -> "value: " + i + "\n")
                        .forEach((s) -> {
                            try {
                                channel.write(ByteBuffer.wrap(s.getBytes()));
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                        });

            } catch (IOException e) {
                e.printStackTrace();
            }
            System.out.println("[Server " + log + "] Data created!");
        }
    }
}
