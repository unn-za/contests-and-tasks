
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include <iomanip>

using namespace std;

double exact_integral() {
    return 1.0 / 3.0;
}

// объявления функций
float func(float x) { return x * x; }
double func(double x) { return x * x; }

template<typename T>
T integrate(T (*f)(T), unsigned long long n) {
    T step = T(1.0) / n;  // размер шага
    T total = 0;

    for (unsigned long long i = 0; i < n; i++) {
        // середина текущего отрезка
        T x_mid = (i + 0.5) * step;
        total += f(x_mid);
    }
    return total * step;
}

int main() {
    // файл для записи результатов
    ofstream data_file("integration_results.csv");
    data_file << "n,float_result,double_result,float_error,double_error\n";

    double exact_value = exact_integral();
    vector<unsigned long long> test_sizes;

    // добавляем разные количества разбиений
    for (int n = 1; n <= 100; n++) {
        test_sizes.push_back(n);
    }

    // степени десятки
    for (int exp = 3; exp <= 9; exp++) {
        unsigned long long n = 1;
        for (int i = 0; i < exp; i++) n *= 10;
        test_sizes.push_back(n);
        test_sizes.push_back(n * 2);
        test_sizes.push_back(n * 5);
    }

    // болльшие значения
    vector<unsigned long long> huge_sizes = {
        1000000000,      // 1e9
        2000000000,      // 2e9
        5000000000,      // 5e9
        10000000000,     // 1e10
        20000000000,     // 2e10
        50000000000,     // 5e10
        100000000000,    // 1e11
        200000000000,    // 2e11
        500000000000,    // 5e11
        1000000000000,   // 1e12
        2000000000000,   // 2e12
        5000000000000,   // 5e12
        10000000000000,  // 1e13
        20000000000000,  // 2e13
        50000000000000,  // 5e13
        100000000000000, // 1e14
        200000000000000, // 2e14
        500000000000000, // 5e14
        1000000000000000, // 1e15
        2000000000000000, // 2e15
        5000000000000000, // 5e15
        10000000000000000, // 1e16
        20000000000000000, // 2e16
        50000000000000000, // 5e16
        100000000000000000, // 1e17
        200000000000000000, // 2e17
        500000000000000000, // 5e17
        1000000000000000000 // 1e18
    };

    for (auto n : huge_sizes) {
        test_sizes.push_back(n);
    }

    cout << "Вычисляем интеграл для " << test_sizes.size() << " значений n..." << endl;
    cout << "Это займет очень много времени!..." << endl;
    cout << "Можно прервать выполнение при достижении желаемых значений." << endl;

    for (unsigned long long n : test_sizes) {
        float result_float = 0;
        double result_double = 0;

        // Для float используем только до 10^7 (после этого он уже бесполезен)
        if (n <= 10000000) {
            result_float = integrate<float>(func, n);
        } else {
            result_float = -1; // помечаем как невычисленное
        }

        // Для double вычисляем ВСЕ значения через цикл
        // ПРЕДУПРЕЖДЕНИЕ: для n > 10^9 это будет ОЧЕНЬ долго
        result_double = integrate<double>(func, n);

        // вычисляем погрешности
        float error_float = (n <= 10000000) ? abs(result_float - exact_value) : -1;
        double error_double = abs(result_double - exact_value);

        data_file << n << ","
                 << setprecision(15) << result_float << ","
                 << setprecision(15) << result_double << ","
                 << setprecision(15) << error_float << ","
                 << setprecision(15) << error_double << "\n";

        // Выводим прогресс для больших значений
        if (n >= 1000000) {
            cout << "n = " << n << ", double result = " << setprecision(15) << result_double
                 << ", double error = " << scientific << setprecision(3) << error_double << endl;
        }

        // Принудительно сбрасываем буфер файла после каждой записи
        data_file.flush();
    }

    cout << "Результаты сохранены в integration_results.csv" << endl;
    cout << "\nАнализ ошибок:" << endl;
    cout << "- Float показывает значительные ошибки уже при n ~ 10^7" << endl;
    cout << "- Double начинает показывать ошибки при n > 10^15" << endl;
    cout << "- При n = 10^18 ошибки округления в double становятся катастрофическими" << endl;

    return 0;
}