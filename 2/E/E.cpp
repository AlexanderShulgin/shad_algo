#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>
struct Coin {
    int position;
    int expiration_time;
    Coin(int pos, int time) : position(pos), expiration_time(time) {}
};

struct Answer {
    bool manage_to_collect_on_time;
    int current_time = -2;
    int current_position;
    // Answer(bool man, int curt, int curp): manage_to_collect_on_time(man),
    // current_time(curt), current_position(curp){}
};

struct ShortAnswer {
    bool manage_full;
    int wasted_time;
};

ShortAnswer ManageOnSegmentFull(Answer& answer, Coin& last_coin) {
    if (!answer.manage_to_collect_on_time) {
        return {false, -1};
    }
    int wasted = answer.current_time +
                 std::abs(last_coin.position - answer.current_position);
    return {wasted <= last_coin.expiration_time, wasted};
}

void UpdateCache(std::vector<std::vector<std::pair<Answer, Answer>>>& cache,
                 Answer& ans, bool lean_left, int from, int to) {
    if (lean_left) {
        cache[from][to].first = ans;
    } else {
        cache[from][to].second = ans;
    }
}

Answer CollectCoinsOnSegment(
    std::vector<Coin>& coins, int from, int to, bool lean_left,
    std::vector<std::vector<std::pair<Answer, Answer>>>& cache) {
    if (from == to) {
        return {true, 0, coins[from].position};
    }
    if (lean_left) {
        if (cache[from][to].first.current_time != -2) {
            return cache[from][to].first;
        }
    } else {
        if (cache[from][to].second.current_time != -2) {
            return cache[from][to].second;
        }
    }

    int lean_to = to + 1;
    if (lean_left) {
        lean_to = from - 1;
    }

    Answer answer_right =
        CollectCoinsOnSegment(coins, from + 1, to, true, cache);
    Answer answer_left =
        CollectCoinsOnSegment(coins, from, to - 1, false, cache);
    ShortAnswer short_answer_right =
        ManageOnSegmentFull(answer_right, coins[from]);
    ShortAnswer short_answer_left = ManageOnSegmentFull(answer_left, coins[to]);
    if (short_answer_right.manage_full) {
        if (short_answer_left.manage_full) {
            if ((short_answer_left.wasted_time +
                 std::abs(coins[to].position - coins[lean_to].position)) <
                (short_answer_right.wasted_time +
                 std::abs(coins[from].position - coins[lean_to].position))) {
                Answer ans{true, short_answer_left.wasted_time,
                           coins[to].position};
                UpdateCache(cache, ans, lean_left, from, to);
                return ans;
            }
            Answer ans = {true, short_answer_right.wasted_time,
                          coins[from].position};
            UpdateCache(cache, ans, lean_left, from, to);
            return ans;
        }
        Answer ans = {true, short_answer_right.wasted_time,
                      coins[from].position};
        UpdateCache(cache, ans, lean_left, from, to);
        return ans;
    }
    if (short_answer_left.manage_full) {
        Answer ans = {true, short_answer_left.wasted_time, coins[to].position};
        UpdateCache(cache, ans, lean_left, from, to);
        return ans;
    }
    Answer ans = {false, -1, -1};
    UpdateCache(cache, ans, lean_left, from, to);
    return ans;
}

Answer CollectCoins(
    std::vector<Coin>& coins, int from, int to,
    std::vector<std::vector<std::pair<Answer, Answer>>>& cache) {
    if (from == to) {
        return {true, 0, coins[from].position};
    }
    Answer answer_right =
        CollectCoinsOnSegment(coins, from + 1, to, true, cache);
    Answer answer_left =
        CollectCoinsOnSegment(coins, from, to - 1, false, cache);
    ShortAnswer short_answer_right =
        ManageOnSegmentFull(answer_right, coins[from]);
    ShortAnswer short_answer_left = ManageOnSegmentFull(answer_left, coins[to]);
    if (short_answer_right.manage_full) {
        if (short_answer_left.manage_full) {
            if (short_answer_left.wasted_time <
                short_answer_right.wasted_time) {
                return {true, short_answer_left.wasted_time,
                        coins[to].position};
            }
            return {true, short_answer_right.wasted_time, coins[from].position};
        }
        return {true, short_answer_right.wasted_time, coins[from].position};
    }
    if (short_answer_left.manage_full) {
        return {true, short_answer_left.wasted_time, coins[to].position};
    }
    return {false, -1, -1};
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_coins;
    std::cin >> number_of_coins;
    std::vector<Coin> coins_dupl;
    coins_dupl.reserve(number_of_coins);
    for (int i = 0; i < number_of_coins; ++i) {
        int pos;
        std::cin >> pos;
        int time;
        std::cin >> time;
        coins_dupl.emplace_back(pos, time);
    }
    if (number_of_coins == 1) {
        std::cout << 0;
        return 0;
    }
    std::sort(coins_dupl.begin(), coins_dupl.end(),
              [](Coin& first, Coin& second) {
                  return first.position < second.position;
              });

    std::vector<Coin> coins;
    coins.reserve(number_of_coins);
    coins.push_back(coins_dupl[0]);
    for (int i = 0; i < number_of_coins - 1; ++i) {
        if (coins_dupl[i].position == coins_dupl[i + 1].position) {
            if (coins_dupl[i].expiration_time >
                coins_dupl[i + 1].expiration_time) {
                coins.back().expiration_time =
                    coins_dupl[i + 1].expiration_time;
            }
        } else {
            coins.push_back(coins_dupl[i + 1]);
        }
    }

    int new_number_of_coins = coins.size(); //тут раньше было ssize
    std::vector<std::vector<std::pair<Answer, Answer>>> cache(
        new_number_of_coins,
        std::vector<std::pair<Answer, Answer>>(new_number_of_coins));
    // std::vector<std::vector<Answer>> lean_right_cache(new_number_of_coins,
    // std::vector<Answer>(new_number_of_coins));

    Answer final_answer =
        CollectCoins(coins, 0, new_number_of_coins - 1, cache);
    if (final_answer.manage_to_collect_on_time) {
        std::cout << final_answer.current_time;
        return 0;
    }
    std::cout << "No solution";
    return 0;
}