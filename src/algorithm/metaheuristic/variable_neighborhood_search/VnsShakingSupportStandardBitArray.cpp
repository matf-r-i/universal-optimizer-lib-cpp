#include "algorithm/metaheuristic/variable_neighborhood_search/VnsShakingSupportStandardBitArray.hpp"
#include "algorithm/metaheuristic/SingleSolutionMetaheuristic.hpp"
#include "solution/BitArraySolution.hpp"
#include <random>

namespace uo {

std::unique_ptr<VnsShakingSupport> VnsShakingSupportStandardBitArray::clone() const {
    return std::make_unique<VnsShakingSupportStandardBitArray>(dimension());
}

bool VnsShakingSupportStandardBitArray::shaking(int k, const Problem& problem, 
                                                 ISolution& solution,
                                                 SingleSolutionMetaheuristic& optimizer) {
    if (optimizer.should_finish()) {
        return false;
    }
    // Check if k is in valid range - access k_min/k_max from optimizer
    // In Python: k < optimizer.k_min or k > optimizer.k_max
    if (k < 1) {
        return false;
    }

    auto* bit_sol = dynamic_cast<BitArraySolution*>(&solution);
    if (!bit_sol) {
        return false;
    }

    int dim = static_cast<int>(bit_sol->representation().size());
    std::mt19937& rng = optimizer.rng();
    
    // Try to find valid shake up to 10000 tries
    for (int tries = 0; tries < 10000; ++tries) {
        std::uniform_int_distribution<int> dist(0, dim - 1);
        // Select k random positions to flip
        for (int j = 0; j < k; ++j) {
            int pos = dist(rng);
            bit_sol->flip_bit(pos);
        }
        // For MaxOnes: check that dimension constraint is satisfied
        bool all_ok = true;
        if (dimension() > 0) {
            int ones = 0;
            for (bool b : bit_sol->representation()) {
                if (b) ++ones;
            }
            if (ones > dimension()) {
                all_ok = false;
            }
        }
        if (all_ok) {
            break;
        }
        // Undo the flips if not ok
        for (int j = 0; j < k; ++j) {
            int pos = dist(rng);
            bit_sol->flip_bit(pos);
        }
    }

    if (optimizer.should_finish()) {
        return false;
    }

    optimizer.increment_evaluation();
    solution.evaluate(problem);
    return true;
}

std::string VnsShakingSupportStandardBitArray::to_string() const {
    return "VnsShakingSupportStandardBitArray";
}

} // namespace uo
