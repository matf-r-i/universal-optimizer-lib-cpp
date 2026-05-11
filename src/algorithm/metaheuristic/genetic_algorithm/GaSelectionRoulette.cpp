#include "algorithm/metaheuristic/genetic_algorithm/GaSelectionRoulette.hpp"
#include "algorithm/metaheuristic/genetic_algorithm/GaOptimizer.hpp"
#include <random>

namespace uo {

std::unique_ptr<GaSelection> GaSelectionRoulette::clone() const {
    return std::make_unique<GaSelectionRoulette>();
}

void GaSelectionRoulette::selection(Algorithm& optimizer) {
    // Dynamic cast to GaOptimizer to access GA-specific members
    auto* ga_opt = dynamic_cast<GaOptimizer*>(&optimizer);
    if (!ga_opt) {
        return; // Not a GA optimizer, nothing to do
    }

    auto& pop = const_cast<std::vector<std::unique_ptr<ISolution>>&>(
        ga_opt->current_population());
    if (pop.empty()) {
        return;
    }

    int n = static_cast<int>(pop.size());
    int n_e = ga_opt->elite_count();
    int l_lim = (n_e > 0) ? n_e : 0;

    if (l_lim >= n) {
        return; // No non-elite individuals to select
    }

    std::mt19937& rng = ga_opt->rng();
    std::uniform_int_distribution<int> dist(0, n - 1);

    // Create temporary storage for selected individuals
    std::vector<std::unique_ptr<ISolution>> temp;
    for (int i = l_lim; i < n; ++i) {
        int ind = dist(rng);
        temp.push_back(pop[ind]->clone());
    }

    // Replace the non-elite portion of the population
    for (int i = l_lim; i < n; ++i) {
        pop[i] = std::move(temp[i - l_lim]);
    }
}

std::string GaSelectionRoulette::to_string() const {
    return "GaSelectionRoulette";
}

} // namespace uo
