#ifndef UO_ALGORITHM_VNS_OPTIMIZER_HPP
#define UO_ALGORITHM_VNS_OPTIMIZER_HPP

#include <memory>
#include <optional>
#include <vector>

#include "algorithm/metaheuristic/SingleSolutionMetaheuristic.hpp"
#include "algorithm/metaheuristic/simulated_annealing/SaNeighborhood.hpp"

namespace uo {

class VnsOptimizer : public SingleSolutionMetaheuristic {
public:
    explicit VnsOptimizer(
        std::vector<std::unique_ptr<SaNeighborhood>> neighborhoods,
        FinishControl finish_control,
        std::unique_ptr<Problem> problem,
        std::unique_ptr<ISolution> solution_template,
        std::shared_ptr<OutputControl> output_control = nullptr,
        std::optional<int> random_seed = std::nullopt,
        std::shared_ptr<AdditionalStatisticsControl> additional_statistics_control = nullptr);

    ~VnsOptimizer() override = default;
    VnsOptimizer(const VnsOptimizer&) = delete;
    VnsOptimizer& operator=(const VnsOptimizer&) = delete;
    VnsOptimizer(VnsOptimizer&&) = default;
    VnsOptimizer& operator=(VnsOptimizer&&) = default;

    [[nodiscard]] std::unique_ptr<Optimizer> clone() const override;
    void init() override;
    void main_loop_iteration() override;
    [[nodiscard]] std::string to_string() const override;

private:
    std::vector<std::unique_ptr<SaNeighborhood>> neighborhoods_;
    int current_neighborhood_index_{0};
};

} // namespace uo

#endif // UO_ALGORITHM_VNS_OPTIMIZER_HPP
