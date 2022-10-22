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
     if (a != b)       \
     {                 \
       std::cout << a << " != " << b << std::endl; \
       assert(0);                  \
     }                  \
     }

namespace {

    std::vector<int64_t> input = {3, 225, 1, 225, 6, 6, 1100, 1, 238, 225, 104, 0, 1101, 81, 30, 225, 1102, 9,
                                  63,
                                  225, 1001, 92, 45, 224, 101, -83, 224, 224, 4, 224, 102, 8, 223, 223, 101, 2,
                                  224,
                                  224, 1, 224, 223, 223, 1102, 41, 38, 225, 1002, 165, 73, 224, 101, -2920, 224,
                                  224,
                                  4, 224, 102, 8, 223, 223, 101, 4, 224, 224, 1, 223, 224, 223, 1101, 18, 14,
                                  224,
                                  1001, 224, -32, 224, 4, 224, 1002, 223, 8, 223, 101, 3, 224, 224, 1, 224, 223,
                                  223,
                                  1101, 67, 38, 225, 1102, 54, 62, 224, 1001, 224, -3348, 224, 4, 224, 1002, 223,
                                  8,
                                  223, 1001, 224, 1, 224, 1, 224, 223, 223, 1, 161, 169, 224, 101, -62, 224, 224,
                                  4,
                                  224, 1002, 223, 8, 223, 101, 1, 224, 224, 1, 223, 224, 223, 2, 14, 18, 224,
                                  1001,
                                  224, -1890, 224, 4, 224, 1002, 223, 8, 223, 101, 3, 224, 224, 1, 223, 224, 223,
                                  1101, 20, 25, 225, 1102, 40, 11, 225, 1102, 42, 58, 225, 101, 76, 217, 224,
                                  101,
                                  -153, 224, 224, 4, 224, 102, 8, 223, 223, 1001, 224, 5, 224, 1, 224, 223, 223,
                                  102,
                                  11, 43, 224, 1001, 224, -451, 224, 4, 224, 1002, 223, 8, 223, 101, 6, 224, 224,
                                  1,
                                  223, 224, 223, 1102, 77, 23, 225, 4, 223, 99, 0, 0, 0, 677, 0, 0, 0, 0, 0, 0,
                                  0, 0,
                                  0, 0, 0, 1105, 0, 99999, 1105, 227, 247, 1105, 1, 99999, 1005, 227, 99999,
                                  1005, 0,
                                  256, 1105, 1, 99999, 1106, 227, 99999, 1106, 0, 265, 1105, 1, 99999, 1006, 0,
                                  99999, 1006, 227, 274, 1105, 1, 99999, 1105, 1, 280, 1105, 1, 99999, 1, 225,
                                  225,
                                  225, 1101, 294, 0, 0, 105, 1, 0, 1105, 1, 99999, 1106, 0, 300, 1105, 1, 99999,
                                  1,
                                  225, 225, 225, 1101, 314, 0, 0, 106, 0, 0, 1105, 1, 99999, 8, 226, 677, 224,
                                  1002,
                                  223, 2, 223, 1006, 224, 329, 1001, 223, 1, 223, 7, 226, 226, 224, 102, 2, 223,
                                  223,
                                  1006, 224, 344, 101, 1, 223, 223, 108, 677, 677, 224, 1002, 223, 2, 223, 1006,
                                  224,
                                  359, 101, 1, 223, 223, 1107, 226, 677, 224, 1002, 223, 2, 223, 1005, 224, 374,
                                  101,
                                  1, 223, 223, 1008, 677, 226, 224, 1002, 223, 2, 223, 1005, 224, 389, 101, 1,
                                  223,
                                  223, 1007, 677, 226, 224, 1002, 223, 2, 223, 1005, 224, 404, 1001, 223, 1, 223,
                                  1107, 677, 226, 224, 1002, 223, 2, 223, 1005, 224, 419, 1001, 223, 1, 223, 108,
                                  677, 226, 224, 102, 2, 223, 223, 1006, 224, 434, 1001, 223, 1, 223, 7, 226,
                                  677,
                                  224, 102, 2, 223, 223, 1005, 224, 449, 1001, 223, 1, 223, 107, 226, 226, 224,
                                  102,
                                  2, 223, 223, 1006, 224, 464, 101, 1, 223, 223, 107, 677, 226, 224, 102, 2, 223,
                                  223, 1006, 224, 479, 101, 1, 223, 223, 1007, 677, 677, 224, 1002, 223, 2, 223,
                                  1006, 224, 494, 1001, 223, 1, 223, 1008, 226, 226, 224, 1002, 223, 2, 223,
                                  1006,
                                  224, 509, 101, 1, 223, 223, 7, 677, 226, 224, 1002, 223, 2, 223, 1006, 224,
                                  524,
                                  1001, 223, 1, 223, 1007, 226, 226, 224, 102, 2, 223, 223, 1006, 224, 539, 101,
                                  1,
                                  223, 223, 8, 677, 226, 224, 1002, 223, 2, 223, 1006, 224, 554, 101, 1, 223,
                                  223,
                                  1008, 677, 677, 224, 102, 2, 223, 223, 1006, 224, 569, 101, 1, 223, 223, 1108,
                                  677,
                                  226, 224, 102, 2, 223, 223, 1005, 224, 584, 101, 1, 223, 223, 107, 677, 677,
                                  224,
                                  102, 2, 223, 223, 1006, 224, 599, 1001, 223, 1, 223, 1108, 677, 677, 224, 1002,
                                  223, 2, 223, 1006, 224, 614, 1001, 223, 1, 223, 1107, 677, 677, 224, 1002, 223,
                                  2,
                                  223, 1005, 224, 629, 1001, 223, 1, 223, 108, 226, 226, 224, 1002, 223, 2, 223,
                                  1005, 224, 644, 101, 1, 223, 223, 8, 226, 226, 224, 1002, 223, 2, 223, 1005,
                                  224,
                                  659, 101, 1, 223, 223, 1108, 226, 677, 224, 1002, 223, 2, 223, 1006, 224, 674,
                                  101,
                                  1, 223, 223, 4, 223, 99, 226};

