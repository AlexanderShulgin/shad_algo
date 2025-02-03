#include <vector>
#include <cmath>
#include <iostream>


void PrintVector(std::vector<unsigned int> vec) {
    for (int elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

struct TwoPointers {
    int first_equal_pointer;
    int first_big_pointer;
};
void SortFiveElements(std::vector<unsigned int>& array, int from) {
    int to = from + 4;
    for (int lp = from; lp < to; ++lp) {
        for (int rp = lp + 1; rp <= to; ++rp) {
            if (array[rp] < array[lp]) {
                std::swap(array[rp], array[lp]);
            }
        }
    }
}

void SortReminderElements(std::vector<unsigned int>& array, int from, int to) {
    for (int lp = from; lp < to; ++lp) {
        for (int rp = lp + 1; rp <= to; ++rp) {
            if (array[rp] < array[lp]) {
                std::swap(array[rp], array[lp]);
            }
        }
    }
}

TwoPointers Partition(std::vector<unsigned int>& array, int from, int to,
                      unsigned int pivot) {
    int first_equal_pointer = from;
    int first_big_pointer = from;
    int current_pointer = from;
    while (current_pointer <= to) {
        if (array[current_pointer] > pivot) {
            ++current_pointer;
        } else if (array[current_pointer] == pivot) {
            std::swap(array[first_big_pointer], array[current_pointer]);
            ++first_big_pointer;
            ++current_pointer;
        } else {
            std::swap(array[first_big_pointer], array[current_pointer]);
            std::swap(array[first_big_pointer], array[first_equal_pointer]);
            ++first_equal_pointer;
            ++first_big_pointer;
            ++current_pointer;
        }
    }
    return {first_equal_pointer, first_big_pointer};
}


unsigned int QuickSelect(std::vector<unsigned int>& array, int from, int to,
                         int kth) {
    int array_size = to - from + 1;
    int five_number = array_size / 5;
    if (five_number == 0) {
        SortReminderElements(array, from, to);
        return array[from + kth - 1];
    }
    for (int current_five = 0; current_five < five_number; ++current_five) {
        SortFiveElements(array, from + 5 * current_five);
    }
    SortReminderElements(array, from + 5 * five_number, to);

    std::vector<unsigned int> subarray;
    for (int index = 2; index < array_size; index += 5) {
        subarray.push_back(array[from + index]);
    }
    int subarray_size = (array_size + 2) / 5;
    unsigned int median;
    if (subarray_size == 1) {
        median = subarray[0];
    } else {
        median = QuickSelect(subarray, 0, subarray_size - 1,
                             (subarray_size + 1) / 2);
    }
    TwoPointers tp = Partition(array, from, to, median);
    /*if(array_size == 10){
        PrintVector(array);
        std::cout<<"fe"<< tp.first_equal_pointer<<"\n";
        std::cout<<"fb"<< tp.first_big_pointer<<"\n";
        std::cout<<"inner median"<< median<<"\n";
    }*/
    if (kth <= tp.first_equal_pointer - from) {
        return QuickSelect(array, from, tp.first_equal_pointer - 1, kth);
    }
    if (kth <= tp.first_big_pointer - from) {
        return array[tp.first_equal_pointer];
    }
    return QuickSelect(array, tp.first_big_pointer, to,
                       kth - tp.first_big_pointer + from);
}