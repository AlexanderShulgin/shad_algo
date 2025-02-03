#include <algorithm>
#include <iostream>
#include <vector>

const int64_t kModulo = 123456789;

int64_t CountDifferentTrees(std::vector<int>& keys, short begin, short end,
                            std::vector<std::vector<int64_t>>& cache) {
    if (begin == end || begin + 1 == end) {
        return 1;
    }
    if (cache[begin][end] != -1) {
        return cache[begin][end];
    }
    int64_t counter = 0;
    counter += CountDifferentTrees(keys, begin + 1, end, cache);
    counter %= kModulo;
    for (int root_index = begin + 1; root_index < end; ++root_index) {
        if (keys[root_index] == keys[root_index - 1]) {
            continue;
        }
        counter += (CountDifferentTrees(keys, begin, root_index, cache) *
                    CountDifferentTrees(keys, root_index + 1, end, cache)) %
                   kModulo;
        ;
        counter %= kModulo;
    }
    cache[begin][end] = counter;
    return counter;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    short number_of_vertices;
    std::cin >> number_of_vertices;

    std::vector<int> keys;
    keys.reserve(number_of_vertices);
    for (int index = 0; index < number_of_vertices; ++index) {
        int elem;
        std::cin >> elem;
        keys.push_back(elem);
    }

    std::sort(keys.begin(), keys.end());

    std::vector<std::vector<int64_t>> cache(
        number_of_vertices + 1,
        std::vector<int64_t>(number_of_vertices + 1, -1));

    std::cout << CountDifferentTrees(keys, 0, number_of_vertices, cache);
    return 0;
}