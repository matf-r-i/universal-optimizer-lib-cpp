#include "algorithm/metaheuristic/genetic_algorithm/GaOptimizerSteadyState.hpp"
#include <algorithm>
#include <random>
#include <sstream>

namespace uo {

std::unique_ptr<Optimizer> GaOptimizerSteadyState::clone() const {
    return std::make_unique<GaOptimizerSteadyState>(
        ga_crossover_support_ ? ga_crossover_support_->clone() : nullptr,
        ga_mutation_support_ ? ga_mutation_support_->clone() : nullptr,
        ga_selection_ ? ga_selection_->clone() : nullptr,
        population_size_,
        elite_count_,
        std::make_unique<FinishControl>(finish_control().clone()),
        problem().clone(),
        solution_template() ? solution_template()->clone() : nullptr,
        output_control(),
        random_seed(),
        additional_statistics_control()
    );
}

void GaOptimizerSteadyState::main_loop_iteration() {
    increment_iteration();
    
    write_output_values_if_needed("before_step_in_iteration", "selection");
    ga_selection_->selection(*this);
    write_output_values_if_needed("after_step_in_iteration", "selection");

    int l_lim = (elite_count_ > 0) ? elite_count_ : 0;

    write_output_values_if_needed("before_step_in_iteration", "crossover");

    // Create indices for selection (non-elite individuals)
    std::vector<int> indices_for_selection;
    for (int i = l_lim; i < static_cast<int>(current_population_.size()); ++i) {
        indices_for_selection.push_back(i);
    }

    // Perform crossover on pairs until all non-elite individuals are processed
    std::mt19937& rng = rng_;
    while (indices_for_selection.size() > 1) {
        std::uniform_int_distribution<int> dist(0, static_cast<int>(indices_for_selection.size()) - 1);
        
        int sel_idx1 = dist(rng);
        int sel_ind1 = indices_for_selection[sel_idx1];
        indices_for_selection.erase(indices_for_selection.begin() + sel_idx1);
        
        int sel_idx2 = dist(rng);
        int sel_ind2 = indices_for_selection[sel_idx2];
        indices_for_selection.erase(indices_for_selection.begin() + sel_idx2);

        // Create child solutions from the solution template
        const ISolution* tmpl = solution_template();
        auto child1 = tmpl ? tmpl->clone() : nullptr;
        auto child2 = tmpl ? tmpl->clone() : nullptr;

        ga_crossover_support_->crossover(
            problem(),
            *current_population_[sel_ind1], *current_population_[sel_ind2],
            *child1, *child2,
            *this);

        current_population_[sel_ind1] = std::move(child1);
        current_population_[sel_ind2] = std::move(child2);
    }
    write_output_values_if_needed("after_step_in_iteration", "crossover");

    write_output_values_if_needed("before_step_in_iteration", "mutation");
    for (int i = l_lim; i < static_cast<int>(current_population_.size()); ++i) {
        ga_mutation_support_->mutation(
            problem(),
            *current_population_[i],
            *this);
    }
    write_output_values_if_needed("after_step_in_iteration", "mutation");

    // Update best solution
    int best_idx = index_of_best_in_population();
    set_best_solution(current_population_[best_idx]->clone());

    // Update additional statistics for each individual in the population
    for (const auto& sol : current_population_) {
        update_additional_statistics_if_required(*sol);
    }
}

std::string GaOptimizerSteadyState::to_string() const {
    std::ostringstream oss;
    oss << "GaOptimizerSteadyState{"
        << GaOptimizer::to_string()
        << "}";
    return oss.str();
}

} // namespace uo

