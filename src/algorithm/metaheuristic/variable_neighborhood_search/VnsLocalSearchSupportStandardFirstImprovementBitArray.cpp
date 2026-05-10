#include "algorithm/metaheuristic/variable_neighborhood_search/VnsLocalSearchSupportStandardFirstImprovementBitArray.hpp"
#include "algorithm/metaheuristic/SingleSolutionMetaheuristic.hpp"
#include "solution/BitArraySolution.hpp"
#include <cmath>
#include <memory>

namespace uo {

std::unique_ptr<VnsLocalSearchSupport> VnsLocalSearchSupportStandardFirstImprovementBitArray::clone() const {
    return std::make_unique<VnsLocalSearchSupportStandardFirstImprovementBitArray>(dimension());
}

bool VnsLocalSearchSupportStandardFirstImprovementBitArray::local_search(
        int k, const Problem& problem, ISolution& solution,
        SingleSolutionMetaheuristic& optimizer) {
    if (optimizer.should_finish()) {
        return false;
    }
    // Check k bounds
    if (k < 1) {
        return false;
    }

    auto* bit_sol = dynamic_cast<BitArraySolution*>(&solution);
    if (!bit_sol) {
        return false;
    }

    // Save starting solution
    auto start_sol = bit_sol->clone();

    // Initialize indexes for combinations of k bits
    int dim = static_cast<int>(bit_sol->representation().size());
    // dim for indexes = ceil(log2(dimension)) - as in Python
    int index_dim = static_cast<int>(std::ceil(std::log2(static_cast<double>(dimension()))));
    if (index_dim < 1) index_dim = 1;

    ComplexCounterUniformAscending indexes(k, index_dim);
    bool in_loop = indexes.reset();
    
    while (in_loop) {
        // Get positions from indexes
        const std::vector<int>& positions = indexes.current_state();
        
        // Invert bits at those positions
        for (int pos : positions) {
            if (pos < dim) {
                bit_sol->flip_bit(pos);
            }
        }

        if (optimizer.should_finish()) {
            // Restore and return
            bit_sol->copy_from(*start_sol);
            return false;
        }

        optimizer.increment_evaluation();
        solution.evaluate(problem);

        // Check if better than start
        if (solution.is_better_than(*start_sol, problem).has_value() && 
            solution.is_better_than(*start_sol, problem).value()) {
            return true;
        }

        // Undo the inversion
        for (int pos : positions) {
            if (pos < dim) {
                bit_sol->flip_bit(pos);
            }
        }

        in_loop = indexes.progress();
    }

    // No improvement found, restore original
    bit_sol->copy_from(*start_sol);
    return false;
}

std::string VnsLocalSearchSupportStandardFirstImprovementBitArray::to_string() const {
    return "VnsLocalSearchSupportStandardFirstImprovementBitArray";
}

} // namespace uo
