package ru.stankin.labs;

import java.net.URL;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.FileChannel;
import java.nio.channels.ReadableByteChannel;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.text.DecimalFormat;
import java.text.NumberFormat;

public class Main {

    public static void main(String[] args) throws Exception {

        URL address = new URL("http://speedtest.ftp.otenet.gr/files/test10Mb.db");
        String fileName = "test10Mb.db";
        NumberFormat formatter = new DecimalFormat("#0.00");
        int speed = 1024 * 1024; // 1 мбайт

        try (ReadableByteChannel channel = Channels.newChannel(address.openStream());
             FileChannel fileChannel = FileChannel.open(
                     Path.of(fileName),
                     StandardOpenOption.CREATE,
                     StandardOpenOption.TRUNCATE_EXISTING,
                     StandardOpenOption.WRITE
             )) {
            System.out.println("Download from " + address
                    + " with speed: " + speed
                    + " byte/sec or "
                    + formatter.format(((double) speed) / 1024 / 1024) + " mbyte/sec");

            ByteBuffer downloadBuffer = ByteBuffer.allocate(speed);

            long byteFileSize = 0;
            while (true) {
                long start = System.currentTimeMillis();
                int readCount = channel.read(downloadBuffer);
                long downloadTime = System.currentTimeMillis() - start;

                if (readCount <= 0) {
                    break;
                }

                fileChannel.write(downloadBuffer.flip());
                byteFileSize += readCount;
                downloadBuffer.clear();

                System.out.println("Downloading " + formatter.format(((double) byteFileSize) / 1024 / 1024) + " MB");

                long delta = 1000 - downloadTime;
                // Усреднее скорости. Т.е если текущая скорость еще не поднялось
                // до необходимой (ограничивающей скорости), то задержку мы ставим меньше
                // delta -= (int) ((double) (speed - readCount) * 1000 / speed);

                if (delta > 0) {
                    Thread.sleep(delta);
                }
            }

            System.out.println("File downloaded!");
        }
    }
}
