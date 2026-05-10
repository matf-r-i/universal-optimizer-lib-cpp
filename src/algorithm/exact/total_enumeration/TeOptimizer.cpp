#include "algorithm/exact/total_enumeration/TeOptimizer.hpp"
#include <sstream>

namespace uo {

TeOptimizer::TeOptimizer(
    std::unique_ptr<TeOperationsSupport> te_operations_support,
    std::unique_ptr<Problem> problem,
    std::unique_ptr<ISolution> solution_template,
    std::shared_ptr<OutputControl> output_control)
    : Algorithm(std::move(problem), std::move(solution_template), "total_enumeration", std::move(output_control))
    , te_operations_support_(std::move(te_operations_support)) {}

std::unique_ptr<Optimizer> TeOptimizer::clone() const {
    return std::make_unique<TeOptimizer>(
        te_operations_support_ ? te_operations_support_->clone() : nullptr,
        problem().clone(),
        solution_template() ? solution_template()->clone() : nullptr,
        output_control()
    );
}

void TeOptimizer::init() {
    Algorithm::init();
    if (solution_template()) {
        current_solution_ = solution_template()->clone();
    }
    if (te_operations_support_ && current_solution_) {
        te_operations_support_->reset(problem(), *current_solution_, *this);
    }
    set_evaluation(1);
    // In real impl: evaluate and set best
    set_iteration(1);
}

std::unique_ptr<ISolution> TeOptimizer::optimize() {
    init();
    while (true) {
        increment_iteration();
        if (te_operations_support_) {
            te_operations_support_->progress(problem(), *current_solution_, *this);
        }
        if (te_operations_support_ && !te_operations_support_->can_progress(problem(), *current_solution_, *this)) {
            break;
        }
    }
    set_execution_ended(std::chrono::system_clock::now());
    return nullptr; // Would return best_solution
}

std::string TeOptimizer::to_string() const {
    std::ostringstream oss;
    oss << "TeOptimizer{"
        << Algorithm::to_string()
        << ", te_operations_support=" << (te_operations_support_ ? te_operations_support_->to_string() : "null")
        << "}";
    return oss.str();
}

} // namespace uo
