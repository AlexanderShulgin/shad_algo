#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, m, l;
  std::cin >> n >> m >> l;

  std::vector<std::vector<int>> A(n, std::vector<int>(l));
  for (int i = 0; i < n; ++i) {
    for (int k = 0; k < l; ++k) {
      std::cin >> A[i][k];
    }
  }

  std::vector<std::vector<int>> B(m, std::vector<int>(l));
  for (int i = 0; i < m; ++i) {
    for (int k = 0; k < l; ++k) {
      std::cin >> B[i][k];
    }
  }
  int q;
  std::cin >> q;

  int i, j;
  while (q > 0) {
    std::cin >> i >> j;

    if (A[i - 1][0] >= B[j - 1][0]) {
      std::cout << 1 << "\n";
    } else if (B[j - 1][l - 1] >= A[i - 1][l - 1]) {
      std::cout << l << "\n";
    } else {
      int left = 0;
      int right = l - 1;
      while (left != right) {
        int middle = left + (right - left) / 2;
        if (A[i - 1][middle] == B[j - 1][middle]) {
          std::cout << middle + 1 << "\n";
          break;
        } else if (A[i - 1][middle] < B[j - 1][middle]) {
          left = middle;
        } else {
          right = middle;
        }
        if (left == right - 1) {
          if (B[j - 1][left] > A[i - 1][right]) {
            std::cout << right + 1 << "\n";
          } else {
            std::cout << left + 1 << "\n";
          }
          break;
        }
      }
    }
    --q;
  }

  return 0;
}