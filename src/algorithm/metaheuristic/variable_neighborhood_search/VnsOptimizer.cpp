#include "algorithm/metaheuristic/variable_neighborhood_search/VnsOptimizer.hpp"
#include <random>
#include <sstream>

namespace uo {

VnsOptimizer::VnsOptimizer(
    std::vector<std::unique_ptr<SaNeighborhood>> neighborhoods,
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
        "vns",
        std::move(output_control),
        random_seed,
        std::move(additional_statistics_control))
    , neighborhoods_(std::move(neighborhoods)) {}

std::unique_ptr<Optimizer> VnsOptimizer::clone() const {
    std::vector<std::unique_ptr<SaNeighborhood>> cloned_neighborhoods;
    return std::make_unique<VnsOptimizer>(
        std::move(cloned_neighborhoods),
        finish_control(),
        problem().clone(),
        solution_template() ? solution_template()->clone() : nullptr,
        output_control(),
        random_seed(),
        additional_statistics_control()
    );
}

void VnsOptimizer::init() {
    Metaheuristic::init();
    if (solution_template()) {
        auto sol = solution_template()->clone();
        sol->init_random(problem());
        set_current_solution(std::move(sol));
    }
    set_evaluation(1);
    set_iteration(0);
    current_neighborhood_index_ = 0;
}

void VnsOptimizer::main_loop_iteration() {
    increment_iteration();

    if (!current_solution() || neighborhoods_.empty()) return;

    // Use current neighborhood to generate neighbor
    auto& neighborhood = neighborhoods_[current_neighborhood_index_];
    auto neighbor = neighborhood->generate_neighbor(*current_solution_, problem(), this);
    if (!neighbor) return;

    neighbor->evaluate(problem());

    auto cmp = current_solution_->is_better_than(*neighbor, problem());
    bool neighbor_is_better = cmp.has_value() && !cmp.value();

    if (neighbor_is_better) {
        set_current_solution(std::move(neighbor));
        current_neighborhood_index_ = 0; // restart from first neighborhood
    } else {
        // Move to next neighborhood
        current_neighborhood_index_ = (current_neighborhood_index_ + 1) % neighborhoods_.size();
    }
    increment_evaluation();
}

std::string VnsOptimizer::to_string() const {
    std::ostringstream oss;
    oss << "VnsOptimizer{"
        << SingleSolutionMetaheuristic::to_string()
        << ", neighborhood_count=" << neighborhoods_.size()
        << ", current_neighborhood=" << current_neighborhood_index_
        << "}";
    return oss.str();
}

} // namespace uo
