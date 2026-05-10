#include "algorithm/Optimizer.hpp"
#include <chrono>
#include <sstream>

namespace uo {

Optimizer::Optimizer(std::unique_ptr<Problem> problem,
                     std::string name,
                     std::shared_ptr<OutputControl> output_control)
    : problem_(std::move(problem))
    , name_(std::move(name))
    , output_control_(std::move(output_control)) {}

void Optimizer::init() {
    execution_started_ = std::chrono::system_clock::now();
}

double Optimizer::elapsed_seconds() const {
    auto now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(
        now - execution_started_);
    return elapsed.count();
}

std::string Optimizer::to_string() const {
    std::ostringstream oss;
    oss << "Optimizer{name=" << name_
        << ", problem=" << (problem_ ? problem_->to_string() : "null")
        << "}";
    return oss.str();
}

} // namespace uo
