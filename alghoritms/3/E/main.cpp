#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

const int64_t kPrime = 1000000007;
const int64_t kX = 1000;
const int64_t kX2 = 1000000;
struct Triangle {
    Triangle(int aa, int bb, int cc) : a(aa), b(bb), c(cc){};
    int a;
    int b;
    int c;
    bool operator==(const Triangle& other) const {
        return (a == other.a) && (b == other.b) && (c == other.c);
    }
};

int Hash(Triangle& triangle, int number_of_triangles) {
    return ((kX2 * triangle.c + kX * triangle.b + triangle.a) % kPrime) %
           number_of_triangles;
}

int HowManyClasses(std::vector<Triangle>& triangles, int number_of_triangles) {
    std::vector<std::vector<Triangle>> cache(number_of_triangles);
    int classes_number = 0;
    for (Triangle& triangle : triangles) {
        int hash = Hash(triangle, number_of_triangles);
        if (cache[hash].empty()) {
            cache[hash].push_back(triangle);
            classes_number++;
        } else {
            bool not_at = true;
            for (Triangle& sub_triangle : cache[hash]) {
                if (triangle == sub_triangle) {
                    not_at = false;
                    break;
                }
            }
            if (not_at) {
                cache[hash].push_back(triangle);
                classes_number++;
            }
        }
    }
    return classes_number;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_triangles;
    std::cin >> number_of_triangles;

    std::vector<Triangle> triangles;
    triangles.reserve(number_of_triangles);
    for (int i = 0; i < number_of_triangles; ++i) {
        int a_side;
        int b_side;
        int c_side;
        std::cin >> a_side >> b_side >> c_side;
        int divisor = std::gcd(std::gcd(a_side, b_side), c_side);
        a_side /= divisor;
        b_side /= divisor;
        c_side /= divisor;
        if (a_side > b_side) {
            std::swap(a_side, b_side);
        }
        if (b_side > c_side) {
            std::swap(b_side, c_side);
        }
        if (a_side > b_side) {
            std::swap(a_side, b_side);
        }
        triangles.emplace_back(a_side, b_side, c_side);
    }
    std::cout << HowManyClasses(triangles, number_of_triangles);
    return 0;
}