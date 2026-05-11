#include "algorithm/metaheuristic/genetic_algorithm/GaSelectionIdle.hpp"

namespace uo {

std::unique_ptr<GaSelection> GaSelectionIdle::clone() const {
    return std::make_unique<GaSelectionIdle>();
}

void GaSelectionIdle::selection(Algorithm& optimizer) {
    (void)optimizer; // No-op
}

std::string GaSelectionIdle::to_string() const {
    return "GaSelectionIdle";
}

} // namespace uo
