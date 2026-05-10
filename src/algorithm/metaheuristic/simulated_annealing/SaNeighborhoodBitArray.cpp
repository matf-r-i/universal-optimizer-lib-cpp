#include "algorithm/metaheuristic/simulated_annealing/SaNeighborhoodBitArray.hpp"
#include "algorithm/metaheuristic/Metaheuristic.hpp"
#include "solution/BitArraySolution.hpp"
#include <random>
#include <sstream>

namespace uo {

SaNeighborhoodBitArray::SaNeighborhoodBitArray(int dimension, int k)
    : dimension_(dimension), k_(k) {}

std::unique_ptr<SaNeighborhood> SaNeighborhoodBitArray::clone() const {
    return std::make_unique<SaNeighborhoodBitArray>(dimension_, k_);
}

std::unique_ptr<ISolution> SaNeighborhoodBitArray::generate_neighbor(
        const ISolution& current,
        const Problem& problem,
        const Metaheuristic* optimizer) const {
    // Try up to 10000 times to generate a valid neighbor
    for (int tries = 0; tries < 10000; ++tries) {
        auto neighbor = current.clone();
        auto* bit_sol = dynamic_cast<BitArraySolution*>(neighbor.get());
        if (!bit_sol) {
            return current.clone();
        }

        int bit_length = static_cast<int>(bit_sol->representation().size());
        std::mt19937& rng = const_cast<std::mt19937&>(
            optimizer ? optimizer->rng() 
                     : []() -> std::mt19937& { 
                          static std::mt19937 default_rng(std::random_device{}());
                          return default_rng;
                       }()
        );
        std::uniform_int_distribution<int> dist(0, bit_length - 1);

        // Select k random positions to flip
        for (int j = 0; j < k_; ++j) {
            int pos = dist(rng);
            bit_sol->flip_bit(pos);
        }

        // Optional: check dimension constraint
        if (dimension_ > 0) {
            int ones = 0;
            for (bool b : bit_sol->representation()) {
                if (b) ++ones;
            }
            if (ones > dimension_) {
                continue; // Invalid, try again
            }
        }

        // Write output before evaluation if optimizer provides it
        if (optimizer) {
            const_cast<Metaheuristic*>(optimizer)->write_output_values_if_needed(
                "before_evaluation", "b_e");
        }

        neighbor->evaluate(problem);

        if (optimizer) {
            const_cast<Metaheuristic*>(optimizer)->write_output_values_if_needed(
                "after_evaluation", "a_e");
            // Increment evaluation counter (matches Python generate_neighbor pattern)
            const_cast<Metaheuristic*>(optimizer)->increment_evaluation();
        }

        return neighbor;
    }

    // If no valid neighbor found, return a copy of the original
    return current.clone();
}

std::string SaNeighborhoodBitArray::to_string() const {
    std::ostringstream oss;
    oss << "SaNeighborhoodBitArray{dimension=" << dimension_
        << ", k=" << k_ << "}";
    return oss.str();
}

} // namespace uo

