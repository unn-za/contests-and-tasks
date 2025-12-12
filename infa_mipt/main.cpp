/*
 #include <fstream>
#include <iostream>
#include <chrono>
#include <random>
#include <cmath>
int rand_uns(int min, int max) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}
using namespace std;


// Bubble sort

/*
int main()
{
    ofstream f("data_bubble", ios::out);
    for (long i = 1; i < 15000; i += 1) {
        int arr[i];
        for (int j = 1; j < i; j++) {
            arr[j] = rand_uns(-1000, 1000);
        }
        int lol;
        auto start = std::chrono::high_resolution_clock::now();
        for (int k = 1; k < i; k++) {
            for (int j = 1; j < k; j++) {
                if (arr[i] > arr[j]) {
                    lol = arr[i];
                    arr[i] = arr[j];
                    arr[j] = lol;
                }
            }
        }
             auto end = std::chrono::high_resolution_clock::now();
            auto nsec = end - start;
            std::cout << nsec.count() << " nanosec " << i <<  std::endl;
            f << nsec.count() << endl;
    }
    return 0;
}
*/


#include <fstream>
#include <iostream>
#include <chrono>
#include <random>


// сортировка Вставка

/*
int main()
{
    ofstream f("data_insertion", ios::out);
    for (long i = 1; i < 15000; i += 1) {
        int arr[i];
        for (int j = 0; j < i; j++) {
            arr[j] = rand_uns(-1000, 1000);
        }

        auto start = std::chrono::high_resolution_clock::now();

        // Сортировка вставками
        for (int k = 1; k < i; k++) {
            int key = arr[k];
            int j = k - 1;

            // Сдвигаем элементы большие чем key
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto nsec = end - start;
        std::cout << nsec.count() << " nanosec " << i << std::endl;
        f << nsec.count() << endl;
    }
    f.close();
    return 0;
}
*/

#include <fstream>
#include <iostream>
#include <chrono>
#include <random>

// сортировка Выбор

/*
int main()
{
    ofstream f("data_selection", ios::out);
    for (long i = 1; i < 15000; i += 1) {
        int arr[i];
        for (int j = 0; j < i; j++) {
            arr[j] = rand_uns(-1000, 1000);
        }

        auto start = std::chrono::high_resolution_clock::now();

        // Сортировка простым выбором
        for (int k = 0; k < i - 1; k++) {
            int min_idx = k;

            // Находим индекс минимального элемента в оставшейся части
            for (int j = k + 1; j < i; j++) {
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }
            }

            // Обмен минимального элемента с текущим
            if (min_idx != k) {
                int temp = arr[k];
                arr[k] = arr[min_idx];
                arr[min_idx] = temp;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto nsec = end - start;
        std::cout << nsec.count() << " nanosec " << i << std::endl;
        f << nsec.count() << endl;
    }
    f.close();
    return 0;
} */

// сортировка Хоара

/*
void quickSort(int arr[], int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}

int main() {
    ofstream f("data_quick", ios::out);
    ofstream f_norm("data_quick_normalized", ios::out);

    for (long i = 1; i < 15000; i += 1) {
        int arr[i];
        for (int j = 0; j < i; j++) {
            arr[j] = rand_uns(-1000, 1000);
        }

        auto start = std::chrono::high_resolution_clock::now();
        if (i > 1) {
            quickSort(arr, 0, i - 1);
        }
        auto end = std::chrono::high_resolution_clock::now();

        auto nsec = end - start;
        std::cout << nsec.count() << " nanosec " << i << std::endl;
        f << nsec.count() << endl;

        if (i > 1) {
            double normalized = static_cast<double>(nsec.count()) / (i * log2(i));
            f_norm << normalized << endl;
        }
    }
    return 0;
} */

// мердж сорт


/*
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    ofstream f("data_merge", ios::out);
    ofstream f_norm("data_merge_normalized", ios::out);

    for (long i = 1; i < 15000; i += 1) {
        int arr[i];
        for (int j = 0; j < i; j++) {
            arr[j] = rand_uns(-1000, 1000);
        }

        auto start = std::chrono::high_resolution_clock::now();
        if (i > 1) {
            mergeSort(arr, 0, i - 1);
        }
        auto end = std::chrono::high_resolution_clock::now();

        auto nsec = end - start;
        std::cout << nsec.count() << " nanosec " << i << std::endl;
        f << nsec.count() << endl;

        if (i > 1) {
            double normalized = static_cast<double>(nsec.count()) / (i * log2(i));
            f_norm << normalized << endl;
        }
    }
    return 0;
}

*/

// Пирамидальная сортировка
 /*
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    ofstream f("data_heap", ios::out);
    ofstream f_norm("data_heap_normalized", ios::out);

    for (long i = 1; i < 15000; i += 1) {
        int arr[i];
        for (int j = 0; j < i; j++) {
            arr[j] = rand_uns(-1000, 1000);
        }

        auto start = std::chrono::high_resolution_clock::now();
        if (i > 1) {
            heapSort(arr, i);
        }
        auto end = std::chrono::high_resolution_clock::now();

        auto nsec = end - start;
        std::cout << nsec.count() << " nanosec " << i << std::endl;
        f << nsec.count() << endl;

        if (i > 1) {
            double normalized = static_cast<double>(nsec.count()) / (i * log2(i));
            f_norm << normalized << endl;
        }
    }
    return 0;
}


*/











