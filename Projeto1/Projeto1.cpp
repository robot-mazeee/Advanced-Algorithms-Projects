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

// vector<int> BDyn(vector<vector<int>> T, vector<int> X, int n, int m, int c) {
//     // tabela de programação dinâmica
//     vector<int> table[m][m] = {{}};
//     vector<vector<int>> open[m][m] = {{}};
//     vector<vector<int>> close[m][m] = {{}};
    
//     for (int i = 0; i < m; i++) {
//         // caso base 1
//         vector<int> v;
//         v.push_back(X[i]);
//         table[i][i] = v;
//         open[i][i].push_back({});
//         close[i][i].push_back({});

//         // caso base 2
//         if (i < m-1) {
//             vector<int> w, p;
//             w.push_back(T[X[i]-1][X[i+1]-1]);
//             table[i][i+1] = w;
//             open[i][i+1].push_back({i});
//             close[i][i+1].push_back({i+1});

//         }
//     }
//     //cout << "Start1\n";

//     for (int i = 2; i < m; i++) {
//         for (int j = 0; j < m-i; j++) {
//             int row = j, col = j+i, count = 0;
//             vector<int> result = {};
//             vector<vector<int>> result_open = {{}}, result_close = {{}};
//             for (int k = col; k > row; k--) {
//                 vector<int> first = table[row][k-1], second = table[k][col];
//                 vector<vector<int>> first_open = open[row][k-1], second_open = open[k][col];
//                 vector<vector<int>> first_close = close[row][k-1], second_close = close[k][col];

//                 for (int i1 = 0; i1 < first.size(); i1++) {
//                     for (int i2 = 0; i2 < second.size(); i2++) {
//                         int value = T[first[i1]-1][second[i2]-1];

//                         vector<int> value_open;
//                         for (int v1 : first_open[i1])
//                             value_open.push_back(v1);
//                         for (int v2 : second_open[i2])
//                             value_open.push_back(v2);
//                         value_open.push_back(row);

//                         vector<int> value_close;
//                         for (int v1 : first_close[i1])
//                             value_close.push_back(v1);
//                         for (int v2 : second_close[i2])
//                             value_close.push_back(v2);
//                         value_close.push_back(col);

//                         bool to_add = true;
//                         for (int u = 0; u < count; u++) {
//                             if (result[u] == value) {
//                                 to_add = false;
//                                 break;
//                             }
//                         }
//                         if (to_add) {
//                             result.push_back(value);
//                             result_open.push_back(value_open);
//                             result_close.push_back(value_close);
//                             count++;
//                         }

//                         if (count == n) break;
//                     }
//                     if (count == n) break;
//                 }
//                 if (count == n) break;
//             }
//             table[row][col] = result;
//             open[row][col] = result_open;
//             close[row][col] = result_close;
//         }
//     }

//     for (int h = 0; h < m; h++) {
//         for (int l = 0; l < m; l++) {
//             vector<vector<int>> result = open[h][l];
//             for (int i = 0; i < result.size(); i++) {
//                 for (int j = 0; j < result[i].size(); j++) {
//                     cout << result[i][j] << '\n';
//                 }
//             }
//         }
//     }

//     return table[0][m-1];
// }

vector<vector<int>> BDyn(vector<vector<int>> T, vector<int> X, int n, int m, int c) {
    // PREENCHER A TABELA

    // tabela de programação dinâmica
    vector<vector<int>> table[m][m];
    // caso base 
    for (int i = 0; i < m; i++) {
        vector<int> v;
        v.push_back(X[i]);
        table[i][i].push_back(v);
    }
    // caso iterativo
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < m-i; j++) {
            int row = j, col = j+i;
            for (int k = col; k > row; k--) {
                cout << k << '\n';
                vector<vector<int>> left = table[row][k-1], 
                right = table[k][col];

                for (int i = 0; i < left.size(); i++) {
                    vector<int> l = left[i];
                    int res_left;
                    if (l.size() == 1) res_left = l[0];
                    else res_left = T[l[0]-1][l[2]-1];

                    for (int j = 0; j < right.size(); j++) {
                        vector<int> r = right[j];
                        int res_right;
                        // se for um caso base
                        if (r.size() == 1) res_right = r[0];
                        // se nao 
                        else res_right = T[r[0]-1][r[2]-1];

                        int res_value = T[res_left-1][res_right-1];
                        vector<int> res = {res_left, k, res_right, res_value};
                        table[row][col].push_back(res);
                    }
                }
            }
        }
    }

        /**
3 4
2 2 2
2 1 2
1 3 3
2 2 3 3
2
     */

    // RECUPERAR OS PARENTESIS
    vector<int> table[0][m-1];

    

    // for (int i = 0; i < m; i++) {
    //     for (int j =0; j < m-i; j++) {
    //         for (vector<int> v : table[j][j+i]) {
    //             cout << "left: " << v[0] << " k: " << v[1] << " right: " << v[2] << " res: "<< v[3] << '\n';
    //         }
    //     }
    // }

    for (vector<int> v : table[0][m-1]) {
        cout << "left: " << v[0] << " k: " << v[1] << " right: " << v[2] << " res: "<< v[3] << '\n';
    }

    return table[0][m-1];
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

    vector<vector<int>> ANSWER = BDyn(T, X, n, m, result);
    // if (ANSWER=="")
    //     printf("0\n");
    // else
    //     printf("1\n%s\n", ANSWER.c_str());
    // for (int i : ANSWER) cout << i << '\n';

    return 0;
}
