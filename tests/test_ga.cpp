#include <iostream>
#include <cassert>
#include <memory>
#include <sstream>
#include <cmath>

#include "problem/MaxOnesProblem.hpp"
#include "solution/BitArraySolution.hpp"
#include "algorithm/OutputControl.hpp"
#include "algorithm/metaheuristic/FinishControl.hpp"
#include "algorithm/metaheuristic/AdditionalStatisticsControl.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaSelection.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaSelectionIdle.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaSelectionRoulette.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaCrossoverSupport.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaCrossoverSupportIdle.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaCrossoverSupportIdleBitArray.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaCrossoverSupportOnePointBitArray.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaMutationSupport.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaMutationSupportIdle.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaMutationSupportIdleBitArray.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaMutationSupportOnePointBitArray.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaOptimizer.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaOptimizerSteadyState.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaOptimizerGenerational.hpp"

// ============================================================================
// GaSelection tests
// ============================================================================

void test_ga_selection_idle() {
    std::cout << "  Testing GaSelectionIdle..." << std::flush;
    {
        auto sel = std::make_unique<uo::GaSelectionIdle>();
        assert(sel->to_string().find("GaSelectionIdle") != std::string::npos);

        auto cloned = sel->clone();
        assert(cloned != nullptr);
        assert(cloned->to_string() == sel->to_string());

        std::cout << " PASS" << std::endl;
    }
}

void test_ga_selection_roulette() {
    std::cout << "  Testing GaSelectionRoulette..." << std::flush;
    {
        auto sel = std::make_unique<uo::GaSelectionRoulette>();
        assert(sel->to_string().find("GaSelectionRoulette") != std::string::npos);

        auto cloned = sel->clone();
        assert(cloned != nullptr);
        assert(cloned->to_string() == sel->to_string());

        std::cout << " PASS" << std::endl;
    }
}

// ============================================================================
// GaCrossoverSupport tests
// ============================================================================

void test_ga_crossover_idle() {
    std::cout << "  Testing GaCrossoverSupportIdle..." << std::flush;
    {
        auto co = std::make_unique<uo::GaCrossoverSupportIdle>();
        assert(co->to_string().find("GaCrossoverSupportIdle") != std::string::npos);

        auto cloned = co->clone();
        assert(cloned != nullptr);
        assert(cloned->to_string() == co->to_string());

        std::cout << " PASS" << std::endl;
    }
}

void test_ga_crossover_idle_bit_array() {
    std::cout << "  Testing GaCrossoverSupportIdleBitArray..." << std::flush;
    {
        auto co = std::make_unique<uo::GaCrossoverSupportIdleBitArray>();
        assert(co->to_string().find("GaCrossoverSupportIdleBitArray") != std::string::npos);

        auto cloned = co->clone();
        assert(cloned != nullptr);
        assert(cloned->to_string() == co->to_string());

        std::cout << " PASS" << std::endl;
    }
}

void test_ga_crossover_one_point_bit_array() {
    std::cout << "  Testing GaCrossoverSupportOnePointBitArray..." << std::flush;
    {
        auto co = std::make_unique<uo::GaCrossoverSupportOnePointBitArray>(0.8);
        assert(std::abs(co->crossover_probability() - 0.8) < 1e-9);
        assert(co->to_string().find("GaCrossoverSupportOnePointBitArray") != std::string::npos);

        auto cloned = co->clone();
        assert(cloned != nullptr);
        assert(cloned->to_string() == co->to_string());
        auto* derived = dynamic_cast<uo::GaCrossoverSupportOnePointBitArray*>(cloned.get());
        assert(derived != nullptr);
        assert(std::abs(derived->crossover_probability() - 0.8) < 1e-9);

        std::cout << " PASS" << std::endl;
    }
}

// ============================================================================
// GaMutationSupport tests
// ============================================================================

void test_ga_mutation_idle() {
    std::cout << "  Testing GaMutationSupportIdle..." << std::flush;
    {
        auto mut = std::make_unique<uo::GaMutationSupportIdle>();
        assert(mut->to_string().find("GaMutationSupportIdle") != std::string::npos);

        auto cloned = mut->clone();
        assert(cloned != nullptr);
        assert(cloned->to_string() == mut->to_string());

        std::cout << " PASS" << std::endl;
    }
}

