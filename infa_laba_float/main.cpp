#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
void dec2bin(unsigned int a) {
    for  (int i = 31; i >= 0; i--) {
        unsigned int b;
        b = a>>i;
        cout << b%2;
        if (i%4 == 0)
            cout << " ";
    }
}
void dec2bin_float(unsigned int a) {
    cout << "  ";
    for  (int i = 31; i >= 0; i--) {
        unsigned int b;
        b = a>>i;
        cout << b%2;
        if (i%31 == 0)
            cout << "   ";
        if (i%23 == 0)
            cout << "   ";
        if (i%4 == 0)
            cout << " ";
        if (i%8 == 0)
            cout << " ";
    }
    cout << endl << "Sign    Power               Mantissa";
}

union pseudo_float {
    float f;
    unsigned int u;
};

void task_0(){
    //задание 0
    unsigned int a;
    cin >> a;
    dec2bin(a);
}
void task_1() {
// задание 2
     pseudo_float a;
     cin >> a.f;
     dec2bin_float(a.u);
}

void task_2(){
     cout << fixed;
     cout.precision(1);
    pseudo_float i;
    for (i.f = 1; i.f < 1e15; i.f*=10) {
        cout << i.f << endl;
        dec2bin_float(i.u);
        cout << endl <<endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}


void task_3() {
    cout << fixed;
    cout.precision(1);
    for (float i = 16770000; i < 1e11; i++) {
        cout << i << endl;
    }
}
int main()
{
    task_3();
    return 0;
}