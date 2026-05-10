#ifndef UO_UTILS_COMPLEX_COUNTER_UNIFORM_ASCENDING_HPP
#define UO_UTILS_COMPLEX_COUNTER_UNIFORM_ASCENDING_HPP

#include <stdexcept>
#include <string>
#include <vector>

namespace uo {

/**
 * @brief Complex counter with uniform values that counts only ascending data.
 * 
 * This is the C++ equivalent of the Python `ComplexCounterUniformAscending` class.
 * It generates combinations of `k` elements from `[0, counter_size-1]` in 
 * lexicographically ascending order (e.g., for k=3, n=6: [0,1,2], [0,1,3], ..., [3,4,5]).
 */
class ComplexCounterUniformAscending {
public:
    /**
     * @brief Construct a new ComplexCounterUniformAscending.
     * @param number_of_counters Number of counters (k) - number of items to pick.
     * @param counter_size Size of each counter (n) - max value for each position.
     */
    ComplexCounterUniformAscending(int number_of_counters, int counter_size);

    /**
     * @brief Get the current state (the current combination).
     * @return const std::vector<int>& The current combination values.
     */
    [[nodiscard]] const std::vector<int>& current_state() const noexcept { return counters_; }

    /**
     * @brief Reset the counter to the initial state.
     * @return bool True if progress is possible after resetting.
     */
    bool reset();

    /**
     * @brief Progress to the next combination.
     * @return bool True if progress was successful, false if enumeration is complete.
     */
    bool progress();

    /**
     * @brief Get the number of counters (k).
     * @return int Number of counters.
     */
    [[nodiscard]] int number_of_counters() const noexcept { return number_of_counters_; }

    /**
     * @brief Get the counter size (n).
     * @return int Counter size.
     */
    [[nodiscard]] int counter_size() const noexcept { return counter_size_; }

    /**
     * @brief String representation.
     * @return std::string Human-readable string.
     */
    [[nodiscard]] std::string to_string() const;

private:
    int number_of_counters_;
    int counter_size_;
    std::vector<int> counters_;
};

} // namespace uo

#endif // UO_UTILS_COMPLEX_COUNTER_UNIFORM_ASCENDING_HPP
