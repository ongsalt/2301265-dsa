#include <algorithm>
#include <iostream>
#include <ostream>
#include <stack>
#include <string>
#include <vector>

const int NO_PATH = 1e9;
const int NO_SOUND = -1e9;

struct Params {
  std::vector<std::vector<int>> graph;
  std::vector<std::pair<int, int>> queries;
};

Params getAndParseInput() {
  int vertexCount, edgeCount, queryCount;

  std::cin >> vertexCount >> edgeCount >> queryCount;
  auto queries = std::vector<std::pair<int, int>>(queryCount);
  auto graph = std::vector<std::vector<int>>(
    vertexCount,
    std::vector<int>(vertexCount, NO_PATH)
  );

  for (int v = 0; v < edgeCount; v++) {
    int i, j, cost;

    std::cin >> i >> j >> cost;
    i -= 1;
    j -= 1;
    // No bound check becuase fuck you

    graph[i][j] = cost;
    graph[j][i] = cost;
  }

  for (int q = 0; q < queryCount; q++) {
    int i, j;

    std::cin >> i >> j;
    i -= 1;
    j -= 1;

    queries[q] = std::make_pair(i, j);
  }

  return { .graph = graph, .queries = queries };
}

std::vector<std::vector<int>> findMinimumLoudness(
  const std::vector<std::vector<int>>& graph
) {
  // clone
  auto minimumLoudness = std::vector<std::vector<int>>(graph);
  auto vertexCount = graph.size();

  for (int v = 0; v < vertexCount; v++) {
    minimumLoudness[v][v] = NO_SOUND;
  }

  for (int k = 0; k < vertexCount; k++) {
    for (int i = 0; i < vertexCount; i++) {
      for (int j = 0; j < vertexCount; j++) {
        auto former_half = minimumLoudness[i][k];
        auto latter_half = minimumLoudness[k][j];
        auto l = NO_PATH;
        if (former_half != NO_PATH && latter_half != NO_PATH) {
          l = std::max(former_half, latter_half);
        }

        if (minimumLoudness[i][j] > l) {
          minimumLoudness[i][j] = l;
        }
      }
    }
  }

  return minimumLoudness;
}

void printGraph(std::vector<std::vector<int>>& graph) {
  for (auto r : graph) {
    for (auto c : r) {
      if (c == NO_PATH || c == NO_SOUND) {
        std::cout << "_\t";
      } else {
        std::cout << c << '\t';
      }
    }
    std::cout << std::endl;
  }
}

std::vector<int> findPath(
  std::vector<std::vector<int>>& graph,
  int start,
  int end,
  int maxLoudness
) {
  if (maxLoudness == NO_PATH) {
    return {};
  }

  int n = graph.size();
  std::vector<int> parent(n, -1);
  std::vector<bool> visited(n, false);
  std::stack<int> stack;

  stack.push(start);
  visited[start] = true;

  while (!stack.empty()) {
    int current = stack.top();
    stack.pop();

    if (current == end) {
      std::vector<int> path;
      int node = end;
      while (node != -1) {
        path.push_back(node);
        node = parent[node];
      }
      std::reverse(path.begin(), path.end());
      return path;
    }

    for (int neighbor = 0; neighbor < n; neighbor++) {
      if (!visited[neighbor] && 
          graph[current][neighbor] != NO_PATH && 
          graph[current][neighbor] <= maxLoudness) {
        visited[neighbor] = true;
        parent[neighbor] = current;
        stack.push(neighbor);
      }
    }
  }

  return {};
}

int main() {
  auto params = getAndParseInput();
  auto minimumLoudness = findMinimumLoudness(params.graph);

  // printGraph(params.graph);
  // std::cout << std::endl;
  // printGraph(minimumLoudness);

  for (auto [i, j] : params.queries) {
    auto loudness = minimumLoudness[i][j];
    std::cout << i + 1 << " -> " << j + 1 << " : ";
    std::cout << (loudness == NO_PATH ? "no path" : std::to_string(loudness))
              << std::endl;

    auto path = findPath(params.graph, i, j, loudness);

    std::cout << "   ";
    int index = 0;
    for (auto node : path) {
      index += 1;
      std::cout << node + 1;
      if (index < path.size()) {
        std::cout << " -> ";
      }
    }

    std::cout << std::endl;
  }

  return 0;
}