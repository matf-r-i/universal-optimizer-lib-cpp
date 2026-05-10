#ifndef UO_ALGORITHM_SA_NEIGHBORHOOD_BIT_ARRAY_HPP
#define UO_ALGORITHM_SA_NEIGHBORHOOD_BIT_ARRAY_HPP

#include <memory>
#include <string>

#include "algorithm/metaheuristic/simulated_annealing/SaNeighborhood.hpp"

namespace uo {

/**
 * @brief BitArray neighborhood for Simulated Annealing.
 * Generates a neighbor by flipping k random bits in the bit array representation.
 * Equivalent to Python's SaNeighborhoodBitArray.
 */
class SaNeighborhoodBitArray : public SaNeighborhood {
public:
    explicit SaNeighborhoodBitArray(int dimension, int k = 1);

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

#endif // UO_ALGORITHM_SA_NEIGHBORHOOD_BIT_ARRAY_HPP

