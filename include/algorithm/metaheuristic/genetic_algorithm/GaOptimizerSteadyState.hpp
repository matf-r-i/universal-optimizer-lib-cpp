#ifndef UO_ALGORITHM_GA_OPTIMIZER_STEADY_STATE_HPP
#define UO_ALGORITHM_GA_OPTIMIZER_STEADY_STATE_HPP

#include <memory>
#include <optional>
#include <string>

#include "algorithm/metaheuristic/genetic_algorithm/GaOptimizer.hpp"

namespace uo {

/**
 * @brief Steady-state GA optimizer.
 * Equivalent to Python's GaOptimizerSteadyState.
 * In each iteration, selection -> crossover -> mutation is applied
 * directly to the current population (replacing individuals in place).
 */
class GaOptimizerSteadyState : public GaOptimizer {
public:
    using GaOptimizer::GaOptimizer;

    ~GaOptimizerSteadyState() override = default;

    GaOptimizerSteadyState(const GaOptimizerSteadyState&) = delete;
    GaOptimizerSteadyState& operator=(const GaOptimizerSteadyState&) = delete;
    GaOptimizerSteadyState(GaOptimizerSteadyState&&) = default;
    GaOptimizerSteadyState& operator=(GaOptimizerSteadyState&&) = default;

    [[nodiscard]] std::unique_ptr<Optimizer> clone() const override;

    void main_loop_iteration() override;

    [[nodiscard]] std::string to_string() const override;
};

} // namespace uo

#endif // UO_ALGORITHM_GA_OPTIMIZER_STEADY_STATE_HPP
