#ifndef UO_ALGORITHM_OUTPUT_CONTROL_HPP
#define UO_ALGORITHM_OUTPUT_CONTROL_HPP

#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace uo {

/**
 * @brief Controls when and what output is written during algorithm execution.
 * 
 * This is the C++ equivalent of the Python `OutputControl` class.
 * It determines output moments (before/after algorithm, iteration, evaluation)
 * and which fields are written.
 */
class OutputControl {
public:
    /**
     * @brief Construct a new OutputControl object.
     * @param output_stream The output stream to write to (default: nullptr, no output).
     * @param fields Comma-separated field definitions (e.g., "iteration, evaluation, best_solution.fitness_value").
     * @param moments Comma-separated moments for output (e.g., "after_algorithm, after_iteration").
     */
    explicit OutputControl(
        std::shared_ptr<std::ostream> output_stream = nullptr,
        std::string fields = "iteration, evaluation, step_name, "
                             "best_solution.string_representation(), "
                             "best_solution.fitness_value, "
                             "best_solution.objective_value, "
                             "best_solution.is_feasible",
        std::string moments = "after_algorithm");

    /**
     * @brief Create a deep copy of this OutputControl.
     * @return OutputControl A new copy.
     */
    [[nodiscard]] OutputControl clone() const;

    //@{
    /// @name Output stream management
    /** @brief Get the output stream. */
    [[nodiscard]] std::shared_ptr<std::ostream> output_stream() const noexcept { return output_stream_; }

    /** @brief Set the output stream. */
    void set_output_stream(std::shared_ptr<std::ostream> stream) noexcept { output_stream_ = std::move(stream); }
    //@}

    //@{
    /// @name Field management
    /** @brief Get the field headings. */
    [[nodiscard]] const std::vector<std::string>& field_headings() const noexcept { return field_headings_; }

    /** @brief Get the field definitions. */
    [[nodiscard]] const std::vector<std::string>& field_definitions() const noexcept { return field_definitions_; }
    //@}

    //@{
    /// @name Moment flags
    /** @brief Check whether to write before algorithm execution. */
    [[nodiscard]] bool write_before_algorithm() const noexcept { return write_before_algorithm_; }

    /** @brief Check whether to write after algorithm execution. */
    [[nodiscard]] bool write_after_algorithm() const noexcept { return write_after_algorithm_; }

    /** @brief Check whether to write before each iteration. */
    [[nodiscard]] bool write_before_iteration() const noexcept { return write_before_iteration_; }

    /** @brief Check whether to write after each iteration. */
    [[nodiscard]] bool write_after_iteration() const noexcept { return write_after_iteration_; }

    /** @brief Check whether to write before each evaluation. */
    [[nodiscard]] bool write_before_evaluation() const noexcept { return write_before_evaluation_; }

    /** @brief Check whether to write after each evaluation. */
    [[nodiscard]] bool write_after_evaluation() const noexcept { return write_after_evaluation_; }
    //@}

    /**
     * @brief String representation of this OutputControl.
     * @return std::string A human-readable string.
     */
    [[nodiscard]] std::string to_string() const;

private:
    void parse_fields(const std::string& fields);
    void parse_moments(const std::string& moments);

    std::shared_ptr<std::ostream> output_stream_;
    std::vector<std::string> field_headings_;
    std::vector<std::string> field_definitions_;

    bool write_before_algorithm_{false};
    bool write_after_algorithm_{true};
    bool write_before_iteration_{false};
    bool write_after_iteration_{false};
    bool write_before_evaluation_{false};
    bool write_after_evaluation_{false};
};

} // namespace uo

#endif // UO_ALGORITHM_OUTPUT_CONTROL_HPP
