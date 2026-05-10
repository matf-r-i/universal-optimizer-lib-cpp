#include "solution/BitArraySolution.hpp"
#include "problem/MaxOnesProblem.hpp"
#include <algorithm>
#include <sstream>
#include <stdexcept>

namespace uo {

BitArraySolution::BitArraySolution(std::optional<int> random_seed,
                                    std::optional<double> fitness_value,
                                    std::optional<double> objective_value,
                                    bool is_feasible)
    : Solution<std::vector<bool>>(random_seed, fitness_value, objective_value, is_feasible) {}

std::unique_ptr<ISolution> BitArraySolution::clone() const {
    auto cloned = std::make_unique<BitArraySolution>();
    cloned->copy_from(*this);
    return cloned;
}

void BitArraySolution::copy_from(const ISolution& other) {
    auto* derived = dynamic_cast<const BitArraySolution*>(&other);
    if (derived) {
        representation_ = derived->representation_;
        set_fitness_value(derived->fitness_value());
        set_objective_value(derived->objective_value());
        set_is_feasible(derived->is_feasible());
    }
}

void BitArraySolution::init_random(const Problem& problem) {
    auto* max_ones = dynamic_cast<const MaxOnesProblem*>(&problem);
    if (max_ones) {
        representation_.resize(max_ones->dimension());
    }
    std::uniform_int_distribution<int> dist(0, 1);
    for (size_t i = 0; i < representation_.size(); ++i) {
        representation_[i] = (dist(rng_) == 1);
    }
}

void BitArraySolution::init_from(const std::string& representation, const Problem& problem) {
    (void)problem;
    representation_ = native_representation(representation);
}

std::vector<bool> BitArraySolution::native_representation(const std::string& representation_str) const {
    std::vector<bool> result;
    for (char c : representation_str) {
        if (c == '0') result.push_back(false);
        else if (c == '1') result.push_back(true);
    }
    return result;
}

QualityOfSolution BitArraySolution::calculate_quality_directly(const Problem& problem) {
    (void)problem;
    int ones_count = 0;
    for (bool bit : representation_) {
        if (bit) ++ones_count;
    }
    return QualityOfSolution(
        static_cast<double>(ones_count),
        static_cast<double>(ones_count),
        true
    );
}

std::string BitArraySolution::to_string() const {
    std::string result;
    for (bool bit : representation_) {
        result += bit ? '1' : '0';
    }
    return result;
}

double BitArraySolution::representation_distance(const ISolution& other) const {
    auto* derived = dynamic_cast<const BitArraySolution*>(&other);
    if (!derived) return -1.0;

    int hamming = 0;
    size_t min_len = std::min(representation_.size(), derived->representation_.size());
    for (size_t i = 0; i < min_len; ++i) {
        if (representation_[i] != derived->representation_[i]) ++hamming;
    }
    return static_cast<double>(hamming);
}

} // namespace uo
