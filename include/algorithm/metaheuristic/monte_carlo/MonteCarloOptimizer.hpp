#ifndef UO_ALGORITHM_MONTE_CARLO_OPTIMIZER_HPP
#define UO_ALGORITHM_MONTE_CARLO_OPTIMIZER_HPP

#include <memory>
#include <optional>
#include <string>

#include "algorithm/metaheuristic/SingleSolutionMetaheuristic.hpp"

namespace uo {

/**
 * @brief Monte Carlo optimizer.
 * 
 * Equivalent to Python's MonteCarloOptimizer.
 * In each iteration, generates a completely random solution and keeps it
 * if it is better than the current best.
 */
class MonteCarloOptimizer : public SingleSolutionMetaheuristic {
public:
    explicit MonteCarloOptimizer(
        std::unique_ptr<FinishControl> finish_control,
        std::unique_ptr<Problem> problem,
        std::unique_ptr<ISolution> solution_template,
        std::shared_ptr<OutputControl> output_control = nullptr,
        std::optional<int> random_seed = std::nullopt,
        std::shared_ptr<AdditionalStatisticsControl> additional_statistics_control = nullptr);

    ~MonteCarloOptimizer() override = default;
    MonteCarloOptimizer(const MonteCarloOptimizer&) = delete;
    MonteCarloOptimizer& operator=(const MonteCarloOptimizer&) = delete;
    MonteCarloOptimizer(MonteCarloOptimizer&&) = default;
    MonteCarloOptimizer& operator=(MonteCarloOptimizer&&) = default;

    [[nodiscard]] std::unique_ptr<Optimizer> clone() const override;
    void init() override;
    void main_loop_iteration() override;
    [[nodiscard]] std::string to_string() const override;
};

} // namespace uo

#endif // UO_ALGORITHM_MONTE_CARLO_OPTIMIZER_HPP
