#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

struct Best {
    int64_t sum;
    int lp;
    int rp;
};

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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int number;
    std::cin >> number;

    std::vector<int64_t> eff(number, 0);

    for (int64_t& elem : eff) {
        std::cin >> elem;
    }

    if (number == 1) {
        std::cout << eff[0] << "\n";
        std::cout << 1;
        return 0;
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
                Print(best, indexes);
                return 0;
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
    Print(best, indexes);
    return 0;
}