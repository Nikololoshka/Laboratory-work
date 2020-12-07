package ru.stankin.labs;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.channels.SocketChannel;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Client {

    private static final String FILENAME = "download_file.txt";

    private final ExecutorService service = Executors.newSingleThreadExecutor();
    private final int speed;
    private final int log;

    public Client(int speed) {
        this.speed = 1024 * speed;
        this.log = speed;
    }

    public void start(String address, int port) {
        service.execute(() -> {
            startDownload(address, port);
            service.shutdown();
        });
    }

    private void startDownload(String address, int port) {
        InetSocketAddress serverAddress = new InetSocketAddress(address, port);
        try (SocketChannel channel = SocketChannel.open(serverAddress)) {
            receiveData(channel);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void receiveData(SocketChannel channel) throws IOException {
        NumberFormat formatter = new DecimalFormat("#0.00");

        System.out.println(
                "[Client " + log + "] " +
                "Receive from: " + channel.getLocalAddress() +
                ", speed: " + formatter.format(speed / 1024.0) + " kbyte/sec"
        );

        try (FileChannel fileChannel = FileChannel.open(
                Path.of(FILENAME),
                StandardOpenOption.CREATE,
                StandardOpenOption.TRUNCATE_EXISTING,
                StandardOpenOption.WRITE)) {

            ByteBuffer downloadBuffer = ByteBuffer.allocate(speed);
            long byteFileSize = 0;

            long receiveStart = System.currentTimeMillis();
            while (true) {
                long start = System.currentTimeMillis();
                int readCount = channel.read(downloadBuffer);
                if (readCount <= 0) {
                    break;
                }

                fileChannel.write(downloadBuffer.flip());
                downloadBuffer.clear();

                long receiveTime = System.currentTimeMillis() - start;
                byteFileSize += readCount;

                System.out.println(
                        "[Client " + log + "] " +
                        "Receive: " + formatter.format(byteFileSize / (1024.0 * 1024.0)) + " MB");

                long delta = 1000 - receiveTime;
                if (delta > 0) {
                    Thread.sleep(delta);
                }
            }

            double time = (System.currentTimeMillis() - receiveStart) / 1000.0;
            System.out.println(
                    "[Client " + log + "] " +
                    "File receive!. Time: " + time +
                    ", AVG speed: " + formatter.format((byteFileSize / 1024.0) / time) + " kbyte/sec");

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}
