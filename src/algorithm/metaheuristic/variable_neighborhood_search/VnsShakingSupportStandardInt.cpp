#include "algorithm/metaheuristic/variable_neighborhood_search/VnsShakingSupportStandardInt.hpp"
#include "algorithm/metaheuristic/SingleSolutionMetaheuristic.hpp"
// For IntSolution we would use Solution<int> - cast appropriately
#include "solution/Solution.hpp"
#include <random>

namespace uo {

std::unique_ptr<VnsShakingSupport> VnsShakingSupportStandardInt::clone() const {
    return std::make_unique<VnsShakingSupportStandardInt>(dimension());
}

bool VnsShakingSupportStandardInt::shaking(int k, const Problem& problem, 
                                            ISolution& solution,
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

    std::mt19937& rng = optimizer.rng();
    std::uniform_int_distribution<int> pos_dist(0, dimension() - 1);
    
    for (int tries = 0; tries < 10000; ++tries) {
        int mask = 0;
        for (int j = 0; j < k; ++j) {
            int p = pos_dist(rng);
            mask |= (1 << p);
        }
        int repr = int_sol->representation();
        repr ^= mask;
        int_sol->set_representation(repr);
        
        // Check constraint: number of 1 bits should not exceed dimension
        bool all_ok = true;
        if (dimension() > 0 && std::popcount(static_cast<unsigned>(repr)) > dimension()) {
            all_ok = false;
        }
        if (all_ok) {
            break;
        }
    }

    if (optimizer.should_finish()) {
        return false;
    }

    optimizer.increment_evaluation();
    solution.evaluate(problem);
    return true;
}

std::string VnsShakingSupportStandardInt::to_string() const {
    return "VnsShakingSupportStandardInt";
}

} // namespace uo
