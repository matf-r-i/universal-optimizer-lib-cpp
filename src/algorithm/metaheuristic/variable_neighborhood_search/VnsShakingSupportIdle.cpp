#include "algorithm/metaheuristic/variable_neighborhood_search/VnsShakingSupportIdle.hpp"

namespace uo {

std::unique_ptr<VnsShakingSupport> VnsShakingSupportIdle::clone() const {
    return std::make_unique<VnsShakingSupportIdle>(dimension());
}

bool VnsShakingSupportIdle::shaking(int /*k*/, const Problem& /*problem*/, 
                                     ISolution& /*solution*/,
                                     SingleSolutionMetaheuristic& /*optimizer*/) {
    return false;
}

std::string VnsShakingSupportIdle::to_string() const {
    return "VnsShakingSupportIdle";
}

} // namespace uo
