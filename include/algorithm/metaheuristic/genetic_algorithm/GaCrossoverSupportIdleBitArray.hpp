#ifndef UO_ALGORITHM_GA_CROSSOVER_SUPPORT_IDLE_BIT_ARRAY_HPP
#define UO_ALGORITHM_GA_CROSSOVER_SUPPORT_IDLE_BIT_ARRAY_HPP

#include <memory>
#include <string>

#include "algorithm/metaheuristic/genetic_algorithm/GaCrossoverSupport.hpp"

namespace uo {

/**
 * @brief Idle (no-op) crossover support for GA with BitArray solutions.
 * Equivalent to Python's GaCrossoverSupportIdleBitArray.
 */
class GaCrossoverSupportIdleBitArray : public GaCrossoverSupport {
public:
    [[nodiscard]] std::unique_ptr<GaCrossoverSupport> clone() const override;

    void crossover(
        const Problem& problem,
        const ISolution& solution1, const ISolution& solution2,
        ISolution& child1, ISolution& child2,
        PopulationBasedMetaheuristic& optimizer) override;

    [[nodiscard]] std::string to_string() const override;
};

} // namespace uo

#endif // UO_ALGORITHM_GA_CROSSOVER_SUPPORT_IDLE_BIT_ARRAY_HPP
