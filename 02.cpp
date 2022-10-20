#include <iostream>
#include <vector>

static std::vector<int64_t> input0 = {1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50};
static std::vector<int64_t> input = {1, 0, 0, 3, 1, 1, 2, 3, 1, 3, 4, 3, 1, 5, 0, 3, 2, 1, 6, 19, 1, 5, 19, 23, 1, 23,
                                     6, 27, 1, 5, 27, 31, 1, 31, 6, 35, 1, 9, 35, 39, 2, 10, 39, 43, 1, 43, 6, 47, 2, 6,
                                     47, 51, 1, 5, 51, 55, 1, 55, 13, 59, 1, 59, 10, 63, 2, 10, 63, 67, 1, 9, 67, 71, 2,
                                     6, 71, 75, 1, 5, 75, 79, 2, 79, 13, 83, 1, 83, 5, 87, 1, 87, 9, 91, 1, 5, 91, 95,
                                     1, 5, 95, 99, 1, 99, 13, 103, 1, 10, 103, 107, 1, 107, 9, 111, 1, 6, 111, 115, 2,
                                     115, 13, 119, 1, 10, 119, 123, 2, 123, 6, 127, 1, 5, 127, 131, 1, 5, 131, 135, 1,
                                     135, 6, 139, 2, 139, 10, 143, 2, 143, 9, 147, 1, 147, 6, 151, 1, 151, 13, 155, 2,
                                     155, 9, 159, 1, 6, 159, 163, 1, 5, 163, 167, 1, 5, 167, 171, 1, 10, 171, 175, 1,
                                     13, 175, 179, 1, 179, 2, 183, 1, 9, 183, 0, 99, 2, 14, 0, 0};

static void loop(std::vector<int64_t> &code) {
    size_t index = 0;
    int64_t arg0, arg1, arg2;
    while (true) {
        auto op_code = code[index];
        switch (op_code) {
            case 1:
                arg0 = code[index + 1];
                arg1 = code[index + 2];
                arg2 = code[index + 3];
                code[arg2] = code[arg0] + code[arg1];
                index += 4;
                break;
            case 2:
                arg0 = code[index + 1];
                arg1 = code[index + 2];
                arg2 = code[index + 3];
                code[arg2] = code[arg0] * code[arg1];
                index += 4;
                break;
            case 99:
                return;
        }
    }
}

int _2() {
    loop(input0);
    std::cout << input0[0] << std::endl;

    auto input_task_1 = input;
    input_task_1[1] = 12;
    input_task_1[2] = 2;
    loop(input_task_1);
    std::cout << input_task_1[0] << std::endl;

    for (int64_t noun = 0; noun < 100; noun++) {
        for (int64_t verb = 0; verb < 100; verb++) {
            auto input_copy = input;
            input_copy[1] = noun;
            input_copy[2] = verb;
            loop(input_copy);
            auto result = input_copy[0];
            if (result == 19690720) {
                std::cout << 100 * noun + verb << std::endl;
            }
        }
    }

    return 0;
}
