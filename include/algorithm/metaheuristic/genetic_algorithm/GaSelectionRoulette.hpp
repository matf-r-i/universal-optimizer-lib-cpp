#ifndef UO_ALGORITHM_GA_SELECTION_ROULETTE_HPP
#define UO_ALGORITHM_GA_SELECTION_ROULETTE_HPP

#include <memory>
#include <string>

#include "algorithm/metaheuristic/genetic_algorithm/GaSelection.hpp"

namespace uo {

/**
 * @brief Roulette wheel selection for GA.
 * Equivalent to Python's GaSelectionRoulette.
 * Selects random individuals from the population (with replacement) 
 * starting from the elite index.
 */
class GaSelectionRoulette : public GaSelection {
public:
    [[nodiscard]] std::unique_ptr<GaSelection> clone() const override;
    void selection(Algorithm& optimizer) override;
    [[nodiscard]] std::string to_string() const override;
};

} // namespace uo

#endif // UO_ALGORITHM_GA_SELECTION_ROULETTE_HPP
