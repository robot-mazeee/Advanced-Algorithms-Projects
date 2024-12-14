#include <iostream>
using namespace std;

/*
visited = []
queue = []

def bfs(visited, graph, node): #function for BFS
  visited.append(node)
  queue.append(node)
  distance = []

  while queue != empty:          # Creating loop to visit each node
    m = queue.pop(0) 

    for neighbour in graph[m]:
      if neighbour not in visited:
        visited.append(neighbour)
        queue.append(neighbour)
        distance[neighbour] = distance[parent]+1
*/

int main() {
    // n estacoes, m arcos, l linhas
    int n, m, l;
    scanf("%d%d%d", &n, &m, &l);

    

    return 0;
}