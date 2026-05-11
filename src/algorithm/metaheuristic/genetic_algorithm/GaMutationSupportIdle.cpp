#include "algorithm/metaheuristic/genetic_algorithm/GaMutationSupportIdle.hpp"

namespace uo {

std::unique_ptr<GaMutationSupport> GaMutationSupportIdle::clone() const {
    return std::make_unique<GaMutationSupportIdle>();
}

void GaMutationSupportIdle::mutation(
    const Problem& problem,
    ISolution& solution,
    PopulationBasedMetaheuristic& optimizer) {
    (void)problem;
    (void)solution;
    (void)optimizer;
    // No-op
}

std::string GaMutationSupportIdle::to_string() const {
    return "GaMutationSupportIdle";
}

} // namespace uo
