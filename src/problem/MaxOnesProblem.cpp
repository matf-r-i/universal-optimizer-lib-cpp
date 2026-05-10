#include "problem/MaxOnesProblem.hpp"
#include <sstream>

namespace uo {

MaxOnesProblem::MaxOnesProblem(int dimension)
    : Problem("MaxOnesProblem", false, false) // maximization, single-objective
    , dimension_(dimension) {}

std::unique_ptr<Problem> MaxOnesProblem::clone() const {
    return std::make_unique<MaxOnesProblem>(dimension_);
}

std::string MaxOnesProblem::to_string(const std::string& delimiter,
                                       int indentation,
                                       const std::string& indentation_symbol) const {
    std::ostringstream oss;
    oss << Problem::to_string(delimiter, indentation, indentation_symbol);
    // Could add dimension-specific info
    return oss.str();
}

} // namespace uo
