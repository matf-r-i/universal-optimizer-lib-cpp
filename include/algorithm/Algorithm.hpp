#ifndef UO_ALGORITHM_ALGORITHM_HPP
#define UO_ALGORITHM_ALGORITHM_HPP

#include <memory>
#include <optional>
#include <string>

#include "algorithm/Optimizer.hpp"
#include "algorithm/OutputControl.hpp"
#include "problem/Problem.hpp"
#include "solution/Solution.hpp"

namespace uo {

class Algorithm : public Optimizer {
public:
    explicit Algorithm(std::unique_ptr<Problem> problem,
                       std::unique_ptr<ISolution> solution_template,
                       std::string name,
                       std::shared_ptr<OutputControl> output_control = nullptr);

    ~Algorithm() override = default;

    Algorithm(const Algorithm&) = delete;
    Algorithm& operator=(const Algorithm&) = delete;
    Algorithm(Algorithm&&) = default;
    Algorithm& operator=(Algorithm&&) = default;

    [[nodiscard]] std::unique_ptr<Optimizer> clone() const override = 0;

    void init() override;
    std::unique_ptr<ISolution> optimize() override = 0;

    [[nodiscard]] const ISolution* solution_template() const noexcept { return solution_template_.get(); }
    void set_solution_template(std::unique_ptr<ISolution> st) noexcept { solution_template_ = std::move(st); }

    [[nodiscard]] int evaluation() const noexcept { return evaluation_; }
    void increment_evaluation() noexcept { ++evaluation_; }
    void set_evaluation(int value) noexcept { evaluation_ = value; }

    [[nodiscard]] int iteration() const noexcept { return iteration_; }
    void increment_iteration() noexcept { ++iteration_; }
    void set_iteration(int value) noexcept { iteration_ = value; }

    [[nodiscard]] int iteration_best_found() const noexcept { return iteration_best_found_; }
    void set_iteration_best_found(int value) noexcept { iteration_best_found_ = value; }

    [[nodiscard]] int evaluation_best_found() const noexcept { return evaluation_best_found_; }
    void set_evaluation_best_found(int value) noexcept { evaluation_best_found_ = value; }

    [[nodiscard]] std::string to_string() const override;

private:
    std::unique_ptr<ISolution> solution_template_;
    int evaluation_{0};
    int iteration_{0};
    int iteration_best_found_{0};
    int evaluation_best_found_{0};
};

} // namespace uo

#endif // UO_ALGORITHM_ALGORITHM_HPP
