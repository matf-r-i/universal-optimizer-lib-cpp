#ifndef UO_ALGORITHM_OPTIMIZER_HPP
#define UO_ALGORITHM_OPTIMIZER_HPP

#include <chrono>
#include <memory>
#include <optional>
#include <string>

#include "algorithm/OutputControl.hpp"
#include "problem/Problem.hpp"

namespace uo {

// Forward declaration only
class ISolution;

/**
 * @brief Abstract base class for all optimizers.
 */
class Optimizer {
public:
    explicit Optimizer(std::unique_ptr<Problem> problem,
                       std::string name,
                       std::shared_ptr<OutputControl> output_control = nullptr);

    virtual ~Optimizer() = default;

    Optimizer(const Optimizer&) = delete;
    Optimizer& operator=(const Optimizer&) = delete;
    Optimizer(Optimizer&&) = default;
    Optimizer& operator=(Optimizer&&) = default;

    [[nodiscard]] virtual std::unique_ptr<Optimizer> clone() const = 0;

    virtual void init();
    virtual std::unique_ptr<ISolution> optimize() = 0;

    [[nodiscard]] const Problem& problem() const noexcept { return *problem_; }
    [[nodiscard]] const std::string& name() const noexcept { return name_; }

    [[nodiscard]] std::chrono::system_clock::time_point execution_started() const noexcept { return execution_started_; }
    void set_execution_started(std::chrono::system_clock::time_point time) noexcept { execution_started_ = time; }

    [[nodiscard]] std::chrono::system_clock::time_point execution_ended() const noexcept { return execution_ended_; }
    void set_execution_ended(std::chrono::system_clock::time_point time) noexcept { execution_ended_ = time; }

    [[nodiscard]] double elapsed_seconds() const;

    [[nodiscard]] std::shared_ptr<OutputControl> output_control() const noexcept { return output_control_; }
    void set_output_control(std::shared_ptr<OutputControl> oc) noexcept { output_control_ = std::move(oc); }

    [[nodiscard]] virtual std::string to_string() const;

private:
    std::unique_ptr<Problem> problem_;
    std::string name_;
    std::shared_ptr<OutputControl> output_control_;
    std::chrono::system_clock::time_point execution_started_;
    std::chrono::system_clock::time_point execution_ended_;
};

} // namespace uo

#endif // UO_ALGORITHM_OPTIMIZER_HPP
