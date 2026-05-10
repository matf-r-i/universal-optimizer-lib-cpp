#ifndef UO_ALGORITHM_VNS_LOCAL_SEARCH_SUPPORT_STANDARD_BI_BIT_ARRAY_HPP
#define UO_ALGORITHM_VNS_LOCAL_SEARCH_SUPPORT_STANDARD_BI_BIT_ARRAY_HPP

#include <memory>
#include <string>

#include "algorithm/metaheuristic/variable_neighborhood_search/VnsLocalSearchSupport.hpp"
#include "utils/ComplexCounterUniformAscending.hpp"

namespace uo {

/**
 * @brief Best Improvement local search for BitArray solutions in VNS.
 * Inverts combinations of k bits and selects the best improvement.
 */
class VnsLocalSearchSupportStandardBestImprovementBitArray : public VnsLocalSearchSupport {
public:
    using VnsLocalSearchSupport::VnsLocalSearchSupport;

    [[nodiscard]] std::unique_ptr<VnsLocalSearchSupport> clone() const override;
    bool local_search(int k, const Problem& problem, ISolution& solution,
                      SingleSolutionMetaheuristic& optimizer) override;
    [[nodiscard]] std::string to_string() const override;
};

} // namespace uo

#endif // UO_ALGORITHM_VNS_LOCAL_SEARCH_SUPPORT_STANDARD_BI_BIT_ARRAY_HPP
