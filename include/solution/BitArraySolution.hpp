#ifndef UO_SOLUTION_BIT_ARRAY_SOLUTION_HPP
#define UO_SOLUTION_BIT_ARRAY_SOLUTION_HPP

#include <memory>
#include <random>
#include <string>
#include <vector>

#include "solution/Solution.hpp"
#include "problem/Problem.hpp"

namespace uo {

class BitArraySolution : public Solution<std::vector<bool>> {
public:
    explicit BitArraySolution(std::optional<int> random_seed = std::nullopt,
                              std::optional<double> fitness_value = std::nullopt,
                              std::optional<double> objective_value = std::nullopt,
                              bool is_feasible = false);

    [[nodiscard]] std::unique_ptr<ISolution> clone() const override;
    void copy_from(const ISolution& other) override;
    void init_random(const Problem& problem) override;
    void init_from(const std::string& representation, const Problem& problem) override;

    [[nodiscard]] QualityOfSolution calculate_quality_directly(const Problem& problem) override;
    [[nodiscard]] std::string to_string() const override;
    [[nodiscard]] std::vector<bool> native_representation(const std::string& representation_str) const override;
    [[nodiscard]] double representation_distance(const ISolution& other) const override;

    [[nodiscard]] int dimension() const noexcept { return static_cast<int>(representation_.size()); }
    void flip_bit(int index) {
        if (index >= 0 && index < static_cast<int>(representation_.size())) {
            representation_[index] = !representation_[index];
        }
    }
};

} // namespace uo

#endif // UO_SOLUTION_BIT_ARRAY_SOLUTION_HPP
