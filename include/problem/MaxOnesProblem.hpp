#ifndef UO_PROBLEM_MAX_ONES_HPP
#define UO_PROBLEM_MAX_ONES_HPP

#include <memory>
#include <string>
#include "problem/Problem.hpp"

namespace uo {

/**
 * @brief MaxOnes problem (maximize the number of 1-bits).
 * 
 * A simple benchmark optimization problem: find a binary string
 * with the maximum number of 1's.
 */
class MaxOnesProblem : public Problem {
public:
    explicit MaxOnesProblem(int dimension);

    [[nodiscard]] std::unique_ptr<Problem> clone() const override;
    [[nodiscard]] std::string to_string(const std::string& delimiter = "|",
                                         int indentation = 0,
                                         const std::string& indentation_symbol = "") const override;

    [[nodiscard]] int dimension() const noexcept { return dimension_; }

private:
    int dimension_;
};

} // namespace uo

#endif // UO_PROBLEM_MAX_ONES_HPP