void test_ga_mutation_idle_bit_array() {
    std::cout << "  Testing GaMutationSupportIdleBitArray..." << std::flush;
    {
        auto mut = std::make_unique<uo::GaMutationSupportIdleBitArray>();
        assert(mut->to_string().find("GaMutationSupportIdleBitArray") != std::string::npos);

        auto cloned = mut->clone();
        assert(cloned != nullptr);
        assert(cloned->to_string() == mut->to_string());

        std::cout << " PASS" << std::endl;
    }
}

void test_ga_mutation_one_point_bit_array() {
    std::cout << "  Testing GaMutationSupportOnePointBitArray..." << std::flush;
    {
        auto mut = std::make_unique<uo::GaMutationSupportOnePointBitArray>(0.1);
        assert(std::abs(mut->mutation_probability() - 0.1) < 1e-9);
        assert(mut->to_string().find("GaMutationSupportOnePointBitArray") != std::string::npos);

        auto cloned = mut->clone();
        assert(cloned != nullptr);
        assert(cloned->to_string() == mut->to_string());
        auto* derived = dynamic_cast<uo::GaMutationSupportOnePointBitArray*>(cloned.get());
        assert(derived != nullptr);
        assert(std::abs(derived->mutation_probability() - 0.1) < 1e-9);

        std::cout << " PASS" << std::endl;
    }
}

// ============================================================================
// GaOptimizerSteadyState tests
// ============================================================================

