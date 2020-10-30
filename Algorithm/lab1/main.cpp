#include <iostream>
#include <chrono>

using namespace std;

int exFib(int N) {
    if (N == 1)
        return 1;
    if (N == 0)
        return 0;
    return exFib(N - 1) + exFib(N - 2);
}

long polFib(int N) {
    long *p = new long[N];
    p[0] = 0;
    p[1] = 1;

    for (int i = 2; i <= N; ++i) {
        p[i] = p[i - 1] + p[i - 2];
    }
    long result = p[N];
    delete[] p;
    return result;
}
//static int swapCount = 1;
//static int sravCount = 1;

//bool foo() {
//    ::sravCount++;
//    return true;
//}

template<typename T>
void insertionSorting(T arr[], size_t arrSize) {

    for (size_t i = 1; i < arrSize; ++i)
        for (size_t j = i; /*foo() &&*/ arr[j] < arr[j - 1] && j > 0; --j) {
            std::swap(arr[j], arr[j - 1]);
//            ::swapCount++;
        }
}

template<typename T>
void gnomeSorting(T arr[], size_t arrSize) {
    size_t i = 1;
    while (i < arrSize) {
        if (i == 0 || ( /*foo() &&*/ arr[i - 1] <= arr[i]))
            ++i;
        else {
            std::swap(arr[i], arr[i - 1]);
//            ::swapCount++;
            --i;
        }
    }
}

template<typename T>
void printArray(T arr[], size_t arrSize) {
    for (size_t i = 0; i < arrSize; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template<typename T>
void greedySorting(T arr[], int arrSize) {
    for (int i = 0; i < arrSize - 1; i++) {
        int index = i;
        for (int j = i + 1; j < arrSize; j++) {
            if (arr[j] < arr[index]) {
                index = j;
            }
        }

        if (index != i) {
            swap(arr[i], arr[index]);
//            cout << "swap" << endl;
            index = i;
        }
    }
}

int main()
{
//    cout << "exFib(42):\t";
//    auto start = std::chrono::high_resolution_clock::now();
//    exFib(42);
//    auto end = std::chrono::high_resolution_clock::now();
//    cout << endl;
//    cout << "Dur: " << (static_cast<std::chrono::duration<float>>(end - start)).count() << endl;

//    start = std::chrono::high_resolution_clock::now();
//    cout << "polFib(42):\t" << polFib(42) << endl;
//    end = std::chrono::high_resolution_clock::now();
//    cout << "Dur: " << (static_cast<std::chrono::duration<float>>(end - start)).count() << endl;
//    const int SIZE = 1000;

//    int arr1[SIZE], arr2[SIZE];
//    srand(time(0));
//    for (int i = 0; i < SIZE; ++i) {
//        arr1[i] = arr2[i] = std::rand() % 10;
//    }
//    auto start = std::chrono::high_resolution_clock::now();
//    insertionSorting(arr1, SIZE);
//    auto end = std::chrono::high_resolution_clock::now();
//    cout << "Dur: " << (static_cast<std::chrono::duration<float>>(end - start)).count() << endl;
//    cout << "swap: " << ::swapCount - 1 << endl;
//    cout << "srav: " << ::sravCount - 1 << endl;
//    ::swapCount = 1;
//    ::sravCount = 1;
//    start = std::chrono::high_resolution_clock::now();
//    gnomeSorting(arr2, SIZE);
//    end = std::chrono::high_resolution_clock::now();
//    cout << "Dur: " << (static_cast<std::chrono::duration<float>>(end - start)).count() << endl;
//    cout << "swap: " << ::swapCount - 1 << endl;
//    cout << "srav: " << ::sravCount - 1 << endl;

//    cout << "Array:\t\t\t";
//    printArray(arr, SIZE);

//    insertionSorting<int>(arr, SIZE);
//    cout << "Inserting sorting:\t";
//    printArray(arr, SIZE);

//    gnomeSorting<int>(arr, SIZE);
//    cout << "Gnome sorting:\t\t";
//    printArray(arr, SIZE);

//    int arr[3] = {3, 2, 1};
//    greedySorting(arr, 3);

    return 0;
}
