#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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
string B(vector<vector<int>> T, vector<int> X, int n, int c, int a, int b)
{
    if (a == b)
    {
        if (X[a - 1] == c)
        {
            return to_string(X[a - 1]);
        }
        return "";
    }
    if (a == b - 1)
    {
        if (T[X[a - 1] - 1][X[b - 1] - 1] == c)
            return "(" + to_string(X[a - 1]) + " " + to_string(X[b - 1]) + ")";
        return "";
    }

    for (int i = b - 1; i > a; i--)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (T[j][k] == c)
                {
                    if (B(T, X, n, j + 1, a, i) != "" && B(T, X, n, k + 1, i + 1, b) != "")
                        return "(" + B(T, X, n, j + 1, a, i) + " " + B(T, X, n, k + 1, i + 1, b) + ")";
                }
            }
        }
    }
    return "";
}

void BDyn(vector<vector<int>> T, vector<int> X, int n, int m, int c)
{   
    if (m == 1){
        if (X[0] == c) cout << "1\n" << c << "\n";
        else cout << "0\n";
        return;
    }
    if (m == 2){
        if (T[X[0]-1][X[1]-1] == c) cout << "1\n(" << X[0] << " " << X[1] << ")\n";
        else cout << "0\n";
        return;
    }


    // tabela de programação dinâmica
    vector<int> table[m][m] = {{}};
    vector<vector<int>> open[m][m] = {{}};
    vector<vector<int>> close[m][m] = {{}};
    vector<int> value_open = {};
    vector<int> value_close = {};
    bool finish = false;


    for (int i = 0; i < m; i++)
    {
        // caso base 1
        vector<int> v;
        v.push_back(X[i]);
        table[i][i] = v;
        open[i][i].push_back({});
        close[i][i].push_back({});

        // caso base 2
        if (i < m - 1)
        {
            vector<int> w;
            w.push_back(T[X[i] - 1][X[i + 1] - 1]);
            table[i][i + 1] = w;
            open[i][i + 1].push_back({i});
            close[i][i + 1].push_back({i + 1});
        }
    }
    // cout << "Start1\n";

    for (int i = 2; i < m; i++)
    {
        for (int j = 0; j < m - i; j++)
        {
            int row = j, col = j + i;
            vector<int> result = {};
            vector<vector<int>> result_open = {}, result_close = {};
            int count = 0;
            for (int k = col; k > row; k--)
            {
                vector<int> first = table[row][k - 1], second = table[k][col];
                vector<vector<int>> first_open = open[row][k - 1], second_open = open[k][col];
                vector<vector<int>> first_close = close[row][k - 1], second_close = close[k][col];

                for (int i1 = 0; i1 < (int)first.size(); i1++)
                {
                    for (int i2 = 0; i2 < (int)second.size(); i2++)
                    {
                        int value = T[first[i1] - 1][second[i2] - 1];

                        value_open = {};

                        for (int v1 = 0; v1 < (int)first_open[i1].size(); v1++)
                            value_open.push_back(first_open[i1][v1]);
                        for (int v2 = 0; v2 < (int)second_open[i2].size(); v2++)
                            value_open.push_back(second_open[i2][v2]);
                        value_open.push_back(row);

                        value_close = {};
                        for (int v3 = 0; v3 < (int)first_close[i1].size(); v3++)
                            value_close.push_back(first_close[i1][v3]);
                        for (int v4 = 0; v4 < (int)second_close[i2].size(); v4++)
                            value_close.push_back(second_close[i2][v4]);
                        value_close.push_back(col);

                        bool to_add = true;
                        for (int u = 0; u < count; u++)
                        {
                            if (result[u] == value)
                            {
                                to_add = false;
                                break;
                            }
                        }
                        if (to_add)
                        {
                            if (row == 0 && col == m - 1 && value == c)
                                finish = true;
                            result.push_back(value);
                            result_open.push_back(value_open);
                            result_close.push_back(value_close);
                            count++;
                        }

                        if (count == n || finish)
                            break;
                    }
                    if (count == n || finish)
                        break;
                }
                if (count == n || finish)
                    break;
            }

            if (finish)
                break;

            table[row][col] = result;

            open[row][col] = result_open;
            close[row][col] = result_close;

            // if (finish) break;
        }
        if (finish){
            cout << "1\n";
            break;}
        
    }
    if (!finish)
    cout << "0\n";

    else{
        for (int i = 0; i < m; i++)
        {

            for (int i1 = 0; i1 < count(value_open.begin(), value_open.end(), i); i1++)
                cout << "(";

            cout << X[i];

            for (int i1 = 0; i1 < count(value_close.begin(), value_close.end(), i); i1++)
                cout << ")";

            if (i != m - 1)
                cout << " ";
        }
        cout << "\n";
    }
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    vector<vector<int>> T;
    for (int i = 0; i < n; i++)
    {
        vector<int> v;
        T.push_back(v);
        for (int j = 0; j < n; j++)
        {
            int a;
            scanf("%d", &a);
            T[i].push_back(a);
        }
    }

    vector<int> X;
    for (int i = 0; i < m; i++)
    {
        int a;
        scanf("%d", &a);
        X.push_back(a);
    }

    int result;
    scanf("%d", &result);

    BDyn(T, X, n, m, result);
    // if (ANSWER=="")
    //     printf("0\n");
    // else
    //     printf("1\n%s\n", ANSWER.c_str());
    // for (int i : ANSWER) cout << i << '\n';

    return 0;
}
