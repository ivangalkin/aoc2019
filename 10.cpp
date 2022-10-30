#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <tuple>
#include <math.h>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <algorithm>

#define ASSERT_EQ(a, b) \
   { __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     if (a != b)       \
     {                 \
       std::cout << a << " != " << b << std::endl; \
       assert(0);                  \
     }                  \
     }

namespace {
    using input_t = std::vector<std::string>;

    using i64 = int64_t;

    bool find_same_angle_with_coef(std::set<std::tuple<i64, i64>> existing_angles, i64 i, i64 j) {
        auto max_coef = std::max(i, j);
        for (auto [existing_i, existing_j]: existing_angles) {
            for (i64 c = 1; c <= max_coef; c++) {
                if (existing_i * c == i && existing_j * c == j) {
                    return true;
                }
            }
        }
        return false;
    }

    std::set<std::tuple<i64, i64>> create_angles(const input_t &map) {
        auto map_width = map.at(0).size();
        auto map_height = map.size();

        std::set<std::tuple<i64, i64>> result;
        for (i64 i = 0; i < map_width; i++) {
            for (i64 j = 0; j < map_height; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                if (!find_same_angle_with_coef(result, i, j)) {
                    result.insert({i, j});
                    result.insert({-i, j});
                    result.insert({i, -j});
                    result.insert({-i, -j});
                }
            }
        }

        return result;
    }

    i64 count_visible(i64 observer_x, i64 observer_y, const input_t &map, i64 i, i64 j) {
        auto sum = 0;
        auto x = observer_x;
        auto y = observer_y;
        for (; x >= 0 && x < map.at(0).size() && y >= 0 && y < map.size();) {
            if (x == observer_x && y == observer_y) {
                x += i;
                y += j;
                continue;
            }

            if (map.at(y).at(x) == '#') {
                sum++;
            }
            x += i;
            y += j;
        }
        return std::min(1, sum);
    }

    struct DestroyStep {
        i64 gun_x;
        i64 gun_y;
        i64 x;
        i64 y;
        i64 i;
        i64 j;
        static i64 destroy_index;

        void destroy(const input_t &map) {
            for (; x >= 0 && x < map.at(0).size() && y >= 0 && y < map.size();) {
                if (x == gun_x && y == gun_y) {
                    x += i;
                    y += j;
                    continue;
                }

                if (map.at(y).at(x) == '#') {
                    ++DestroyStep::destroy_index;
                    std::cout << DestroyStep::destroy_index << " destroy at " << x << ", " << y << " (" << x * 100 + y
                              << ")" << std::endl;
                    x += i;
                    y += j;
                    return;
                }
                x += i;
                y += j;
            }
        }
    };

    i64 DestroyStep::destroy_index = 0;


    i64 observe(i64 observer_x, i64 observer_y, const input_t &map, const std::set<std::tuple<i64, i64>> &angles) {
        std::set < i64 > checked_ks;
        i64 sum = 0;

        for (auto [i, j]: angles) {
            sum += count_visible(observer_x, observer_y, map, i, j);
        }
        return sum;
    }

    void walk_map(const input_t &map) {
        const auto angles = create_angles(map);
        i64 max = std::numeric_limits<i64>::min();
        i64 max_x, max_y;
        for (i64 y = 0; y < map.size(); y++) {
            for (i64 x = 0; x < map.at(0).size(); x++) {
                if (map.at(y).at(x) == '#') {
                    auto res = observe(x, y, map, angles);
                    if (res > max) {
                        max = res;
                        max_x = x;
                        max_y = y;
                    }
                    std::cout << res;

                } else {
                    std::cout << ".";
                }
            }
            std::cout << std::endl;
        }
        std::cout << max << " at (" << max_x << ", " << max_y << ")" << std::endl;
    }

