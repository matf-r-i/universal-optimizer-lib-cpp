#ifndef UO_SOLUTION_QUALITY_OF_SOLUTION_HPP
#define UO_SOLUTION_QUALITY_OF_SOLUTION_HPP

#include <optional>
#include <vector>
#include <string>

namespace uo {

/**
 * @brief Represents the quality of a solution in terms of fitness, objective value, and feasibility.
 * 
 * This structure mirrors the Python class QualityOfSolution and serves as a container
 * for evaluation results returned by solution evaluation methods.
 */
class QualityOfSolution {
public:
    /**
     * @brief Default constructor.
     */
    QualityOfSolution() = default;

    /**
     * @brief Construct a new QualityOfSolution object.
     * @param objective_value The objective value of the solution (e.g., cost, profit).
     * @param fitness_value The fitness value derived from the objective.
     * @param is_feasible Whether the solution satisfies all constraints.
     */
    QualityOfSolution(std::optional<double> objective_value,
                     std::optional<double> fitness_value,
                     bool is_feasible);

    /**
     * @brief Get the objective value.
     * @return std::optional<double> The objective value, if set.
     */
    [[nodiscard]] std::optional<double> objective_value() const noexcept { return objective_value_; }

    /**
     * @brief Set the objective value.
     * @param value The objective value to set.
     */
    void set_objective_value(std::optional<double> value) noexcept { objective_value_ = value; }

    /**
     * @brief Get the fitness value.
     * @return std::optional<double> The fitness value, if set.
     */
    [[nodiscard]] std::optional<double> fitness_value() const noexcept { return fitness_value_; }

    /**
     * @brief Set the fitness value.
     * @param value The fitness value to set.
     */
    void set_fitness_value(std::optional<double> value) noexcept { fitness_value_ = value; }

    /**
     * @brief Check if the solution is feasible.
     * @return true if the solution is feasible.
     */
    [[nodiscard]] bool is_feasible() const noexcept { return is_feasible_; }

    /**
     * @brief Set the feasibility flag.
     * @param value true if the solution is feasible.
     */
    void set_is_feasible(bool value) noexcept { is_feasible_ = value; }

    /**
     * @brief String representation of this QualityOfSolution.
     * @return std::string A human-readable string.
     */
    [[nodiscard]] std::string to_string() const;

private:
    std::optional<double> objective_value_{std::nullopt};
    std::optional<double> fitness_value_{std::nullopt};
    bool is_feasible_{false};
};

} // namespace uo

#endif // UO_SOLUTION_QUALITY_OF_SOLUTION_HPP
