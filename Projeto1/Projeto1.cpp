#include <iostream>
#include <vector>
using namespace std;

int fib(int n) {
    if (n == 0 || n == 1) return n;
    else return fib(n-1)+fib(n-2);
}

bool B(vector<vector<int>> T, int X[], int c, int n) {
    if (n == 1) {
        return X[0] == c;
    } else if (n == 2) {
        return T[X[0]-1][X[1]-1] == c;
    } else {
        bool result1 = false, result2 = false;
        // se for verdade, o resultado eh c
        if (B(T, X, c, n-1)) {
            int value = T[c-1][n-1];
            result1 = value == c;
        }
        if (B(T, X, c, n-2)) {
            int value = T[c-1][n-2];
            result2 = value == c;
        }
        return result1 || result2;
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> T;
    for (int i = 0; i < n; i++) {
        vector<int> v;
        T.push_back(v);
        for (int j = 0; j < n; j++) {
            int a;
            cin >> a;
            T[i].push_back(a);
        }
    }

    int X[m];
    for (int i = 0; i < m; i++) {
        cin >> X[i];
    }

    cout << B(T, X, 2, 4);

    return 0;
}