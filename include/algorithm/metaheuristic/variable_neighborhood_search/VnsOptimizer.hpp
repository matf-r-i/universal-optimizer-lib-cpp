#ifndef UO_ALGORITHM_VNS_OPTIMIZER_HPP
#define UO_ALGORITHM_VNS_OPTIMIZER_HPP

#include <memory>
#include <optional>
#include <string>

#include "algorithm/metaheuristic/SingleSolutionMetaheuristic.hpp"
#include "algorithm/metaheuristic/variable_neighborhood_search/VnsShakingSupport.hpp"
#include "algorithm/metaheuristic/variable_neighborhood_search/VnsLocalSearchSupport.hpp"

namespace uo {

/**
 * @brief Variable Neighborhood Search (VNS) optimizer.
 * 
 * This is the C++ equivalent of the Python `VnsOptimizer` class.
 * It uses shaking and local search procedures to escape local optima.
 * 
 * Architecture matches the Python implementation:
 * - VnsShakingSupport: generates random perturbations
 * - VnsLocalSearchSupport: improves solutions via local search
 * - k_min, k_max: parameters controlling neighborhood size
 */
class VnsOptimizer : public SingleSolutionMetaheuristic {
public:
    explicit VnsOptimizer(
        std::unique_ptr<VnsShakingSupport> vns_shaking_support,
        std::unique_ptr<VnsLocalSearchSupport> vns_ls_support,
        int k_min,
        int k_max,
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

    //@{
    /// @name VNS parameters
    [[nodiscard]] int k_min() const noexcept { return k_min_; }
    [[nodiscard]] int k_max() const noexcept { return k_max_; }
    [[nodiscard]] int k_current() const noexcept { return k_current_; }
    void set_k_min(int val) noexcept { k_min_ = val; }
    void set_k_max(int val) noexcept { k_max_ = val; }
    //@}

    //@{
    /// @name VNS support
    [[nodiscard]] VnsShakingSupport& vns_shaking_support() const noexcept { return *vns_shaking_support_; }
    [[nodiscard]] VnsLocalSearchSupport& vns_ls_support() const noexcept { return *vns_ls_support_; }
    //@}

private:
    std::unique_ptr<VnsShakingSupport> vns_shaking_support_;
    std::unique_ptr<VnsLocalSearchSupport> vns_ls_support_;
    int k_min_;
    int k_max_;
    int k_current_{0};
};

} // namespace uo

#endif // UO_ALGORITHM_VNS_OPTIMIZER_HPP
