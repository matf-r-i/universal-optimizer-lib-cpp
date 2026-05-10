#ifndef UO_ALGORITHM_TE_OPERATIONS_SUPPORT_HPP
#define UO_ALGORITHM_TE_OPERATIONS_SUPPORT_HPP

#include <memory>
#include "solution/Solution.hpp"
#include "problem/Problem.hpp"

namespace uo {

class Algorithm; // Forward declaration

/**
 * @brief Support operations for Total Enumeration (TE) algorithm.
 * 
 * Defines reset, progress, and can_progress operations for enumerating
 * all possible solutions of a problem.
 */
class TeOperationsSupport {
public:
    virtual ~TeOperationsSupport() = default;

    /** @brief Reset to the initial state for enumeration. */
    virtual void reset(const Problem& problem, ISolution& solution, Algorithm& algorithm) = 0;

    /** @brief Progress to the next solution in the enumeration. */
    virtual void progress(const Problem& problem, ISolution& solution, Algorithm& algorithm) = 0;

    /** @brief Check whether enumeration can progress further. */
    [[nodiscard]] virtual bool can_progress(const Problem& problem, ISolution& solution, Algorithm& algorithm) = 0;

    /** @brief Get the total number of evaluations needed for full enumeration. */
    [[nodiscard]] virtual long long overall_number_of_evaluations(
        const Problem& problem, ISolution& solution, Algorithm& algorithm) = 0;

    /** @brief Polymorphic clone. */
    [[nodiscard]] virtual std::unique_ptr<TeOperationsSupport> clone() const = 0;

    /** @brief String representation. */
    [[nodiscard]] virtual std::string to_string() const = 0;
};

} // namespace uo

#endif // UO_ALGORITHM_TE_OPERATIONS_SUPPORT_HPP
