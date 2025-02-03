#include <chrono>

#include "fixed_set_optional_count.h"
using namespace std::chrono;

std::vector<int> GenRandomArray(std::mt19937* gen, size_t count, int from,
                                int to) {
    std::uniform_int_distribution<int> dist(from, to);
    std::vector<int> data(count);
    for (auto& cur : data) {
        cur = dist(*gen);
    }
    return data;
}

int main() {
    std::vector<int> numbers;
    numbers.reserve(100000);//NOLINT
    for(int i = -50000; i<50000; i++){ //NOLINT
        numbers.push_back(i);
    }
    auto start = high_resolution_clock::now();

    FixedSet set;
    set.Initialize(numbers);
    

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count()
              << " microseconds"
              << "\n";

    return 0;
}
