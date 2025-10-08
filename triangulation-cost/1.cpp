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
  std::vector<double> cache;
  uint64_t vertexCount;

 public:
  PolygonCostCache(uint64_t vertexCount)
      : cache(vertexCount * vertexCount, -1.0), vertexCount(vertexCount) {
  }

  auto get(uint64_t start, uint64_t end) {
    return cache[start * vertexCount + end];
  }

  auto set(uint64_t start, uint64_t end, double value) {
    cache[start * vertexCount + end] = value;
  }
};

struct Point {
  double x;
  double y;
};

auto findDistance(Point p1, Point p2) -> double {
  double dx = static_cast<double>(p1.x - p2.x);
  double dy = static_cast<double>(p1.y - p2.y);
  return std::sqrt(dx * dx + dy * dy);
}

auto getPerimeter(Point p1, Point p2, Point p3) {
  return findDistance(p1, p2) + findDistance(p1, p3) + findDistance(p2, p3);
}

// well we can just pipe it in instead
// std::vector<Point> parse(const std::string path) {}

auto getInput() -> std::vector<Point> {
  uint64_t n;
  std::cin >> n;

  // Assumption: points order = outline
  // wait, THIS MUST BE TRUE
  std::vector<Point> points;
  points.reserve(n);
  for (uint64_t i = 0; i < n; i++) {
    double x, y;
    std::cin >> x >> y;
    points.push_back(Point{ x, y });
  }

  return points;
}

// gfg:
// > Time Complexity: O(2n)
// ok mf, this is just brute force with extra step
auto getTriangulationCost(
  std::span<const Point> points,
  uint64_t start,
  uint64_t end,
  PolygonCostCache& cache,
  uint64_t indentation = 0,
  bool findMax = false
) -> double {
  if (end - start < 2) {
    return 0.0;
  }

  auto cached = cache.get(start, end);
  if (cached != -1) {
    // std::println(
    //   "{}cache hit: ({}, {}) = {}",
    //   std::string(indentation * 2, ' '),
    //   start,
    //   end,
    //   cached
    // );
    return cached;
  }

  auto cost = findMax ? std::numeric_limits<double>::min()
                      : std::numeric_limits<double>::max();
  for (uint64_t i = start + 1; i < end; i++) {
    auto triangulationCost =
      getPerimeter(points[start], points[i], points[end]);
    // std::println(
    //   "{}perimeter({}, {}, {}) = {}",
    //   std::string(indentation * 2, ' '),
    //   start,
    //   i,
    //   end,
    //   triangulationCost
    // );
    auto newCost =
      triangulationCost +
      getTriangulationCost(points, start, i, cache, indentation + 1, findMax) +
      getTriangulationCost(points, i, end, cache, indentation + 1, findMax);

    if (findMax) {
      cost = std::max(cost, newCost);
    } else {
      cost = std::min(cost, newCost);
    }
  }

  cache.set(start, end, cost);
  // std::println(
  //   "{}getTriangulationCost({}, {}) = {}",
  //   std::string(indentation * 2, ' '),
  //   start,
  //   end,
  //   cost
  // );

  return cost;
}

auto sortPoints(std::span<const Point> points) {
  Point center = { 0, 0 };

  for (auto point : points) {
    center.x += point.x;
    center.y += point.y;
  }

  center.x /= points.size();
  center.y /= points.size();

  auto newPoints = std::vector(points.begin(), points.end());
  std::ranges::sort(newPoints, [&](auto a, auto b) {
    double angle_a = std::atan2(a.y - center.y, a.x - center.x);
    double angle_b = std::atan2(b.y - center.y, b.x - center.x);
    return angle_a < angle_b;
  });

  return newPoints;
}

int main() {
  auto points = getInput();
  auto sortedPoints = sortPoints(points);
  if (points.size() < 3) {
    std::print("no");
  }

  // auto triangleCache = std::map<TriangleVertexesIndex, double>();
  auto minCache = PolygonCostCache(points.size());
  auto maxCache = PolygonCostCache(points.size());

  auto minCost =
    getTriangulationCost(sortedPoints, 0, points.size() - 1, minCache);
  auto maxCost =
    getTriangulationCost(sortedPoints, 0, points.size() - 1, maxCache, 0, true);

  std::println("{} {}", minCost, maxCost);

  return 0;
}