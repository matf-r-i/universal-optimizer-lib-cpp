#ifndef UO_ALGORITHM_GA_OPTIMIZER_HPP
#define UO_ALGORITHM_GA_OPTIMIZER_HPP

#include <memory>
#include <optional>
#include <string>

#include "algorithm/metaheuristic/PopulationBasedMetaheuristic.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaSelection.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaCrossoverSupport.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaMutationSupport.hpp"

namespace uo {

/**
 * @brief Abstract base class for GA (Genetic Algorithm) optimizers.
 * Equivalent to Python's GaOptimizer.
 */
class GaOptimizer : public PopulationBasedMetaheuristic {
public:
    GaOptimizer(
        std::unique_ptr<GaCrossoverSupport> ga_crossover_support,
        std::unique_ptr<GaMutationSupport> ga_mutation_support,
        std::unique_ptr<GaSelection> ga_selection,
        int population_size,
        int elite_count,
        FinishControl finish_control,
        std::unique_ptr<Problem> problem,
        std::unique_ptr<ISolution> solution_tmpl,
        std::shared_ptr<OutputControl> output_control = nullptr,
        std::optional<int> random_seed = std::nullopt,
        std::shared_ptr<AdditionalStatisticsControl> additional_statistics_control = nullptr);

    ~GaOptimizer() override = default;

    GaOptimizer(const GaOptimizer&) = delete;
    GaOptimizer& operator=(const GaOptimizer&) = delete;
    GaOptimizer(GaOptimizer&&) = default;
    GaOptimizer& operator=(GaOptimizer&&) = default;

    [[nodiscard]] std::unique_ptr<Optimizer> clone() const override = 0;

    void init() override;
    std::unique_ptr<ISolution> optimize() override;

    [[nodiscard]] int elite_count() const noexcept { return elite_count_; }
    void set_elite_count(int value) noexcept { elite_count_ = value; }

    [[nodiscard]] int population_size() const noexcept { return population_size_; }

    [[nodiscard]] const GaCrossoverSupport& ga_crossover_support() const noexcept { return *ga_crossover_support_; }
    [[nodiscard]] const GaMutationSupport& ga_mutation_support() const noexcept { return *ga_mutation_support_; }
    [[nodiscard]] const GaSelection& ga_selection() const noexcept { return *ga_selection_; }

    [[nodiscard]] int index_of_best_in_population() const;

    [[nodiscard]] std::string to_string() const override;

protected:
    std::unique_ptr<GaCrossoverSupport> ga_crossover_support_;
    std::unique_ptr<GaMutationSupport> ga_mutation_support_;
    std::unique_ptr<GaSelection> ga_selection_;
    int population_size_;
    int elite_count_;
};

} // namespace uo

#endif // UO_ALGORITHM_GA_OPTIMIZER_HPP
