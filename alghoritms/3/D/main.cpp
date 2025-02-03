#include <algorithm>
#include <iostream>
#include <vector>

int CurrentSum(std::vector<int>& mask, int border) {
    int sum = 0;
    for (int index = border; index >= 0; index = ((index + 1) & index) - 1) {
        sum += mask[index];
    }
    return sum;
}

int DesiredIndex(int kth, int numbers_size, std::vector<int>& mask) {
    int lp = -1;
    int rp = numbers_size;
    while (rp > (lp + 1)) {
        int middle = (lp + rp) / 2;
        if (CurrentSum(mask, middle) < kth) {
            lp = middle;
        } else {
            rp = middle;
        }
    }
    return rp;
}

int IndexInSorted(std::vector<int>& sorted_numbers, int element) {
    return std::lower_bound(sorted_numbers.begin(), sorted_numbers.end(),
                            element) -
           sorted_numbers.begin();
}

void KThStatistics(std::vector<int>& numbers, std::vector<char>& shifts,
                   int k_th) {
    std::vector<int> sorted_numbers = numbers;
    std::sort(sorted_numbers.begin(), sorted_numbers.end());
    int numbers_size = numbers.size();
    std::vector<int> mask(numbers.size());
    int left = 0;
    int right = 0;
    if (shifts.empty()) {
        return;
    }

    for (int index = IndexInSorted(sorted_numbers, numbers.front());
         index < numbers_size; index = ((index + 1) | index)) {
        mask[index] += 1;
    }
    for (char& shift : shifts) {
        if (shift == 'R') {
            ++right;
            for (int index = IndexInSorted(sorted_numbers, numbers[right]);
                 index < numbers_size; index = ((index + 1) | index)) {
                mask[index] += 1;
            }
        } else {
            for (int index = IndexInSorted(sorted_numbers, numbers[left]);
                 index < numbers_size; index = ((index + 1) | index)) {
                mask[index] -= 1;
            }
            ++left;
        }
        int desired_index = DesiredIndex(k_th, numbers_size, mask);
        if (desired_index == numbers_size) {
            std::cout << -1 << '\n';
        } else {
            std::cout << sorted_numbers[desired_index] << '\n';
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int numbers_size;
    int shifts_size;
    int k_th;
    std::cin >> numbers_size >> shifts_size >> k_th;

    std::vector<int> numbers;
    numbers.reserve(numbers_size);
    for (int i = 0; i < numbers_size; ++i) {
        int elem;
        std::cin >> elem;
        numbers.push_back(elem);
    }

    std::vector<char> shifts;
    shifts.reserve(shifts_size);
    for (int i = 0; i < shifts_size; ++i) {
        char shift;
        std::cin >> shift;
        shifts.push_back(shift);
    }

    KThStatistics(numbers, shifts, k_th);
    return 0;
}