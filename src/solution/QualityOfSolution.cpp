#include "solution/QualityOfSolution.hpp"
#include <sstream>

namespace uo {

QualityOfSolution::QualityOfSolution(std::optional<double> objective_value,
                                     std::optional<double> fitness_value,
                                     bool is_feasible)
    : objective_value_(objective_value)
    , fitness_value_(fitness_value)
    , is_feasible_(is_feasible) {}

std::string QualityOfSolution::to_string() const {
    std::ostringstream oss;
    oss << "QualityOfSolution{"
        << "objective_value=";
    if (objective_value_) oss << *objective_value_; else oss << "nullopt";
    oss << ", fitness_value=";
    if (fitness_value_) oss << *fitness_value_; else oss << "nullopt";
    oss << ", is_feasible=" << (is_feasible_ ? "true" : "false")
        << "}";
    return oss.str();
}

} // namespace uo
