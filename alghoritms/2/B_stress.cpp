#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

struct Best {
    int64_t sum;
    int lp;
    int rp;
};

void PrintVector(std::vector<int> vec) {
    for (int elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

void Print(const Best& best, std::vector<int>& indexes) {
    std::sort(indexes.begin() + best.lp, indexes.begin() + best.rp + 1);
    std::cout << best.sum << "\n";
    for (int ind = best.lp; ind <= best.rp; ++ind) {
        std::cout << indexes[ind] + 1 << " ";
    }
}

void UpdateBest(Best& best, const int& lp, const int& rp,
                const int64_t& curr_sum) {
    if (curr_sum > best.sum) {
        best.sum = curr_sum;
        best.lp = lp;
        best.rp = rp;
    };
}

int64_t Answer(int number, std::vector<int>& eff) {
    if (number == 1) {
        // std::cout << eff[0] << "\n";
        // std::cout << 1;
        return eff[0];
    }

    std::vector<int> indexes(number, 0);
    std::iota(indexes.begin(), indexes.end(), 0);

    std::sort(indexes.begin(), indexes.end(), [&eff](int& first, int& second) {
        return eff[first] > eff[second];
    });

    int lp = 0;
    int rp = 1;
    Best best{eff[indexes[lp]] + eff[indexes[rp]], 0, 1};
    int64_t curr_sum = best.sum;

    while (rp < number - 1) {
        while (eff[indexes[lp]] <= (eff[indexes[rp]] + eff[indexes[rp + 1]])) {
            ++rp;
            curr_sum += eff[indexes[rp]];
            if (rp == (number - 1)) {
                UpdateBest(best, lp, rp, curr_sum);
                // Print(best, indexes);
                return best.sum;
                // return 0;
            }
        }
        UpdateBest(best, lp, rp, curr_sum);
        while ((eff[indexes[lp]] > (eff[indexes[rp]] + eff[indexes[rp + 1]]))) {
            curr_sum -= eff[indexes[lp]];
            ++lp;
            if (lp == rp) {
                ++rp;
                curr_sum += eff[indexes[rp]];
                break;
            }
        }
    }
    UpdateBest(best, lp, rp, curr_sum);
    // Print(best, indexes);
    return best.sum;
}

bool CheckSpl(size_t l, size_t r, std::vector<int>& eff) {  // NOLINT
    if (l == (r - 1)) {
        return true;
    }
    return eff[r] <= (eff[l] + eff[l + 1]);
}

int64_t AnswerStupid(std::vector<int> eff) {
    int64_t max = 0;
    std::sort(eff.begin(), eff.end());
    for (size_t i = 0; i + 1 < eff.size(); i++) {
        for (size_t j = i + 1; j < eff.size(); j++) {
            if (CheckSpl(i, j, eff)) {
                int64_t sum =
                    std::accumulate(eff.begin() + i, eff.begin() + j + 1, 0);
                if (sum > max) {
                    max = sum;
                }
            }
        }
    }
    return max;
}

std::vector<int> GenRandomArray(std::mt19937* gen, size_t count, int from,
                                int to) {
    std::uniform_int_distribution<int> dist(from, to);
    std::vector<int> data(count);
    for (int& cur : data) {
        cur = dist(*gen);
    }
    return data;
}

void StressTest() {
    std::mt19937 generator(72874);  // NOLINT
    const int kMaxValue = 100000;
    const int kMaxSize = 1000;
    for (int iter = 1; iter <= 100000; ++iter) {  // NOLINT
        std::cerr << "Test " << iter << "... ";
        auto data = GenRandomArray(&generator, kMaxSize, 1, kMaxValue);
        auto ok_answer = AnswerStupid(data);
        auto my_answer = Answer(kMaxSize, data);
        if (ok_answer == my_answer) {
            std::cerr << "OK\n";
        } else {
            std::cerr << "Fail\n";
            for (auto cur : data) {
                std::cerr << cur << " ";
            }
            std::cerr << "\n";
            std::cerr << "Ok ans " << ok_answer << ", my ans " << my_answer
                      << "\n";
            break;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    StressTest();
}