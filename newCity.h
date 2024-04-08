#ifndef NEWCITY_H
#define NEWCITY_H
#include <iostream>
#include <string>
#include <vector>

class newCity {
private:
  int N;
  std::vector<std::vector<int>> graph;

public:
  newCity(int n);
  void streets(int from, int to, int time);
  void floydWarshall(std::vector<std::vector<int>> &dist);
  int getShortestPath(int from, int to);
  void function_for_a_new_street(std::vector<std::vector<int>> &distance, int from, int to, int time);
  int visibilityZone() const;
  void dijkstra(int start, std::vector<int> &distance,
                std::vector<int> &predecessor);
  std::vector<int> reconstructPath(int from, int to,
                                   std::vector<int> predecessor);

  void constructStreet();

  void addBus();

  void detail();
};

#endif // NEWCITY_H