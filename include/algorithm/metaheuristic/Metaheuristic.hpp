#ifndef UO_ALGORITHM_METAHEURISTIC_HPP
#define UO_ALGORITHM_METAHEURISTIC_HPP

#include <memory>
#include <optional>
#include <random>
#include <string>

#include "algorithm/Algorithm.hpp"
#include "algorithm/metaheuristic/FinishControl.hpp"
#include "algorithm/metaheuristic/AdditionalStatisticsControl.hpp"

namespace uo {

class Metaheuristic : public Algorithm {
public:
    explicit Metaheuristic(
        FinishControl finish_control,
        std::unique_ptr<Problem> problem,
        std::unique_ptr<ISolution> solution_template,
        std::string name,
        std::shared_ptr<OutputControl> output_control = nullptr,
        std::optional<int> random_seed = std::nullopt,
        std::shared_ptr<AdditionalStatisticsControl> additional_statistics_control = nullptr);

    ~Metaheuristic() override = default;

    Metaheuristic(const Metaheuristic&) = delete;
    Metaheuristic& operator=(const Metaheuristic&) = delete;
    Metaheuristic(Metaheuristic&&) = default;
    Metaheuristic& operator=(Metaheuristic&&) = default;

    [[nodiscard]] std::unique_ptr<Optimizer> clone() const override = 0;

    void init() override;
    virtual void main_loop_iteration() = 0;
    virtual void main_loop();
    std::unique_ptr<ISolution> optimize() override;

    [[nodiscard]] const FinishControl& finish_control() const noexcept { return finish_control_; }
    void set_finish_control(const FinishControl& fc) noexcept { finish_control_ = fc.clone(); }

    [[nodiscard]] int random_seed() const noexcept { return random_seed_; }
    void set_random_seed(int seed) noexcept { random_seed_ = seed; rng_.seed(seed); }

    [[nodiscard]] std::shared_ptr<AdditionalStatisticsControl> additional_statistics_control() const noexcept {
        return additional_statistics_control_;
    }
    void set_additional_statistics_control(std::shared_ptr<AdditionalStatisticsControl> asc) noexcept {
        additional_statistics_control_ = std::move(asc);
    }

    [[nodiscard]] bool should_finish() const;

    //@{
    /// @name RNG access (needed by VNS support classes)
    [[nodiscard]] std::mt19937& rng() noexcept { return rng_; }
    [[nodiscard]] const std::mt19937& rng() const noexcept { return rng_; }
    //@}

    //@{
    /// @name Best solution
    [[nodiscard]] const ISolution* best_solution() const noexcept { return best_solution_.get(); }
    void set_best_solution(std::unique_ptr<ISolution> sol) noexcept { best_solution_ = std::move(sol); }
    //@}

    /**
     * @brief Write output values if the output control is configured.
     * @param moment The output moment (e.g., "before_evaluation").
     * @param step The step name for grouped output.
     */
    virtual void write_output_values_if_needed(const std::string& moment, const std::string& step);

    /**
     * @brief Update additional statistics if the control is configured.
     * @param solution The current solution to consider for statistics.
     */
    virtual void update_additional_statistics_if_required(const ISolution& solution);

    [[nodiscard]] std::string to_string() const override;

protected:
    std::mt19937 rng_;
    std::unique_ptr<ISolution> best_solution_;

private:
    FinishControl finish_control_;
    int random_seed_;
    std::shared_ptr<AdditionalStatisticsControl> additional_statistics_control_;
};

} // namespace uo

#endif // UO_ALGORITHM_METAHEURISTIC_HPP
