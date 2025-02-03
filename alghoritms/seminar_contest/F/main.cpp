#include <algorithm>
#include <cstdint>
#include <deque>
#include <iostream>
#include <vector>

struct Diamond {
    Diamond(int64_t we, int64_t co) : weight(we), cost(co) {}
    int64_t weight;
    int64_t cost;
};

struct Configuration {
    Configuration(int64_t tw, int64_t tc, unsigned int dn)
        : total_weight(tw), total_cost(tc), diamond_numbers(dn) {}
    int64_t total_weight = 0;
    int64_t total_cost = 0;
    unsigned int diamond_numbers = 0;
};

struct DesiredConfiguration {
    Configuration best_first_half_config;
    int64_t best_cost = 0;
};

void FillHalf(std::vector<Diamond>& diamonds,
              std::vector<Configuration>& first_half,
              short current_diamond_index, short last_diamond_index,
              Configuration configuration) {
    if (current_diamond_index == last_diamond_index) {
        first_half.emplace_back(configuration.total_weight,
                                configuration.total_cost,
                                (configuration.diamond_numbers << 1));
        first_half.emplace_back(
            configuration.total_weight + diamonds[current_diamond_index].weight,
            configuration.total_cost + diamonds[current_diamond_index].cost,
            (configuration.diamond_numbers << 1) + 1);
    } else {
        configuration.diamond_numbers = configuration.diamond_numbers << 1;
        FillHalf(diamonds, first_half, current_diamond_index + 1,
                 last_diamond_index, configuration);
        configuration.diamond_numbers++;
        configuration.total_cost += diamonds[current_diamond_index].cost;
        configuration.total_weight += diamonds[current_diamond_index].weight;
        FillHalf(diamonds, first_half, current_diamond_index + 1,
                 last_diamond_index, configuration);
    }
}

DesiredConfiguration RunThrough(std::vector<Configuration>& first_half,
                                std::vector<Configuration>& second_half,
                                int64_t lower_bound, int64_t upper_bound) {
    int64_t desired_weight;
    DesiredConfiguration best{{0, 0, 0}, 0};
    auto first_iterator = first_half.begin();
    auto right_iterator = second_half.begin();
    auto left_iterator = second_half.begin();
    std::deque<int64_t> cache;
    while (first_iterator != first_half.end()) {
        desired_weight = lower_bound - first_iterator->total_weight;
        while (right_iterator != second_half.end() &&
               (right_iterator->total_weight >= desired_weight)) {
            if (cache.empty()) {
                cache.push_back(right_iterator->total_cost);
                ++right_iterator;
                continue;
            }
            while (cache.back() < right_iterator->total_cost) {
                cache.pop_back();
                if (cache.empty()) {
                    break;
                }
            }
            cache.push_back(right_iterator->total_cost);
            ++right_iterator;
        }

        desired_weight = upper_bound - first_iterator->total_weight;
        while (left_iterator != second_half.end() &&
               (left_iterator->total_weight > desired_weight)) {
            if (left_iterator->total_cost == cache.front()) {
                cache.pop_front();
            }
            ++left_iterator;
        }

        if (left_iterator < right_iterator &&
            (cache.front() + first_iterator->total_cost) > best.best_cost) {
            best.best_cost = cache.front() + first_iterator->total_cost;
            best.best_first_half_config = *first_iterator;
        }
        ++first_iterator;
    }
    return best;
}

std::pair<unsigned int, unsigned int> Solve(std::vector<Diamond>& diamonds,
                                            short number_of_diamonds,
                                            int64_t lower_bound,
                                            int64_t upper_bound) {
    short first_size = number_of_diamonds / 2;
    short second_size = number_of_diamonds - first_size;

    std::vector<Configuration> first_half;
    first_half.reserve(1 << first_size);
    std::vector<Configuration> second_half;
    second_half.reserve(1 << second_size);

    FillHalf(diamonds, first_half, 0, first_size - 1, {0, 0, 0});
    FillHalf(diamonds, second_half, first_size, number_of_diamonds - 1,
             {0, 0, 0});
    std::sort(first_half.begin(), first_half.end(),
              [](Configuration& config1, Configuration& config2) {
                  return config1.total_weight < config2.total_weight;
              });
    std::sort(second_half.begin(), second_half.end(),
              [](Configuration& config1, Configuration& config2) {
                  return config1.total_weight > config2.total_weight;
              });

    if (second_half.front().total_weight + first_half.back().total_weight <
        lower_bound) {
        return {0, 0};
    }
    if (second_half.back().total_weight + first_half.front().total_weight >
        upper_bound) {
        return {0, 0};
    }

    DesiredConfiguration best =
        RunThrough(first_half, second_half, lower_bound, upper_bound);

    if (best.best_cost == 0) {
        return {0, 0};
    }
    int64_t second_cost =
        best.best_cost - best.best_first_half_config.total_cost;
    int64_t new_lower_bound =
        lower_bound - best.best_first_half_config.total_weight;
    int64_t new_upper_bound =
        upper_bound - best.best_first_half_config.total_weight;

    auto it = second_half.begin();
    while (it != second_half.end()) {
        if (it->total_cost == second_cost &&
            it->total_weight >= new_lower_bound &&
            it->total_weight <= new_upper_bound) {
            return {best.best_first_half_config.diamond_numbers,
                    it->diamond_numbers};
        }
        ++it;
    }
    return {0, 0};
}

std::vector<short> ReturnFirstHalfDiamonds(unsigned int configuration,
                                           short first_size) {
    unsigned int mask = 1 << (first_size - 1);
    short index = 0;
    std::vector<short> answer{};
    answer.reserve(first_size);
    while (mask > 0) {
        if ((configuration & mask) > 0) {
            answer.push_back(index + 1);
        }
        index++;
        mask = mask >> 1;
    }
    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    short number_of_diamonds;
    int64_t lower_bound;
    int64_t upper_bound;
    std::cin >> number_of_diamonds >> lower_bound >> upper_bound;

    std::vector<Diamond> diamonds;
    diamonds.reserve(number_of_diamonds);
    for (short i = 0; i < number_of_diamonds; i++) {
        int64_t weight;
        int64_t cost;
        std::cin >> weight >> cost;
        diamonds.emplace_back(weight, cost);
    }
    if (number_of_diamonds == 1) {
        if (diamonds.front().weight <= upper_bound &&
            diamonds.front().weight >= lower_bound) {
            std::cout << 1 << "\n" << 1;
        } else {
            std::cout << 0;
        }
        return 0;
    }
    std::pair<unsigned int, unsigned int> answer =
        Solve(diamonds, number_of_diamonds, lower_bound, upper_bound);
    if (answer.first == 0 && answer.second == 0) {
        std::cout << 0;
        return 0;
    }

    short first_size = number_of_diamonds / 2;
    short second_size = number_of_diamonds - first_size;
    std::vector<short> ans1 = ReturnFirstHalfDiamonds(answer.first, first_size);
    std::vector<short> ans2 =
        ReturnFirstHalfDiamonds(answer.second, second_size);
    std::cout << ans1.size() + ans2.size() << "\n";
    for (short elem : ans1) {
        std::cout << elem << " ";
    }
    for (short elem : ans2) {
        std::cout << elem + first_size << " ";
    }
    return 0;
}