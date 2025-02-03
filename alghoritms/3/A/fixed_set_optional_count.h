#include <iostream>
#include <optional>
#include <random>
#include <vector>

const int kPrime = 2'000'000'011;

uint NextPowerOfTwo(uint number) {
    number--;
    number |= number >> 1;
    number |= number >> 2;
    number |= number >> 4;
    number |= number >> 8;   // NOLINT
    number |= number >> 16;  // NOLINT
    return number + 1;
}

std::pair<int, int> GenRandomPair(std::mt19937* gen) {
    std::uniform_int_distribution<int> dist(1, kPrime - 1);
    return {dist(*gen), dist(*gen)};
}

uint Modulo(int64_t a_value) {
    int c_value = a_value % kPrime;
    if (c_value < 0) {
        return c_value + kPrime;
    }
    return c_value;
}

struct HashFunction {
    int a;
    int b;
    uint m;
    int ComputeHash(int number) const {
        return (Modulo(static_cast<int64_t>(a) * number + b) & (m - 1));
    }
};

int64_t MemoryUsage(std::vector<std::vector<std::optional<int>>>& cache,
                    HashFunction& hash, const std::vector<int>& numbers) {
    for (const int& number : numbers) {
        cache[hash.ComputeHash(number)].push_back(number);
    }
    int64_t overall_usage = 0;
    for (std::vector<std::optional<int>>& subcache : cache) {
        overall_usage += (subcache.size() * subcache.size());
    }
    return overall_usage;
};

bool HaveCollisions(HashFunction& hash,
                    std::vector<std::optional<int>>& numbers,
                    std::vector<std::optional<int>>& scratch) {
    for (std::optional<int>& number : numbers) {
        int index = hash.ComputeHash(number.value());
        if (scratch[index].has_value()) {
            return true;
        }
        scratch[index] = number;
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
        uint cache_size = NextPowerOfTwo(numbers.size());

        cache_ = std::vector<std::vector<std::optional<int>>>(cache_size);
        subhashes_ = std::vector<HashFunction>(cache_size);

        main_hash_.a = 1;
        main_hash_.b = 0;
        main_hash_.m = cache_size;

        while (MemoryUsage(cache_, main_hash_, numbers) >
               ((5 + 5) * cache_size)) {
            std::pair<int, int> pair = GenRandomPair(&generator);
            main_hash_.a = pair.first;
            main_hash_.b = pair.second;
            for (auto& sub_cache : cache_) {
                std::vector<std::optional<int>>().swap(sub_cache);
            }
        }
        for (uint sub_cache_number = 0; sub_cache_number < cache_size;
             sub_cache_number++) {
            std::vector<std::optional<int>>& sub_cache =
                cache_[sub_cache_number];
            if (!sub_cache.empty()) {
                uint mm = NextPowerOfTwo(sub_cache.size() * sub_cache.size());
                HashFunction hash{1, 0, mm};
                std::vector<std::optional<int>> scratch(mm);
                while (HaveCollisions(hash, sub_cache, scratch)) {
                    std::pair<int, int> pair = GenRandomPair(&generator);
                    hash.a = pair.first;
                    hash.b = pair.second;
                    scratch = std::vector<std::optional<int>>(mm);
                }
                subhashes_[sub_cache_number] = hash;
                std::swap(sub_cache, scratch);
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