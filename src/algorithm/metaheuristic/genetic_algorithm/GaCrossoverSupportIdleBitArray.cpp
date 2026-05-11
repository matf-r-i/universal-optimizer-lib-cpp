#include "algorithm/metaheuristic/genetic_algorithm/GaCrossoverSupportIdleBitArray.hpp"

namespace uo {

std::unique_ptr<GaCrossoverSupport> GaCrossoverSupportIdleBitArray::clone() const {
    return std::make_unique<GaCrossoverSupportIdleBitArray>();
}

void GaCrossoverSupportIdleBitArray::crossover(
    const Problem& problem,
    const ISolution& solution1, const ISolution& solution2,
    ISolution& child1, ISolution& child2,
    PopulationBasedMetaheuristic& optimizer) {
    (void)problem;
    (void)solution1;
    (void)solution2;
    (void)child1;
    (void)child2;
    (void)optimizer;
    // No-op
}

std::string GaCrossoverSupportIdleBitArray::to_string() const {
    return "GaCrossoverSupportIdleBitArray";
}

} // namespace uo
