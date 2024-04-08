#include "newCity.h"
#include <algorithm>
#include <iostream>
#include <limits.h>

const int inf = INT_MAX;

newCity::newCity(int n) : N(n) {
  graph.assign(N, std::vector<int>(N, inf));
  for (int i = 0; i < N; ++i)
    graph[i][i] = 0;
}

void newCity::streets(int from, int to, int time) {
  graph[from][to] = graph[to][from] = time;
}

void newCity::floydWarshall(std::vector<std::vector<int>> &dist) {
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

void newCity::function_for_a_new_street(std::vector<std::vector<int>> &distance,
                                  int from, int to, int time) {
  int size_ = graph.size();
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      distance[i][j] = std::min(
          distance[i][j], std::min(distance[i][from] + time + distance[to][j],
                                   distance[i][to] + time + distance[from][j]));
      distance[j][i] = distance[i][j];
    }
  }
}

int newCity::getShortestPath(int from, int to) { return graph[from][to]; }

int newCity::visibilityZone() const { return N; }

void newCity::dijkstra(int start, std::vector<int> &distance,
                       std::vector<int> &predecessor) {
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

std::vector<int> newCity::reconstructPath(int from, int to,
                                          std::vector<int> predecessor) {
  std::vector<int> path;
  for (int i = to; i != -1; i = predecessor[i]) {
    path.push_back(i);
  }
  std::reverse(path.begin(), path.end());
  return path;
}

void newCity::constructStreet() {
  int from, to, time;
  std::cin >> from >> to >> time;
  if (from < 0 || from >= visibilityZone() || to < 0 ||
      to >= visibilityZone()) {
    std::cout << "Такого пути не существует!";
    return;
  }

  streets(from, to, time);
  std::vector<std::vector<int>> distance = graph;
  function_for_a_new_street(distance, from, to, time);
}

void newCity::addBus() {
  int a, b;
  std::cin >> a >> b;
  if (a < 0 || a >= visibilityZone() || b < 0 || b >= visibilityZone()) {
    std::cout << "Такого пути не существует!";
    return;
  }
  std::vector<std::vector<int>> matrix;
  floydWarshall(matrix);
  if (matrix[a][b] == inf) {
    std::cout << "Наикратчайший путь от А до B: "
              << "inf";
  } else {
    std::cout << "Наикратчайший путь от А до B: " << matrix[a][b];
  }
}

void newCity::detail() {
  int from, to;
  std::cin >> from >> to;
  if (from < 0 || from >= visibilityZone() || to < 0 || to >= visibilityZone()) {
    std::cout << "Такого пути не существует!";
    return;
  }

  std::vector<int> dist, predecessor;
  std::vector<bool> visited;
  dijkstra(from, dist, predecessor);
  std::vector<int> path = reconstructPath(from, to, predecessor);
  std::cout << "Вершины по которым проходит автобус, проезжая по "
               "наикратчайшему пути: ";
  for (size_t i = 0; i < path.size(); ++i) {
    std::cout << path[i];
    if (i < path.size() - 1) {
      std::cout << "->";
    }
  }
}
