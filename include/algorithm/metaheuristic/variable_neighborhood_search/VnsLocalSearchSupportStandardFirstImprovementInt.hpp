#ifndef UO_ALGORITHM_VNS_LOCAL_SEARCH_SUPPORT_STANDARD_FI_INT_HPP
#define UO_ALGORITHM_VNS_LOCAL_SEARCH_SUPPORT_STANDARD_FI_INT_HPP

#include <memory>
#include <string>

#include "algorithm/metaheuristic/variable_neighborhood_search/VnsLocalSearchSupport.hpp"
#include "utils/ComplexCounterUniformAscending.hpp"

namespace uo {

/**
 * @brief First Improvement local search for Int solutions in VNS.
 */
class VnsLocalSearchSupportStandardFirstImprovementInt : public VnsLocalSearchSupport {
public:
    using VnsLocalSearchSupport::VnsLocalSearchSupport;

    [[nodiscard]] std::unique_ptr<VnsLocalSearchSupport> clone() const override;
    bool local_search(int k, const Problem& problem, ISolution& solution,
                      SingleSolutionMetaheuristic& optimizer) override;
    [[nodiscard]] std::string to_string() const override;
};

} // namespace uo

#endif // UO_ALGORITHM_VNS_LOCAL_SEARCH_SUPPORT_STANDARD_FI_INT_HPP
