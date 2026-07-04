#include "algorithm/Algorithm.hpp"
#include <sstream>

namespace uo {

Algorithm::Algorithm(std::unique_ptr<Problem> problem,
                     std::unique_ptr<ISolution> solution_template,
                     std::string name,
                     std::shared_ptr<OutputControl> output_control)
    : Optimizer(std::move(problem), std::move(name), std::move(output_control))
    , solution_template_(std::move(solution_template)) {}

void Algorithm::init() {
    Optimizer::init();
    evaluation_ = 0;
    iteration_ = 0;
    iteration_best_found_ = 0;
    evaluation_best_found_ = 0;
}

std::string Algorithm::to_string() const {
    std::ostringstream oss;
    oss << "Algorithm{"
        << "name=" << Optimizer::to_string()
        << ", evaluation=" << evaluation_
        << ", iteration=" << iteration_
        << "}";
    return oss.str();
}

} // namespace uo
