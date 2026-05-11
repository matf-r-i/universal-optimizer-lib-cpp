#ifndef UO_ALGORITHM_GA_CROSSOVER_SUPPORT_HPP
#define UO_ALGORITHM_GA_CROSSOVER_SUPPORT_HPP

#include <memory>
#include <string>

namespace uo {

class Problem;
class ISolution;
class PopulationBasedMetaheuristic;

/**
 * @brief Abstract base class for GA crossover support.
 * Equivalent to Python's GaCrossoverSupport.
 */
class GaCrossoverSupport {
public:
    virtual ~GaCrossoverSupport() = default;

    [[nodiscard]] virtual std::unique_ptr<GaCrossoverSupport> clone() const = 0;

    /**
     * @brief Perform crossover on two parent solutions, producing two children.
     * @param problem The problem being solved.
     * @param solution1 First parent.
     * @param solution2 Second parent.
     * @param child1 First child (output).
     * @param child2 Second child (output).
     * @param optimizer The population-based metaheuristic optimizer.
     */
    virtual void crossover(
        const Problem& problem,
        const ISolution& solution1, const ISolution& solution2,
        ISolution& child1, ISolution& child2,
        PopulationBasedMetaheuristic& optimizer) = 0;

    [[nodiscard]] virtual std::string to_string() const = 0;
};

} // namespace uo

#endif // UO_ALGORITHM_GA_CROSSOVER_SUPPORT_HPP