    struct Instruction {
        std::array<int64_t, 3> modes;
        int64_t op_code;

        static constexpr size_t MAX_OPCODE_LEN = 5;
        static constexpr std::array<int64_t, MAX_OPCODE_LEN> pow{1, 10, 100, 1000, 10000};

        static std::array<int64_t, MAX_OPCODE_LEN> getDigits(int64_t nr) {
            std::array<int64_t, MAX_OPCODE_LEN> digits{};
            size_t digit_index = 0;
            for (int64_t i = MAX_OPCODE_LEN - 1; i >= 0; i--) {
                int64_t div = nr / pow.at(i);
                digits.at(digit_index++) = div;
                nr -= div * pow.at(i);
            }
            return digits;
        }

        explicit Instruction(int64_t opcode) {
            const auto digits = getDigits(opcode);
            modes[0] = digits.at(2);
            modes[1] = digits.at(1);
            modes[2] = digits.at(0);
            op_code = digits.at(3) * 10 + digits.at(4);
            std::cout << " original = " << op_code << " arg0=" << modes[0] << " arg1=" << modes[1] << " arg2="
                      << modes[2]
                      << " op=" << op_code << std::endl;
        }
    };

    struct Image {
        std::vector<int64_t> memory;
        std::vector<int64_t> input;
        std::vector<int64_t> output;

        int64_t read(int64_t mode, int64_t argument) const {
            if (mode == 0) {
                return memory.at(argument);
            } else if (mode == 1) {
                return argument;
            } else {
                assert(false);
            }
        }

        void write(int64_t mode, int64_t argument, int64_t value) {
            assert(mode == 0);
            memory.at(argument) = value;
        }

        int64_t readStdin() {
            assert(!input.empty());
            auto value = input.front();
            input.erase(input.begin());
            return value;
        }

        void writeStdout(int64_t value) {
            output.push_back(value);
        }

        void loop() {
            size_t index = 0;
            std::array<int64_t, 3> args{};
            while (true) {
                const Instruction instruction(memory.at(index++));
                auto fetchArgs = [&](size_t how_many) {
                    for (size_t idx = 0; idx < how_many; idx++) {
                        args.at(idx) = memory.at(index++);
                    }
                    for (size_t idx = how_many; idx < args.size(); idx++) {
                        args.at(idx) = std::numeric_limits<int64_t>::min();
                    }
                };
                auto readArg = [&](size_t idx) {
                    assert(args.at(idx) != std::numeric_limits<int64_t>::min());
                    return read(instruction.modes.at(idx), args.at(idx));
                };
                auto writeArg = [&](size_t idx, int64_t value) {
                    assert(args.at(idx) != std::numeric_limits<int64_t>::min());
                    return write(instruction.modes.at(idx), args.at(idx), value);
                };

                switch (instruction.op_code) {
                    case 1:
                        fetchArgs(3);
                        writeArg(2, readArg(0) + readArg(1));
                        break;
                    case 2:
                        fetchArgs(3);
                        writeArg(2, readArg(0) * readArg(1));
                        break;
                    case 3:
                        fetchArgs(1);
                        writeArg(0, readStdin());
                        break;
                    case 4:
                        fetchArgs(1);
                        writeStdout(readArg(0));
                        break;
                    case 5: // jump-if-true
                        fetchArgs(2);
                        if (readArg(0) != 0) {
                            index = readArg(1);
                        }
                        break;
                    case 6: // jump-if-false
                        fetchArgs(2);
                        if (readArg(0) == 0) {
                            index = readArg(1);
                        }
                        break;
                    case 7: // less than
                        fetchArgs(3);
                        writeArg(2, readArg(0) < readArg(1));
                        break;
                    case 8: // equals
                        fetchArgs(3);
                        writeArg(2, readArg(0) == readArg(1));
                        break;
                    case 99:
                        return;
                }
            }
        }
    };

