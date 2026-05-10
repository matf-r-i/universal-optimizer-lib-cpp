#include <iostream>
#include <cassert>
#include <memory>
#include "problem/MaxOnesProblem.hpp"
#include "solution/BitArraySolution.hpp"
#include "algorithm/OutputControl.hpp"
#include "algorithm/metaheuristic/FinishControl.hpp"
#include "algorithm/metaheuristic/AdditionalStatisticsControl.hpp"
#include "algorithm/metaheuristic/simulated_annealing/SaOptimizer.hpp"
#include "algorithm/metaheuristic/simulated_annealing/SaNeighborhood.hpp"
#include "algorithm/metaheuristic/simulated_annealing/SaTemperature.hpp"
#include "algorithm/metaheuristic/simulated_annealing/SaNeighborhoodBitArray.hpp"
int main() {
    std::cout << "Creating..." << std::endl;
    uo::FinishControl fc("evaluations", 100, 0, 0.0);
    auto problem = std::make_unique<uo::MaxOnesProblem>(6);
    auto sol_tmpl = std::make_unique<uo::BitArraySolution>();
    auto neighborhood = std::make_unique<uo::SaNeighborhoodBitArray>(6, 2);
    auto temperature = std::make_unique<uo::SaTemperatureConst>(0.5);
    std::cout << "Constructing SaOptimizer..." << std::endl;
    auto sa = std::make_unique<uo::SaOptimizer>(
        std::move(neighborhood), std::move(temperature),
        std::move(fc), std::move(problem), std::move(sol_tmpl),
        nullptr, 42);
    std::cout << "Calling to_string..." << std::endl;
    std::cout << "  about to call sa->to_string()..." << std::endl;
    // Test the components directly
    std::cout << "  sa_temperature_->to_string()..." << std::endl;
    // Can't access private members directly, let's just try to_string
    try {
    std::string s = sa->to_string();
    std::cout << "to_string result: " << s << std::endl;
    std::cout << "Checking strings..." << std::endl;
    assert(s.find("SaOptimizer") != std::string::npos);
    assert(s.find("SaTemperatureConst") != std::string::npos);
    assert(s.find("SaNeighborhoodBitArray") != std::string::npos);
    std::cout << "PASS" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Caught unknown exception" << std::endl;
}
    return 0;
}

