#ifndef UO_ALGORITHM_POPULATION_BASED_METAHEURISTIC_HPP
#define UO_ALGORITHM_POPULATION_BASED_METAHEURISTIC_HPP

#include <memory>
#include <vector>

#include "algorithm/metaheuristic/Metaheuristic.hpp"

namespace uo {

class PopulationBasedMetaheuristic : public Metaheuristic {
public:
    using Metaheuristic::Metaheuristic;
    ~PopulationBasedMetaheuristic() override = default;

    PopulationBasedMetaheuristic(const PopulationBasedMetaheuristic&) = delete;
    PopulationBasedMetaheuristic& operator=(const PopulationBasedMetaheuristic&) = delete;
    PopulationBasedMetaheuristic(PopulationBasedMetaheuristic&&) = default;
    PopulationBasedMetaheuristic& operator=(PopulationBasedMetaheuristic&&) = default;

    [[nodiscard]] std::unique_ptr<Optimizer> clone() const override = 0;

    [[nodiscard]] const std::vector<std::unique_ptr<ISolution>>& current_population() const noexcept {
        return current_population_;
    }
    void set_current_population(std::vector<std::unique_ptr<ISolution>> pop) noexcept {
        current_population_ = std::move(pop);
    }

    [[nodiscard]] std::string to_string() const override;

protected:
    std::vector<std::unique_ptr<ISolution>> current_population_;
};

} // namespace uo

#endif // UO_ALGORITHM_POPULATION_BASED_METAHEURISTIC_HPP
