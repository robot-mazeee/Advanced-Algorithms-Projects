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
        cout << "first case:"<<a  << (X[a-1] == c) << "\n";
        return X[a-1] == c;
    } 
    if (a == b-1) {
        cout << "second case:" << a << b <<X[a-1] << X[b-1]  << (T[X[a-1]-1][X[b-1]-1] == c) << "\n";
        return T[X[a-1]-1][X[b-1]-1] == c;
    }
    
    for (int i = b-1; i > a; i--) {    // 1 a 4
        for (int j = 0; j < n; j++) {                 //
            for (int k = 0; k < n; k++) {             //
                if (T[j][k] == c){
                    cout <<"res: "<< c << "-" << j << k ;
                    if (B(T, X, n, j+1, a, i) && B(T, X, n, k+1, i+1, b))
                    return true;
                }
            }
        }
    }
    return false;
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

    bool ANSWER = B(T, X, n, result, 1, m);
    cout << "ANSWER";
    cout << ANSWER;

    return 0;
}