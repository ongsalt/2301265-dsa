#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define fn auto
#define let auto const
#define var auto

template <class T>
using Vec = std::vector<T>;
using String = std::string;

fn get_undirected_graph() -> Vec<Vec<uint64_t>> {
  var graph = Vec<Vec<uint64_t>>();

  size_t node_count, edge_count;
  std::cin >> node_count >> edge_count;

  graph.resize(node_count, Vec<uint64_t>(node_count, -1));

  // Read edges
  for (size_t i = 0; i < edge_count; ++i) {
    size_t u, v;
    uint64_t weight;
    std::cin >> u >> v >> weight;
    graph[u][v] = weight;
    graph[v][u] = weight;
  }

  return graph;
}

fn dijkstra(const Vec<Vec<uint64_t>>& graph, size_t starting) {
  var min_distance = Vec<uint64_t>(graph.size(), UINT64_MAX);
  var finalized = Vec<bool>(graph.size(), false);
  var to_search = std::
    priority_queue<size_t, Vec<size_t>, std::function<bool(size_t, size_t)>>(
      [&](auto first, auto second) {
        return min_distance[first] > min_distance[second];
      }
    );

  min_distance[starting] = 0;

  to_search.push(starting);
  while (!to_search.empty()) {
    let current = to_search.top();
    to_search.pop();

    for (var i = 0; i < graph.size(); i++) {
      let weight = graph[current][i];
      if (weight != -1 && !finalized[i]) {
        min_distance[i] =
          std::min(min_distance[i], weight + min_distance[current]);
        to_search.push(i);
      }
    }

    finalized[current] = true;
  }

  return min_distance;
}

int main(int argc, char* argv[]) {
  Vec<String> args(argv, argv + argc);

  let graph = get_undirected_graph();

  return 0;
}