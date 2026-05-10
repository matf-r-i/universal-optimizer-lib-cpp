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

    void init() override = 0;
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
    [[nodiscard]] std::string to_string() const override;

protected:
    std::mt19937 rng_;

private:
    FinishControl finish_control_;
    int random_seed_;
    std::shared_ptr<AdditionalStatisticsControl> additional_statistics_control_;
};

} // namespace uo

#endif // UO_ALGORITHM_METAHEURISTIC_HPP
