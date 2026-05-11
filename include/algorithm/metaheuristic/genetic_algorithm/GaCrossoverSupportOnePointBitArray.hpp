#ifndef UO_ALGORITHM_GA_CROSSOVER_SUPPORT_ONE_POINT_BIT_ARRAY_HPP
#define UO_ALGORITHM_GA_CROSSOVER_SUPPORT_ONE_POINT_BIT_ARRAY_HPP

#include <memory>
#include <string>

#include "algorithm/metaheuristic/genetic_algorithm/GaCrossoverSupport.hpp"

namespace uo {

/**
 * @brief One-point crossover support for GA with BitArray solutions.
 * Equivalent to Python's GaCrossoverSupportOnePointBitArray.
 * Performs single-point crossover with a given probability.
 */
class GaCrossoverSupportOnePointBitArray : public GaCrossoverSupport {
public:
    explicit GaCrossoverSupportOnePointBitArray(double crossover_probability);

    [[nodiscard]] std::unique_ptr<GaCrossoverSupport> clone() const override;

    void crossover(
        const Problem& problem,
        const ISolution& solution1, const ISolution& solution2,
        ISolution& child1, ISolution& child2,
        PopulationBasedMetaheuristic& optimizer) override;

    [[nodiscard]] double crossover_probability() const noexcept { return crossover_probability_; }

    [[nodiscard]] std::string to_string() const override;

private:
    double crossover_probability_;
};

} // namespace uo

#endif // UO_ALGORITHM_GA_CROSSOVER_SUPPORT_ONE_POINT_BIT_ARRAY_HPP
