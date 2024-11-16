#include <iostream>
using namespace std;

bool B(int T[], int X[], int c, int n) {
    if (n == 1) {
        return X[0] == c;
    } else if (n == 2) {
        return T[X[0]]+T[X[1]] == c;
    } else {
        return ;
    }
}

int fib(int n) {
    if (n == 0 || n == 1) return n;
    else return fib(n-1)+fib(n-2);
}

int main() {
    int n, m;
    cin >> n >> m;

    int T[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> T[i][j];
        }
    }

    int X[m];
    for (int i = 0; i < m; i++) {
        cin >> X[i];
    }

    return 0;
}