#include "algorithm/metaheuristic/variable_neighborhood_search/VnsLocalSearchSupportIdle.hpp"

namespace uo {

std::unique_ptr<VnsLocalSearchSupport> VnsLocalSearchSupportIdle::clone() const {
    return std::make_unique<VnsLocalSearchSupportIdle>(dimension());
}

bool VnsLocalSearchSupportIdle::local_search(int /*k*/, const Problem& /*problem*/,
                                              ISolution& /*solution*/,
                                              SingleSolutionMetaheuristic& /*optimizer*/) {
    return false;
}

std::string VnsLocalSearchSupportIdle::to_string() const {
    return "VnsLocalSearchSupportIdle";
}

} // namespace uo
