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

    int number_of_houses = 10;

    /*std::vector<unsigned int> houses;
    houses.reserve(number_of_houses);
    for (int ii = 0; ii < number_of_houses; ++ii) {
        unsigned int elem;
        std::cin >> elem;
        houses.push_back(elem);
    }*/
    std::vector<unsigned int> houses {10, 3, 4, 6, 1, 9, 8, 6 ,10, 5};

    int64_t sum = 0;
    int64_t median_value = QuickSelect(houses, 0, number_of_houses - 1,
                                            (number_of_houses + 1) / 2);
    std::cout << "Median is equal to:" << median_value << "\n";
    for (int index = 0; index < number_of_houses; ++index) {
        sum += std::abs(median_value - static_cast<int64_t>(houses[index]));
    }
    std::cout << sum;
    return 0;
}