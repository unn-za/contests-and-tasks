#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
//#include <string>

using namespace std;

struct drevo{
    int sz;
    vector <int> tree;
    void init(int n) {
        sz = 1;
        while(sz <= n) sz *= 2;
        tree.assign( sz - 1, 0);
    }
    void build(vector <int>& a, int x, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < a.size()) {
                tree[x] = a[lx];
                return;
            }
        } else {
            int m = (lx + rx) / 2;
            build(a, 2 * x + 1, lx, m);
            build(a, 2 * x + 2, m, rx);
            tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
        }
    }
    void build(vector <int>& a) {
        init(a.size());
        build(a, 0, 0, sz);
    }
    void set(int k, int val, int x, int lx, int rx) {
        if(rx - lx == 1) {
            tree[x] = val;
        }
        else {
            int m = (lx + rx) / 2;
            if(k < m) {
                set(k, val, 2 * x + 1, lx, m);
            } else{
                set(k, val, 2 * x + 2, m, rx);
            }
            tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
        }
    }
    void set(int k, int val) {
        set(k, val, 0, 0, sz);
    }
    int sum(int l, int r, int x, int lx, int rx) {
        if(l <= lx && rx <= r) {
            return tree[x];
        }
        if(rx <= l || lx >= r) {
            return 0;
        } else{
            int m = (lx + rx) / 2;
            int sum_left = sum(l, r, 2 * x + 1, lx, m);
            int sum_right = sum(l, r, 2 * x + 2, m, rx);
            return sum_left + sum_right;
        }
    }
    int sum(int l, int r) {
        return sum(l, r, 0, 0, sz);
    }
};
signed main()
{
    int n, k, I, x, L, R;
    char s;
    drevo deo;
    cin >> n >> k;
    vector <int> a(n);
    deo.build(a);
    for(int i = 0; i < k; i++){
        cin >> s;
        if(s == 'A'){
            cin >> I >> x;
            deo.set(I, x);
        }
        else{
            cin >> L >> R;
            cout << deo.sum(L, R) << '\n';
        }
    }
}
