#include <iostream>
#include <vector>

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

void MergeSort(std::vector<unsigned int>& array, int from, int to,
               std::vector<unsigned int>& scratch) {
    if (from == to) {
        return;
    }
    int pivot = (from + to) / 2;
    MergeSort(array, from, pivot, scratch);
    MergeSort(array, pivot + 1, to, scratch);

    int l_size = pivot - from + 1;
    for (int index = 0; index < l_size; ++index) {
        scratch[index] = array[from + index];
    }
    int lp = 0;
    int rp = pivot + 1;
    int lp_end = l_size;
    int rp_end = to + 1;
    while ((lp < lp_end) && (rp < rp_end)) {
        if (scratch[lp] <= array[rp]) {
            array[lp + rp - l_size] = scratch[lp];
            ++lp;
        } else {
            array[lp + rp - l_size] = array[rp];
            ++rp;
        }
    }
    if (lp == lp_end) {
        while (rp < rp_end) {
            array[lp + rp - l_size] = array[rp];
            ++rp;
        }
    } else {
        while (lp < lp_end) {
            array[lp + rp - l_size] = scratch[lp];
            ++lp;
        }
    }
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
    std::vector<unsigned> houses;
    houses.reserve(number_of_houses);
    for (int ii = 0; ii < number_of_houses; ++ii) {
        houses.push_back(NextRand32(cur, a_seed, b_seed));
    }
    std::vector<unsigned int> scratch(number_of_houses / 2 + 1);

    MergeSort(houses, 0, number_of_houses - 1, scratch);
    int median_index = (number_of_houses + 1) / 2;
    unsigned int median_value = houses[median_index];
    int64_t sum = 0;

    for (int index = 0; index < median_index; ++index) {
        sum += (median_value - houses[index]);
    }
    for (int index = median_index; index < number_of_houses; ++index) {
        sum += (houses[index] - median_value);
    }
    std::cout << sum;
    return 0;
}