    std::vector<std::tuple<i64, i64>> sort_angles(const std::set<std::tuple<i64, i64>> &unsorted_angles) {
        std::vector<std::tuple<i64, i64>> result{unsorted_angles.begin(), unsorted_angles.end()};
        std::sort(result.begin(), result.end(), [](auto lhs, auto rhs) {
            auto [lhs_i, lhs_j] = lhs;
            auto [rhs_i, rhs_j] = rhs;
            auto get_quadrant = [](i64 i, i64 j) {
                if (j <= 0 && i >= 0) {
                    return 1;
                } else if (j > 0 && i >= 0) {
                    return 2;
                } else if (j > 0 && i < 0) {
                    return 3;
                } else if (j <= 0 && i < 0) {
                    return 4;
                }
                assert(false);
            };

            std::tuple<i64, double> lhs_comp{get_quadrant(lhs_i, lhs_j), atan((double) lhs_j / (double) lhs_i)};
            std::tuple<i64, double> rhs_comp{get_quadrant(rhs_i, rhs_j), atan((double) rhs_j / (double) rhs_i)};

            return lhs_comp < rhs_comp;
        });
        return result;
    }
}

int _10() {
    walk_map({".#..#",
              ".....",
              "#####",
              "....#",
              "...##"});
    walk_map({".#..##.###...#######",
              "##.############..##.",
              ".#.######.########.#",
              ".###.#######.####.#.",
              "#####.##.#.##.###.##",
              "..#####..#.#########",
              "####################",
              "#.####....###.#.#.##",
              "##.#################",
              "#####.##.###..####..",
              "..######..##.#######",
              "####.##.####...##..#",
              ".#####..#.######.###",
              "##...#.##########...",
              "#.##########.#######",
              ".####.#.###.###.#.##",
              "....##.##.###..#####",
              ".#.#.###########.###",
              "#.#.#.#####.####.###",
              "###.##.####.##.#..##"});

    input_t input = {"#.....#...#.........###.#........#..",
                     "....#......###..#.#.###....#......##",
                     "......#..###.......#.#.#.#..#.......",
                     "......#......#.#....#.##....##.#.#.#",
                     "...###.#.#.......#..#...............",
                     "....##...#..#....##....#...#.#......",
                     "..##...#.###.....##....#.#..##.##...",
                     "..##....#.#......#.#...#.#...#.#....",
                     ".#.##..##......##..#...#.....##...##",
                     ".......##.....#.....##..#..#..#.....",
                     "..#..#...#......#..##...#.#...#...##",
                     "......##.##.#.#.###....#.#..#......#",
                     "#..#.#...#.....#...#...####.#..#...#",
                     "...##...##.#..#.....####.#....##....",
                     ".#....###.#...#....#..#......#......",
                     ".##.#.#...#....##......#.....##...##",
                     ".....#....###...#.....#....#........",
                     "...#...#....##..#.#......#.#.#......",
                     ".#..###............#.#..#...####.##.",
                     ".#.###..#.....#......#..###....##..#",
                     "#......#.#.#.#.#.#...#.#.#....##....",
                     ".#.....#.....#...##.#......#.#...#..",
                     "...##..###.........##.........#.....",
                     "..#.#..#.#...#.....#.....#...###.#..",
                     ".#..........#.......#....#..........",
                     "...##..#..#...#..#...#......####....",
                     ".#..#...##.##..##..###......#.......",
                     ".##.....#.......#..#...#..#.......#.",
                     "#.#.#..#..##..#..............#....##",
                     "..#....##......##.....#...#...##....",
                     ".##..##..#.#..#.................####",
                     "##.......#..#.#..##..#...#..........",
                     "#..##...#.##.#.#.........#..#..#....",
                     ".....#...#...#.#......#....#........",
                     "....#......###.#..#......##.....#..#",
                     "#..#...##.........#.....##.....#...."};
    // part 1
    // output
    // 303 at (26, 29)
    walk_map(input);

    // part2
    auto unsorted_angles = create_angles(input);
    auto sorted_angles = sort_angles(unsorted_angles);
    std::vector<DestroyStep> destroy_steps;
    for (auto [i, j]: sorted_angles) {
        destroy_steps.push_back({26, 29, 26, 29, i, j});
    }

    while (true) {
        for (auto &step: destroy_steps) {
            step.destroy(input);
            if (DestroyStep::destroy_index == 200) {
                return 0;
            }
        }
    }

    return 0;
}
