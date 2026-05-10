#ifndef UO_ALGORITHM_TE_OPTIMIZER_HPP
#define UO_ALGORITHM_TE_OPTIMIZER_HPP

#include <memory>
#include "algorithm/Algorithm.hpp"
#include "algorithm/exact/total_enumeration/TeOperationsSupport.hpp"

namespace uo {

/**
 * @brief Total Enumeration (TE) optimizer.
 * 
 * This is the C++ equivalent of the Python `TeOptimizer` class.
 * It exhaustively enumerates all possible solutions.
 */
class TeOptimizer : public Algorithm {
public:
    explicit TeOptimizer(
        std::unique_ptr<TeOperationsSupport> te_operations_support,
        std::unique_ptr<Problem> problem,
        std::unique_ptr<ISolution> solution_template,
        std::shared_ptr<OutputControl> output_control = nullptr);

    ~TeOptimizer() override = default;
    TeOptimizer(const TeOptimizer&) = delete;
    TeOptimizer& operator=(const TeOptimizer&) = delete;
    TeOptimizer(TeOptimizer&&) = default;
    TeOptimizer& operator=(TeOptimizer&&) = default;

    [[nodiscard]] std::unique_ptr<Optimizer> clone() const override;
    void init() override;
    std::unique_ptr<ISolution> optimize() override;

    [[nodiscard]] const ISolution* current_solution() const noexcept { return current_solution_.get(); }
    void set_current_solution(std::unique_ptr<ISolution> sol) noexcept { current_solution_ = std::move(sol); }

    [[nodiscard]] std::string to_string() const override;

private:
    std::unique_ptr<TeOperationsSupport> te_operations_support_;
    std::unique_ptr<ISolution> current_solution_;
};

} // namespace uo

#endif // UO_ALGORITHM_TE_OPTIMIZER_HPP
