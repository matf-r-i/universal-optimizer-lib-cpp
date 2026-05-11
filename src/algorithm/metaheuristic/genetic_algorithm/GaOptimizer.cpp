#include "algorithm/metaheuristic/genetic_algorithm/GaOptimizer.hpp"
#include <algorithm>
#include <sstream>

namespace uo {

GaOptimizer::GaOptimizer(
    std::unique_ptr<GaCrossoverSupport> ga_crossover_support,
    std::unique_ptr<GaMutationSupport> ga_mutation_support,
    std::unique_ptr<GaSelection> ga_selection,
    int population_size,
    int elite_count,
    std::unique_ptr<FinishControl> finish_control,
    std::unique_ptr<Problem> problem,
    std::unique_ptr<ISolution> solution_tmpl,
    std::shared_ptr<OutputControl> output_control,
    std::optional<int> random_seed,
    std::shared_ptr<AdditionalStatisticsControl> additional_statistics_control)
    : PopulationBasedMetaheuristic(
        std::move(finish_control),
        std::move(problem),
        std::move(solution_tmpl),
        "ga",
        std::move(output_control),
        random_seed,
        std::move(additional_statistics_control))
    , ga_crossover_support_(std::move(ga_crossover_support))
    , ga_mutation_support_(std::move(ga_mutation_support))
    , ga_selection_(std::move(ga_selection))
    , population_size_(population_size)
    , elite_count_(elite_count) {
    
    // Initialize population with copies of solution template
    const ISolution* tmpl = solution_template();
    if (tmpl) {
        for (int i = 0; i < population_size_; ++i) {
            current_population_.push_back(tmpl->clone());
        }
    }
}

void GaOptimizer::init() {
    Algorithm::init();
    const ISolution* tmpl = solution_template();
    if (current_population_.empty() && tmpl) {
        for (int i = 0; i < population_size_; ++i) {
            current_population_.push_back(tmpl->clone());
        }
    }
    // Initialize all individuals in the population
    for (auto& individual : current_population_) {
        if (individual) {
            individual->init_random(problem());
            increment_evaluation();
            individual->evaluate(problem());
        }
    }
    // Set best solution as the best in the population
    if (!current_population_.empty()) {
        int best_idx = index_of_best_in_population();
        set_best_solution(current_population_[best_idx]->clone());
    }
    // Sort elites to the front if elite_count > 0
    if (elite_count_ > 0) {
        // Sort by fitness descending to bring elites to front
        std::sort(current_population_.begin(), current_population_.end(),
            [this](const std::unique_ptr<ISolution>& a, const std::unique_ptr<ISolution>& b) {
                auto a_fit = a->fitness_value();
                auto b_fit = b->fitness_value();
                if (!a_fit.has_value()) return false;
                if (!b_fit.has_value()) return true;
                return a_fit.value() > b_fit.value();
            });
    }
}

std::unique_ptr<ISolution> GaOptimizer::optimize() {
    init();
    main_loop();
    set_execution_ended(std::chrono::system_clock::now());
    return best_solution_ ? best_solution_->clone() : nullptr;
}

int GaOptimizer::index_of_best_in_population() const {
    int best_idx = 0;
    for (size_t i = 1; i < current_population_.size(); ++i) {
        auto cmp = current_population_[i]->is_better_than(
            *current_population_[best_idx], problem());
        if (cmp.has_value() && cmp.value()) {
            best_idx = static_cast<int>(i);
        }
    }
    return best_idx;
}

std::string GaOptimizer::to_string() const {
    std::ostringstream oss;
    oss << "GaOptimizer{"
        << PopulationBasedMetaheuristic::to_string()
        << ", population_size=" << population_size_
        << ", elite_count=" << elite_count_
        << ", crossover=" << (ga_crossover_support_ ? ga_crossover_support_->to_string() : "null")
        << ", mutation=" << (ga_mutation_support_ ? ga_mutation_support_->to_string() : "null")
        << ", selection=" << (ga_selection_ ? ga_selection_->to_string() : "null")
        << "}";
    return oss.str();
}

} // namespace uo

