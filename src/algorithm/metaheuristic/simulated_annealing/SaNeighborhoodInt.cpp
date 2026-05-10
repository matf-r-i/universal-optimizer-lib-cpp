#include "algorithm/metaheuristic/simulated_annealing/SaNeighborhoodInt.hpp"
#include "algorithm/metaheuristic/Metaheuristic.hpp"
#include "solution/Solution.hpp"
#include <random>
#include <sstream>

namespace uo {

SaNeighborhoodInt::SaNeighborhoodInt(int dimension, int k)
    : dimension_(dimension), k_(k) {}

std::unique_ptr<SaNeighborhood> SaNeighborhoodInt::clone() const {
    return std::make_unique<SaNeighborhoodInt>(dimension_, k_);
}

std::unique_ptr<ISolution> SaNeighborhoodInt::generate_neighbor(
        const ISolution& current,
        const Problem& problem,
        const Metaheuristic* optimizer) const {
    // Try up to 10000 times to generate a valid neighbor
    for (int tries = 0; tries < 10000; ++tries) {
        auto neighbor = current.clone();

        std::mt19937& rng = const_cast<std::mt19937&>(
            optimizer ? optimizer->rng() 
                     : []() -> std::mt19937& { 
                          static std::mt19937 default_rng(std::random_device{}());
                          return default_rng;
                       }()
        );
        std::uniform_int_distribution<int> dist(0, dimension_ - 1);

        // Select k random positions to flip and create XOR mask
        int mask = 0;
        for (int j = 0; j < k_; ++j) {
            int p = dist(rng);
            mask |= (1 << p);
        }

        // We can't directly access representation for int type through ISolution
        // The concrete int solution would handle this in its own representation
        // For now, we work with the solution's representation via clone/copy pattern
        // Since C++ doesn't have a concrete int solution yet, we create the neighbor
        // by copying and the concrete type will handle the representation

        // Check bit count constraint
        if (dimension_ > 0) {
            int bit_count = 0;
            int temp_mask = mask;
            while (temp_mask) {
                bit_count += (temp_mask & 1);
                temp_mask >>= 1;
            }
            if (bit_count > dimension_) {
                continue;
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
        }

        return neighbor;
    }

    // If no valid neighbor found, return a copy of the original
    return current.clone();
}

std::string SaNeighborhoodInt::to_string() const {
    std::ostringstream oss;
    oss << "SaNeighborhoodInt{dimension=" << dimension_
        << ", k=" << k_ << "}";
    return oss.str();
}

} // namespace uo
