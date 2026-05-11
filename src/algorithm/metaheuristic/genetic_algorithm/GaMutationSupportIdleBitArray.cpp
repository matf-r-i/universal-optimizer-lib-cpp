#include "algorithm/metaheuristic/genetic_algorithm/GaMutationSupportIdleBitArray.hpp"

namespace uo {

std::unique_ptr<GaMutationSupport> GaMutationSupportIdleBitArray::clone() const {
    return std::make_unique<GaMutationSupportIdleBitArray>();
}

void GaMutationSupportIdleBitArray::mutation(
    const Problem& problem,
    ISolution& solution,
    PopulationBasedMetaheuristic& optimizer) {
    (void)problem;
    (void)solution;
    (void)optimizer;
    // No-op
}

std::string GaMutationSupportIdleBitArray::to_string() const {
    return "GaMutationSupportIdleBitArray";
}

} // namespace uo
