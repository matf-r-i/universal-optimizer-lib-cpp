#ifndef UO_ALGORITHM_VNS_LOCAL_SEARCH_SUPPORT_HPP
#define UO_ALGORITHM_VNS_LOCAL_SEARCH_SUPPORT_HPP

#include <memory>
#include <string>

#include "problem/Problem.hpp"
#include "solution/Solution.hpp"

namespace uo {

class SingleSolutionMetaheuristic; // forward declaration

/**
 * @brief Abstract base class for VNS local search support.
 * 
 * This is the C++ equivalent of the Python `VnsLocalSearchSupport` class.
 * It defines the interface for local search procedures in Variable Neighborhood Search.
 */
class VnsLocalSearchSupport {
public:
    explicit VnsLocalSearchSupport(int dimension) : dimension_(dimension) {}
    virtual ~VnsLocalSearchSupport() = default;

    /**
     * @brief Polymorphic clone.
     * @return std::unique_ptr<VnsLocalSearchSupport> A new copy.
     */
    [[nodiscard]] virtual std::unique_ptr<VnsLocalSearchSupport> clone() const = 0;

    /**
     * @brief Get the dimension.
     * @return int The dimension.
     */
    [[nodiscard]] int dimension() const noexcept { return dimension_; }

    /**
     * @brief Execute the local search procedure.
     * @param k VNS parameter k (neighborhood index).
     * @param problem The problem being solved.
     * @param solution The solution to improve.
     * @param optimizer The optimizer context.
     * @return bool True if local search found an improvement.
     */
    virtual bool local_search(int k, const Problem& problem, ISolution& solution,
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

#endif // UO_ALGORITHM_VNS_LOCAL_SEARCH_SUPPORT_HPP
