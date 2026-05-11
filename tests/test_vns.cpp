#include <iostream>
#include <cassert>
#include <memory>
#include <sstream>

#include "problem/MaxOnesProblem.hpp"
#include "solution/BitArraySolution.hpp"
#include "algorithm/OutputControl.hpp"
#include "algorithm/metaheuristic/FinishControl.hpp"
#include "algorithm/metaheuristic/AdditionalStatisticsControl.hpp"
#include "algorithm/metaheuristic/variable_neighborhood_search/VnsOptimizer.hpp"
#include "algorithm/metaheuristic/variable_neighborhood_search/VnsShakingSupport.hpp"
#include "algorithm/metaheuristic/variable_neighborhood_search/VnsLocalSearchSupport.hpp"
#include "algorithm/metaheuristic/variable_neighborhood_search/VnsShakingSupportIdle.hpp"
#include "algorithm/metaheuristic/variable_neighborhood_search/VnsLocalSearchSupportIdle.hpp"
#include "algorithm/metaheuristic/variable_neighborhood_search/VnsShakingSupportStandardBitArray.hpp"
#include "algorithm/metaheuristic/variable_neighborhood_search/VnsLocalSearchSupportStandardFirstImprovementBitArray.hpp"
#include "algorithm/metaheuristic/variable_neighborhood_search/VnsLocalSearchSupportStandardBestImprovementBitArray.hpp"
#include "utils/ComplexCounterUniformAscending.hpp"

void test_complex_counter() {
    std::cout << "  Testing ComplexCounterUniformAscending..." << std::flush;
    {
        uo::ComplexCounterUniformAscending cc(3, 5);
        bool ok = cc.reset();
        assert(ok == true);
        std::vector<int> state = cc.current_state();
        assert(state.size() == 3);
        assert(state[0] == 0);
        assert(state[1] == 1);
        assert(state[2] == 2);

        ok = cc.progress();
        assert(ok == true);
        state = cc.current_state();
        assert(state[0] == 0);
        assert(state[1] == 1);
        assert(state[2] == 3);

        for (int i = 0; i < 5; ++i) cc.progress();
        state = cc.current_state();

        try {
            uo::ComplexCounterUniformAscending bad(6, 3);
            assert(false);
        } catch (const std::invalid_argument&) {
            // expected
        }

        std::cout << " PASS" << std::endl;
    }
}

void test_vns_shaking_support_idle() {
    std::cout << "  Testing VnsShakingSupportIdle..." << std::flush;
    {
        auto shs = std::make_unique<uo::VnsShakingSupportIdle>(5);
        assert(shs->dimension() == 5);
        assert(shs->to_string() == "VnsShakingSupportIdle");

        auto cloned = shs->clone();
        assert(cloned->dimension() == 5);

        std::cout << " PASS" << std::endl;
    }
}

void test_vns_ls_support_idle() {
    std::cout << "  Testing VnsLocalSearchSupportIdle..." << std::flush;
    {
        auto ls = std::make_unique<uo::VnsLocalSearchSupportIdle>(5);
        assert(ls->dimension() == 5);
        assert(ls->to_string() == "VnsLocalSearchSupportIdle");

        auto cloned = ls->clone();
        assert(cloned->dimension() == 5);

        std::cout << " PASS" << std::endl;
    }
}

void test_vns_shaking_support_standard_bit_array() {
    std::cout << "  Testing VnsShakingSupportStandardBitArray..." << std::flush;
    {
        auto shs = std::make_unique<uo::VnsShakingSupportStandardBitArray>(5);
        assert(shs->dimension() == 5);
        assert(shs->to_string() == "VnsShakingSupportStandardBitArray");

        auto cloned = shs->clone();
        assert(cloned->dimension() == 5);

        std::cout << " PASS" << std::endl;
    }
}

