#include "algorithm/metaheuristic/genetic_algorithm/GaCrossoverSupportOnePointBitArray.hpp"
#include "algorithm/metaheuristic/Metaheuristic.hpp"
#include "algorithm/metaheuristic/PopulationBasedMetaheuristic.hpp"
#include "solution/BitArraySolution.hpp"
#include <random>
#include <sstream>

namespace uo {

GaCrossoverSupportOnePointBitArray::GaCrossoverSupportOnePointBitArray(double crossover_probability)
    : crossover_probability_(crossover_probability) {}

std::unique_ptr<GaCrossoverSupport> GaCrossoverSupportOnePointBitArray::clone() const {
    return std::make_unique<GaCrossoverSupportOnePointBitArray>(crossover_probability_);
}

void GaCrossoverSupportOnePointBitArray::crossover(
    const Problem& problem,
    const ISolution& solution1, const ISolution& solution2,
    ISolution& child1, ISolution& child2,
    PopulationBasedMetaheuristic& optimizer) {
    
    auto* bit_sol1 = dynamic_cast<const BitArraySolution*>(&solution1);
    auto* bit_sol2 = dynamic_cast<const BitArraySolution*>(&solution2);
    auto* bit_child1 = dynamic_cast<BitArraySolution*>(&child1);
    auto* bit_child2 = dynamic_cast<BitArraySolution*>(&child2);

    // If any solution is not a BitArraySolution, fall back to copy
    if (!bit_sol1 || !bit_sol2 || !bit_child1 || !bit_child2) {
        child1.copy_from(solution1);
        child2.copy_from(solution2);
        return;
    }

    const auto& repr1 = bit_sol1->representation();
    const auto& repr2 = bit_sol2->representation();
    
    if (repr1.empty() || repr2.empty()) {
        child1.copy_from(solution1);
        child2.copy_from(solution2);
        return;
    }

    // Clone children's representations from parents initially
    bit_child1->set_representation(repr1);
    bit_child2->set_representation(repr2);

    // Check crossover probability
    std::mt19937& rng = optimizer.rng();
    std::uniform_real_distribution<double> prob_dist(0.0, 1.0);
    if (prob_dist(rng) > crossover_probability_) {
        return; // No crossover performed
    }

    // Select random crossover point
    int len = static_cast<int>(repr1.size());
    std::uniform_int_distribution<int> point_dist(0, len);
    int index = point_dist(rng);

    // Create child representations
    std::vector<bool> child_repr1, child_repr2;
    child_repr1.reserve(len);
    child_repr2.reserve(len);

    for (int i = 0; i < index; ++i) {
        child_repr1.push_back(repr1[i]);
        child_repr2.push_back(repr2[i]);
    }
    for (int i = index; i < len; ++i) {
        child_repr1.push_back(repr2[i]);
        child_repr2.push_back(repr1[i]);
    }

    bit_child1->set_representation(child_repr1);
    bit_child2->set_representation(child_repr2);

    // Evaluate both children and increment evaluation counter (2 evaluations)
    optimizer.increment_evaluation();
    child1.evaluate(problem);
    optimizer.increment_evaluation();
    child2.evaluate(problem);
}

std::string GaCrossoverSupportOnePointBitArray::to_string() const {
    std::ostringstream oss;
    oss << "GaCrossoverSupportOnePointBitArray{crossover_probability=" 
        << crossover_probability_ << "}";
    return oss.str();
}

} // namespace uo
