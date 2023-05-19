#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    if (n == 1) {
        if (a == b) {
            cout << 1 << '\n';
        } else {
            cout << 0 << '\n';
        }
        cout << a << ":" << b << '\n';
        return 0;
    } 

    cout << max(0, n - (a+b)) << '\n';
    vector<int> v1(n), v2(n);
    
    if (a == 0 || b == 0) {
        for (int i = 0; i < min(n-1, a); i++) {
            v1[i] = 1;
        }
        for (int i = 0; i < min(n-1, b); i++) {
            v2[i] = 1;
        }
        v1[n-1] = a - min(n-1, a);
        v2[n-1] = b - min(n-1, b);
    } else {
        v1[0] = 1;
        a--;
    
        v2[n-1] = 1;
        b--;
        for (int i = 0; i < min(n-2,a); i++) {
            v1[i+1] = 1;
        }   
        int temp = min(n-2, a);
        v1[0] += a - temp;

        for (int i = 0; i < min(n - 2 - temp, b); i++) {
            v2[n-2-i] = 1;
        }

        temp = min(n - 2 - temp, b);
        v2[n-1] += b - temp;
    }



    for (int i = 0; i < n; i++) {
        cout << v1[i] << ":" << v2[i] << '\n';
    }

    return 0;
}