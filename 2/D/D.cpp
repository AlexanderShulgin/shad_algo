#include <cstdint>
#include "D_func.cpp"

const int kPush = 8;
unsigned int NextRand24(unsigned int& cur, int a_seed, int b_seed) {
    cur = cur * a_seed + b_seed;
    return cur >> kPush;
}
unsigned int NextRand32(unsigned int& cur, int a_seed, int b_seed) {
    unsigned int aa = NextRand24(cur, a_seed, b_seed);
    unsigned int bb = NextRand24(cur, a_seed, b_seed);
    return (aa << kPush) ^ bb;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_houses;
    std::cin >> number_of_houses;
    if (number_of_houses == 1) {
        std::cout << 0;
        return 0;
    }
    int a_seed;
    int b_seed;
    std::cin >> a_seed >> b_seed;

    unsigned int cur = 0;
    std::vector<unsigned int> houses;
    houses.reserve(number_of_houses);
    for (int i = 0; i < number_of_houses; ++i) {
        houses.push_back(NextRand32(cur, a_seed, b_seed));
    }

    int64_t sum = 0;
    int64_t median_value = QuickSelect(houses, 0, number_of_houses - 1,
                                       (number_of_houses + 1) / 2);
    for (int index = 0; index < number_of_houses; ++index) {
        sum += std::abs(median_value - static_cast<int64_t>(houses[index]));
    }
    std::cout << sum;
    return 0;
}