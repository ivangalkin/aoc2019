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
   do { __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     if (_a != _b)       \
     {                 \
       std::cout << _a << " != " << _b << std::endl; \
       assert(0);                  \
     }                  \
     }while(0)


namespace {

    using Doze = std::tuple<int64_t, std::string>;
    using ORE_source = std::tuple<int64_t, int64_t>;
    using Reaction = std::tuple<std::vector<Doze>, Doze>;
    std::vector<Reaction> input_31 = {
            {{{10, "ORE"}},         {10, "A"}},
            {{{1,  "ORE"}},         {1,  "B"}},
            {{{7,  "A"}, {1, "B"}}, {1,  "C"}},
            {{{7,  "A"}, {1, "C"}}, {1,  "D"}},
            {{{7,  "A"}, {1, "D"}}, {1,  "E"}},
            {{{7,  "A"}, {1, "E"}}, {1,  "FUEL"}},
    };
    std::vector<Reaction> input_165 = {
            {{{9, "ORE"}},                      {2, "A"}},
            {{{8, "ORE"}},                      {3, "B"}},
            {{{7, "ORE"}},                      {5, "C"}},
            {{{3, "A"},  {4, "B"}},             {1, "AB"}},
            {{{5, "B"},  {7, "C"}},             {1, "BC"}},
            {{{4, "C"},  {1, "A"}},             {1, "CA"}},
            {{{2, "AB"}, {3, "BC"}, {4, "CA"}}, {1, "FUEL"}},
    };
    std::vector<Reaction> input_13312 = {
            {{{157, "ORE"}},                                                                          {5, "NZVS"}},
            {{{165, "ORE"}},                                                                          {6, "DCFZ"}},
            {{{44,  "XJWVT"}, {5, "KHKGT"}, {1, "QDVJ"},  {29, "NZVS"}, {9, "GPVTF"}, {48, "HKGWZ"}}, {1, "FUEL"}},
            {{{12,  "HKGWZ"}, {1, "GPVTF"}, {8, "PSHF"}},                                             {9, "QDVJ"}},
            {{{179, "ORE"}},                                                                          {7, "PSHF"}},
            {{{177, "ORE"}},                                                                          {5, "HKGWZ"}},
            {{{7,   "DCFZ"},  {7, "PSHF"}},                                                           {2, "XJWVT"}},
            {{{165, "ORE"}},                                                                          {2, "GPVTF"}},
            {{{3,   "DCFZ"},  {7, "NZVS"},  {5, "HKGWZ"}, {10, "PSHF"}},                              {8, "KHKGT"}},
    };
    std::vector<Reaction> input_180697 = {
            {{{2,   "VPVL"},  {7,  "FWMGM"}, {2,  "CXFTF"}, {11, "MNCFX"}},                             {1, "STKFG"}},
            {{{17,  "NVRVD"}, {3,  "JNWZP"}},                                                           {8, "VPVL"}},
            {{{53,  "STKFG"}, {6,  "MNCFX"}, {46, "VJHF"},  {81, "HVMC"}, {68, "CXFTF"}, {25, "GNMV"}}, {1, "FUEL"}},
            {{{22,  "VJHF"},  {37, "MNCFX"}},                                                           {5, "FWMGM"}},
            {{{139, "ORE"}},                                                                            {4, "NVRVD"}},
            {{{144, "ORE"}},                                                                            {7, "JNWZP"}},
            {{{5,   "MNCFX"}, {7,  "RFSQX"}, {2,  "FWMGM"}, {2,  "VPVL"}, {19, "CXFTF"}},               {3, "HVMC"}},
            {{{5,   "VJHF"},  {7,  "MNCFX"}, {9,  "VPVL"},  {37, "CXFTF"}},                             {6, "GNMV"}},
            {{{145, "ORE"}},                                                                            {6, "MNCFX"}},
            {{{1,   "NVRVD"}},                                                                          {8, "CXFTF"}},
            {{{1,   "VJHF"},  {6,  "MNCFX"}},                                                           {4, "RFSQX"}},
            {{{176, "ORE"}},                                                                            {6, "VJHF"}},
    };
    std::vector<Reaction> input_2210736 = {
            {{{171, "ORE"}},                                                                                           {8, "CNZTR"}},
            {{{7,   "ZLQW"},  {3,  "BMBT"},  {9,  "XCVML"}, {26, "XMNCP"}, {1,  "WPTQ"},  {2,  "MZWV"}, {1, "RJRHP"}}, {4, "PLWSL"}},
            {{{114, "ORE"}},                                                                                           {4, "BHXH"}},
            {{{14,  "VRPVC"}},                                                                                         {6, "BMBT"}},
            {{{6,   "BHXH"},  {18, "KTJDG"}, {12, "WPTQ"},  {7,  "PLWSL"}, {31, "FHTLT"}, {37, "ZDVW"}},               {1, "FUEL"}},
            {{{6,   "WPTQ"},  {2,  "BMBT"},  {8,  "ZLQW"},  {18, "KTJDG"}, {1,  "XMNCP"}, {6,  "MZWV"}, {1, "RJRHP"}}, {6, "FHTLT"}},
            {{{15,  "XDBXC"}, {2,  "LTCX"},  {1,  "VRPVC"}},                                                           {6, "ZLQW"}},
            {{{13,  "WPTQ"},  {10, "LTCX"},  {3,  "RJRHP"}, {14, "XMNCP"}, {2,  "MZWV"},  {1,  "ZLQW"}},               {1, "ZDVW"}},
            {{{5,   "BMBT"}},                                                                                          {4, "WPTQ"}},
            {{{189, "ORE"}},                                                                                           {9, "KTJDG"}},
            {{{1,   "MZWV"},  {17, "XDBXC"}, {3,  "XCVML"}},                                                           {2, "XMNCP"}},
            {{{12,  "VRPVC"}, {27, "CNZTR"}},                                                                          {2, "XDBXC"}},
            {{{15,  "KTJDG"}, {12, "BHXH"}},                                                                           {5, "XCVML"}},
            {{{3,   "BHXH"},  {2,  "VRPVC"}},                                                                          {7, "MZWV"}},
            {{{121, "ORE"}},                                                                                           {7, "VRPVC"}},
            {{{7,   "XCVML"}},                                                                                         {6, "RJRHP"}},
            {{{5,   "BHXH"},  {4,  "VRPVC"}},                                                                          {5, "LTCX"}},
    };
    std::vector<Reaction> input = {
            {{{4,   "NZGF"}},                                                                                                                                      {6, "WBMZG"}},
            {{{20,  "FWMN"},  {2,  "QTMF"},  {5,  "FMVDV"}, {1,  "CVBPJ"}, {2,  "KVJK"},  {20, "XSTBX"}, {7,  "NBFS"}},                                            {5, "SHPSF"}},
            {{{7,   "LVQM"}},                                                                                                                                      {5, "NXDHX"}},
            {{{1,   "FNDMP"}, {1,  "QZJV"},  {12, "RMTG"}},                                                                                                        {7, "JBFW"}},
            {{{10,  "GKVF"},  {1,  "NXDHX"}},                                                                                                                      {8, "NZGF"}},
            {{{12,  "QZJV"}},                                                                                                                                      {8, "RSMC"}},
            {{{8,   "RWTD"}},                                                                                                                                      {7, "NBFS"}},
            {{{4,   "CZGXS"}, {25, "QTMF"},  {2,  "PHFQB"}},                                                                                                       {3, "BWQN"}},
            {{{3,   "WQZD"}},                                                                                                                                      {9, "CTZKV"}},
            {{{2,   "DCTQ"},  {18, "CTZKV"}},                                                                                                                      {4, "QLHZW"}},
            {{{31,  "QLHZW"}, {11, "FNDMP"}},                                                                                                                      {6, "WFDXN"}},
            {{{8,   "RLQC"}},                                                                                                                                      {2, "ZPJS"}},
            {{{2,   "SWSQG"}, {13, "CVBPJ"}},                                                                                                                      {9, "DWCND"}},
            {{{7,   "PBXB"},  {6,  "HKSWM"}, {4,  "BDPC"},  {4,  "KVJK"},  {2,  "ZLGKH"}, {9,  "LXFG"},  {1,  "ZPJS"}},                                            {4, "SWCWH"}},
            {{{6,   "QZJV"}},                                                                                                                                      {7, "RLQC"}},
            {{{3,   "QZJV"},  {11, "MRQHX"}, {15, "GKVF"}},                                                                                                        {4, "FMVDV"}},
            {{{3,   "NXDHX"}, {1,  "GKNQL"}},                                                                                                                      {3, "VMDS"}},
            {{{1,   "VMDS"}},                                                                                                                                      {2, "RHSQ"}},
            {{{13,  "GKNQL"}, {4,  "NXDHX"}, {2,  "GKVF"}},                                                                                                        {8, "MRQHX"}},
            {{{4,   "PVRN"}},                                                                                                                                      {2, "WBSL"}},
            {{{2,   "CVBPJ"}},                                                                                                                                     {9, "PVRN"}},
            {{{3,   "FNDMP"}},                                                                                                                                     {9, "BZKC"}},
            {{{180, "ORE"}},                                                                                                                                       {6, "FWMN"}},
            {{{13,  "DCTQ"},  {2,  "RHSQ"}},                                                                                                                       {5, "CVBPJ"}},
            {{{1,   "DWCND"}, {12, "BZKC"},  {2,  "WBRBV"}},                                                                                                       {6, "HTLZ"}},
            {{{1,   "LMGL"},  {11, "XDVL"},  {7,  "DWCND"}},                                                                                                       {5, "ZLGKH"}},
            {{{3,   "FMFTD"}},                                                                                                                                     {3, "HKSWM"}},
            {{{1,   "FNDMP"}, {5,  "RMTG"},  {3,  "QLHZW"}},                                                                                                       {9, "CZGXS"}},
            {{{7,   "DCTQ"}},                                                                                                                                      {3, "FNDMP"}},
            {{{1,   "SHPSF"}, {2,  "SWCWH"}, {40, "WFDXN"}, {67, "WBMZG"}, {53, "WBSL"},  {2,  "CQJDJ"}, {41, "BWQN"}, {12, "GMQVW"}, {48, "PDRJ"}, {42, "RSMC"}}, {1, "FUEL"}},
            {{{3,   "VMDS"},  {1,  "BHRZ"}},                                                                                                                       {9, "DCTQ"}},
            {{{22,  "DCTQ"},  {4,  "NZGF"}},                                                                                                                       {7, "RMTG"}},
            {{{29,  "RWTD"},  {3,  "FMFTD"}},                                                                                                                      {5, "LMGL"}},
            {{{12,  "WBRBV"}, {13, "PDRJ"},  {36, "RSRG"}},                                                                                                        {4, "LXFG"}},
            {{{1,   "SWSQG"}, {2,  "NLPB"}},                                                                                                                       {3, "WBRBV"}},
            {{{7,   "HTKLM"}, {8,  "CTZKV"}},                                                                                                                      {2, "RWTD"}},
            {{{4,   "BQXL"},  {1,  "FWMN"}},                                                                                                                       {9, "GKNQL"}},
            {{{4,   "WFDXN"}},                                                                                                                                     {9, "HTKLM"}},
            {{{2,   "XDVL"}},                                                                                                                                      {5, "QTMF"}},
            {{{1,   "PHFQB"}, {21, "LMGL"},  {2,  "SWSQG"}},                                                                                                       {7, "GMQVW"}},
            {{{23,  "CZGXS"}, {11, "FMVDV"}},                                                                                                                      {3, "PDRJ"}},
            {{{1,   "DWCND"}, {1,  "NPMXR"}, {1,  "RSRG"},  {1,  "JBFW"},  {12, "VXWKZ"}, {9,  "KVJK"}},                                                           {4, "CQJDJ"}},
            {{{106, "ORE"}},                                                                                                                                       {4, "BQXL"}},
            {{{4,   "PHFQB"}},                                                                                                                                     {8, "NPMXR"}},
            {{{1,   "GKNQL"}},                                                                                                                                     {8, "WQZD"}},
            {{{6,   "BDPC"}},                                                                                                                                      {2, "PHFQB"}},
            {{{1,   "DWCND"}},                                                                                                                                     {7, "PBXB"}},
            {{{1,   "RSMC"},  {1,  "PDRJ"}},                                                                                                                       {8, "SWSQG"}},
            {{{1,   "LVQM"}},                                                                                                                                      {4, "BHRZ"}},
            {{{7,   "CVBPJ"}, {1,  "SWSQG"}, {1,  "NLPB"}},                                                                                                        {2, "VXWKZ"}},
            {{{1,   "BHRZ"},  {1,  "JBFW"}},                                                                                                                       {6, "XDVL"}},
            {{{12,  "LMGL"},  {8,  "RWTD"}},                                                                                                                       {4, "XSTBX"}},
            {{{4,   "RSMC"}},                                                                                                                                      {6, "BDPC"}},
            {{{1,   "BHRZ"},  {5,  "NXDHX"}},                                                                                                                      {3, "GKVF"}},
            {{{6,   "FMVDV"}, {6,  "VXWKZ"}, {37, "CVBPJ"}},                                                                                                       {5, "KVJK"}},
            {{{7,   "NLPB"},  {3,  "HTLZ"}},                                                                                                                       {4, "RSRG"}},
            {{{1,   "PDRJ"}},                                                                                                                                      {1, "FMFTD"}},
            {{{6,   "RHSQ"},  {1,  "NZGF"}},                                                                                                                       {5, "QZJV"}},
            {{{127, "ORE"}},                                                                                                                                       {3, "LVQM"}},
            {{{3,   "RHSQ"},  {2,  "RLQC"},  {1,  "WFDXN"}},                                                                                                       {1, "NLPB"}},
    };

