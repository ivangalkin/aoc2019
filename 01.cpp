#include <iostream>
#include <math.h>

static int64_t input[] = {
        134492,
        88713,
        84405,
        148193,
        95951,
        63545,
        137840,
        65558,
        124836,
        95431,
        77622,
        91864,
        108677,
        116871,
        119496,
        97172,
        86115,
        105704,
        68613,
        77114,
        114013,
        52766,
        57048,
        80814,
        73888,
        58253,
        135934,
        97409,
        112439,
        98262,
        116047,
        57456,
        124261,
        83006,
        101495,
        133449,
        111372,
        56146,
        87818,
        92209,
        149259,
        124559,
        141838,
        147988,
        65703,
        125566,
        59650,
        139564,
        92430,
        126307,
        120406,
        147383,
        84362,
        51529,
        146366,
        131840,
        53270,
        71886,
        118767,
        104311,
        126181,
        76964,
        129430,
        95489,
        91098,
        54133,
        110057,
        107276,
        118226,
        96104,
        135382,
        85152,
        61697,
        143417,
        148879,
        126846,
        130205,
        111170,
        86687,
        113729,
        123330,
        56976,
        148470,
        66028,
        129715,
        75686,
        74964,
        148258,
        72669,
        88809,
        78173,
        92699,
        124806,
        67217,
        139066,
        136002,
        135730,
        145708,
        142054,
        135772
};

static inline int64_t simple_fuel(int64_t mass) {
    return trunc((double) mass / 3) - 2;
}

static inline int64_t recursive_fuel(int64_t mass) {
    int64_t result = 0;
    int64_t current_input = mass;
    int64_t current_output = 0;
    while (true) {
        current_output = simple_fuel(current_input);
        if (current_output <= 0) {
            break;
        }
        current_input = current_output;
        result += current_output;
    }
    return result;
}

int _1() {
    int64_t result0 = 0;
    int64_t result1 = 0;
    std::cout << recursive_fuel(14) << std::endl;
    std::cout << recursive_fuel(1969) << std::endl;
    std::cout << recursive_fuel(100756) << std::endl;

    for (auto mass: input) {
        result0 += simple_fuel(mass);
        result1 += recursive_fuel(mass);
    }
    std::cout << result0 << std::endl;
    std::cout << result1 << std::endl;
    return 0;
}
