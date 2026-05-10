#ifndef UO_PROBLEM_PROBLEM_HPP
#define UO_PROBLEM_PROBLEM_HPP

#include <string>
#include <memory>

namespace uo {

/**
 * @brief Abstract base class representing an optimization problem.
 * 
 * This is the C++ equivalent of the Python `Problem` class.
 * It provides a common interface for defining optimization problems,
 * including whether it is a minimization or multi-objective problem.
 */
class Problem {
public:
    /**
     * @brief Construct a new Problem object.
     * @param name The name of the problem.
     * @param is_minimization Whether this is a minimization problem.
     * @param is_multi_objective Whether this is a multi-objective problem.
     */
    Problem(std::string name, bool is_minimization, bool is_multi_objective);

    /// Virtual destructor for proper cleanup of derived classes.
    virtual ~Problem() = default;

    /// Prevent copy semantics; use clone() instead.
    Problem(const Problem&) = delete;
    Problem& operator=(const Problem&) = delete;

    /// Default move semantics.
    Problem(Problem&&) = default;
    Problem& operator=(Problem&&) = default;

    /**
     * @brief Polymorphic clone (deep copy).
     * @return std::unique_ptr<Problem> A new copy of this problem.
     */
    [[nodiscard]] virtual std::unique_ptr<Problem> clone() const = 0;

    /**
     * @brief Get the name of the problem.
     * @return const std::string& The problem name.
     */
    [[nodiscard]] const std::string& name() const noexcept { return name_; }

    /**
     * @brief Set the name of the problem.
     * @param name The new problem name.
     */
    void set_name(const std::string& name) { name_ = name; }

    /**
     * @brief Check whether this is a minimization problem.
     * @return true if minimization.
     */
    [[nodiscard]] bool is_minimization() const noexcept { return is_minimization_; }

    /**
     * @brief Set the minimization flag.
     * @param value Whether this is a minimization problem.
     */
    void set_is_minimization(bool value) noexcept { is_minimization_ = value; }

    /**
     * @brief Check whether this is a multi-objective problem.
     * @return true if multi-objective.
     */
    [[nodiscard]] bool is_multi_objective() const noexcept { return is_multi_objective_; }

    /**
     * @brief Set the multi-objective flag.
     * @param value Whether this is a multi-objective problem.
     */
    void set_is_multi_objective(bool value) noexcept { is_multi_objective_ = value; }

    /**
     * @brief String representation of this problem.
     * @param delimiter The delimiter to use between fields.
     * @param indentation The indentation level.
     * @return std::string The formatted string.
     */
    [[nodiscard]] virtual std::string to_string(
        const std::string& delimiter = "|",
        int indentation = 0,
        const std::string& indentation_symbol = "") const;

private:
    std::string name_;
    bool is_minimization_;
    bool is_multi_objective_;
};

} // namespace uo

#endif // UO_PROBLEM_PROBLEM_HPP
