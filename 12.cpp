#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <tuple>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <algorithm>

#define ASSERT_EQ(a, b) \
   { __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     if (_a != _b)       \
     {                 \
       std::cout << _a << " != " << _b << std::endl; \
       assert(0);                  \
     }                  \
     }

namespace {
    struct Moon {
        std::tuple<int64_t, int64_t, int64_t> position;
        std::tuple<int64_t, int64_t, int64_t> velocity;

        template<size_t p>
        void apply_gravity_single(Moon &other) {
            if (std::get<p>(position) > std::get<p>(other.position)) {
                std::get<p>(velocity)--;
                std::get<p>(other.velocity)++;
            } else if (std::get<p>(position) < std::get<p>(other.position)) {
                std::get<p>(velocity)++;
                std::get<p>(other.velocity)--;
            }
        }

        void apply_gravity(Moon &other) {
            apply_gravity_single<0>(other);
            apply_gravity_single<1>(other);
            apply_gravity_single<2>(other);
        }


        template<size_t p>
        void apply_velocity_single() {
            std::get<p>(position) += std::get<p>(velocity);
        }

        void apply_velocity() {
            apply_velocity_single<0>();
            apply_velocity_single<1>();
            apply_velocity_single<2>();
        }
    };

// cycles:
//    186028
//    56344
//    231614
// LCM = 303459551979256
    std::array<Moon, 4> moons_real_input = {{
                                                    {{-16, 15, -9}, {0, 0, 0}},
                                                    {{-14, 5, 4}, {0, 0, 0}},
                                                    {{2, 0, 6}, {0, 0, 0}},
                                                    {{-3, 18, 9}, {0, 0, 0}}
                                            }};
// cycles:
//    18
//    28
//    44
// LCM = 2772
    std::array<Moon, 4> moons_ex_0 = {{
                                              {{-1, 0, 2}, {0, 0, 0}},
                                              {{2, -10, -7}, {0, 0, 0}},
                                              {{4, -8, 8}, {0, 0, 0}},
                                              {{3, 5, -1}, {0, 0, 0}}
                                      }};

// cycles:
//    2028
//    5898
//    4702
// LCM = 4686774924
    std::array<Moon, 4> moons_ex_1 = {{
                                              {{-8, -10, 0}, {0, 0, 0}},
                                              {{5, 5, 10}, {0, 0, 0}},
                                              {{2, -7, 3}, {0, 0, 0}},
                                              {{9, -8, -3}, {0, 0, 0}}
                                      }};

    template<size_t p>
    void step_single(std::array<Moon, 4> &moons) {
        for (size_t i = 0; i < moons.size(); i++) {
            for (size_t j = i + 1; j < moons.size(); j++) {
                auto &m0 = moons[i];
                auto &m1 = moons[j];
                m0.apply_gravity_single<p>(m1);
            }
        }
        for (auto &m: moons) {
            m.apply_velocity_single<p>();
        }
    }

    void step(std::array<Moon, 4> &moons) {
        step_single<0>(moons);
        step_single<1>(moons);
        step_single<2>(moons);
    }

    int64_t calculate_energy(const std::array<Moon, 4> &moons) {
        int64_t total_energy = 0;
        for (size_t i = 0; i < moons.size(); i++) {
            auto &m = moons.at(i);

            std::cout << "pos=<x=" << std::get<0>(m.position) << ", y=" << std::get<1>(m.position) << ", z="
                      << std::get<2>(m.position) << ", vel=<x=" << std::get<0>(m.velocity) << ", y="
                      << std::get<1>(m.velocity) << ", z=" << std::get<2>(m.velocity) << ">" << std::endl;
            total_energy += (
                    (abs(std::get<0>(m.position)) + abs(std::get<1>(m.position)) + abs(std::get<2>(m.position))) *
                    (abs(std::get<0>(m.velocity)) + abs(std::get<1>(m.velocity)) + abs(std::get<2>(m.velocity))));
        }
        std::cout << "energy=" << total_energy << std::endl;
        return total_energy;
    }

    template<size_t p>
    bool is_a_cycle(const std::array<Moon, 4> &origin_moons, const std::array<Moon, 4> &moons) {
        for (size_t i = 0; i < moons.size(); i++) {
            if (std::get<p>(moons[i].position) != std::get<p>(origin_moons[i].position) ||
                std::get<p>(moons[i].velocity) != std::get<p>(origin_moons[i].velocity)) {
                return false;
            }
        }
        return true;
    }

    template<size_t p>
    int64_t detect_cycle_single(const std::array<Moon, 4> &origin_moons) {
        auto moons = origin_moons;
        std::set<int64_t> maybe_cycles;
        for (int64_t s = 0; s < std::numeric_limits<int64_t>::max(); s++) {
            step_single<p>(moons);

            // check existing cycles
            bool found_existing_cycle = false;
            for (auto it = maybe_cycles.begin(); it != maybe_cycles.end();) {
                if ((s + 1) % *it == 0) {
                    if (is_a_cycle<p>(origin_moons, moons)) {
                        // confirm the existing cycle
                        ++it;
                        found_existing_cycle = true;
                    } else {
                        // reject the wrong existing (not-really-a) cycle
                        it = maybe_cycles.erase(it);
                    }
                } else {
                    ++it;
                }
            }
            // check new cycles
            if (!found_existing_cycle && is_a_cycle<p>(origin_moons, moons)) {
                maybe_cycles.insert(s + 1);
            }
            if (s > 10000 && maybe_cycles.size() == 1) {
                return *maybe_cycles.begin();
            }
        }
        assert(false);
    }
}

int _12() {
    // part 1
    {
        auto moons = moons_real_input;
        for (int64_t i = 0; i < 1000; i++) {
            step(moons);
        }
        ASSERT_EQ(10664, calculate_energy(moons));
    }

    // part 2
    {
        auto cycle_for_x = detect_cycle_single<0>(moons_real_input);
        auto cycle_for_y = detect_cycle_single<1>(moons_real_input);
        auto cycle_for_z = detect_cycle_single<2>(moons_real_input);

        // TODO implement LCM (e.g. division method?), for now goto
        std::cout << "https://www.calculatorsoup.com/calculators/math/lcm.php?input=" << cycle_for_x << "+"
                  << cycle_for_y << "+" << cycle_for_z << "&data=division_method&action=solve";
    }
    return 0;
}
