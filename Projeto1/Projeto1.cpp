#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

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
// string B(vector<vector<int>> T, vector<int> X, int n, int c, int a, int b)
// {
//     if (a == b)
//     {
//         if (X[a - 1] == c)
//         {
//             return to_string(X[a - 1]);
//         }
//         return "";
//     }
//     if (a == b - 1)
//     {
//         if (T[X[a - 1] - 1][X[b - 1] - 1] == c)
//             return "(" + to_string(X[a - 1]) + " " + to_string(X[b - 1]) + ")";
//         return "";
//     }

//     for (int i = b - 1; i > a; i--)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             for (int k = 0; k < n; k++)
//             {
//                 if (T[j][k] == c)
//                 {
//                     if (B(T, X, n, j + 1, a, i) != "" && B(T, X, n, k + 1, i + 1, b) != "")
//                         return "(" + B(T, X, n, j + 1, a, i) + " " + B(T, X, n, k + 1, i + 1, b) + ")";
//                 }
//             }
//         }
//     }
//     return "";
// }

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





struct node {
    int l = -1;
    int r = -1;
    int k;
    int res;
};

string recuperar_parentesis(vector<vector<vector<node>>>& table, int c, int i, int j) {
    // caso base
    if (i == j) {
        return to_string(c);
    }
    // caso iterativo
    vector<node>& res = table[i][j];
    for (node& v : res) {
        if (v.res == c) {
            int left = v.l, k = v.k, right = v.r;
            return "(" + recuperar_parentesis(table, left, i, k-1) + " " + recuperar_parentesis(table, right, k, j) + ")";
        }
    }
    return "";
} 

void BDyn(vector<vector<int>>& T, vector<int>& X, int n, int m, int c) {
    // PREENCHER A TABELA

    vector<vector<vector<node>>> table;
    table.resize(m);
    for (int i = 0; i < m; i++) table[i].resize(m);
    bool finish = false;

    // caso base {a}
    for (int i = 0; i < m; i++) {
        node v;
        v.res = X[i];
        table[i][i].push_back(v);
    }
    // caso iterativo {left, k, right, res}
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < m-i; j++) {
            int row = j, col = j+i;
            int registered[n] = {0};
            int count = 0;

            for (int k = col; k > row; k--) {
                vector<node>& left = table[row][k-1], right = table[k][col];

                for (int i = 0; i < (int) left.size(); i++) {
                    node& l = left[i];
                    int res_left;
                    if (l.l == -1) res_left = l.res;
                    else res_left = T[l.l-1][l.r-1];

                    for (int j = 0; j < (int) right.size(); j++) {
                        node& r = right[j];
                        int res_right;
                        // se for um caso base
                        if (r.l == -1) res_right = r.res;
                        // se nao 
                        else res_right = T[r.l-1][r.r-1];

                        int res_value = T[res_left-1][res_right-1];

                        if (registered[res_value-1] == 0) {
                            // adicionar
                            if (row == 0 && col == m - 1){
                                if (res_value == c){
                                    finish = true;
                                    node res;
                                    res.l = res_left;
                                    res.k = k;
                                    res.r = res_right;
                                    res.res = res_value;
                                    table[row][col].push_back(res);
                                }
                            }
                            else{
                                count++;
                                node res;
                                res.l = res_left;
                                res.k = k;
                                res.r = res_right;
                                res.res = res_value;
                                table[row][col].push_back(res);
                            }
                            // resgistar no vetor
                            registered[res_value-1]++;
                        }
                            
                        if (count == n || finish) break;
                    }
                    if (count == n || finish) break;
                }
                if (count == n || finish) break;
            }
            if (finish) break;
        }
        if (finish) break;
    }

    // RECUPERAR OS PARENTESIS
    vector<node>& res = table[0][m-1]; // resposta esta neste indice
    bool found = false;
    string ANSWER;
    for (node v : res) {
        if (v.res == c) {
            found = true;
            ANSWER = recuperar_parentesis(table, c, 0, m-1);
            break;
        }
    }

    if (found) {
        cout << "1\n" << ANSWER << '\n';
    } else cout << "0\n";

    return;
}

int main() {
    auto start = chrono::high_resolution_clock::now();

    int n, m;
    scanf("%d%d", &n, &m);

    vector<vector<int>> T(n, vector<int> (n));
    for (int i = 0; i < n; i++)
    {
        vector<int> v;
        T.push_back(v);
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &T[i][j]);
        }
    }

    vector<int> X(m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &X[i]);
    }

    int result;
    scanf("%d", &result);

    BDyn(T, X, n, m, result);

    // auto stop = chrono::high_resolution_clock::now();                                                    
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    // printf("%d", duration.count());

    return 0;
}