    std::ostream &operator<<(std::ostream &ostream, const Reaction &r) {
        auto &[source, target] = r;
        std::cout << "{";
        for (auto &s: source) {
            auto &[amount, mineral] = s;
            std::cout << amount << " " << mineral << ", ";
        }
        std::cout << " => ";
        auto &[amount, mineral] = target;
        std::cout << amount << " " << mineral << "}";
        return ostream;
    }

    std::map<std::string, int64_t> getFuelFormula(const std::vector<Reaction> &reactions) {
        std::map < std::string, int64_t > formula;
        for (auto &[sources, target]: reactions) {
            auto &[target_amount, target_mineral] = target;
            if (target_mineral == "FUEL") {
                for (auto &[source_amount, source_mineral]: sources) {
                    formula.insert_or_assign(source_mineral, source_amount);
                }
            }
        }
        return formula;
    }

    void resolveTarget(
            const std::tuple<const std::string, int64_t> &doze,
            std::map<std::string, int64_t> &formula,
            const std::vector<Reaction> &reactions,
            int64_t current_step,
            std::map<std::string, int64_t> &statistics,
            bool is_statistics_run) {


        auto it = std::find_if(reactions.begin(), reactions.end(), [&doze](auto &entry) {
            auto &[expected_mineral, expected_amount] = doze;
            auto &[sources, target] = entry;
            auto &[target_amount, target_mineral] = target;
            return target_mineral == expected_mineral;
        });

        auto matches = std::count_if(reactions.begin(), reactions.end(), [&doze](auto &entry) {
            auto &[expected_mineral, expected_amount] = doze;
            auto &[sources, target] = entry;
            auto &[target_amount, target_mineral] = target;
            return target_mineral == expected_mineral;
        });
        ASSERT_EQ(matches, 1);

        assert(it != reactions.end());

        auto &[expected_mineral, expected_amount] = doze;
        auto &[target_amount, target_mineral] = std::get<1>(*it);

        auto statistics_it = statistics.find(expected_mineral);
        bool is_correct_step = statistics_it != statistics.end() && statistics_it->second <= current_step;
        bool perform_transformation = is_statistics_run || is_correct_step;

        if (perform_transformation) {

            size_t source_int_multiplier = expected_amount / target_amount;
            if (expected_amount % target_amount) {
                source_int_multiplier++;
            }

            for (auto &[source_amount, source_mineral]: std::get<0>(*it)) {
                std::cout << source_mineral << " / " << target_mineral << " == " << source_amount << "/"
                          << target_amount
                          << " == " << (double) source_amount / (double) target_amount << std::endl;

                formula[source_mineral] += source_amount * source_int_multiplier;
            }

            if (is_statistics_run) {
                if (statistics_it != statistics.end()) {
                    std::cout << "!STATISTICS: " << expected_mineral << " postponed from " << statistics_it->second
                              << " to " << current_step << std::endl;
                }
                statistics[expected_mineral] = current_step;
            }
        } else {
            formula[expected_mineral] += expected_amount;
        }
    }

