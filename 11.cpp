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
    std::vector<int64_t> input = {3, 8, 1005, 8, 319, 1106, 0, 11, 0, 0, 0, 104, 1, 104, 0, 3, 8, 1002, 8, -1, 10, 101,
                                  1, 10, 10, 4, 10, 108, 0, 8, 10, 4, 10, 1002, 8, 1, 28, 3, 8, 1002, 8, -1, 10, 1001,
                                  10, 1, 10, 4, 10, 1008, 8, 1, 10, 4, 10, 102, 1, 8, 51, 2, 1008, 18, 10, 3, 8, 1002,
                                  8, -1, 10, 1001, 10, 1, 10, 4, 10, 1008, 8, 1, 10, 4, 10, 101, 0, 8, 77, 1, 1006, 8,
                                  10, 1006, 0, 88, 3, 8, 1002, 8, -1, 10, 1001, 10, 1, 10, 4, 10, 1008, 8, 1, 10, 4, 10,
                                  1002, 8, 1, 106, 1006, 0, 47, 2, 5, 0, 10, 3, 8, 102, -1, 8, 10, 101, 1, 10, 10, 4,
                                  10, 1008, 8, 0, 10, 4, 10, 101, 0, 8, 135, 2, 105, 3, 10, 2, 1101, 6, 10, 3, 8, 102,
                                  -1, 8, 10, 101, 1, 10, 10, 4, 10, 1008, 8, 0, 10, 4, 10, 1002, 8, 1, 165, 3, 8, 102,
                                  -1, 8, 10, 101, 1, 10, 10, 4, 10, 108, 0, 8, 10, 4, 10, 1002, 8, 1, 186, 1, 1009, 11,
                                  10, 1, 9, 3, 10, 2, 1003, 10, 10, 1, 107, 11, 10, 3, 8, 1002, 8, -1, 10, 101, 1, 10,
                                  10, 4, 10, 1008, 8, 1, 10, 4, 10, 1002, 8, 1, 225, 1006, 0, 25, 1, 1009, 14, 10, 1,
                                  1008, 3, 10, 3, 8, 102, -1, 8, 10, 101, 1, 10, 10, 4, 10, 108, 1, 8, 10, 4, 10, 1002,
                                  8, 1, 257, 1, 1006, 2, 10, 3, 8, 1002, 8, -1, 10, 1001, 10, 1, 10, 4, 10, 1008, 8, 0,
                                  10, 4, 10, 101, 0, 8, 284, 2, 1004, 7, 10, 1006, 0, 41, 2, 1106, 17, 10, 1, 104, 3,
                                  10, 101, 1, 9, 9, 1007, 9, 919, 10, 1005, 10, 15, 99, 109, 641, 104, 0, 104, 1, 21101,
                                  0, 937108545948, 1, 21102, 1, 336, 0, 1105, 1, 440, 21102, 1, 386577203612, 1, 21102,
                                  347, 1, 0, 1105, 1, 440, 3, 10, 104, 0, 104, 1, 3, 10, 104, 0, 104, 0, 3, 10, 104, 0,
                                  104, 1, 3, 10, 104, 0, 104, 1, 3, 10, 104, 0, 104, 0, 3, 10, 104, 0, 104, 1, 21102, 1,
                                  21478178819, 1, 21102, 1, 394, 0, 1106, 0, 440, 21102, 21477985447, 1, 1, 21101, 405,
                                  0, 0, 1105, 1, 440, 3, 10, 104, 0, 104, 0, 3, 10, 104, 0, 104, 0, 21101, 984458351460,
                                  0, 1, 21101, 428, 0, 0, 1106, 0, 440, 21101, 709048034148, 0, 1, 21102, 439, 1, 0,
                                  1106, 0, 440, 99, 109, 2, 21201, -1, 0, 1, 21101, 0, 40, 2, 21101, 471, 0, 3, 21102,
                                  461, 1, 0, 1105, 1, 504, 109, -2, 2106, 0, 0, 0, 1, 0, 0, 1, 109, 2, 3, 10, 204, -1,
                                  1001, 466, 467, 482, 4, 0, 1001, 466, 1, 466, 108, 4, 466, 10, 1006, 10, 498, 1101, 0,
                                  0, 466, 109, -2, 2105, 1, 0, 0, 109, 4, 2101, 0, -1, 503, 1207, -3, 0, 10, 1006, 10,
                                  521, 21101, 0, 0, -3, 22102, 1, -3, 1, 21201, -2, 0, 2, 21102, 1, 1, 3, 21102, 540, 1,
                                  0, 1106, 0, 545, 109, -4, 2105, 1, 0, 109, 5, 1207, -3, 1, 10, 1006, 10, 568, 2207,
                                  -4, -2, 10, 1006, 10, 568, 22101, 0, -4, -4, 1105, 1, 636, 21201, -4, 0, 1, 21201, -3,
                                  -1, 2, 21202, -2, 2, 3, 21102, 587, 1, 0, 1106, 0, 545, 21202, 1, 1, -4, 21102, 1, 1,
                                  -1, 2207, -4, -2, 10, 1006, 10, 606, 21101, 0, 0, -1, 22202, -2, -1, -2, 2107, 0, -3,
                                  10, 1006, 10, 628, 22101, 0, -1, 1, 21101, 628, 0, 0, 105, 1, 503, 21202, -2, -1, -2,
                                  22201, -4, -2, -4, 109, -5, 2105, 1, 0};

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
        int64_t relative_base = 0;

        std::function<void(int64_t)> on_output = [this](int64_t value) {
            output.push_back(value);
        };

        void grow_memory(size_t times) {
            auto old_size = memory.size();
            memory.resize(old_size * times);
            std::fill(std::next(memory.begin(), old_size), memory.end(), 0);
        }

        void print_output() {
            std::cout << "<output size=" << output.size() << ">" << std::endl;
            for (auto o: output) {
                std::cout << o << " ";
            }
            std::cout << std::endl << "</output>" << std::endl;
        }

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
            } else if (mode == 2) {
                int64_t offset = relative_base + argument;
                assert(offset >= 0);
                return memory.at(offset);
            } else {
                assert(false);
            }
        }

        void write(int64_t mode, int64_t argument, int64_t value) {
            if (mode == 0) {
                memory.at(argument) = value;
            } else if (mode == 2) {
                int64_t offset = relative_base + argument;
                assert(offset >= 0);
                memory.at(offset) = value;
            } else {
                assert(false);
            }
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
                    case 9:
                        fetchArgs(1);
                        relative_base += readArg(0);
                        break;
                    case 99:
                        return;
                }
            }
        }
    };

    enum Orientation {
        N, O, S, W
    };

    Orientation apply_rotation(Orientation o, int64_t r) {
        switch (o) {
            case N:
                return (r == 0) ? W : O;
            case O:
                return (r == 0) ? N : S;
            case S:
                return (r == 0) ? O : W;
            case W:
                return (r == 0) ? S : N;
        }
    }

    std::tuple<int64_t, int64_t> do_step(std::tuple<int64_t, int64_t> pos, Orientation o) {
        auto [x, y] = pos;
        switch (o) {
            case N:
                y++;
                break;
            case O:
                x++;
                break;
            case S:
                --y;
                break;
            case W:
                --x;
                break;
        }
        return {x, y};
    }

    void print_field(std::map<std::tuple<int64_t, int64_t>, int64_t> field) {
        int64_t min_x = std::numeric_limits<int64_t>::max();
        int64_t min_y = std::numeric_limits<int64_t>::max();
        int64_t max_x = std::numeric_limits<int64_t>::min();
        int64_t max_y = std::numeric_limits<int64_t>::min();
        for (auto [key, value]: field) {
            auto [x, y] = key;
            min_x = std::min(min_x, x);
            min_y = std::min(min_y, y);
            max_x = std::max(max_x, x);
            max_y = std::max(max_y, x);
        }
        for (auto x = min_x; x <= max_x; x++) {
            for (auto y = min_y; y <= max_y; y++) {
                auto it = field.find({x, y});
                int64_t color = (it == field.end()) ? 0 : it->second;
                std::cout << ((color == 0) ? ' ' : '#');
            }
            std::cout << std::endl;
        }
    }

    void paint_field(std::map < std::tuple<int64_t, int64_t>, int64_t > &field) {
        std::tuple<int64_t, int64_t> pos = {0, 0};
        int64_t output_counter = 0;
        Orientation current_orientation = N;

        Image image;
        image.memory = input;
        image.grow_memory(10);
        image.on_output = [&](int64_t value) {
            if (output_counter % 2 == 0) {
                field.insert_or_assign(pos, value);
            } else {
                current_orientation = apply_rotation(current_orientation, value);
                pos = do_step(pos, current_orientation);
            }
            output_counter++;
        };
        image.on_input = [&]() {
            auto it = field.find(pos);
            int64_t color = (it == field.end()) ? 0 : it->second;
            return std::make_optional(color);
        };
        image.loop();
    }

}


int _11() {
    // part 1
    {
        std::map < std::tuple<int64_t, int64_t>, int64_t > field;
        paint_field(field);
        std::cout << field.size() << std::endl;
        print_field(field);

    }
    // part 2
    {
        std::map < std::tuple<int64_t, int64_t>, int64_t > field;
        std::tuple<int64_t, int64_t> pos = {0, 0};
        field.insert_or_assign(pos, 1);
        paint_field(field);
        std::cout << field.size() << std::endl;
        print_field(field);
    }

    return 0;
}
