#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <print>
#include <span>
#include <string>
#include <vector>

typedef int64_t i64;
typedef uint64_t u64;
typedef double_t f64;

class PolygonCostCache {
private:
  std::vector<f64> cache;
  u64 vertexCount;

public:
  PolygonCostCache(u64 vertexCount)
      : cache(vertexCount * vertexCount, -1.0), vertexCount(vertexCount) {}

  auto get(u64 start, u64 end) { return cache[start * vertexCount + end]; }

  auto set(u64 start, u64 end, f64 value) {
    cache[start * vertexCount + end] = value;
  }
};

struct Point {
  i64 x;
  i64 y;
};

struct TriangleVertexesIndex {
  u64 a;
  u64 b;
  u64 c;
};

struct PolygonVertexesIndex {
  u64 start;
  u64 end;
};

auto findDistance(Point p1, Point p2) -> f64 {
  f64 dx = static_cast<f64>(p1.x - p2.x);
  f64 dy = static_cast<f64>(p1.y - p2.y);
  return std::sqrt(dx * dx + dy * dy);
}

auto getPerimeter(Point p1, Point p2, Point p3) {
  return findDistance(p1, p2) + findDistance(p1, p3) + findDistance(p2, p3);
}

// well we can just pipe it in
// std::vector<Point> parse(const std::string path) {}

auto getInput() -> std::vector<Point> {
  u64 n;
  std::cin >> n;

  // Assumption: points order = outline
  // wait, THIS MUST BE TRUE
  std::vector<Point> points;
  points.reserve(n);
  for (u64 i = 0; i < n; i++) {
    i64 x, y;
    std::cin >> x >> y;
    points.push_back(Point{x, y});
  }

  return points;
}

// gfg:
// > Time Complexity: O(2n)
// ok mf, this is just brute force with extra step
auto getMinimumTriangulationCost(
    std::span<const Point> points, u64 start, u64 end,
    // std::map<TriangleVertexesIndex, f64> &triangleCache,
    PolygonCostCache &cache, u64 indentation = 0) -> f64 {

  if (end - start < 2) {
    return 0.0;
  }

  auto cached = cache.get(start, end);
  if (cached != -1) {
    // std::println("{}cache hit: ({}, {}) = {}",
    //              std::string(indentation * 2, ' '), start, end, cached);
    return cached;
  }

  auto minimumCost = std::numeric_limits<f64>::max();
  for (u64 i = start + 1; i < end; i++) {
    auto triangulationCost =
        getPerimeter(points[start], points[i], points[end]);
    // std::println("{}perimeter({}, {}, {}) = {}",
    //              std::string(indentation * 2, ' '), start, i, end,
    //              triangulationCost);

    minimumCost = std::min(
        minimumCost, triangulationCost +
                         getMinimumTriangulationCost(points, start, i, cache,
                                                     indentation + 1) +
                         getMinimumTriangulationCost(points, i, end, cache,
                                                     indentation + 1));
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
  // auto triangleCache = std::map<TriangleVertexesIndex, f64>();
  auto cache = PolygonCostCache(points.size());

  auto cost = getMinimumTriangulationCost(span, 0, points.size() - 1, cache);

  std::println("{}", cost);

  return 0;
}