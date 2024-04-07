#include <algorithm>
#include <iostream>
#include <limits.h>
#include <string>
#include <vector>

const int inf = INT_MAX;
class newCity {

private:
  int N;
  std::vector<std::vector<int>> graph;

public:
  newCity(int n) : N(n) {
    graph.assign(N, std::vector<int>(N, inf));
    for (int i = 0; i < N; ++i)
      graph[i][i] = 0;
  }
  void streets(int from, int to, int time) {
    graph[from][to] = graph[to][from] = time;
  }

  void floydWarshall(std::vector<std::vector<int>> &dist) {
    int size_ = graph.size();
    dist = graph;
    for (int k = 0; k < size_; ++k) {
      for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
          if (dist[i][k] != inf && dist[k][j] != inf &&
              dist[i][k] + dist[k][j] < dist[i][j]) {
            dist[i][j] = dist[i][k] + dist[k][j];
          }
        }
      }
    }
  }
  int getShortestPath(int from, int to) { return graph[from][to]; }
  int visibilityZone() const { return N; }

void dijkstra(int start, std::vector<int> &distance, std::vector<int> &predecessor) {
    std::vector<bool> visited(N, false);
    distance.assign(N, inf);
    predecessor.assign(N, -1);
    distance[start] = 0;

    for (int i = 0; i < N - 1; ++i) {
        int u = -1;
        for (int j = 0; j < N; ++j) {
            if (!visited[j] && (u == -1 || distance[j] < distance[u]))
                u = j;
        }

        visited[u] = true;
        for (int v = 0; v < N; ++v) {
            if (graph[u][v] != inf && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
                predecessor[v] = u;
            }
        }
    }
}

  std::vector<int> reconstructPath(int from, int to,
                                   std::vector<int> predecessor) {
    std::vector<int> path;
    for (int i = to; i != -1; i = predecessor[i]) {
      path.push_back(i);
    }
    std::reverse(path.begin(), path.end());
    return path;
  }
};
int main() {
  int n, m;
  std::cin >> n >> m;
  newCity city(n);
  std::vector<std::vector<int>> graph(n, std::vector<int>(n, inf));
  for (int i = 0; i < m; ++i) {
    int from, to, time;
    std::cin >> from >> to >> time;
    int a = 0, b = 0;
    if (a > from && b > to) {
      std::cout << "NO";
    }
    city.streets(from, to, time);
  }
  std::vector<std::vector<int>> matrix;
  city.floydWarshall(matrix);
  int busID = 0;
  while (true) {
    std::string operation;
    std::cin >> operation;
    if (operation == "add_bus") {
      int a, b;
      std::cin >> a >> b;
      if (a < 0 || a >= city.visibilityZone() || b < 0 ||
          b >= city.visibilityZone()) {
        std::cout << "There are no such crossroads";
        continue;
      }
      if (matrix[a][b] == inf) {
        std::cout << "inf";
      } else {
        std::cout << matrix[a][b];
      }
      busID++;
    } else if (operation == "construct_street") {
      int from, to, time;
      std::cin >> from >> to >> time;
      if (from < 0 || from >= city.visibilityZone() || to < 0 ||
          to >= city.visibilityZone()) {
        std::cout << "There are no such crossroads";
        continue;
      }
      city.streets(from, to, time);
      city.floydWarshall(matrix);

    } else if (operation == "detail") {
      int from, to;
      std::cin >> from >> to;

      std::vector<int> dist, predecessor;
      std::vector<bool> visited;
      city.dijkstra(from, dist, predecessor);
      std::vector<int> path = city.reconstructPath(from, to, predecessor);

      for (int v : path) {
        std::cout << v << " ";
      }
      std::cout << std::endl;
    }

    else if (operation == "end") {
      break;
    }
  }
  return 0;
}