#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    long long t, r, ans = 0, n, m, L, R;
    string s;
    cin >> t >> r >> s >> m;
    n = s.size();
    vector <long long> pref(n+1), st(n+1);
    st[0] = 1;
    for(int i = 1; i <= n; i++)
        st[i] = ((st[i-1]%r)*(t%r))%r;  // оставить
    pref[0] = 0;
    for(int i = 0; i < n; i++){
        pref[i+1] = (pref[i]*(t%r)+s[i])%r;
    }
    for(int i = 0; i < m; i++) {
        cin >> L >> R;
        cout << (pref[R + 1] - pref[L]*st[R - L + 1]%r + r) % r << '\n';
    }
    return 0;
}