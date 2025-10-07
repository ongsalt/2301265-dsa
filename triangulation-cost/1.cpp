#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <print>
#include <span>
#include <vector>

class PolygonCostCache {
 private:
  std::vector<double_t> cache;
  uint64_t vertexCount;

 public:
  PolygonCostCache(uint64_t vertexCount)
      : cache(vertexCount * vertexCount, -1.0), vertexCount(vertexCount) {
  }

  auto get(uint64_t start, uint64_t end) {
    return cache[start * vertexCount + end];
  }

  auto set(uint64_t start, uint64_t end, double_t value) {
    cache[start * vertexCount + end] = value;
  }
};

struct Point {
  int64_t x;
  int64_t y;
};

struct TriangleVertexesIndex {
  uint64_t a;
  uint64_t b;
  uint64_t c;
};

struct PolygonVertexesIndex {
  uint64_t start;
  uint64_t end;
};

auto findDistance(Point p1, Point p2) -> double_t {
  double_t dx = static_cast<double_t>(p1.x - p2.x);
  double_t dy = static_cast<double_t>(p1.y - p2.y);
  return std::sqrt(dx * dx + dy * dy);
}

auto getPerimeter(Point p1, Point p2, Point p3) {
  return findDistance(p1, p2) + findDistance(p1, p3) + findDistance(p2, p3);
}

// well we can just pipe it in
// std::vector<Point> parse(const std::string path) {}

auto getInput() -> std::vector<Point> {
  uint64_t n;
  std::cin >> n;

  // Assumption: points order = outline
  // wait, THIS MUST BE TRUE
  std::vector<Point> points;
  points.reserve(n);
  for (uint64_t i = 0; i < n; i++) {
    int64_t x, y;
    std::cin >> x >> y;
    points.push_back(Point{ x, y });
  }

  return points;
}

// gfg:
// > Time Complexity: O(2n)
// ok mf, this is just brute force with extra step
auto getMinimumTriangulationCost(
  std::span<const Point> points,
  uint64_t start,
  uint64_t end,
  PolygonCostCache& cache,
  uint64_t indentation = 0
) -> double_t {
  if (end - start < 2) {
    return 0.0;
  }

  auto cached = cache.get(start, end);
  if (cached != -1) {
    // std::println("{}cache hit: ({}, {}) = {}",
    //              std::string(indentation * 2, ' '), start, end, cached);
    return cached;
  }

  auto minimumCost = std::numeric_limits<double_t>::max();
  for (uint64_t i = start + 1; i < end; i++) {
    auto triangulationCost =
      getPerimeter(points[start], points[i], points[end]);
    // std::println("{}perimeter({}, {}, {}) = {}",
    //              std::string(indentation * 2, ' '), start, i, end,
    //              triangulationCost);

    minimumCost = std::min(
      minimumCost,
      triangulationCost +
        getMinimumTriangulationCost(points, start, i, cache, indentation + 1) +
        getMinimumTriangulationCost(points, i, end, cache, indentation + 1)
    );
  }

  cache.set(start, end, minimumCost);
  // std::println("{}getMinimumTriangulationCost({}, {}) = {}",
  // std::string(indentation * 2, ' '),
  //              start, end, minimumCost);

  return minimumCost;
}

int main() {
  auto points = getInput();
  if (points.size() < 3) {
    std::print("no");
  }

  auto span = std::span(points);

  // auto triangleCache = std::map<TriangleVertexesIndex, double_t>();
  auto cache = PolygonCostCache(points.size());

  auto cost = getMinimumTriangulationCost(span, 0, points.size() - 1, cache);

  std::println("{}", cost);

  return 0;
}