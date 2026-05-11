#include "algorithm/metaheuristic/genetic_algorithm/GaOptimizerGenerational.hpp"
#include <algorithm>
#include <random>
#include <sstream>

namespace uo {

std::unique_ptr<Optimizer> GaOptimizerGenerational::clone() const {
    return std::make_unique<GaOptimizerGenerational>(
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

void GaOptimizerGenerational::main_loop_iteration() {
    increment_iteration();
    
    write_output_values_if_needed("before_step_in_iteration", "selection");
    ga_selection_->selection(*this);
    write_output_values_if_needed("after_step_in_iteration", "selection");

    int l_lim = (elite_count_ > 0) ? elite_count_ : 0;

    write_output_values_if_needed("before_step_in_iteration", "crossover");

    // Create new population from solution templates
    std::vector<std::unique_ptr<ISolution>> new_population;
    const ISolution* tmpl = solution_template();
    for (int i = 0; i < population_size_; ++i) {
        new_population.push_back(tmpl ? tmpl->clone() : nullptr);
    }

    // Copy elites to the new population
    if (l_lim > 0) {
        // Sort current population by fitness descending
        std::sort(current_population_.begin(), current_population_.end(),
            [this](const std::unique_ptr<ISolution>& a, const std::unique_ptr<ISolution>& b) {
                auto cmp = a->is_better_than(*b, problem());
                if (!cmp.has_value()) return false;
                return cmp.value();
            });
        // Copy elites
        for (int i = 0; i < l_lim; ++i) {
            new_population[i] = current_population_[i]->clone();
        }
    }

    // Create indices for non-elite positions
    std::vector<int> indices_for_selection;
    for (int i = l_lim; i < population_size_; ++i) {
        indices_for_selection.push_back(i);
    }

    std::mt19937& rng = rng_;

    // Perform crossover on pairs for non-elite individuals
    while (!indices_for_selection.empty()) {
        if (indices_for_selection.size() == 1) {
            // Single remaining individual, just copy from current population
            int sel_ind = indices_for_selection[0];
            new_population[sel_ind] = current_population_[sel_ind]->clone();
            indices_for_selection.clear();
            break;
        }

        std::uniform_int_distribution<int> dist(0, static_cast<int>(indices_for_selection.size()) - 1);
        
        int sel_idx1 = dist(rng);
        int sel_ind1 = indices_for_selection[sel_idx1];
        indices_for_selection.erase(indices_for_selection.begin() + sel_idx1);
        
        int sel_idx2 = dist(rng);
        int sel_ind2 = indices_for_selection[sel_idx2];
        indices_for_selection.erase(indices_for_selection.begin() + sel_idx2);

        ga_crossover_support_->crossover(
            problem(),
            *current_population_[sel_ind1], *current_population_[sel_ind2],
            *new_population[sel_ind1], *new_population[sel_ind2],
            *this);
    }
    write_output_values_if_needed("after_step_in_iteration", "crossover");

    write_output_values_if_needed("before_step_in_iteration", "mutation");
    for (int i = l_lim; i < population_size_; ++i) {
        ga_mutation_support_->mutation(
            problem(),
            *new_population[i],
            *this);
    }
    write_output_values_if_needed("after_step_in_iteration", "mutation");

    // Replace old population with new one
    current_population_ = std::move(new_population);

    // Update best solution
    int best_idx = index_of_best_in_population();
    set_best_solution(current_population_[best_idx]->clone());

    // Update additional statistics for each individual
    for (const auto& sol : current_population_) {
        update_additional_statistics_if_required(*sol);
    }
}

std::string GaOptimizerGenerational::to_string() const {
    std::ostringstream oss;
    oss << "GaOptimizerGenerational{"
        << GaOptimizer::to_string()
        << "}";
    return oss.str();
}

} // namespace uo

