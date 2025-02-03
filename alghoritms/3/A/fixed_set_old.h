#include <iostream>
#include <random>
#include <utility>
#include <vector>
const int kPrime = 1'000'000'007;

std::pair<int, int> GenRandomPair(std::mt19937* gen) {
    std::uniform_int_distribution<int> dist(1, kPrime - 1);
    return {dist(*gen), dist(*gen)};
}

int Modulo(int64_t a_value, int b_value) {
    int c_value = a_value % b_value;
    if (c_value < 0) {
        return c_value + b_value;
    }
    return c_value;
}

struct HashFunction {
    int a;
    int b;
    int m;
    int ComputeHash(int number) const {
        return (Modulo(static_cast<int64_t>(a) * number + b, kPrime) % m);
    }
};

int MemoryUsage(std::vector<std::vector<std::pair<int, bool>>>& cache,
                HashFunction& hash, const std::vector<int>& numbers) {
    for (const int& number : numbers) {
        cache[hash.ComputeHash(number)].emplace_back(number, true);
    }
    int overall_usage = 0;
    for (std::vector<std::pair<int, bool>>& sub_cache : cache) {
        overall_usage += (sub_cache.size() * sub_cache.size());
    }
    return overall_usage;
};

bool HaveCollisions(std::vector<bool>& scratch, HashFunction& hash,
                    std::vector<std::pair<int, bool>>& numbers) {
    for (std::pair<int, bool>& number : numbers) {
        int index = hash.ComputeHash(number.first);
        if (scratch[index]) {
            return true;
        }
        scratch[index] = true;
    }
    return false;
};

class FixedSet {
public:
    FixedSet() = default;
    void Initialize(const std::vector<int>& numbers) {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        if (numbers.empty()) {
            return;
        }

        std::mt19937 generator(5);
        int cache_size = numbers.size();

        cache_ = std::vector<std::vector<std::pair<int, bool>>>(cache_size);
        subhashes_ = std::vector<HashFunction>(cache_size);
        main_hash_ = HashFunction{1, 0, cache_size};
        while (MemoryUsage(cache_, main_hash_, numbers) > ((5+5) * cache_size)) {
            for (auto& sub_cache : cache_) {
                std::vector<std::pair<int, bool>>().swap(sub_cache);
            }
            std::pair<int, int> pair = GenRandomPair(&generator);
            main_hash_.a = pair.first;
            main_hash_.b = pair.second;
        }
        for (int sub_cache_number = 0; sub_cache_number < cache_size;
             sub_cache_number++) {
            std::vector<std::pair<int, bool>>& sub_cache =
                cache_[sub_cache_number];
            if (!sub_cache.empty()) {
                int mm = sub_cache.size() * sub_cache.size();
                std::vector<bool> scratch(mm, false);
                HashFunction hash{1, 0, mm};
                while (HaveCollisions(scratch, hash, sub_cache)) {
                    scratch = std::vector<bool>(mm, false);
                    std::pair<int, int> pair = GenRandomPair(&generator);
                    hash.a = pair.first;
                    hash.b = pair.second;
                }
                subhashes_[sub_cache_number] = hash;
                std::vector<std::pair<int, bool>> new_sub_cache(mm);
                for (std::pair<int, bool>& elem : sub_cache) {
                    new_sub_cache[hash.ComputeHash(elem.first)] = {elem.first,
                                                                   true};
                }
                std::swap(sub_cache, new_sub_cache);
            }
        }
    };
    bool Contains(int number) const {
        if (cache_.empty()) {
            return false;
        }
        int first_order_hash = main_hash_.ComputeHash(number);
        if (cache_[first_order_hash].empty()) {
            return false;
        }
        std::pair<int, bool> key_value =
            cache_[first_order_hash]
                  [subhashes_[first_order_hash].ComputeHash(number)];
        return (key_value.first == number && key_value.second);
    };

private:
    std::vector<std::vector<std::pair<int, bool>>> cache_;
    HashFunction main_hash_;
    std::vector<HashFunction> subhashes_;
};