#ifndef UO_ALGORITHM_GA_OPTIMIZER_GENERATIONAL_HPP
#define UO_ALGORITHM_GA_OPTIMIZER_GENERATIONAL_HPP

#include <memory>
#include <optional>
#include <string>

#include "algorithm/metaheuristic/genetic_algorithm/GaOptimizer.hpp"

namespace uo {

/**
 * @brief Generational GA optimizer.
 * Equivalent to Python's GaOptimizerGenerational.
 * In each iteration, a new population is created via selection -> crossover -> mutation,
 * and the old population is replaced entirely.
 */
class GaOptimizerGenerational : public GaOptimizer {
public:
    using GaOptimizer::GaOptimizer;

    ~GaOptimizerGenerational() override = default;

    GaOptimizerGenerational(const GaOptimizerGenerational&) = delete;
    GaOptimizerGenerational& operator=(const GaOptimizerGenerational&) = delete;
    GaOptimizerGenerational(GaOptimizerGenerational&&) = default;
    GaOptimizerGenerational& operator=(GaOptimizerGenerational&&) = default;

    [[nodiscard]] std::unique_ptr<Optimizer> clone() const override;

    void main_loop_iteration() override;

    [[nodiscard]] std::string to_string() const override;
};

} // namespace uo

#endif // UO_ALGORITHM_GA_OPTIMIZER_GENERATIONAL_HPP
