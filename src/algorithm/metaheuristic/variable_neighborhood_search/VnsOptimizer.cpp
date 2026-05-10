#include "algorithm/metaheuristic/variable_neighborhood_search/VnsOptimizer.hpp"
#include <sstream>

namespace uo {

VnsOptimizer::VnsOptimizer(
    std::unique_ptr<VnsShakingSupport> vns_shaking_support,
    std::unique_ptr<VnsLocalSearchSupport> vns_ls_support,
    int k_min,
    int k_max,
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
    , vns_shaking_support_(std::move(vns_shaking_support))
    , vns_ls_support_(std::move(vns_ls_support))
    , k_min_(k_min)
    , k_max_(k_max) {}

std::unique_ptr<Optimizer> VnsOptimizer::clone() const {
    std::unique_ptr<VnsShakingSupport> vss = vns_shaking_support_ ? vns_shaking_support_->clone() : nullptr;
    std::unique_ptr<VnsLocalSearchSupport> vls = vns_ls_support_ ? vns_ls_support_->clone() : nullptr;
    return std::make_unique<VnsOptimizer>(
        std::move(vss),
        std::move(vls),
        k_min_,
        k_max_,
        finish_control(),
        problem().clone(),
        solution_template() ? solution_template()->clone() : nullptr,
        output_control(),
        random_seed(),
        additional_statistics_control()
    );
}

void VnsOptimizer::init() {
    // Call Algorithm::init() directly - Metaheuristic::init() is pure virtual
    Algorithm::init();
    k_current_ = k_min_;
    if (solution_template()) {
        auto sol = solution_template()->clone();
        sol->copy_from(*solution_template());
        sol->init_random(problem());
        set_current_solution(std::move(sol));
        set_evaluation(1);
        if (current_solution()) {
            set_best_solution(current_solution()->clone());
        }
    }
}

void VnsOptimizer::main_loop_iteration() {
    // Step 1: Shaking phase
    write_output_values_if_needed("before_step_in_iteration", "shaking");
    if (!vns_shaking_support_ || 
        !vns_shaking_support_->shaking(k_current_, problem(), *current_solution_, *this)) {
        write_output_values_if_needed("after_step_in_iteration", "shaking");
        return;
    }
    write_output_values_if_needed("after_step_in_iteration", "shaking");
    
    increment_iteration();
    
    // Step 2: Local search phase (repeat while k_current <= k_max)
    while (k_current_ <= k_max_) {
        write_output_values_if_needed("before_step_in_iteration", "ls");
        bool improvement = false;
        if (vns_ls_support_) {
            improvement = vns_ls_support_->local_search(k_current_, problem(), *current_solution_, *this);
        }
        write_output_values_if_needed("after_step_in_iteration", "ls");
        
        if (improvement) {
            // Update statistics and reset k
            update_additional_statistics_if_required(*current_solution_);
            set_best_solution(current_solution_->clone());
            k_current_ = k_min_;
        } else {
            k_current_ += 1;
        }
    }
}

std::string VnsOptimizer::to_string() const {
    std::ostringstream oss;
    oss << "VnsOptimizer{"
        << SingleSolutionMetaheuristic::to_string()
        << ", k_min=" << k_min_
        << ", k_max=" << k_max_
        << ", k_current=" << k_current_
        << ", shaking=" << (vns_shaking_support_ ? vns_shaking_support_->to_string() : "null")
        << ", ls=" << (vns_ls_support_ ? vns_ls_support_->to_string() : "null")
        << "}";
    return oss.str();
}

} // namespace uo
