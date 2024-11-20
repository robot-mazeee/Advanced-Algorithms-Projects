#include <iostream>
#include <vector>
using namespace std;

// int fib(int n) {
//     if (n == 0 || n == 1) return n;
//     else return fib(n-1)+fib(n-2);
// }

// bool B(vector<vector<int>> T, int X[], int c, int n) {
//     if (n == 1) {
//         return X[0] == c;
//     } else if (n == 2) {
//         return T[X[0]-1][X[1]-1] == c;
//     } else {
//         bool result1 = false, result2 = false;
//         // se for verdade, o resultado eh c
//         if (B(T, X, c, n-1)) {
//             int value = T[c-1][n-1];
//             result1 = value == c;
//         }
//         if (B(T, X, c, n-2)) {
//             int value = T[c-1][n-2];
//             result2 = value == c;
//         }
//         return result1 || result2;
//     }
// }

/**
 * @brief 
 *      caso base 1: sequencia de um elemento
 *      caso base 2: sequencia de dois elementos
 *      caso recursivo: iterar por todas as posições de a a b
 *                      X1 subsequencia de a ate i
 *                      X2 subsequencia de i ate b
 *                      valor de X1 + X2 tem de ser c
 *                      valor de X1 = c1 e valor de X2 = c2
 *                      tal que c1 + c2 = c
 * 
 * @param T tabela de valores
 * @param X sequencia
 * @param n dimensao da tabela
 * @param c valor que queremos obter
 * @param a posição inicial da sequencia
 * @param b posição final da sequencia
 */
bool B(vector<vector<int>> T, int X[], int n, int c, int a, int b) {
    if (a == b) {
        return X[a-1] == c;
    } 
    if (a == b-1) {
        return T[a][b] == c;
    }
    
    for (int i = a; i < b; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (T[j][k] == c)
                    return B(T, X, n, j, a, i) && B(T, X, n, k, i+1, b);
            }
        }
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

    int result;
    cin >> result;

    cout << B(T, X, n, result, 1, 4);

    return 0;
}