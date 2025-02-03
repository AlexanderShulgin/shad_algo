#include <algorithm>
#include <iostream>
#include <vector>

void InOrder(std::vector<int>& keys, int begin, int end) {
    if (begin == end) {
        return;
    }
    if (begin + 1 == end) {
        std::cout << keys[begin] << " ";
        return;
    }
    int border = std::lower_bound(keys.begin() + begin + 1, keys.begin() + end,
                                  keys[begin]) -
                 keys.begin();
    InOrder(keys, begin + 1, border);
    std::cout << keys[begin] << " ";
    InOrder(keys, border, end);
}

void PostOrder(std::vector<int>& keys, int begin, int end) {
    if (begin == end) {
        return;
    }
    if (begin + 1 == end) {
        std::cout << keys[begin] << " ";
        return;
    }
    int border = std::lower_bound(keys.begin() + begin + 1, keys.begin() + end,
                                  keys[begin]) -
                 keys.begin();
    PostOrder(keys, begin + 1, border);
    PostOrder(keys, border, end);
    std::cout << keys[begin] << " ";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_vertices;
    std::cin >> number_of_vertices;

    std::vector<int> keys_preorder;
    keys_preorder.reserve(number_of_vertices);
    int key;
    for (int index = 0; index < number_of_vertices; ++index) {
        std::cin >> key;
        keys_preorder.push_back(key);
    }

    PostOrder(keys_preorder, 0, static_cast<int>(keys_preorder.size()));
    std::cout << "\n";
    InOrder(keys_preorder, 0, static_cast<int>(keys_preorder.size()));

    return 0;
}