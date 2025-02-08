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
    // auto start = chrono::high_resolution_clock::now();

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
