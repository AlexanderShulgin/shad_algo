#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

struct Node {
    int64_t val, len, mx;
    int prio, sz;
    std::shared_ptr<Node> left, right;
    Node(int64_t val, int64_t len)
        : val(val),
          len(len),
          mx(len),
          prio(rand()),
          sz(1),
          left(nullptr),
          right(nullptr) {}
};

int GetSz(std::shared_ptr<Node> kek) { return kek ? kek->sz : 0; }

int64_t GetMx(std::shared_ptr<Node> kek) { return kek ? kek->mx : 0; }

void Upd(std::shared_ptr<Node> kek) {
    kek->sz = GetSz(kek->left) + 1 + GetSz(kek->right);
    kek->mx = std::max({GetMx(kek->left), kek->len, GetMx(kek->right)});
}

std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> SplitVal(
    std::shared_ptr<Node> kek, int val) {
    if (!kek) {
        return {nullptr, nullptr};
    }
    if (kek->val >= val) {
        auto [tOne, tTwo] = SplitVal(kek->left, val);
        kek->left = tTwo;
        Upd(kek);
        return {tOne, kek};
    }
    auto [tOne, tTwo] = SplitVal(kek->right, val);
    kek->right = tOne;
    Upd(kek);
    return {kek, tTwo};
}

std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> SplitNum(
    std::shared_ptr<Node> kek, int val) {
    if (!kek) {
        return {nullptr, nullptr};
    }
    int sz = GetSz(kek->left);
    if (sz >= val) {
        auto [tOne, tTwo] = SplitNum(kek->left, val);
        kek->left = tTwo;
        Upd(kek);
        return {tOne, kek};
    }
    auto [tOne, tTwo] = SplitNum(kek->right, val - sz - 1);
    kek->right = tOne;
    Upd(kek);
    return {kek, tTwo};
}

std::shared_ptr<Node> Merge(std::shared_ptr<Node> t_one,
                            std::shared_ptr<Node> t_two) {
    if (!t_one) {
        return t_two;
    }
    if (!t_two) {
        return t_one;
    }
    if (t_one->prio > t_two->prio) {
        t_one->right = Merge(t_one->right, t_two);
        Upd(t_one);
        return t_one;
    }
    t_two->left = Merge(t_one, t_two->left);
    Upd(t_two);
    return t_two;
}

void Add(std::shared_ptr<Node>& kek, int64_t val, int64_t len) {
    auto [tOne, tTwo] = SplitVal(kek, val);
    std::shared_ptr<Node> tmp = std::make_shared<Node>(val, len);
    tmp = Merge(tmp, tTwo);
    kek = Merge(tOne, tmp);
}

void Rm(std::shared_ptr<Node>& kek, int64_t val) {
    auto [tOne, tTwo] = SplitVal(kek, val);
    tTwo = SplitNum(tTwo, 1).second;
    kek = Merge(tOne, tTwo);
}

std::shared_ptr<Node> Get(std::shared_ptr<Node> kek) {
    if (!kek) {
        return nullptr;
    }
    if (GetMx(kek->left) == kek->mx) {
        return Get(kek->left);
    }
    if (kek->len == kek->mx) {
        return kek;
    }
    return Get(kek->right);
}

void Func(std::shared_ptr<Node>& kek, std::vector<int64_t>& queries,
          int& cur_query, std::vector<int64_t>& ans) {
    auto res = Get(kek);
    if (!res || res->len < queries[cur_query]) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << res->val << std::endl;
        ans[cur_query] = res->val;
        std::pair<int64_t, int64_t> tmp = {res->val, res->len};
        Rm(kek, res->val);
        if (tmp.second != queries[cur_query]) {
            Add(kek, res->val + queries[cur_query],
                tmp.second - queries[cur_query]);
        }
    }
}

int main() {
    int64_t len;
    int queries_num;
    std::cin >> len >> queries_num;
    std::shared_ptr<Node> kek = std::make_shared<Node>(1, len);
    std::vector<int64_t> queries(queries_num);
    std::vector<int64_t> ans(queries_num, -1);
    for (int cur_query = 0; cur_query < queries_num; ++cur_query) {
        std::cin >> queries[cur_query];
        if (queries[cur_query] > 0) {
            Func(kek, queries, cur_query, ans);
        } else {
            int64_t query = -queries[cur_query] - 1;
            if (ans[query] == -1) {
                continue;
            }
            int64_t cur_len = queries[query];
            int64_t cur_val = ans[query];
            auto [tOne, tTwo] = SplitVal(kek, ans[query]);
            if (tOne) {
                auto [tOneOne, tOneTwo] = SplitNum(tOne, GetSz(tOne) - 1);
                if (tOneTwo->val + tOneTwo->len == ans[query]) {
                    cur_len += tOneTwo->len;
                    cur_val = tOneTwo->val;
                    tOne = tOneOne;
                } else {
                    tOne = Merge(tOneOne, tOneTwo);
                }
            }
            if (tTwo) {
                auto [tTwoOne, tTwoTwo] = SplitNum(tTwo, 1);
                if (tTwoOne->val == ans[query] + queries[query]) {
                    cur_len += tTwoOne->len;
                    tTwo = tTwoTwo;
                } else {
                    tTwo = Merge(tTwoOne, tTwoTwo);
                }
            }
            kek = Merge(tOne, tTwo);
            Add(kek, cur_val, cur_len);
        }
    }

    return 0;
}