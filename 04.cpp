#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <tuple>
#include <assert.h>
#include <algorithm>

static bool isValid1(int64_t pwd) {
    // 6 digits
    // 284639
    // 748759
    std::vector<int64_t> original;
    int64_t pow[]{1, 10, 100, 1000, 10000, 100000};
    for (int i = 5; i >= 0; i--) {
        int div = pwd / pow[i];
        original.push_back(div);
        pwd -= div * pow[i];
    }

    std::vector<int64_t> sorted = original;
    std::sort(sorted.begin(), sorted.end());

    if (original != sorted) {
        return false;
    }

    if (std::set < int64_t > (sorted.begin(), sorted.end()).size() <= original.size() - 1) {
        return true;
    }

    return false;
}


static bool isValid2(int64_t pwd) {
    // 6 digits
    // 284639
    // 748759
    std::vector<int64_t> original;
    int64_t pow[]{1, 10, 100, 1000, 10000, 100000};
    for (int i = 5; i >= 0; i--) {
        int div = pwd / pow[i];
        original.push_back(div);
        pwd -= div * pow[i];
    }

    std::vector<int64_t> sorted = original;
    std::sort(sorted.begin(), sorted.end());

    if (original != sorted) {
        return false;
    }

    std::vector<std::tuple<int64_t, int64_t>> groups;

    for (auto digit: sorted) {
        if (groups.empty()) {
            groups.push_back({digit, 1});
        } else {
            auto &[previous_digit, previous_count] = groups.back();
            if (previous_digit == digit) {
                ++previous_count;
            } else {
                groups.push_back({digit, 1});
            }
        }
    }

    return std::count_if(groups.begin(), groups.end(), [](const auto &group) { return std::get<1>(group) == 2; }) >= 1;

}

int _4() {
    {
        std::cout << isValid1(111111) << std::endl;
        std::cout << isValid1(223450) << std::endl;
        std::cout << isValid1(123789) << std::endl;
        int64_t count = 0;
        for (int64_t pwd = 284639; pwd <= 748759; pwd++) {
            count += isValid1(pwd);
        }
        std::cout << count << std::endl;
    }
    {
        std::cout << isValid2(112233) << std::endl;
        std::cout << isValid2(123444) << std::endl;
        std::cout << isValid2(111122) << std::endl;
        int64_t count = 0;
        for (int64_t pwd = 284639; pwd <= 748759; pwd++) {
            count += isValid2(pwd);
        }
        std::cout << count << std::endl;
    }
    return 0;
}
