#include <vector>
#include <string>
#include <algorithm>

int levenshteinMemo(const std::string& a, const std::string& b) {
    static std::vector<std::vector<int>> memo;
    memo.assign(a.length() + 1, std::vector<int>(b.length() + 1));

    auto rec = [&](auto&& self, size_t i, size_t j) -> int {
        if (i == a.length()) return static_cast<int>(j);
        if (j == b.length()) return static_cast<int>(i);
        if (memo[i][j]) return memo[i][j];

        char c1 = a[i-1];
        char c2 = b[j-1];
        int cost = (c1 == c2) ? 0 : 1;

        return memo[i][j] = 1 + std::min({
            self(self, i, j - 1),
            self(self, i - 1, j),        
            self(self, i - 1, j - 1) + cost
        });
    };

    return rec(rec, static_cast<size_t>(a.length()), static_cast<size_t>(b.length()));
}


bool didYouMean(const std::string& query, const std::string& candidate, int threshold = 2) {
    return levenshteinMemo(query, candidate) <= threshold;
}
