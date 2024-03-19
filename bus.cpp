#include <iostream>
#include <limits.h>
#include <queue>
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

  void floydWarshall() {
    int size_ = graph.size();
    for (int k = 0; k < size_; ++k) {
      for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
          if (graph[i][k] != inf && graph[k][j] != inf &&
              graph[i][k] + graph[k][j] < graph[i][j]) {
            graph[i][j] = graph[i][k] + graph[k][j];
          }
        }
      }
    }
  }
  int getShortestPath(int from, int to) { return graph[from][to]; }
  int visibilityZone() const {
    return N;
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
    if( a > from && b > to) {
      std::cout<< "NO";
    }
    city.streets(from, to, time);
  }
  city.floydWarshall();
  int busID = 0;
  while (true) {
    std::string operation;
    std::cin >> operation;
    if (operation == "add_bus") {
      int a, b;
      std::cin >> a >> b;
      if(a < 0 || a >= city.visibilityZone() || b < 0 || b >= city.visibilityZone()) {
        std::cout << "There are no such crossroads";
        continue;
      }
      if(city.getShortestPath(a, b) == inf) {
        std::cout << "inf";
      } else {
        std::cout << city.getShortestPath(a, b);
      }
      busID++;
    }
  }
  return 0;
}
