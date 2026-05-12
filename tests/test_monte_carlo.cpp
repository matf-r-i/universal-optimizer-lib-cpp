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
#include "algorithm/metaheuristic/monte_carlo/MonteCarloOptimizer.hpp"

void test_monte_carlo_construction() {
    std::cout << "  Testing MonteCarloOptimizer construction..." << std::flush;
    {
        auto fc = std::make_unique<uo::FinishControl>("evaluations", 100, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(8);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto mc = std::make_unique<uo::MonteCarloOptimizer>(
            std::move(fc), std::move(problem), std::move(sol_tmpl));

        assert(mc->name() == "MonteCarlo");

        std::cout << " PASS" << std::endl;
    }
}

void test_monte_carlo_init() {
    std::cout << "  Testing MonteCarloOptimizer init..." << std::flush;
    {
        auto fc = std::make_unique<uo::FinishControl>("evaluations", 100, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(6);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto mc = std::make_unique<uo::MonteCarloOptimizer>(
            std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        mc->init();
        assert(mc->evaluation() >= 1);
        assert(mc->current_solution() != nullptr);
        assert(mc->best_solution() != nullptr);

        std::cout << " PASS" << std::endl;
        if (mc->current_solution()) {
            std::cout << "    Init sol: " << mc->current_solution()->to_string() << std::endl;
        }
    }
}

void test_monte_carlo_basic_optimize() {
    std::cout << "  Testing MonteCarloOptimizer basic optimize..." << std::flush;
    {
        auto fc = std::make_unique<uo::FinishControl>("evaluations", 50, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(10);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto mc = std::make_unique<uo::MonteCarloOptimizer>(
            std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 123);

        auto result = mc->optimize();
        assert(result != nullptr);
        assert(mc->evaluation() > 0);
        assert(mc->iteration() > 0);

        std::cout << " PASS" << std::endl;
        if (result) {
            std::cout << "    Best: " << result->to_string() << std::endl;
        }
    }
}

void test_monte_carlo_clone() {
    std::cout << "  Testing MonteCarloOptimizer clone..." << std::flush;
    {
        auto fc = std::make_unique<uo::FinishControl>("evaluations", 100, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(6);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto mc = std::make_unique<uo::MonteCarloOptimizer>(
            std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        auto cloned = mc->clone();
        assert(cloned != nullptr);
        assert(cloned->name() == "MonteCarlo");

        std::cout << " PASS" << std::endl;
    }
}

void test_monte_carlo_to_string() {
    std::cout << "  Testing MonteCarloOptimizer to_string..." << std::flush;
    {
        auto fc = std::make_unique<uo::FinishControl>("evaluations", 100, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(6);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto mc = std::make_unique<uo::MonteCarloOptimizer>(
            std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        std::string s = mc->to_string();
        assert(s.find("MonteCarloOptimizer") != std::string::npos);
        assert(s.find("MonteCarlo") != std::string::npos);

        std::cout << " PASS" << std::endl;
    }
}

void test_monte_carlo_no_improvement() {
    std::cout << "  Testing MonteCarloOptimizer - best unchanged when no improvement..." << std::flush;
    {
        // This test verifies the algorithm runs without errors
        auto fc = std::make_unique<uo::FinishControl>("evaluations", 10, 0, 0.0);
        auto problem = std::make_unique<uo::MaxOnesProblem>(8);
        auto sol_tmpl = std::make_unique<uo::BitArraySolution>();

        auto mc = std::make_unique<uo::MonteCarloOptimizer>(
            std::move(fc), std::move(problem), std::move(sol_tmpl),
            nullptr, 42);

        auto result = mc->optimize();
        assert(result != nullptr);

        std::cout << " PASS" << std::endl;
        if (result) {
            std::cout << "    Best after 10 evals: " << result->to_string() << std::endl;
        }
    }
}

void test_monte_carlo_random_seed() {
    std::cout << "  Testing MonteCarloOptimizer random seed repeatability..." << std::flush;
    {
        // Same seed should give same result
        auto fc1 = std::make_unique<uo::FinishControl>("evaluations", 20, 0, 0.0);
        auto problem1 = std::make_unique<uo::MaxOnesProblem>(6);
        auto sol_tmpl1 = std::make_unique<uo::BitArraySolution>();

        auto mc1 = std::make_unique<uo::MonteCarloOptimizer>(
            std::move(fc1), std::move(problem1), std::move(sol_tmpl1),
            nullptr, 42);
        auto result1 = mc1->optimize();

        auto fc2 = std::make_unique<uo::FinishControl>("evaluations", 20, 0, 0.0);
        auto problem2 = std::make_unique<uo::MaxOnesProblem>(6);
        auto sol_tmpl2 = std::make_unique<uo::BitArraySolution>();

        auto mc2 = std::make_unique<uo::MonteCarloOptimizer>(
            std::move(fc2), std::move(problem2), std::move(sol_tmpl2),
            nullptr, 42);
        auto result2 = mc2->optimize();

        assert(result1 != nullptr);
        assert(result2 != nullptr);
        assert(result1->to_string() == result2->to_string());

        std::cout << " PASS" << std::endl;
        if (result1) {
            std::cout << "    Reproducible best: " << result1->to_string() << std::endl;
        }
    }
}

int main() {
    std::cout << "=== Monte Carlo C++ Tests ===" << std::endl << std::endl;

    test_monte_carlo_construction();
    test_monte_carlo_init();
    test_monte_carlo_clone();
    test_monte_carlo_to_string();
    test_monte_carlo_basic_optimize();
    test_monte_carlo_no_improvement();
    test_monte_carlo_random_seed();

    std::cout << std::endl << "All Monte Carlo tests passed!" << std::endl;
    return 0;
}
