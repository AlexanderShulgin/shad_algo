#include "func.cpp"
#include <numeric>
#include <random>
int64_t RightAnswer(std::vector<int>& array, Bound bound) {
    int64_t count = 0;
    for(int i = 0; i < static_cast<int>(array.size());++i){
        for(int j=i;j < static_cast<int>(array.size());++j){
            int64_t sum = std::accumulate(array.begin()+i, array.begin()+j+1, 0);
            if((sum >= bound.l) && (sum <= bound.r)){
                ++count;
            }
        }
    }
    return count;
}

std::vector<int> GenRandomArray(std::mt19937* gen, size_t count, int from,
                                int to) {
    std::uniform_int_distribution<int> dist(from, to);
    std::vector<int> data(count);
    for (auto& cur : data) {
        cur = dist(*gen);
    }
    return data;
}


void StressTest() {
    std::mt19937 generator(72874);  // NOLINT
    for (int iter = 1; iter <= 1000; ++iter) {  //NOLINT
        std::cerr << "Test " << iter << "... ";
     
        std::vector<int> numbers1 = GenRandomArray(&generator, 100, -100, 100); // NOLINT
        std::vector<int> numbers2 = numbers1;
        auto right_answer = RightAnswer(numbers1, {-10, 10}); //NOLINT
        auto my_answer = MainFunc(numbers2, {-10, 10}); //NOLINT
        if (right_answer == my_answer) {
            std::cerr << "OK\n";
        } else {
            std::cerr << "Fail\n";
            std::cerr << "Data\n";
            for (auto cur : numbers1) {
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