    int64_t calculate_impl(const std::vector<Reaction> &reactions, std::map<std::string, int64_t> &statistics,
                           int64_t multiplicator) {
        auto fuel_formula = getFuelFormula(reactions);
        for (auto &[source_mineral, source_amount]: fuel_formula) {
            source_amount *= multiplicator;
        }
        const auto is_statistics_run = statistics.empty();


        int64_t step = 0;
        while (fuel_formula.size() != 1) {
            std::cout << "STEP " << (step++) << std::endl;

            std::map < std::string, int64_t > fuel_formula_unwrapped;

            for (auto &[mineral, amount]: fuel_formula) {
                std::cout << "Resolve " << amount << " x " << mineral << std::endl;
                if (mineral != "ORE") {
                    resolveTarget({mineral, amount}, fuel_formula_unwrapped, reactions, step, statistics,
                                  is_statistics_run);
                }
                std::cout << "Current needs:" << std::endl;
                for (auto &[k, v]: fuel_formula_unwrapped) {
                    std::cout << k << " : " << v << std::endl;
                }
                if (is_statistics_run) {
                    std::cout << "Statistics:" << std::endl;
                    for (auto &[key, value]: statistics) {
                        std::cout << key << " -> " << value << std::endl;
                    }
                }
            }
            std::swap(fuel_formula, fuel_formula_unwrapped);
        }

        ASSERT_EQ(fuel_formula.size(), 1);

        return fuel_formula["ORE"];

    }

