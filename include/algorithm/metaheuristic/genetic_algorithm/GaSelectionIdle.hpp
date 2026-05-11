#ifndef UO_ALGORITHM_GA_SELECTION_IDLE_HPP
#define UO_ALGORITHM_GA_SELECTION_IDLE_HPP

#include <memory>
#include <string>

#include "algorithm/metaheuristic/genetic_algorithm/GaSelection.hpp"

namespace uo {

/**
 * @brief Idle (no-op) selection for GA.
 * Equivalent to Python's GaSelectionIdle.
 */
class GaSelectionIdle : public GaSelection {
public:
    [[nodiscard]] std::unique_ptr<GaSelection> clone() const override;
    void selection(Algorithm& optimizer) override;
    [[nodiscard]] std::string to_string() const override;
};

} // namespace uo

#endif // UO_ALGORITHM_GA_SELECTION_IDLE_HPP
