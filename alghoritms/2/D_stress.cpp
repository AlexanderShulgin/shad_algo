#include <algorithm>
#include <random>
#include <error.h>
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


int64_t MyAnswer(int number_of_houses, std::vector<unsigned int>& houses) {
    if (number_of_houses == 1) {
        return 0;
    }
    int64_t sum = 0;
    int64_t median_value = QuickSelect(houses, 0, number_of_houses - 1,
                                            (number_of_houses + 1) / 2);
    for (int index = 0; index < number_of_houses; ++index) {
        sum += std::abs(median_value - static_cast<int64_t>(houses[index]));
    }
    return sum;
}

int64_t RightAnswer(int number_of_houses, std::vector<unsigned int>& houses) {
    int64_t sum = 0;
    int median_index = (number_of_houses - 1) / 2;
    std::sort(houses.begin(), houses.end());
    int64_t median_value = houses[median_index];

    for (auto& house : houses) {
        sum += std::abs( median_value - static_cast<int64_t>(house));
    }
    return sum;
}

std::vector<unsigned int> GenRandomArray(std::mt19937* gen, size_t count, int from,
                                int to) {
    std::uniform_int_distribution<int> dist(from, to);
    std::vector<unsigned int> data(count);
    for (auto& cur : data) {
        cur = dist(*gen);
    }
    return data;
}


void StressTest() {
    std::mt19937 generator(72874);  // NOLINT
    const int kMaxValue = 100000;
    for (int iter = 1; iter <= 100000; ++iter) {  
        std::cerr << "Test " << iter << "... ";
        /*auto seeds = GenRandomArray(&generator, 2, 1, kMaxValue);
        auto number = GenRandomArray(&generator, 1, 1, 10);

        int number_of_houses = number[0];
        auto a_seed = seeds[0];
        auto b_seed = seeds[1];
        unsigned int cur = 0;
        std::vector<unsigned int> houses;
        houses.reserve(number_of_houses);
        for (int ii = 0; ii < number_of_houses; ++ii) {
            houses.push_back(NextRand32(cur, a_seed, b_seed));
        }*/
        std::vector<unsigned int> houses = GenRandomArray(&generator, 100000, 1, kMaxValue);
        std::vector<unsigned int> houses1 = houses;
        std::vector<unsigned int> houses2 = houses;
        int number_of_houses = static_cast<int>(houses.size());
        auto right_answer = RightAnswer(number_of_houses, houses1);
        auto my_answer = MyAnswer(number_of_houses, houses2);
        if (right_answer == my_answer) {
            std::cerr << "OK\n";
        } else {
            std::cerr << "Fail\n";
            std::cerr << "Data\n";
            for (auto cur : houses) {
                std::cerr << cur << " ";
            }
            std::cerr << "\n";
            std::cerr << "Sorted data\n";
            for (auto cur : houses1) {
                std::cerr << cur << " ";
            }
            std::cerr << "\n";
            std::cerr << "Right ans " << right_answer << ", my ans "
                      << my_answer << "\n";
            break;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    StressTest();

    return 0;
}