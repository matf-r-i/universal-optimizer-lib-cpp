#ifndef UO_ALGORITHM_VNS_SHAKING_SUPPORT_IDLE_HPP
#define UO_ALGORITHM_VNS_SHAKING_SUPPORT_IDLE_HPP

#include <memory>
#include <string>

#include "algorithm/metaheuristic/variable_neighborhood_search/VnsShakingSupport.hpp"

namespace uo {

/**
 * @brief Idle VNS shaking support that does nothing.
 */
class VnsShakingSupportIdle : public VnsShakingSupport {
public:
    using VnsShakingSupport::VnsShakingSupport;

    [[nodiscard]] std::unique_ptr<VnsShakingSupport> clone() const override;
    bool shaking(int k, const Problem& problem, ISolution& solution,
                 SingleSolutionMetaheuristic& optimizer) override;
    [[nodiscard]] std::string to_string() const override;
};

} // namespace uo

#endif // UO_ALGORITHM_VNS_SHAKING_SUPPORT_IDLE_HPP
