#ifndef UO_ALGORITHM_SA_OPTIMIZER_HPP
#define UO_ALGORITHM_SA_OPTIMIZER_HPP

#include <memory>
#include <optional>

#include "algorithm/metaheuristic/SingleSolutionMetaheuristic.hpp"
#include "algorithm/metaheuristic/simulated_annealing/SaTemperature.hpp"
#include "algorithm/metaheuristic/simulated_annealing/SaNeighborhood.hpp"

namespace uo {

class SaOptimizer : public SingleSolutionMetaheuristic {
public:
    explicit SaOptimizer(
        std::unique_ptr<SaNeighborhood> sa_neighborhood,
        std::unique_ptr<SaTemperature> sa_temperature,
        std::unique_ptr<FinishControl> finish_control,
        std::unique_ptr<Problem> problem,
        std::unique_ptr<ISolution> solution_template,
        std::shared_ptr<OutputControl> output_control = nullptr,
        std::optional<int> random_seed = std::nullopt,
        std::shared_ptr<AdditionalStatisticsControl> additional_statistics_control = nullptr);

    ~SaOptimizer() override = default;
    SaOptimizer(const SaOptimizer&) = delete;
    SaOptimizer& operator=(const SaOptimizer&) = delete;
    SaOptimizer(SaOptimizer&&) = default;
    SaOptimizer& operator=(SaOptimizer&&) = default;

    [[nodiscard]] std::unique_ptr<Optimizer> clone() const override;
    void init() override;
    void main_loop_iteration() override;
    [[nodiscard]] std::string to_string() const override;

private:
    std::unique_ptr<SaNeighborhood> sa_neighborhood_;
    std::unique_ptr<SaTemperature> sa_temperature_;
};

} // namespace uo

#endif // UO_ALGORITHM_SA_OPTIMIZER_HPP
