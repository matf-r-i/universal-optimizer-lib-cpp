#include "algorithm/metaheuristic/variable_neighborhood_search/VnsLocalSearchSupportStandardBestImprovementBitArray.hpp"
#include "algorithm/metaheuristic/SingleSolutionMetaheuristic.hpp"
#include "solution/BitArraySolution.hpp"
#include <cmath>
#include <memory>

namespace uo {

std::unique_ptr<VnsLocalSearchSupport> VnsLocalSearchSupportStandardBestImprovementBitArray::clone() const {
    return std::make_unique<VnsLocalSearchSupportStandardBestImprovementBitArray>(dimension());
}

bool VnsLocalSearchSupportStandardBestImprovementBitArray::local_search(
        int k, const Problem& problem, ISolution& solution,
        SingleSolutionMetaheuristic& optimizer) {
    if (optimizer.should_finish()) {
        return false;
    }
    if (k < 1) {
        return false;
    }

    auto* bit_sol = dynamic_cast<BitArraySolution*>(&solution);
    if (!bit_sol) {
        return false;
    }

    auto start_sol = bit_sol->clone();
    auto best_sol = bit_sol->clone();
    bool better_sol_found = false;

    int dim = static_cast<int>(bit_sol->representation().size());
    int index_dim = static_cast<int>(std::ceil(std::log2(static_cast<double>(dimension()))));
    if (index_dim < 1) index_dim = 1;

    ComplexCounterUniformAscending indexes(k, index_dim);
    bool in_loop = indexes.reset();

    while (in_loop) {
        const std::vector<int>& positions = indexes.current_state();

        for (int pos : positions) {
            if (pos < dim) {
                bit_sol->flip_bit(pos);
            }
        }

        if (optimizer.should_finish()) {
            bit_sol->copy_from(*start_sol);
            return false;
        }

        optimizer.increment_evaluation();
        solution.evaluate(problem);

        if (solution.is_better_than(*best_sol, problem).has_value() && 
            solution.is_better_than(*best_sol, problem).value()) {
            better_sol_found = true;
            best_sol->copy_from(solution);
        }

        // Undo inversion
        for (int pos : positions) {
            if (pos < dim) {
                bit_sol->flip_bit(pos);
            }
        }

        in_loop = indexes.progress();
    }

    if (better_sol_found) {
        bit_sol->copy_from(*best_sol);
        return true;
    }

    bit_sol->copy_from(*start_sol);
    return false;
}

std::string VnsLocalSearchSupportStandardBestImprovementBitArray::to_string() const {
    return "VnsLocalSearchSupportStandardBestImprovementBitArray";
}

} // namespace uo
