#include <deque>
#include <iostream>
#include <vector>
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int numbers_count;
    std::cin >> numbers_count;

    std::vector<int> numbers;
    numbers.reserve(numbers_count);
    for (int i = 0; i < numbers_count; ++i) {
        int elem;
        std::cin >> elem;
        numbers.push_back(elem);
    }

    int shift_count;
    std::cin >> shift_count;

    std::vector<char> shifts;
    shifts.reserve(shift_count);
    for (int i = 0; i < shift_count; ++i) {
        char shift;
        std::cin >> shift;
        shifts.push_back(shift);
    }

    std::deque<int> cache;
    //В деке будем хранить (нестрого убывающе)только те элементы, которые имеют
    //шанс когда-то быть названными максимумом по отрезку. в частности, они,
    //конечно, элементы отрезка кроме того, первый элемент деки всегда является
    //максимумом по нынешнему отрезку дека пуста <=> отрезок пуст, что не
    //случается по условию
    // P.S. первоначально ты хотел хранить пары элемент-его индекс, но потом
    // понял, что индекс никак не используется, значит, пары хранить незачем
    // P.P.S. дека в любой момент времени --
    //  схлопнутый массив максимумов суффиксов?
    int lp = 0;
    int rp = 0;
    cache.push_back(numbers[0]);

    for (const auto& shift : shifts) {
        if (shift == 'L') {
            if (numbers[lp] == cache.front()) {
                cache.pop_front();
            }
            std::cout << cache.front() << " ";
            ++lp;
        } else {
            ++rp;
            while (cache.back() < numbers[rp]) {
                cache.pop_back();
                if (cache.empty()) {
                    break;
                }
            }
            cache.push_back(numbers[rp]);
            std::cout << cache.front() << " ";
        }
    }
    return 0;
}