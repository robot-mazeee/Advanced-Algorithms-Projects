#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

int get_dist(vector<int> dist, int s, int size) {
  int max = dist[1];
  for (int i = 2; i < size; i++) {
      if (i == s) 
          continue;
      if (dist[i] == -1)
          return -1;
      else if (dist[i] > max) 
          max = dist[i];
  }
  return max;
}

// (int) line_graph.size() = size
// s origin node
int bfs(vector<set<int>>& line_graph, int size, int s) {  
    queue<int> q;  
    vector<bool> visited(size, false);
    vector<int> dist(size, -1);
    
    visited[s] = true;
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        for (int neighbour : line_graph[node]) {
            if (!visited[neighbour]) {
                visited[neighbour] = true;
                dist[neighbour] = dist[node] + 1;
                q.push(neighbour);
            }
        }
    }

    int max_dist = get_dist(dist, s, size);
    return max_dist;
}

int main() {
    // n estacoes, m arcos, l linhas
    int n, m, l;
    scanf("%d%d%d", &n, &m, &l);

    // stations array (with lines) - indexes are stations and contents are lines
    // each index is a station, contains the lines that go through that station
    vector<set<int>> stations_lines(n+1);
    vector<set<int>> lines(l+1);

    // O(m(log(ln))) - para construir o grafo inicial em que cada indice é uma estação e os valores são as linhas que passam por essa estação
    for (int i = 0; i < m; i++) { // O(m)
        int x, y, line;
        scanf("%d%d%d", &x, &y, &line);
        stations_lines[x].insert(line); // O(log(l))
        stations_lines[y].insert(line);
        lines[line].insert(x); // O(log(n))
        lines[line].insert(y);
    }

    // O(n) - verificar se há uma estação desconectada, ou seja, não tem linhas
    for (int i = 1; i < n+1; i++) {
        if (stations_lines[i].size() == 0) {
            cout << -1 << '\n';
            return 0;
        }
    }
    
    // O(l) - verificar se há uma linha que contém todas as estações
    for (set<int> stations : lines){
      if ((int) stations.size() == n) {
        cout << 0 << '\n';
        return 0;
      }
    }

    // {2, 3}, {1}, {1} - (connections to other lines)
    //  1       2    3  - indexes (lines)

    // O(nl**2log(l))
    vector<set<int>> line_graph;
    line_graph.resize(l+1);
    for (const set<int>& v : stations_lines) { // O(n) 
        auto it = v.begin();

        while (it != v.end()) { // O(l)
            int first_element = *it;
            auto it_copy = it;
            ++it_copy; // Move the copy iterator to the next element

            while (it_copy != v.end()) { // O(l)
                int second_element = *it_copy;
                line_graph[first_element].insert(second_element); // O(log(l))
                line_graph[second_element].insert(first_element);
                ++it_copy; // Move the inner iterator forward
            }
            ++it; // Move the outer iterator forward
        }
    }

    // O(l**3)
    int answer = -1;
    for (int vertex = 1; vertex < l+1; vertex++) {
        int dist = bfs(line_graph, l+1, vertex);
        answer = max(answer, dist);
    }

    cout << answer << '\n';
    return 0;
}