    int64_t calculate(const std::vector<Reaction> &reactions, int64_t expected_fuel) {
        std::map < std::string, int64_t > statistics;
        std::cout << "->STATISTICS RUN" << std::endl;
        calculate_impl(reactions, statistics, expected_fuel);
        for (auto &[key, value]: statistics) {
            std::cout << key << " -> " << value << std::endl;
        }
        std::cout << "<-STATISTICS RUN" << std::endl;
        return calculate_impl(reactions, statistics, expected_fuel);
    }

    int64_t binary_search(const std::vector<Reaction> &reactions) {
        int64_t target = 1000000000000ll;
        auto for_1_fuel = calculate(reactions, 1);
        auto min_for_trillion_ore_min = target / for_1_fuel;
        auto min_for_trillion_ore_max = min_for_trillion_ore_min * 2;

        auto range_from = min_for_trillion_ore_min;
        auto range_to = min_for_trillion_ore_max;
        int64_t required_from = calculate(reactions, range_from);
        int64_t required_to = calculate(reactions, range_to);
        int64_t range_middle;
        while (range_to - range_from > 1) {
            assert(range_to > range_from);
            range_middle = (range_to - range_from) / 2 + range_from;
            auto required_middle = calculate(reactions, range_middle);
            if (required_middle < target) {
                range_from = range_middle;
                required_from = required_middle;
            } else if (required_middle > target) {
                range_to = range_middle;
                required_to = required_middle;
            } else {
                return range_middle;
            }
        }

        return range_from;
    }

}

int _14() {
    ASSERT_EQ(calculate(input_31, 1), 31);
    ASSERT_EQ(calculate(input_165, 1), 165);
    ASSERT_EQ(calculate(input_13312, 1), 13312);
    ASSERT_EQ(calculate(input_13312, 82892753), 999999999076);
    ASSERT_EQ(binary_search(input_13312), 82892753);
    ASSERT_EQ(calculate(input_180697, 1), 180697);
    ASSERT_EQ(calculate(input_180697, 5586022), 999999895124);
    ASSERT_EQ(binary_search(input_180697), 5586022);
    ASSERT_EQ(calculate(input_2210736, 1), 2210736);
    ASSERT_EQ(calculate(input_2210736, 460664), 999998346916);
    ASSERT_EQ(binary_search(input_2210736), 460664);
    ASSERT_EQ(calculate(input, 1), 857266);
    ASSERT_EQ(binary_search(input), 2144702);
    return 0;
}
