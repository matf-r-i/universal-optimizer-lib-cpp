#include "algorithm/metaheuristic/simulated_annealing/SaOptimizer.hpp"
#include <cmath>
#include <random>
#include <sstream>

namespace uo {

SaOptimizer::SaOptimizer(
    std::unique_ptr<SaNeighborhood> sa_neighborhood,
    std::unique_ptr<SaTemperature> sa_temperature,
    FinishControl finish_control,
    std::unique_ptr<Problem> problem,
    std::unique_ptr<ISolution> solution_template,
    std::shared_ptr<OutputControl> output_control,
    std::optional<int> random_seed,
    std::shared_ptr<AdditionalStatisticsControl> additional_statistics_control)
    : SingleSolutionMetaheuristic(
        std::move(finish_control),
        std::move(problem),
        std::move(solution_template),
        "sa",
        std::move(output_control),
        random_seed,
        std::move(additional_statistics_control))
    , sa_neighborhood_(std::move(sa_neighborhood))
    , sa_temperature_(std::move(sa_temperature)) {}

std::unique_ptr<Optimizer> SaOptimizer::clone() const {
    auto cloned = std::make_unique<SaOptimizer>(
        nullptr, nullptr,
        finish_control(),
        problem().clone(),
        solution_template() ? solution_template()->clone() : nullptr,
        output_control(),
        random_seed(),
        additional_statistics_control()
    );
    return cloned;
}

void SaOptimizer::init() {
    Metaheuristic::init();
    if (solution_template()) {
        auto sol = solution_template()->clone();
        sol->init_random(problem());
        set_current_solution(std::move(sol));
    }
    set_evaluation(1);
    set_iteration(0);
}

void SaOptimizer::main_loop_iteration() {
    double current_temp = sa_temperature_->calculate(iteration());
    increment_iteration();

    if (!current_solution()) return;
    auto neighbor = sa_neighborhood_->generate_neighbor(
        *current_solution_, problem(), this);
    if (!neighbor) return;

    neighbor->evaluate(problem());

    auto cmp = current_solution_->is_better_than(*neighbor, problem());
    bool neighbor_is_better = cmp.has_value() && !cmp.value();

    if (neighbor_is_better) {
        set_current_solution(std::move(neighbor));
    } else {
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        if (dist(rng_) < current_temp) {
            set_current_solution(std::move(neighbor));
        }
    }
    increment_evaluation();
}

std::string SaOptimizer::to_string() const {
    std::ostringstream oss;
    oss << "SaOptimizer{"
        << SingleSolutionMetaheuristic::to_string()
        << ", temperature=" << (sa_temperature_ ? sa_temperature_->to_string() : "null")
        << ", neighborhood=" << (sa_neighborhood_ ? sa_neighborhood_->to_string() : "null")
        << "}";
    return oss.str();
}

} // namespace uo