void test_ga_optimizer_steady_state_construction() {
    std::cout << "  Testing GaOptimizerSteadyState construction..." << std::flush;
    {
        uo::FinishControl fc("evaluations", 100, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(8);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto selection = std::make_unique<uo::GaSelectionRoulette>();
        auto crossover = std::make_unique<uo::GaCrossoverSupportOnePointBitArray>(0.8);
        auto mutation = std::make_unique<uo::GaMutationSupportOnePointBitArray>(0.05);

        auto ga = std::make_unique<uo::GaOptimizerSteadyState>(
            std::move(crossover), std::move(mutation), std::move(selection),
            20, 2, std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        assert(ga->name() == "ga");
        assert(ga->population_size() == 20);
        assert(ga->elite_count() == 2);

        std::cout << " PASS" << std::endl;
    }
}

void test_ga_optimizer_steady_state_init() {
    std::cout << "  Testing GaOptimizerSteadyState init..." << std::flush;
    {
        uo::FinishControl fc("evaluations", 200, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(6);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto selection = std::make_unique<uo::GaSelectionRoulette>();
        auto crossover = std::make_unique<uo::GaCrossoverSupportOnePointBitArray>(0.8);
        auto mutation = std::make_unique<uo::GaMutationSupportOnePointBitArray>(0.05);

        auto ga = std::make_unique<uo::GaOptimizerSteadyState>(
            std::move(crossover), std::move(mutation), std::move(selection),
            10, 2, std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        ga->init();
        assert(ga->evaluation() >= 10); // 10 individuals evaluated
        assert(!ga->current_population().empty());
        assert(ga->current_population().size() == 10);
        assert(ga->best_solution() != nullptr);

        std::cout << " PASS" << std::endl;
    }
}

void test_ga_optimizer_steady_state_basic_optimize() {
    std::cout << "  Testing GaOptimizerSteadyState basic optimize..." << std::flush;
    {
        uo::FinishControl fc("evaluations", 100, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(10);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto selection = std::make_unique<uo::GaSelectionRoulette>();
        auto crossover = std::make_unique<uo::GaCrossoverSupportOnePointBitArray>(0.8);
        auto mutation = std::make_unique<uo::GaMutationSupportOnePointBitArray>(0.05);

        auto ga = std::make_unique<uo::GaOptimizerSteadyState>(
            std::move(crossover), std::move(mutation), std::move(selection),
            10, 1, std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        auto result = ga->optimize();
        assert(result != nullptr);
        assert(ga->evaluation() > 0);
        assert(ga->iteration() > 0);

        std::cout << " PASS" << std::endl;
        if (result) {
            std::cout << "    Best: " << result->to_string() << std::endl;
        }
    }
}

void test_ga_optimizer_steady_state_clone() {
    std::cout << "  Testing GaOptimizerSteadyState clone..." << std::flush;
    {
        uo::FinishControl fc("evaluations", 100, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(6);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto selection = std::make_unique<uo::GaSelectionRoulette>();
        auto crossover = std::make_unique<uo::GaCrossoverSupportOnePointBitArray>(0.8);
        auto mutation = std::make_unique<uo::GaMutationSupportOnePointBitArray>(0.05);

        auto ga = std::make_unique<uo::GaOptimizerSteadyState>(
            std::move(crossover), std::move(mutation), std::move(selection),
            10, 2, std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        auto cloned = ga->clone();
        assert(cloned != nullptr);
        assert(cloned->name() == "ga");

        std::cout << " PASS" << std::endl;
    }
}

void test_ga_optimizer_steady_state_to_string() {
    std::cout << "  Testing GaOptimizerSteadyState to_string..." << std::flush;
    {
        uo::FinishControl fc("evaluations", 100, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(6);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto selection = std::make_unique<uo::GaSelectionRoulette>();
        auto crossover = std::make_unique<uo::GaCrossoverSupportOnePointBitArray>(0.8);
        auto mutation = std::make_unique<uo::GaMutationSupportOnePointBitArray>(0.05);

        auto ga = std::make_unique<uo::GaOptimizerSteadyState>(
            std::move(crossover), std::move(mutation), std::move(selection),
            10, 2, std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        std::string s = ga->to_string();
        assert(s.find("GaOptimizerSteadyState") != std::string::npos);
        assert(s.find("GaOptimizer") != std::string::npos);
        assert(s.find("GaCrossoverSupportOnePointBitArray") != std::string::npos);
        assert(s.find("GaMutationSupportOnePointBitArray") != std::string::npos);
        assert(s.find("GaSelectionRoulette") != std::string::npos);

        std::cout << " PASS" << std::endl;
    }
}

// ============================================================================
// GaOptimizerGenerational tests
// ============================================================================

void test_ga_optimizer_generational_construction() {
    std::cout << "  Testing GaOptimizerGenerational construction..." << std::flush;
    {
        uo::FinishControl fc("evaluations", 100, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(8);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto selection = std::make_unique<uo::GaSelectionRoulette>();
        auto crossover = std::make_unique<uo::GaCrossoverSupportOnePointBitArray>(0.7);
        auto mutation = std::make_unique<uo::GaMutationSupportOnePointBitArray>(0.1);

        auto ga = std::make_unique<uo::GaOptimizerGenerational>(
            std::move(crossover), std::move(mutation), std::move(selection),
            15, 3, std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        assert(ga->name() == "ga");
        assert(ga->population_size() == 15);
        assert(ga->elite_count() == 3);

        std::cout << " PASS" << std::endl;
    }
}

void test_ga_optimizer_generational_init() {
    std::cout << "  Testing GaOptimizerGenerational init..." << std::flush;
    {
        uo::FinishControl fc("evaluations", 200, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(6);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto selection = std::make_unique<uo::GaSelectionRoulette>();
        auto crossover = std::make_unique<uo::GaCrossoverSupportOnePointBitArray>(0.8);
        auto mutation = std::make_unique<uo::GaMutationSupportOnePointBitArray>(0.05);

        auto ga = std::make_unique<uo::GaOptimizerGenerational>(
            std::move(crossover), std::move(mutation), std::move(selection),
            10, 2, std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        ga->init();
        assert(ga->evaluation() >= 10);
        assert(ga->current_population().size() == 10);
        assert(ga->best_solution() != nullptr);

        std::cout << " PASS" << std::endl;
    }
}

void test_ga_optimizer_generational_basic_optimize() {
    std::cout << "  Testing GaOptimizerGenerational basic optimize..." << std::flush;
    {
        uo::FinishControl fc("evaluations", 100, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(10);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto selection = std::make_unique<uo::GaSelectionRoulette>();
        auto crossover = std::make_unique<uo::GaCrossoverSupportOnePointBitArray>(0.8);
        auto mutation = std::make_unique<uo::GaMutationSupportOnePointBitArray>(0.05);

        auto ga = std::make_unique<uo::GaOptimizerGenerational>(
            std::move(crossover), std::move(mutation), std::move(selection),
            10, 1, std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        auto result = ga->optimize();
        assert(result != nullptr);
        assert(ga->evaluation() > 0);
        assert(ga->iteration() > 0);

        std::cout << " PASS" << std::endl;
        if (result) {
            std::cout << "    Best: " << result->to_string() << std::endl;
        }
    }
}

void test_ga_optimizer_generational_clone() {
    std::cout << "  Testing GaOptimizerGenerational clone..." << std::flush;
    {
        uo::FinishControl fc("evaluations", 100, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(6);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto selection = std::make_unique<uo::GaSelectionRoulette>();
        auto crossover = std::make_unique<uo::GaCrossoverSupportOnePointBitArray>(0.8);
        auto mutation = std::make_unique<uo::GaMutationSupportOnePointBitArray>(0.05);

        auto ga = std::make_unique<uo::GaOptimizerGenerational>(
            std::move(crossover), std::move(mutation), std::move(selection),
            10, 2, std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        auto cloned = ga->clone();
        assert(cloned != nullptr);
        assert(cloned->name() == "ga");

        std::cout << " PASS" << std::endl;
    }
}

void test_ga_index_of_best() {
    std::cout << "  Testing GaOptimizer index_of_best_in_population..." << std::flush;
    {
        // Test that index_of_best_in_population works
        uo::FinishControl fc("evaluations", 100, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(8);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto selection = std::make_unique<uo::GaSelectionRoulette>();
        auto crossover = std::make_unique<uo::GaCrossoverSupportOnePointBitArray>(0.8);
        auto mutation = std::make_unique<uo::GaMutationSupportOnePointBitArray>(0.05);

        auto ga = std::make_unique<uo::GaOptimizerSteadyState>(
            std::move(crossover), std::move(mutation), std::move(selection),
            5, 1, std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        ga->init();
        int best_idx = ga->index_of_best_in_population();
        assert(best_idx >= 0 && best_idx < 5);

        std::cout << " PASS" << std::endl;
    }
}

void test_ga_with_idle_supports() {
    std::cout << "  Testing GaOptimizerSteadyState with idle supports..." << std::flush;
    {
        uo::FinishControl fc("evaluations", 30, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(6);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto selection = std::make_unique<uo::GaSelectionIdle>();
        auto crossover = std::make_unique<uo::GaCrossoverSupportIdle>();
        auto mutation = std::make_unique<uo::GaMutationSupportIdle>();

        auto ga = std::make_unique<uo::GaOptimizerSteadyState>(
            std::move(crossover), std::move(mutation), std::move(selection),
            5, 1, std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        auto result = ga->optimize();
        assert(result != nullptr);

        std::cout << " PASS" << std::endl;
        if (result) {
            std::cout << "    Best (idle): " << result->to_string() << std::endl;
        }
    }
}

int main() {
    std::cout << "=== Genetic Algorithm C++ Tests ===" << std::endl << std::endl;

    // Support class tests
    std::cout << "--- Selection tests ---" << std::endl;
    test_ga_selection_idle();
    test_ga_selection_roulette();

    std::cout << "--- Crossover support tests ---" << std::endl;
    test_ga_crossover_idle();
    test_ga_crossover_idle_bit_array();
    test_ga_crossover_one_point_bit_array();

    std::cout << "--- Mutation support tests ---" << std::endl;
    test_ga_mutation_idle();
    test_ga_mutation_idle_bit_array();
    test_ga_mutation_one_point_bit_array();

    std::cout << "--- GaOptimizerSteadyState tests ---" << std::endl;
    test_ga_optimizer_steady_state_construction();
    test_ga_optimizer_steady_state_init();
    test_ga_optimizer_steady_state_clone();
    test_ga_optimizer_steady_state_to_string();
    test_ga_optimizer_steady_state_basic_optimize();

    std::cout << "--- GaOptimizerGenerational tests ---" << std::endl;
    test_ga_optimizer_generational_construction();
    test_ga_optimizer_generational_init();
    test_ga_optimizer_generational_clone();
    test_ga_optimizer_generational_basic_optimize();

    std::cout << "--- Additional tests ---" << std::endl;
    test_ga_index_of_best();
    test_ga_with_idle_supports();

    std::cout << std::endl << "All GA tests passed!" << std::endl;
    return 0;
}
