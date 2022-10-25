#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <tuple>
#include <thread>

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

    std::vector<int64_t> input = {3, 8, 1001, 8, 10, 8, 105, 1, 0, 0, 21, 38, 55, 68, 93, 118, 199, 280, 361, 442,
                                  99999, 3, 9, 1002, 9, 2, 9, 101, 5, 9, 9, 102, 4, 9, 9, 4, 9, 99, 3, 9, 101, 3, 9, 9,
                                  1002, 9, 3, 9, 1001, 9, 4, 9, 4, 9, 99, 3, 9, 101, 4, 9, 9, 102, 3, 9, 9, 4, 9, 99, 3,
                                  9, 102, 2, 9, 9, 101, 4, 9, 9, 102, 2, 9, 9, 1001, 9, 4, 9, 102, 4, 9, 9, 4, 9, 99, 3,
                                  9, 1002, 9, 2, 9, 1001, 9, 2, 9, 1002, 9, 5, 9, 1001, 9, 2, 9, 1002, 9, 4, 9, 4, 9,
                                  99, 3, 9, 101, 1, 9, 9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 101, 1, 9, 9, 4, 9, 3,
                                  9, 101, 1, 9, 9, 4, 9, 3, 9, 101, 1, 9, 9, 4, 9, 3, 9, 101, 2, 9, 9, 4, 9, 3, 9, 1001,
                                  9, 1, 9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 1002, 9, 2,
                                  9, 4, 9, 99, 3, 9, 1001, 9, 1, 9, 4, 9, 3, 9, 1001, 9, 2, 9, 4, 9, 3, 9, 1002, 9, 2,
                                  9, 4, 9, 3, 9, 101, 2, 9, 9, 4, 9, 3, 9, 1001, 9, 2, 9, 4, 9, 3, 9, 1001, 9, 1, 9, 4,
                                  9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 1001, 9, 1, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3,
                                  9, 102, 2, 9, 9, 4, 9, 99, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 1001, 9, 1, 9, 4, 9, 3, 9,
                                  102, 2, 9, 9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 101, 1, 9, 9, 4, 9, 3, 9, 1001, 9,
                                  1, 9, 4, 9, 3, 9, 101, 2, 9, 9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 101, 2, 9, 9, 4,
                                  9, 3, 9, 1001, 9, 2, 9, 4, 9, 99, 3, 9, 1001, 9, 2, 9, 4, 9, 3, 9, 1001, 9, 2, 9, 4,
                                  9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 101, 1, 9, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3,
                                  9, 1002, 9, 2, 9, 4, 9, 3, 9, 1001, 9, 2, 9, 4, 9, 3, 9, 1001, 9, 2, 9, 4, 9, 3, 9,
                                  101, 1, 9, 9, 4, 9, 3, 9, 1001, 9, 1, 9, 4, 9, 99, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9,
                                  1001, 9, 1, 9, 4, 9, 3, 9, 1001, 9, 1, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 1002,
                                  9, 2, 9, 4, 9, 3, 9, 1001, 9, 2, 9, 4, 9, 3, 9, 1002, 9, 2, 9, 4, 9, 3, 9, 102, 2, 9,
                                  9, 4, 9, 3, 9, 102, 2, 9, 9, 4, 9, 3, 9, 101, 2, 9, 9, 4, 9, 99};

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
        }
    };

    struct Image {
        std::vector<int64_t> memory;
        std::vector<int64_t> input;
        std::vector<int64_t> output;
        std::mutex input_mtx;
        bool block_on_missing_input = false;

        std::function<void(int64_t)> on_output = [this](int64_t value) {
            output.push_back(value);
        };

        std::function<std::optional<int64_t>()> on_input = [this]() {
            const std::lock_guard<std::mutex> lock(input_mtx);
            if (block_on_missing_input) {
                if (input.empty()) {
                    return std::optional<int64_t>{};
                }
            }
            assert(!input.empty());
            auto value = input.front();
            input.erase(input.begin());
            return std::make_optional(value);
        };

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
                        if (auto maybe_input = on_input()) {
                            writeArg(0, *maybe_input);
                        } else {
                            // block on missing input
                            index -= 2;
                        }
                        break;
                    case 4:
                        fetchArgs(1);
                        on_output(readArg(0));
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

    int64_t calculate_sequence_part1(std::array<int64_t, 5> sequence) {
        int64_t signal = 0;
        for (auto i: sequence) {
            Image image;
            image.input = {i, signal};
            image.memory = input;
            image.loop();
            signal = image.output.back();
        }
        return signal;
    }

    int64_t get_max_signal_part1() {
        std::array<int64_t, 5> sequence = {0, 1, 2, 3, 4};
        std::sort(sequence.begin(), sequence.end());
        int64_t signal = std::numeric_limits<int64_t>::min();
        do {
            signal = std::max(signal, calculate_sequence_part1(sequence));
        } while (std::next_permutation(sequence.begin(), sequence.end()));
        return signal;
    }

    int64_t calculate_sequence_part2(std::array<int64_t, 5> sequence) {

        std::array<Image, 5> images{};

        for (size_t i = 0; i < images.size(); i++) {
            images[i].block_on_missing_input = true;
            images[i].memory = input;
            images[i].input = {sequence[i]};
        }
        images[0].input.push_back(0);
        images[0].on_output = [&](int64_t value) {
            const std::lock_guard<std::mutex> lock(images[1].input_mtx);
            images[1].input.push_back(value);
        };
        images[1].on_output = [&](int64_t value) {
            const std::lock_guard<std::mutex> lock(images[2].input_mtx);
            images[2].input.push_back(value);
        };
        images[2].on_output = [&](int64_t value) {
            const std::lock_guard<std::mutex> lock(images[3].input_mtx);
            images[3].input.push_back(value);
        };
        images[3].on_output = [&](int64_t value) {
            const std::lock_guard<std::mutex> lock(images[4].input_mtx);
            images[4].input.push_back(value);
        };
        images[4].on_output = [&](int64_t value) {
            const std::lock_guard<std::mutex> lock(images[0].input_mtx);
            images[0].input.push_back(value);
        };

        std::vector<std::thread> workers;
        for (size_t i = 0; i < images.size(); i++) {
            workers.emplace_back([&images, i]() { images[i].loop(); });
        }
        for (size_t i = 0; i < images.size(); i++) {
            workers[i].join();
        }

        for (size_t i = 0; i < images.size(); i++) {
            if (i == 0) {
                ASSERT_EQ(images[i].input.size(), 1);
            } else {
                ASSERT_EQ(images[i].input.size(), 0);
            }
        }
        return images[0].input.at(0);
    }

    int64_t get_max_signal_part2() {
        std::array<int64_t, 5> sequence = {5, 6, 7, 8, 9};
        std::sort(sequence.begin(), sequence.end());
        int64_t signal = std::numeric_limits<int64_t>::min();
        do {
            signal = std::max(signal, calculate_sequence_part2(sequence));
        } while (std::next_permutation(sequence.begin(), sequence.end()));
        return signal;
    }
}

int _7() {
    std::cout << get_max_signal_part1() << std::endl;
    std::cout << get_max_signal_part2() << std::endl;

    return 0;
}
