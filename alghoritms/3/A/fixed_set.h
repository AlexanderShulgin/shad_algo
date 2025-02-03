#include <iostream>
#include <random>
#include <utility>
#include <vector>
const int kPrime = 1'000'000'007;

std::pair<int, int> GenRandomPair(std::mt19937* gen) {
    std::uniform_int_distribution<int> dist(1, kPrime - 1);
    return {dist(*gen), dist(*gen)};
}

int Modulo(int64_t a_value) {
    int c_value = a_value % kPrime;
    if (c_value < 0) {
        return c_value + kPrime;
    }
    return c_value;
}

struct HashFunction {
    int a;
    int b;
    int m;
    int ComputeHash(uint number) const {
        return (Modulo(static_cast<int64_t>(a) * number + b) % m);
    }
};

int64_t MemoryUsage(HashFunction& hash, const std::vector<int>& numbers,
                    int cache_size) {
    std::vector<int> buckets_sizes(cache_size, 0);
    for (const int& number : numbers) {
        buckets_sizes[hash.ComputeHash(number)] += 1;
    }
    int64_t overall_usage = 0;
    for (int& bucket_size : buckets_sizes) {
        overall_usage += (bucket_size * bucket_size);
    }
    return overall_usage;
};

bool HaveCollisions(HashFunction& hash,
                    std::vector<std::pair<int, bool>>& numbers) {
    std::vector<bool> check_collisions(hash.m, false);
    for (std::pair<int, bool>& number : numbers) {
        int index = hash.ComputeHash(number.first);
        if (check_collisions[index]) {
            return true;
        }
        check_collisions[index] = true;
    }
    return false;
};

class FixedSet {
public:
    FixedSet() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
    };
    void Initialize(const std::vector<int>& numbers) {
        if (numbers.empty()) {
            return;
        }

        std::mt19937 generator(1);
        std::uniform_int_distribution<int> dist(1, kPrime - 1);
        int cache_size = numbers.size();

        cache_ = std::vector<std::vector<std::pair<int, bool>>>(cache_size);
        subhashes_ = std::vector<HashFunction>(cache_size);
        main_hash_ = HashFunction{1, 0, cache_size};

        while (MemoryUsage(main_hash_, numbers, cache_size) >
               ((5 + 5) * cache_size)) {
            std::pair<int, int> pair = GenRandomPair(&generator);
            main_hash_.a = pair.first;
            main_hash_.b = pair.second;
        }
        for (const int& number : numbers) {
            cache_[main_hash_.ComputeHash(number)].emplace_back(number, true);
        }

        for (int sub_cache_number = 0; sub_cache_number < cache_size;
             sub_cache_number++) {
            if (!cache_[sub_cache_number].empty()) {
                int mm = cache_[sub_cache_number].size() *
                         cache_[sub_cache_number].size();
                HashFunction hash{1, 0, mm};
                while (HaveCollisions(hash, cache_[sub_cache_number])) {
                    std::pair<int, int> pair = GenRandomPair(&generator);
                    hash.a = pair.first;
                    hash.b = pair.second;
                }
                subhashes_[sub_cache_number] = hash;
                std::vector<std::pair<int, bool>> new_sub_cache(mm);
                for (std::pair<int, bool>& elem : cache_[sub_cache_number]) {
                    new_sub_cache[hash.ComputeHash(elem.first)] = {elem.first,
                                                                   true};
                }
                std::swap(cache_[sub_cache_number], new_sub_cache);
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