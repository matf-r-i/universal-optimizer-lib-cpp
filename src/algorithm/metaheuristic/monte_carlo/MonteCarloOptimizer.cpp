#include "algorithm/metaheuristic/monte_carlo/MonteCarloOptimizer.hpp"
#include <sstream>

namespace uo {

MonteCarloOptimizer::MonteCarloOptimizer(
    std::unique_ptr<FinishControl> finish_control,
    std::unique_ptr<Problem> problem,
    std::unique_ptr<ISolution> solution_template,
    std::shared_ptr<OutputControl> output_control,
    std::optional<int> random_seed,
    std::shared_ptr<AdditionalStatisticsControl> additional_statistics_control)
    : SingleSolutionMetaheuristic(
        std::move(finish_control),
        std::move(problem),
        std::move(solution_template),
        "MonteCarlo",
        std::move(output_control),
        random_seed,
        std::move(additional_statistics_control)) {}

std::unique_ptr<Optimizer> MonteCarloOptimizer::clone() const {
    return std::make_unique<MonteCarloOptimizer>(
        std::make_unique<FinishControl>(finish_control().clone()),
        problem().clone(),
        solution_template() ? solution_template()->clone() : nullptr,
        output_control(),
        random_seed(),
        additional_statistics_control()
    );
}

void MonteCarloOptimizer::init() {
    Algorithm::init();
    if (solution_template()) {
        auto sol = solution_template()->clone();
        sol->init_random(problem());
        set_current_solution(std::move(sol));
        set_evaluation(1);
        if (current_solution()) {
            current_solution_->evaluate(problem());
            set_best_solution(current_solution_->clone());
        }
    }
}

void MonteCarloOptimizer::main_loop_iteration() {
    increment_iteration();

    // Generate a new random solution
    if (solution_template()) {
        auto new_sol = solution_template()->clone();
        new_sol->init_random(problem());

        // Evaluate the new solution
        write_output_values_if_needed("before_evaluation", "b_e");
        increment_evaluation();
        new_sol->evaluate(problem());
        write_output_values_if_needed("after_evaluation", "b_e");

        // Check if the new solution is better than the best
        if (best_solution()) {
            auto cmp = new_sol->is_better_than(*best_solution_, problem());
            if (cmp.has_value() && cmp.value()) {
                // Update additional statistics
                update_additional_statistics_if_required(*new_sol);
                set_best_solution(std::move(new_sol));
            }
        } else {
            set_best_solution(std::move(new_sol));
        }
    }
}

std::string MonteCarloOptimizer::to_string() const {
    std::ostringstream oss;
    oss << "MonteCarloOptimizer{"
        << SingleSolutionMetaheuristic::to_string()
        << "}";
    return oss.str();
}

} // namespace uo
