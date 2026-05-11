#include "algorithm/metaheuristic/genetic_algorithm/GaCrossoverSupportIdle.hpp"

namespace uo {

std::unique_ptr<GaCrossoverSupport> GaCrossoverSupportIdle::clone() const {
    return std::make_unique<GaCrossoverSupportIdle>();
}

void GaCrossoverSupportIdle::crossover(
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

std::string GaCrossoverSupportIdle::to_string() const {
    return "GaCrossoverSupportIdle";
}

} // namespace uo