void test_vns_ls_support_fi_bit_array() {
    std::cout << "  Testing VnsLocalSearchSupportStandardFirstImprovementBitArray..." << std::flush;
    {
        auto ls = std::make_unique<uo::VnsLocalSearchSupportStandardFirstImprovementBitArray>(5);
        assert(ls->dimension() == 5);
        assert(ls->to_string() == "VnsLocalSearchSupportStandardFirstImprovementBitArray");

        auto cloned = ls->clone();
        assert(cloned->dimension() == 5);

        std::cout << " PASS" << std::endl;
    }
}

void test_vns_ls_support_bi_bit_array() {
    std::cout << "  Testing VnsLocalSearchSupportStandardBestImprovementBitArray..." << std::flush;
    {
        auto ls = std::make_unique<uo::VnsLocalSearchSupportStandardBestImprovementBitArray>(5);
        assert(ls->dimension() == 5);
        assert(ls->to_string() == "VnsLocalSearchSupportStandardBestImprovementBitArray");

        auto cloned = ls->clone();
        assert(cloned->dimension() == 5);

        std::cout << " PASS" << std::endl;
    }
}

void test_vns_optimizer_construction() {
    std::cout << "  Testing VnsOptimizer construction..." << std::flush;
    {
        auto fc = std::make_unique<uo::FinishControl>("evaluations", 100, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(6);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto shs = std::make_unique<uo::VnsShakingSupportIdle>(6);
        auto ls = std::make_unique<uo::VnsLocalSearchSupportIdle>(6);

        auto vns = std::make_unique<uo::VnsOptimizer>(
            std::move(shs), std::move(ls), 1, 3,
            std::move(fc), std::move(problem), std::move(sol_tmpl));

        assert(vns->name() == "vns");
        assert(vns->k_min() == 1);
        assert(vns->k_max() == 3);
        assert(vns->vns_shaking_support().to_string() == "VnsShakingSupportIdle");
        assert(vns->vns_ls_support().to_string() == "VnsLocalSearchSupportIdle");

        std::cout << " PASS" << std::endl;
    }
}

void test_vns_optimizer_init() {
    std::cout << "  Testing VnsOptimizer init..." << std::flush;
    {
        auto fc = std::make_unique<uo::FinishControl>("evaluations", 100, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(8);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto shs = std::make_unique<uo::VnsShakingSupportStandardBitArray>(8);
        auto ls = std::make_unique<uo::VnsLocalSearchSupportStandardFirstImprovementBitArray>(8);

        auto vns = std::make_unique<uo::VnsOptimizer>(
            std::move(shs), std::move(ls), 1, 3,
            std::move(fc), std::move(problem), std::move(sol_tmpl), nullptr, 42);

        vns->init();
        assert(vns->evaluation() >= 1);
        assert(vns->current_solution() != nullptr);

        std::cout << " PASS" << std::endl;
    }
}

void test_vns_optimizer_basic_optimize() {
    std::cout << "  Testing VnsOptimizer basic optimize..." << std::flush;
    {
        auto fc = std::make_unique<uo::FinishControl>("evaluations", 50, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(10);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto shs = std::make_unique<uo::VnsShakingSupportStandardBitArray>(10);
        auto ls = std::make_unique<uo::VnsLocalSearchSupportStandardFirstImprovementBitArray>(10);

        auto vns = std::make_unique<uo::VnsOptimizer>(
            std::move(shs), std::move(ls), 1, 2,
            std::move(fc), std::move(problem), std::move(sol_tmpl), nullptr, 123);

        auto result = vns->optimize();
        assert(vns->evaluation() > 0);
        assert(vns->iteration() > 0);

        std::cout << " PASS" << std::endl;
        if (result) {
            std::cout << "    Best: " << result->to_string() << std::endl;
        }
    }
}

int main() {
    std::cout << "=== VNS C++ Tests ===" << std::endl;

    test_complex_counter();
    test_vns_shaking_support_idle();
    test_vns_ls_support_idle();
    test_vns_shaking_support_standard_bit_array();
    test_vns_ls_support_fi_bit_array();
    test_vns_ls_support_bi_bit_array();
    test_vns_optimizer_construction();
    test_vns_optimizer_init();
    test_vns_optimizer_basic_optimize();

    std::cout << "\nAll VNS tests passed!" << std::endl;
    return 0;
}
