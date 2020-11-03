package ru.stankin.labs;

import java.util.concurrent.Callable;
import java.util.function.Consumer;
import java.util.function.Function;

public class SimplePromise<T> extends SimpleFuture<T> {

    private Consumer<T> successCallback = null;
    private Consumer<Exception> failedCallback = null;

    SimplePromise(Runnable runnable) {
        super(runnable);
    }

    SimplePromise(Callable<T> callable) {
        super(callable);
    }

    private <R> SimplePromise(SimplePromise<R> promise, Function<R, T> function) {
        thread = new Thread(() -> {
            try {
                successResult(function.apply(promise.get()));
            } catch (Exception e) {
                failedResult(e);
            }
        });
        thread.start();
    }

    @Override
    protected void successResult(T value) {
        super.successResult(value);
        if (successCallback != null) {
            successCallback.accept(value);
        }
    }

    @Override
    protected void failedResult(Exception e) {
        super.failedResult(e);
        if (failedCallback != null) {
            failedCallback.accept(e);
        }
    }

    public <R> SimplePromise<R> addCompose(Function<T, R> function) {
        return new SimplePromise<R>(this, function);
    }

    public void addSuccessCallback(Consumer<T> callback) {
        successCallback = callback;
        if (isDone) {
            callback.accept(result);
        }
    }

    public void addFailedCallback(Consumer<Exception> callback) {
        failedCallback = callback;
        if (!isDone && exception != null) {
            callback.accept(exception);
        }
    }
}
