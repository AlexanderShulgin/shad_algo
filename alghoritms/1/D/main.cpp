#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>
struct Pair {
  double x;
  double y;
};

struct Interval {
  double x;
  bool open;
};

bool GoodRadius(double r, const std::vector<Pair> &t, int k) {
  std::vector<Interval> intervals;
  for (const Pair &dot : t) {
    if (fabs(dot.y) < r) {
      intervals.push_back({dot.x - sqrt(r * r - dot.y * dot.y), true});
      intervals.push_back({dot.x + sqrt(r * r - dot.y * dot.y), false});
    }
  }
  if (intervals.empty()) {
    return false;
  }

  std::sort(intervals.begin(), intervals.end(),
            [](Interval a, Interval b) { return a.x <= b.x; });
  int count = 0;
  std::vector<int> counts;
  counts.push_back(0);
  for (Interval &i : intervals) {
    if (i.open) {
      ++count;
    } else {
      --count;
    }
    counts.push_back(count);
  }

  return (*std::max_element(counts.begin(), counts.end())) >= k;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  std::vector<Pair> dots;
  dots.reserve(n);
  for (int i = 0; i < n; ++i) {
    double x, y;
    std::cin >> x >> y;
    dots.push_back({x, y});
  }
  double r_max = 1500;
  double r_min = 0;
  while (r_max - r_min > 0.001) {
    double middle = r_min + (r_max - r_min) / 2;
    if (GoodRadius(middle, dots, k)) {
      r_max = middle;
    } else {
      r_min = middle;
    }
  }
  std::cout << std::fixed;
  std::cout << std::setprecision(6) << r_max;

  return 0;
}