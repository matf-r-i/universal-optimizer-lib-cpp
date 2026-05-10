#ifndef UO_SOLUTION_SOLUTION_HPP
#define UO_SOLUTION_SOLUTION_HPP

#include <memory>
#include <optional>
#include <random>
#include <string>
#include <vector>

#include "solution/QualityOfSolution.hpp"
#include "problem/Problem.hpp"

namespace uo {

// Forward declaration
class ISolution;

/**
 * @brief Abstract interface for optimization solutions (type-erased).
 * 
 * This allows the algorithm hierarchy to work with solutions without
 * knowing the concrete representation type.
 */
class ISolution {
public:
    virtual ~ISolution() = default;

    /** @brief Polymorphic clone. */
    [[nodiscard]] virtual std::unique_ptr<ISolution> clone() const = 0;

    /** @brief Copy data from another solution. */
    virtual void copy_from(const ISolution& other) = 0;

    /** @brief Random initialization. */
    virtual void init_random(const Problem& problem) = 0;

    /** @brief Initialize from a string representation. */
    virtual void init_from(const std::string& representation, const Problem& problem) = 0;

    /** @brief Get the string code for this solution. */
    [[nodiscard]] virtual std::string to_string() const = 0;

    //@{
    /// @name Quality methods
    /** @brief Calculate quality directly. */
    [[nodiscard]] virtual QualityOfSolution calculate_quality_directly(const Problem& problem) = 0;

    /** @brief Evaluate this solution. */
    virtual void evaluate(const Problem& problem) = 0;
    //@}

    //@{
    /// @name Fitness and objective
    /** @brief Get the fitness value. */
    [[nodiscard]] virtual std::optional<double> fitness_value() const = 0;

    /** @brief Set the fitness value. */
    virtual void set_fitness_value(std::optional<double> value) = 0;

    /** @brief Get the objective value. */
    [[nodiscard]] virtual std::optional<double> objective_value() const = 0;

    /** @brief Set the objective value. */
    virtual void set_objective_value(std::optional<double> value) = 0;
    //@}

    //@{
    /// @name Feasibility
    /** @brief Check if the solution is feasible. */
    [[nodiscard]] virtual bool is_feasible() const = 0;

    /** @brief Set the feasibility flag. */
    virtual void set_is_feasible(bool value) = 0;
    //@}

    //@{
    /// @name Comparison
    /** @brief Check if this solution is better than another. */
    [[nodiscard]] virtual std::optional<bool> is_better_than(
        const ISolution& other, const Problem& problem) const = 0;
    //@}

    //@{
    /// @name Distance
    /** @brief Calculate distance between two solutions. */
    [[nodiscard]] virtual double representation_distance(
        const ISolution& other) const = 0;
    //@}

    /** @brief Get the random seed. */
    [[nodiscard]] virtual int random_seed() const = 0;
};

/**
 * @brief Templated solution implementation wrapping a concrete representation.
 * 
 * @tparam R The type of the native representation (e.g., std::vector<bool>, int, std::string).
 */
template <typename R>
class Solution : public ISolution {
public:
    Solution() = default;

    explicit Solution(std::optional<int> random_seed = std::nullopt,
                      std::optional<double> fitness_value = std::nullopt,
                      std::optional<double> objective_value = std::nullopt,
                      bool is_feasible = false)
        : fitness_value_(fitness_value)
        , objective_value_(objective_value)
        , is_feasible_(is_feasible)
    {
        if (random_seed.has_value() && random_seed.value() != 0) {
            random_seed_ = random_seed.value();
        } else {
            random_seed_ = std::random_device{}();
        }
        rng_.seed(random_seed_);
    }

    ~Solution() override = default;

    [[nodiscard]] std::unique_ptr<ISolution> clone() const override {
        auto cloned = std::make_unique<Solution<R>>();
        cloned->copy_from(*this);
        return cloned;
    }

    void copy_from(const ISolution& other) override {
        auto* derived = dynamic_cast<const Solution<R>*>(&other);
        if (derived) {
            representation_ = derived->representation_;
            fitness_value_ = derived->fitness_value_;
            objective_value_ = derived->objective_value_;
            is_feasible_ = derived->is_feasible_;
            random_seed_ = derived->random_seed_;
        }
    }

    //@{
    /// @name Representation accessors
    [[nodiscard]] const R& representation() const noexcept { return representation_; }
    void set_representation(const R& repr) { representation_ = repr; }
    void set_representation(R&& repr) { representation_ = std::move(repr); }
    //@}

    [[nodiscard]] std::optional<double> fitness_value() const override { return fitness_value_; }
    void set_fitness_value(std::optional<double> value) override { fitness_value_ = value; }

    [[nodiscard]] std::optional<double> objective_value() const override { return objective_value_; }
    void set_objective_value(std::optional<double> value) override { objective_value_ = value; }

    [[nodiscard]] bool is_feasible() const override { return is_feasible_; }
    void set_is_feasible(bool value) override { is_feasible_ = value; }

    [[nodiscard]] int random_seed() const override { return random_seed_; }

    [[nodiscard]] std::optional<bool> is_better_than(
        const ISolution& other, const Problem& problem) const override {
        if (problem.is_multi_objective()) {
            throw std::runtime_error("Multi-objective comparison not supported");
        }
        auto fit1 = fitness_value();
        auto fit2 = other.fitness_value();
        if (!fit1.has_value() && !fit2.has_value()) return std::nullopt;
        if (!fit1.has_value()) return false;
        if (!fit2.has_value()) return true;
        if (fit1.value() > fit2.value()) return true;
        if (fit1.value() == fit2.value()) return std::nullopt;
        return false;
    }

    void evaluate(const Problem& problem) override {
        QualityOfSolution qos = calculate_quality_directly(problem);
        objective_value_ = qos.objective_value();
        fitness_value_ = qos.fitness_value();
        is_feasible_ = qos.is_feasible();
    }

    void init_from(const std::string& representation, const Problem& problem) override {
        (void)problem;
        representation_ = native_representation(representation);
    }

    //@{
    /// @name Methods to be overridden by concrete implementations
    virtual void init_random(const Problem& problem) override = 0;
    [[nodiscard]] virtual QualityOfSolution calculate_quality_directly(const Problem& problem) override = 0;
    [[nodiscard]] virtual std::string to_string() const override = 0;
    [[nodiscard]] virtual R native_representation(const std::string& representation_str) const = 0;
    [[nodiscard]] virtual double representation_distance(const ISolution& other) const override = 0;
    //@}

protected:
    /// The concrete representation of this solution.
    R representation_;
    
    /// Random number generator.
    std::mt19937 rng_;

private:
    int random_seed_{0};
    std::optional<double> fitness_value_{std::nullopt};
    std::optional<double> objective_value_{std::nullopt};
    bool is_feasible_{false};
};

} // namespace uo

#endif // UO_SOLUTION_SOLUTION_HPP
