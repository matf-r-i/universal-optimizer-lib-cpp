#ifndef UO_ALGORITHM_SA_NEIGHBORHOOD_HPP
#define UO_ALGORITHM_SA_NEIGHBORHOOD_HPP

#include <memory>
#include "solution/Solution.hpp"
#include "problem/Problem.hpp"

namespace uo {

class Metaheuristic; // Forward declaration

class SaNeighborhood {
public:
    virtual ~SaNeighborhood() = default;

    [[nodiscard]] virtual std::unique_ptr<ISolution> generate_neighbor(
        const ISolution& current,
        const Problem& problem,
        const Metaheuristic* optimizer = nullptr) const = 0;

    [[nodiscard]] virtual std::string to_string() const = 0;
};

} // namespace uo

#endif // UO_ALGORITHM_SA_NEIGHBORHOOD_HPP
