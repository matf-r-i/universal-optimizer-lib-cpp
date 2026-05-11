#include "algorithm/metaheuristic/genetic_algorithm/GaMutationSupportOnePointBitArray.hpp"
#include "algorithm/metaheuristic/Metaheuristic.hpp"
#include "algorithm/metaheuristic/PopulationBasedMetaheuristic.hpp"
#include "solution/BitArraySolution.hpp"
#include <random>
#include <sstream>

namespace uo {

GaMutationSupportOnePointBitArray::GaMutationSupportOnePointBitArray(double mutation_probability)
    : mutation_probability_(mutation_probability) {}

std::unique_ptr<GaMutationSupport> GaMutationSupportOnePointBitArray::clone() const {
    return std::make_unique<GaMutationSupportOnePointBitArray>(mutation_probability_);
}

void GaMutationSupportOnePointBitArray::mutation(
    const Problem& problem,
    ISolution& solution,
    PopulationBasedMetaheuristic& optimizer) {
    
    auto* bit_sol = dynamic_cast<BitArraySolution*>(&solution);
    if (!bit_sol) {
        return;
    }

    const auto& repr = bit_sol->representation();
    if (repr.empty()) {
        return;
    }

    std::mt19937& rng = optimizer.rng();
    std::uniform_real_distribution<double> prob_dist(0.0, 1.0);
    bool mutated = false;

    for (size_t i = 0; i < repr.size(); ++i) {
        if (prob_dist(rng) < mutation_probability_) {
            bit_sol->flip_bit(static_cast<int>(i));
            mutated = true;
        }
    }

    if (mutated) {
        // Write output before evaluation if needed
        optimizer.write_output_values_if_needed("before_evaluation", "b_e");
        optimizer.increment_evaluation();
        solution.evaluate(problem);
        optimizer.write_output_values_if_needed("after_evaluation", "b_e");
    }
}

std::string GaMutationSupportOnePointBitArray::to_string() const {
    std::ostringstream oss;
    oss << "GaMutationSupportOnePointBitArray{mutation_probability=" 
        << mutation_probability_ << "}";
    return oss.str();
}

} // namespace uo
