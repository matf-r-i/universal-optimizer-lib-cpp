#ifndef UO_ALGORITHM_SINGLE_SOLUTION_METAHEURISTIC_HPP
#define UO_ALGORITHM_SINGLE_SOLUTION_METAHEURISTIC_HPP

#include <memory>
#include "algorithm/metaheuristic/Metaheuristic.hpp"

namespace uo {

class SingleSolutionMetaheuristic : public Metaheuristic {
public:
    using Metaheuristic::Metaheuristic;
    ~SingleSolutionMetaheuristic() override = default;

    SingleSolutionMetaheuristic(const SingleSolutionMetaheuristic&) = delete;
    SingleSolutionMetaheuristic& operator=(const SingleSolutionMetaheuristic&) = delete;
    SingleSolutionMetaheuristic(SingleSolutionMetaheuristic&&) = default;
    SingleSolutionMetaheuristic& operator=(SingleSolutionMetaheuristic&&) = default;

    [[nodiscard]] std::unique_ptr<Optimizer> clone() const override = 0;

    [[nodiscard]] const ISolution* current_solution() const noexcept { return current_solution_.get(); }
    void set_current_solution(std::unique_ptr<ISolution> sol) noexcept { current_solution_ = std::move(sol); }

    [[nodiscard]] std::string to_string() const override;

protected:
    std::unique_ptr<ISolution> current_solution_;
};

} // namespace uo

#endif // UO_ALGORITHM_SINGLE_SOLUTION_METAHEURISTIC_HPP
