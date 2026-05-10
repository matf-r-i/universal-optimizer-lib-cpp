#ifndef UO_ALGORITHM_VNS_SHAKING_SUPPORT_HPP
#define UO_ALGORITHM_VNS_SHAKING_SUPPORT_HPP

#include <memory>
#include <string>

#include "problem/Problem.hpp"
#include "solution/Solution.hpp"

namespace uo {

class SingleSolutionMetaheuristic; // forward declaration

/**
 * @brief Abstract base class for VNS shaking support.
 * 
 * This is the C++ equivalent of the Python `VnsShakingSupport` class.
 * It defines the interface for generating random perturbations (shaking)
 * in Variable Neighborhood Search.
 */
class VnsShakingSupport {
public:
    explicit VnsShakingSupport(int dimension) : dimension_(dimension) {}
    virtual ~VnsShakingSupport() = default;

    /**
     * @brief Polymorphic clone.
     * @return std::unique_ptr<VnsShakingSupport> A new copy.
     */
    [[nodiscard]] virtual std::unique_ptr<VnsShakingSupport> clone() const = 0;

    /**
     * @brief Get the dimension.
     * @return int The dimension.
     */
    [[nodiscard]] int dimension() const noexcept { return dimension_; }

    /**
     * @brief Perform the shaking operation.
     * @param k VNS parameter k (neighborhood index).
     * @param problem The problem being solved.
     * @param solution The solution to shake.
     * @param optimizer The optimizer context.
     * @return bool True if shaking was successful.
     */
    virtual bool shaking(int k, const Problem& problem, ISolution& solution, 
                         SingleSolutionMetaheuristic& optimizer) = 0;

    /**
     * @brief String representation.
     * @return std::string Human-readable string.
     */
    [[nodiscard]] virtual std::string to_string() const = 0;

private:
    int dimension_;
};

} // namespace uo

#endif // UO_ALGORITHM_VNS_SHAKING_SUPPORT_HPP
