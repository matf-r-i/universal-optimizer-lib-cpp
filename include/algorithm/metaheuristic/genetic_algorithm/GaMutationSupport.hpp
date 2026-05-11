#ifndef UO_ALGORITHM_GA_MUTATION_SUPPORT_HPP
#define UO_ALGORITHM_GA_MUTATION_SUPPORT_HPP

#include <memory>
#include <string>

namespace uo {

class Problem;
class ISolution;
class PopulationBasedMetaheuristic;

/**
 * @brief Abstract base class for GA mutation support.
 * Equivalent to Python's GaMutationSupport.
 */
class GaMutationSupport {
public:
    virtual ~GaMutationSupport() = default;

    [[nodiscard]] virtual std::unique_ptr<GaMutationSupport> clone() const = 0;

    /**
     * @brief Perform mutation on a single solution.
     * @param problem The problem being solved.
     * @param solution The solution to mutate (modified in place).
     * @param optimizer The population-based metaheuristic optimizer.
     */
    virtual void mutation(
        const Problem& problem,
        ISolution& solution,
        PopulationBasedMetaheuristic& optimizer) = 0;

    [[nodiscard]] virtual std::string to_string() const = 0;
};

} // namespace uo

#endif // UO_ALGORITHM_GA_MUTATION_SUPPORT_HPP
