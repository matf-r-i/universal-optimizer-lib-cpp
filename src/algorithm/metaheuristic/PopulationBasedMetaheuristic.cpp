#include "algorithm/metaheuristic/PopulationBasedMetaheuristic.hpp"
#include <sstream>

namespace uo {

std::string PopulationBasedMetaheuristic::to_string() const {
    std::ostringstream oss;
    oss << "PopulationBasedMetaheuristic{"
        << Metaheuristic::to_string()
        << ", population_size=" << current_population_.size()
        << "}";
    return oss.str();
}

} // namespace uo
