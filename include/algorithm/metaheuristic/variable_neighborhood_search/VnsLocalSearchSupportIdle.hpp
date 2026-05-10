#ifndef UO_ALGORITHM_VNS_LOCAL_SEARCH_SUPPORT_IDLE_HPP
#define UO_ALGORITHM_VNS_LOCAL_SEARCH_SUPPORT_IDLE_HPP

#include <memory>
#include <string>

#include "algorithm/metaheuristic/variable_neighborhood_search/VnsLocalSearchSupport.hpp"

namespace uo {

/**
 * @brief Idle VNS local search support that does nothing.
 */
class VnsLocalSearchSupportIdle : public VnsLocalSearchSupport {
public:
    using VnsLocalSearchSupport::VnsLocalSearchSupport;

    [[nodiscard]] std::unique_ptr<VnsLocalSearchSupport> clone() const override;
    bool local_search(int k, const Problem& problem, ISolution& solution,
                      SingleSolutionMetaheuristic& optimizer) override;
    [[nodiscard]] std::string to_string() const override;
};

} // namespace uo

#endif // UO_ALGORITHM_VNS_LOCAL_SEARCH_SUPPORT_IDLE_HPP
