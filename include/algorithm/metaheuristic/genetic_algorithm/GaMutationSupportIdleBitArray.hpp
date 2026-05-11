#ifndef UO_ALGORITHM_GA_MUTATION_SUPPORT_IDLE_BIT_ARRAY_HPP
#define UO_ALGORITHM_GA_MUTATION_SUPPORT_IDLE_BIT_ARRAY_HPP

#include <memory>
#include <string>

#include "algorithm/metaheuristic/genetic_algorithm/GaMutationSupport.hpp"

namespace uo {

/**
 * @brief Idle (no-op) mutation support for GA with BitArray solutions.
 * Equivalent to Python's GaMutationSupportIdleBitArray.
 */
class GaMutationSupportIdleBitArray : public GaMutationSupport {
public:
    [[nodiscard]] std::unique_ptr<GaMutationSupport> clone() const override;

    void mutation(
        const Problem& problem,
        ISolution& solution,
        PopulationBasedMetaheuristic& optimizer) override;

    [[nodiscard]] std::string to_string() const override;
};

} // namespace uo

#endif // UO_ALGORITHM_GA_MUTATION_SUPPORT_IDLE_BIT_ARRAY_HPP
