#include <iostream>
#include <optional>
#include <random>
#include <vector>

const int kPrime = 2'000'000'011;

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
    int ComputeHash(int number) const {

        return (Modulo(static_cast<uint64_t>(a) * number + b) % m);
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
                    std::vector<std::optional<int>>& numbers) {
    std::vector<bool> check_collisions(hash.m, false);
    for (std::optional<int>& number : numbers) {
        int index = hash.ComputeHash(number.value());
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
        int cache_size = numbers.size()*3;

        cache_ = std::vector<std::vector<std::optional<int>>>(cache_size);
        subhashes_ = std::vector<HashFunction>(cache_size);

        main_hash_.a = 1;
        main_hash_.b = 0;
        main_hash_.m = cache_size;

        while (MemoryUsage(main_hash_, numbers, cache_size) >
               ((5 + 5) * cache_size)) {
            std::pair<int, int> pair = GenRandomPair(&generator);
            main_hash_.a = pair.first;
            main_hash_.b = pair.second;
        }
        for (const int& number : numbers) {
            cache_[main_hash_.ComputeHash(number)].emplace_back(number);
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
                std::vector<std::optional<int>> new_sub_cache(mm);
                for (std::optional<int>& elem : cache_[sub_cache_number]) {
                    new_sub_cache[hash.ComputeHash(elem.value())] = elem;
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
        std::optional<int> element =
            cache_[first_order_hash]
                  [subhashes_[first_order_hash].ComputeHash(number)];
        if (element.has_value()) {
            return element.value() == number;
        }
        return false;
    };

private:
    std::vector<std::vector<std::optional<int>>> cache_;
    HashFunction main_hash_;
    std::vector<HashFunction> subhashes_;
};