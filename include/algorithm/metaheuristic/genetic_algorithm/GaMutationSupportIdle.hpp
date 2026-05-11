#ifndef UO_ALGORITHM_GA_MUTATION_SUPPORT_IDLE_HPP
#define UO_ALGORITHM_GA_MUTATION_SUPPORT_IDLE_HPP

#include <memory>
#include <string>

#include "algorithm/metaheuristic/genetic_algorithm/GaMutationSupport.hpp"

namespace uo {

/**
 * @brief Idle (no-op) mutation support for GA.
 * Equivalent to Python's GaMutationSupportIdle.
 */
class GaMutationSupportIdle : public GaMutationSupport {
public:
    [[nodiscard]] std::unique_ptr<GaMutationSupport> clone() const override;

    void mutation(
        const Problem& problem,
        ISolution& solution,
        PopulationBasedMetaheuristic& optimizer) override;

    [[nodiscard]] std::string to_string() const override;
};

} // namespace uo

#endif // UO_ALGORITHM_GA_MUTATION_SUPPORT_IDLE_HPP
