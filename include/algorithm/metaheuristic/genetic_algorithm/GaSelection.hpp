#ifndef UO_ALGORITHM_GA_SELECTION_HPP
#define UO_ALGORITHM_GA_SELECTION_HPP

#include <memory>
#include <string>

namespace uo {

class Algorithm;

/**
 * @brief Abstract base class for GA selection strategies.
 * Equivalent to Python's GaSelection.
 */
class GaSelection {
public:
    virtual ~GaSelection() = default;

    [[nodiscard]] virtual std::unique_ptr<GaSelection> clone() const = 0;

    /**
     * @brief Perform selection on the optimizer's population.
     * @param optimizer The GA optimizer (derived from Algorithm) whose population is modified.
     */
    virtual void selection(Algorithm& optimizer) = 0;

    [[nodiscard]] virtual std::string to_string() const = 0;
};

} // namespace uo

#endif // UO_ALGORITHM_GA_SELECTION_HPP