    std::vector<int64_t> input_day_2 = {1, 0, 0, 3, 1, 1, 2, 3, 1, 3, 4, 3, 1, 5, 0, 3, 2, 1, 6, 19, 1, 5, 19, 23, 1,
                                        23, 6, 27, 1, 5, 27, 31, 1, 31, 6, 35, 1, 9, 35, 39, 2, 10, 39, 43, 1, 43, 6,
                                        47, 2, 6, 47, 51, 1, 5, 51, 55, 1, 55, 13, 59, 1, 59, 10, 63, 2, 10, 63, 67, 1,
                                        9, 67, 71, 2, 6, 71, 75, 1, 5, 75, 79, 2, 79, 13, 83, 1, 83, 5, 87, 1, 87, 9,
                                        91, 1, 5, 91, 95, 1, 5, 95, 99, 1, 99, 13, 103, 1, 10, 103, 107, 1, 107, 9, 111,
                                        1, 6, 111, 115, 2, 115, 13, 119, 1, 10, 119, 123, 2, 123, 6, 127, 1, 5, 127,
                                        131, 1, 5, 131, 135, 1, 135, 6, 139, 2, 139, 10, 143, 2, 143, 9, 147, 1, 147, 6,
                                        151, 1, 151, 13, 155, 2, 155, 9, 159, 1, 6, 159, 163, 1, 5, 163, 167, 1, 5, 167,
                                        171, 1, 10, 171, 175, 1, 13, 175, 179, 1, 179, 2, 183, 1, 9, 183, 0, 99, 2, 14,
                                        0, 0};
}

int _5() {
    {
        Image image;
        image.memory = input_day_2;
        image.memory[1] = 12;
        image.memory[2] = 2;
        image.loop();
        ASSERT_EQ(image.memory[0], 4023471);
    }
    {
        // day5 part1
        Image image;
        image.input = {1};
        image.memory = input;
        image.loop();
        ASSERT_EQ(image.output.back(), 5346030);
    }
    {
        Image image;
        image.input = {3};
        image.memory = {3, 21, 1008, 21, 8, 20, 1005, 20, 22, 107, 8, 21, 20, 1006, 20, 31,
                        1106, 0, 36, 98, 0, 0, 1002, 21, 125, 20, 4, 20, 1105, 1, 46, 104,
                        999, 1105, 1, 46, 1101, 1000, 1, 20, 4, 20, 1105, 1, 46, 98, 99};;
        image.loop();
        ASSERT_EQ(image.output.back(), 999);
    }
    {
        Image image;
        image.input = {8};
        image.memory = {3, 21, 1008, 21, 8, 20, 1005, 20, 22, 107, 8, 21, 20, 1006, 20, 31,
                        1106, 0, 36, 98, 0, 0, 1002, 21, 125, 20, 4, 20, 1105, 1, 46, 104,
                        999, 1105, 1, 46, 1101, 1000, 1, 20, 4, 20, 1105, 1, 46, 98, 99};
        image.loop();
        ASSERT_EQ(image.output.back(), 1000);
    }
    {
        Image image;
        image.input = {9};
        image.memory = {3, 21, 1008, 21, 8, 20, 1005, 20, 22, 107, 8, 21, 20, 1006, 20, 31,
                        1106, 0, 36, 98, 0, 0, 1002, 21, 125, 20, 4, 20, 1105, 1, 46, 104,
                        999, 1105, 1, 46, 1101, 1000, 1, 20, 4, 20, 1105, 1, 46, 98, 99};
        image.loop();
        ASSERT_EQ(image.output.back(), 1001);
    }
    {
        // day5 part2
        Image image;
        image.input = {5};
        image.memory = input;
        image.loop();
        ASSERT_EQ(image.output.back(), 513116);
    }
    return 0;
}
