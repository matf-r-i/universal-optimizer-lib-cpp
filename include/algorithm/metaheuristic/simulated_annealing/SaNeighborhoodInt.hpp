#ifndef UO_ALGORITHM_SA_NEIGHBORHOOD_INT_HPP
#define UO_ALGORITHM_SA_NEIGHBORHOOD_INT_HPP

#include <memory>
#include <string>

#include "algorithm/metaheuristic/simulated_annealing/SaNeighborhood.hpp"

namespace uo {

/**
 * @brief Integer neighborhood for Simulated Annealing.
 * Generates a neighbor by flipping k random bits in the integer representation.
 * Equivalent to Python's SaNeighborhoodInt.
 */
class SaNeighborhoodInt : public SaNeighborhood {
public:
    explicit SaNeighborhoodInt(int dimension, int k = 1);

    [[nodiscard]] std::unique_ptr<SaNeighborhood> clone() const override;

    [[nodiscard]] std::unique_ptr<ISolution> generate_neighbor(
        const ISolution& current,
        const Problem& problem,
        const Metaheuristic* optimizer = nullptr) const override;

    [[nodiscard]] std::string to_string() const override;

    [[nodiscard]] int dimension() const noexcept { return dimension_; }
    [[nodiscard]] int k() const noexcept { return k_; }

private:
    int dimension_;
    int k_;
};

} // namespace uo

#endif // UO_ALGORITHM_SA_NEIGHBORHOOD_INT_HPP

