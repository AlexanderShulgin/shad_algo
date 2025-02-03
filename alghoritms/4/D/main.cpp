#include <iomanip>
#include <iostream>
#include <vector>

double ComputeProbability(short number_of_vertices, short height,
                          std::vector<std::vector<double>>& cache);

double ComputeUnequalCase(short number_of_vertices, short height,
                          std::vector<std::vector<double>>& cache,
                          bool include_middle) {
    double probability = 0;
    short pivot = number_of_vertices / 2;
    if (!include_middle) {
        pivot -= 1;
    }
    for (short left_number = 0; left_number <= pivot; left_number++) {
        short right_number = number_of_vertices - left_number;
        double right_less_probability = 0;
        double left_less_probability = 0;
        for (short sub_height = 0; sub_height < height - 1; sub_height++) {
            right_less_probability +=
                ComputeProbability(right_number, sub_height, cache);
            left_less_probability +=
                ComputeProbability(left_number, sub_height, cache);
        }
        probability += ComputeProbability(left_number, height - 1, cache) *
                       right_less_probability;
        probability += ComputeProbability(right_number, height - 1, cache) *
                       left_less_probability;
        probability += ComputeProbability(left_number, height - 1, cache) *
                       ComputeProbability(right_number, height - 1, cache);
    }
    return probability;
}

double ComputeProbability(short number_of_vertices, short height,
                          std::vector<std::vector<double>>& cache) {
    double probability = 0;
    if (cache[number_of_vertices][height] != -1) {
        return cache[number_of_vertices][height];
    }
    if (number_of_vertices < height) {
        return 0;
    }
    number_of_vertices--;

    if (number_of_vertices % 2 == 1) {
        probability +=
            (ComputeUnequalCase(number_of_vertices, height, cache, true) * 2);
    } else {
        probability +=
            (ComputeUnequalCase(number_of_vertices, height, cache, false) * 2);

        short number = number_of_vertices / 2;
        double inner_probability = 0;
        for (short sub_height = 0; sub_height < height - 1; sub_height++) {
            inner_probability += ComputeProbability(number, sub_height, cache);
        }
        probability += ComputeProbability(number, height - 1, cache) *
                       inner_probability * 2;
        double equal_case = ComputeProbability(number, height - 1, cache);
        probability += (equal_case * equal_case);
    }

    probability /= (number_of_vertices + 1);
    cache[number_of_vertices + 1][height] = probability;
    return probability;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    short number_of_vertices;
    int height_temp;
    std::cin >> number_of_vertices >> height_temp;
    height_temp++;
    if (height_temp > (2 * 2 * 5 * 5)) {
        std::cout << 0 << "\n";
        return 0;
    }
    short height = height_temp;

    std::vector<std::vector<double>> cache(number_of_vertices + 1,
                                           std::vector<double>(height + 1, -1));
    for (short number = 0; number <= number_of_vertices; number++) {
        cache[number][0] = 0;
    }
    for (short hgt = 0; hgt <= height; hgt++) {
        cache[0][hgt] = 0;
        cache[1][hgt] = 0;
    }
    cache[0][0] = 1;
    cache[1][1] = 1;
    std::cout << std::setprecision(5 + 5 + 1)
              << ComputeProbability(number_of_vertices, height, cache) << "\n";
    return 0;
}