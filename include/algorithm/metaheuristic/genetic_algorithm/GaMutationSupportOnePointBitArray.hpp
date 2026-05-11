#ifndef UO_ALGORITHM_GA_MUTATION_SUPPORT_ONE_POINT_BIT_ARRAY_HPP
#define UO_ALGORITHM_GA_MUTATION_SUPPORT_ONE_POINT_BIT_ARRAY_HPP

#include <memory>
#include <string>

#include "algorithm/metaheuristic/genetic_algorithm/GaMutationSupport.hpp"

namespace uo {

/**
 * @brief One-point mutation support for GA with BitArray solutions.
 * Equivalent to Python's GaMutationSupportOnePointBitArray.
 * Flips each bit with a given mutation probability.
 */
class GaMutationSupportOnePointBitArray : public GaMutationSupport {
public:
    explicit GaMutationSupportOnePointBitArray(double mutation_probability);

    [[nodiscard]] std::unique_ptr<GaMutationSupport> clone() const override;

    void mutation(
        const Problem& problem,
        ISolution& solution,
        PopulationBasedMetaheuristic& optimizer) override;

    [[nodiscard]] double mutation_probability() const noexcept { return mutation_probability_; }

    [[nodiscard]] std::string to_string() const override;

private:
    double mutation_probability_;
};

} // namespace uo

#endif // UO_ALGORITHM_GA_MUTATION_SUPPORT_ONE_POINT_BIT_ARRAY_HPP
