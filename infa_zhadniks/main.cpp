#include <iostream>
// #include <algorithm>
using namespace std;

int main() {
    int n, a, b, lol, cnt = 0, c;
    cin >> n;
    int arr[1001];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int i = 0;
    while (i < n - 1) {
        if (arr[i] <= arr[i+1]) {
            cnt += arr[i];
            i++;
        }
        else {
            cnt += arr[i+1];
            i+=2;
        }
    }
    cout << cnt;
}