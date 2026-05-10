#include "algorithm/metaheuristic/SingleSolutionMetaheuristic.hpp"
#include <sstream>

namespace uo {

std::string SingleSolutionMetaheuristic::to_string() const {
    std::ostringstream oss;
    oss << "SingleSolutionMetaheuristic{"
        << Metaheuristic::to_string()
        << ", current_solution=";
    if (current_solution_) {
        oss << current_solution_->to_string();
    } else {
        oss << "null";
    }
    oss << "}";
    return oss.str();
}

} // namespace uo
