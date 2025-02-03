#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

struct FromToPivot {
    int from;
    int to;
    int pivot = 0;
};

struct Bound {
    int64_t l;
    int64_t r;
};

struct JLast {
    int l;
    int r;
};

void CountIntervals(std::vector<int64_t>& array, FromToPivot ftp,
                    int64_t& global, Bound bound) {
    JLast j_last{ftp.pivot + 1, ftp.pivot + 1};

    for (int i_pointer = ftp.from; i_pointer <= ftp.pivot; ++i_pointer) {
        int64_t geq_l = bound.l + array[i_pointer];
        int j_pointer = j_last.l;
        while (j_pointer <= ftp.to) {
            if (array[j_pointer] >= geq_l) {
                break;
            }
            ++j_pointer;
        }
        j_last.l = j_pointer;

        int64_t geq_r = bound.r + 1 + array[i_pointer];
        j_pointer = j_last.r;
        while (j_pointer <= ftp.to) {
            if (array[j_pointer] >= geq_r) {
                break;
            }
            ++j_pointer;
        }
        j_last.r = j_pointer;

        if (j_last.l > ftp.to) {
            return;
        }
        if (j_last.r > ftp.to) {
            global += (ftp.to - j_last.l + 1);
        } else {
            global += (j_last.r - j_last.l);
        }
    }
}

void MergeSort(std::vector<int64_t>& array, FromToPivot ftp,
               std::vector<int64_t>& scratch, int64_t& global, Bound bound) {
    if (ftp.from == ftp.to) {
        return;
    }
    ftp.pivot = (ftp.from + ftp.to) / 2;
    MergeSort(array, {ftp.from, ftp.pivot}, scratch, global, bound);
    MergeSort(array, {ftp.pivot + 1, ftp.to}, scratch, global, bound);

    CountIntervals(array, ftp, global, bound);

    int l_size = ftp.pivot - ftp.from + 1;
    for (int index = 0; index < l_size; ++index) {
        scratch[index] = array[ftp.from + index];
    }
    int lp = 0;
    int rp = ftp.pivot + 1;
    int lp_end = l_size;
    int rp_end = ftp.to + 1;
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

int64_t MainFunc(std::vector<int>& array, Bound bound) {
    if (array.size() == 1) {
        if ((array[0] <= bound.r) && (array[0] >= bound.l)) {
            return 1;
        }
        return 0;
    }
    std::vector<int64_t> prefix_array;
    prefix_array.reserve(array.size() + 1);
    prefix_array.push_back(0);
    for (int& elem : array) {
        prefix_array.push_back(prefix_array.back() + elem);
    }
    std::vector<int64_t> scratch(prefix_array.size(), 0);
    int64_t global = 0;

    MergeSort(prefix_array, {0, static_cast<int>(array.size())}, scratch,
              global, bound);
    return global;
}