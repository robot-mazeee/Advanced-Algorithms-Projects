#include <iostream>
#include <vector>
#include <string>
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
string B(vector<vector<int>> T, vector<int> X, int n, int c, int a, int b) {
    if (a == b) {
        if (X[a-1] == c){
            return to_string(X[a-1]);}
        return "";
    } 
    if (a == b-1) {
        if (T[X[a-1]-1][X[b-1]-1] == c)
            return "(" + to_string(X[a-1]) + " "+ to_string(X[b-1]) + ")";
        return "";
    }
    
    for (int i = b-1; i > a; i--) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (T[j][k] == c){
                    if (B(T, X, n, j+1, a, i) != "" && B(T, X, n, k+1, i+1, b) !="")
                        return "(" + B(T, X, n, j+1, a, i) + " "+ B(T, X, n, k+1, i+1, b) + ")";
                }
            }
        }
    }
    return "";
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<vector<int>> T;
    for (int i = 0; i < n; i++) {
        vector<int> v;
        T.push_back(v);
        for (int j = 0; j < n; j++) {
            int a;
            scanf("%d", &a);
            T[i].push_back(a);
        }
    }

    vector<int> X;
    for (int i = 0; i < m; i++) {
        int a;
        scanf("%d", &a);
        X.push_back(a);
    }

    int result;
    scanf("%d", &result);

    string ANSWER = B(T, X, n, result, 1, m);
    if (ANSWER=="")
        printf("0\n");
    else
        printf("1\n%s\n", ANSWER.c_str());

    return 0;
}
