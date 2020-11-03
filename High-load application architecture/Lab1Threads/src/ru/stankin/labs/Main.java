package ru.stankin.labs;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.Executors;

public class Main {

    public static void main(String[] args) throws Exception {

        // Задание:
        // Разработать свою реализацию концепции Future - Promise, работающую в многопоточной среде

        var pool = Executors.newFixedThreadPool(2);

        // ------------------------------------------------------------------
        // 1. Потоки, ожидающие результата из Future блокируются, пока результат не будет записан.

        var future = pool.submit(() -> {
            Thread.sleep(3000);
            return 123;
        });
        var result = future.get();
        System.out.println("Future: " + result);

        // SimpleFuture
        var myFuture = new SimpleFuture<>(() -> {
            Thread.sleep(1000);
            return 1000 - 123;
        });
        var myResult = myFuture.get();
        System.out.println("MyFuture: " + myResult);


        // ------------------------------------------------------------------
        // 2. Реализовать возможность подписки слушателя на Future и неблокирующей композиции Future.

        var promise1 = CompletableFuture.supplyAsync(() -> {
            try {
                Thread.sleep(3000);
            } catch (InterruptedException ignored) {

            }
            return 789;
        }, pool);
        var promise2 = CompletableFuture.supplyAsync(() -> {
            try {
                Thread.sleep(2500);
            } catch (InterruptedException ignored) {

            }
            return 1000 - 789;
        }, pool);

        var promise = promise1.thenCompose((first) -> promise2.thenApply((second) -> first + second));
        promise.thenAccept((value) -> {
            System.out.println("Promise: " + value);

            // Пока pool работает, программа не завершится
            pool.shutdown();
        });


        // SimplePromise
        var myPromise1 = new SimplePromise<>(() -> {
            Thread.sleep(2000);
            return 789;
        });
        var myPromise2 = new SimplePromise<>(() -> {
            Thread.sleep(5000);
            return 2000 - 789;
        });

        var myPromise = myPromise1.addCompose((first) -> first + myPromise2.get());
        myPromise.addSuccessCallback((value) -> {
            System.out.println("MyPromise: " + value);
        });
    }
}
