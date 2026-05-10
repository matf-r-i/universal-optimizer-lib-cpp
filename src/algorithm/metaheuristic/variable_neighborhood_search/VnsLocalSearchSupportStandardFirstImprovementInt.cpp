#include "algorithm/metaheuristic/variable_neighborhood_search/VnsLocalSearchSupportStandardFirstImprovementInt.hpp"
#include "algorithm/metaheuristic/SingleSolutionMetaheuristic.hpp"
#include "solution/Solution.hpp"
#include <memory>

namespace uo {

std::unique_ptr<VnsLocalSearchSupport> VnsLocalSearchSupportStandardFirstImprovementInt::clone() const {
    return std::make_unique<VnsLocalSearchSupportStandardFirstImprovementInt>(dimension());
}

bool VnsLocalSearchSupportStandardFirstImprovementInt::local_search(
        int k, const Problem& problem, ISolution& solution,
        SingleSolutionMetaheuristic& optimizer) {
    if (optimizer.should_finish()) {
        return false;
    }
    if (k < 1) {
        return false;
    }

    auto* int_sol = dynamic_cast<Solution<int>*>(&solution);
    if (!int_sol) {
        return false;
    }

    auto start_sol = int_sol->clone();

    ComplexCounterUniformAscending indexes(k, dimension());
    bool in_loop = indexes.reset();

    while (in_loop) {
        const std::vector<int>& positions = indexes.current_state();
        int mask = 0;
        for (int pos : positions) {
            mask |= (1 << pos);
        }
        int repr = int_sol->representation();
        repr ^= mask;
        int_sol->set_representation(repr);

        if (optimizer.should_finish()) {
            int_sol->copy_from(*start_sol);
            return false;
        }

        optimizer.increment_evaluation();
        solution.evaluate(problem);

        if (solution.is_better_than(*start_sol, problem).has_value() && 
            solution.is_better_than(*start_sol, problem).value()) {
            return true;
        }

        // Undo: apply XOR mask again
        repr = int_sol->representation();
        repr ^= mask;
        int_sol->set_representation(repr);

        in_loop = indexes.progress();
    }

    int_sol->copy_from(*start_sol);
    return false;
}

std::string VnsLocalSearchSupportStandardFirstImprovementInt::to_string() const {
    return "VnsLocalSearchSupportStandardFirstImprovementInt";
}

} // namespace uo
