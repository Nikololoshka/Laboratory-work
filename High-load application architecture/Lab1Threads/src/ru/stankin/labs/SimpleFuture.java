package ru.stankin.labs;

import java.util.concurrent.Callable;

public class SimpleFuture<T> {

    protected Thread thread;
    protected T result = null;
    protected Exception exception = null;
    protected boolean isDone = false;

    protected SimpleFuture() {
    }

    SimpleFuture(Runnable runnable) {
        thread = new Thread(() -> {
            try {
                runnable.run();
                successResult(null);
            } catch (Exception e) {
                failedResult(e);
            }
        });
        thread.start();
    }

    SimpleFuture(Callable<T> callable) {
        thread = new Thread(() -> {
            try {
                successResult(callable.call());
            } catch (Exception e) {
                failedResult(e);
            }
        });
        thread.start();
    }

    protected void successResult(T value) {
        result = value;
        isDone = true;
    }

    protected void failedResult(Exception e) {
        exception = e;
    }

    public T get() {
        try {
            thread.join();
            if (isDone) {
                return result;
            }
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        throw new RuntimeException(exception);
    }
}
